#include "StdAfx.h"
#include "ValueWrapper.h"
#include "LuaRef.h"
#include <AtlConv.h>
#include "luacom.h"

//#pragma comment(linker, "/delayload:luacom.dll")

CValueWrapper::CValueWrapper()
{
}
CValueWrapper::~CValueWrapper(void)
{
}

void CValueWrapper::setupMetaTables( lua_State* state )
{
	luaL_newmetatable(state,CVW_MT);
	lua_pushstring(state, "__index");
	lua_pushcfunction(state, indexContextFunction);
	lua_rawset(state,-3);
	lua_pushstring(state, "__newindex");
	lua_pushcfunction(state, newindexContextFunction);
	lua_rawset(state,-3);
	lua_pushstring(state, "__gc");
	lua_pushcfunction(state, gcFunction);
	lua_rawset(state,-3);
	lua_pop(state,1);
}

int CValueWrapper::pushCValueWrapper( lua_State* state, const CValue v)
{
	CBLContext* cont=v.GetContext();
	if(cont && cont->IsOleContext()){
		CRuntimeClass* rc=cont->GetRuntimeClass();
		if(rc==RUNTIME_CLASS(CStdOleBLContext)){
			IUnknown* pUnk=((CStdOleBLContext*)cont)->m_IUnknown;
			IDispatch* pDisp=NULL;
			if(!pUnk->QueryInterface(IID_IDispatch,(void**)&pDisp))
			{
				if(pDisp)
				{
					//HINSTANCE h = GetModuleHandle("luacom.dll");
					//if(h)
					{
						//BYTE* adrDisp2Luacom = (BYTE*)GetProcAddress(h,"luacom_IDispatch2LuaCOM");
						luacom_IDispatch2LuaCOM(state,(void*)pDisp);
						return 1;
					}
/*					lua_getglobal(state,"package");
					lua_pushstring(state,"loaded");
					lua_rawget(state,-2);
					lua_pushstring(state,"luacom");
					lua_rawget(state,-2);
					if(!lua_isnil(state,-1)){
						lua_pop(state,1);

						luacom_IDispatch2LuaCOM(state,(void*)pDisp);
						return 1;
					}else{
						lua_pop(state,1);
					}/**/
				}
			}
		}
	}
	CValueWrapper* vw=(CValueWrapper*)lua_newuserdata(state,sizeof(CValueWrapper));
	vw->val=new CValue(v);
	if(cont)
	{
		vw->val->AssignContext(cont);
		cont->IncrRef();
	}
	luaL_getmetatable(state,CVW_MT);
	lua_setmetatable(state, -2);
	return 1;
}

CValueWrapper* CValueWrapper::toCValueWrapper( lua_State* state, int index )
{
	CValueWrapper* w=(CValueWrapper*)lua_touserdata(state,index);
	if(!w) luaL_typerror(state, index, CVW_MT);
	return w;
}

int CValueWrapper::indexContextFunction( lua_State* state)
{
	CValueWrapper* cvw = toCValueWrapper(state,1);
	CValue* val = cvw->val;
	CBLContext* cont=val->GetContext();
	if(val->IsExactValue())	val->LinkContext(1);
	const char* cKey=lua_tostring(state,2);
	lua_pop(state,1);
	if(cont && cKey)
	{
		CRuntimeClass* rc=cont->GetRuntimeClass();
		if (false || cont->IsOleContext() && (rc==RUNTIME_CLASS(CStdOleBLContext)))
		{
			
			int memberNum = cont->FindProp(cKey);
			((CStdOleBLContext*)cont)->TryFindFriendInterface();
			if(memberNum!=-1)
			{
				USES_CONVERSION;
				IDispatch* pDisp=NULL;
				if(((COleGenericBLContext*)cont)->m_IUnknown->QueryInterface(IID_IDispatch,(void**)&pDisp));
				if(pDisp)
				{
					DISPID dispid;
					OLECHAR* member=T2OLE(cKey);
					if(pDisp->GetIDsOfNames(IID_NULL,&member,1,LOCALE_SYSTEM_DEFAULT,&dispid)==S_OK)
					{
						unsigned int argErr;
						VARIANT res;
						DISPPARAMS			dispParamsNoArg={NULL,NULL,0,0};
						HRESULT hr=pDisp->Invoke(dispid,IID_NULL,LOCALE_SYSTEM_DEFAULT,DISPATCH_PROPERTYGET,&dispParamsNoArg,&res,NULL,&argErr);
						if(hr==S_OK){
							CValue propVal;
							cont->GetPropVal(memberNum,propVal);
							lua_pop(state,1);
							CLuaRef::pushCValue(state, &propVal);
							return 1;
						}else{
							int numParams = cont->GetNParams(memberNum);
							int hasRetVal = cont->HasRetVal(memberNum);
							//contextCallInfo* cci=new contextCallInfo(memberNum,1,numParams,val);
							contextCallInfo* cci=new contextCallInfo(memberNum,1,1,val);
							lua_pop(state,1);
							lua_pushlightuserdata(state, cci);
							lua_pushcclosure(state, callAsFunction, 1);
							return 1;
						}
					}
					//delete member;
				}
			}
		} 
		else
		{
			int propNum = cont->FindProp(cKey);
			if(propNum!=-1)
			{
				CValue propVal;
				cont->GetPropVal(propNum,propVal);
				lua_pop(state,1);
				CLuaRef::pushCValue(state, &propVal);
				return 1;
			}
			int methNum = cont->FindMethod(cKey);
			if(methNum!=-1)
			{
				int numParams = cont->GetNParams(methNum);
				int hasRetVal = cont->HasRetVal(methNum);
				contextCallInfo* cci=new contextCallInfo(methNum,hasRetVal,numParams,val);
				lua_pop(state,1);
				lua_pushlightuserdata(state, cci);
				lua_pushcclosure(state, callAsFunction, 1);
				return 1;
			}
		}
	}else{
		lua_pop(state,1);
		lua_pushnil(state);
		return 1;
	}
	return 1;
}

int CValueWrapper::newindexContextFunction( lua_State* state )
{
	CValueWrapper* cvw = toCValueWrapper(state,1);
	CValue* val = cvw->val;
	CBLContext* cont=val->GetContext();
	if(val->IsExactValue())	val->LinkContext(1);
	const char* cKey=lua_tostring(state,2);
	int actualNumParams = lua_gettop(state);
	CValue newVal("_");
	CLuaRef::getCValue(state,3,newVal,NULL);
	if(cont && cKey)
	{
		int propNum = cont->FindProp(cKey);
		if(propNum!=-1)
		{
			if(cont->SetPropVal(propNum,newVal))
			{
				lua_settop(state,0);
				return 0;
			}else{
				RuntimeError("Ошибка при установке свойства %s",cKey);
			}
		}
	}else{
		lua_settop(state,0);
		return 0;
	}
	return 0;
}

int CValueWrapper::callAsFunction( lua_State* state )
{
	contextCallInfo* cci=(contextCallInfo*)lua_touserdata(state,lua_upvalueindex(1));
	int methNum = cci->methNum;
	int hasRetVal = cci->hasRetVal;
	int numParams = cci->numParams;
	CValue* val =cci->val;
	CBLContext* cont;
	if(val->IsExactValue())	val->LinkContext(1);
	cont=val->GetContext();
	int actualNumParams = lua_gettop(state);
	CValue p1="_", p2="_", p3="_", p4="_", p5="_", p6="_", p7="_", p8="_", p9="_", p10="_";
	CValue *pArray[10]={&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10};
	for(int i=1;i<=actualNumParams;i++)
	{
		CLuaRef::getCValue(state,i,*(pArray[i-1]),NULL);
	}
	int res;
	if(hasRetVal)
	{
		CValue ret("_");
		res=cont->CallAsFunc(methNum,ret,pArray);
		CLuaRef::pushCValue(state,&ret);
	}else{
		res = cont->CallAsProc(methNum,pArray);
	}
	if(res)
		return hasRetVal;
	else{
		RuntimeError(GetRuntimeErrorString());
	}
	return FALSE;
}

int CValueWrapper::gcFunction( lua_State* state )
{
	CValueWrapper* cvw = toCValueWrapper(state,1);
	CValue* val=cvw->val;
	if(val->m_Context){
		val->m_Context->DecrRef();
		val->UnlinkContext();
	}
	//Msg("collected %s",val->GetString());
	delete val;
	return 0;
}

