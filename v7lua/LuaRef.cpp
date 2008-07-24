#include "StdAfx.h"
#include "LuaRef.h"
#include "ValueWrapper.h"

#pragma warning (disable : 4786)

IMPLEMENT_DYNCREATE(CLuaRef,CBLContext);

void* l_alloc (void *ud, void *ptr, size_t osize, size_t nsize) {
	(void)ud;     /* not used */
	(void)osize;  /* not used */
	if (nsize == 0) {
		HeapFree(GetProcessHeap(),1,ptr);  /* ANSI requires that free(NULL) has no effect */
		return NULL;
	}
	else
		/* ANSI requires that realloc(NULL, size) == malloc(size) */
	if(ptr)
		return HeapReAlloc(GetProcessHeap(),1,ptr, nsize);
	else
		return HeapAlloc(GetProcessHeap(),1,nsize);
}

int CLuaRef::printFunction( lua_State* state )
{
	int n = lua_gettop(state);  /* number of arguments */
	int i;
	ostrstream out;
	lua_getglobal(state, "tostring");
	for (i=1; i<=n; i++) {
		const char *s;
		lua_pushvalue(state, -1);  /* function to be called */
		lua_pushvalue(state, i);   /* value to print */
		lua_call(state, 1, 1);
		s = lua_tostring(state, -1);  /* get result */
		if (s == NULL)
			return luaL_error(state, LUA_QL("tostring") " must return a string to "
			LUA_QL("print"));
		if (i>1){ out << "\t"; }
		out << s;
		lua_pop(state, 1);  /* pop result */
	}
	//out << "\r\n" << ends;
	out << ends;
	char* m=out.str();
	if(m) Msg(m);
	out.rdbuf()->freeze(0);
	return 0;
}

int CLuaRef::createobjectFunction( lua_State* state )
{
	const char* className=lua_tostring(state,-1);
	CBLContext* context;
	CValue* val=new CValue(0L);
	if(className)
		context=CBLContext::CreateInstance(className);
	else
		RuntimeError("Передано неверное имя класса");
	if(context)
		val->AssignContext(context);
	else
		RuntimeError("Неудачная попытка создания класса %s",className);
	lua_settop(state,0);
	pushCValue(state,val);
	return 1;
}

void toCString(lua_State* state, int index, CString& s)
{
	size_t len;
	const char* c=lua_tolstring(state,index,&len);
	LPCSTR buf = (LPCSTR)s.GetBufferSetLength(len+1);
	//LPCSTR buf = (LPCSTR)malloc(len+1);
	if(buf && c)
	{
		memcpy((void*)buf,c,len+1);
//		return buf;
	}//else return "";/**/
}

int CLuaRef::dofileFunction( lua_State* state )
{
	char* m=(char*)lua_tostring(state,-1);
	if(m)
	{
/*		if(!luaL_loadfile(state,m))
		{
			int res=lua_pcall(state,0,1,0);
			if(!res)
			{
				return TRUE;
			}else{
				m=(char*)lua_tostring(state,-1);
				RuntimeError(m);
				lua_settop(state,0);
				return FALSE;
			}/**/
		if(!luaL_dofile(state,m)){
		}else{
			RuntimeError(lua_tostring(state,-1));
		}
	}
	return FALSE;
}

int CLuaRef::dostringFunction( lua_State* state )
{
	char* m=(char*)lua_tostring(state,-1);
	if(m)
	{
		if(!luaL_loadstring(state,m))
		{
			if(!lua_pcall(state,0,1,0))
			{
				return TRUE;
			}else{
				m=(char*)lua_tostring(state,-1);
				RuntimeError(m);
				lua_settop(state,0);
				return FALSE;
			}
		}else{
			m=(char*)lua_tostring(state,-1);
			GetBkEndUI()->DoMessageLine(m,mmRedErr);
			lua_settop(state,0);
			return FALSE;
		}
	}
	return FALSE;
}

void CLuaRef::getCValue(lua_State* state, int index, CValue& val, const CBLContext* parent)
{
	int t = lua_type(state, index);
	//val=0L;
	//val.Reset();
	CValueWrapper* cvw;
	CString s;
	switch(t)
	{
	case LUA_TNIL:
		return;
	case LUA_TNUMBER:
		val.SetType(CType(1));
		val.m_Number=lua_tonumber(state,index);
		return;
	case LUA_TSTRING:
		val.SetType(CType(2));
		//s=val.GetString();
		val.m_String=lua_tostring(state,index);
		return;
	case LUA_TTABLE:
		val.SetType(CType(2));
		val.AssignContext(new CLuaRef(state,lua_ref(state,LUA_REGISTRYINDEX),(CLuaRef*)parent));
		val.GetContext()->DecrRef();
		return;
	case LUA_TUSERDATA:
		cvw=(CValueWrapper*)luaL_checkudata(state,index,CVW_MT);
		if(cvw)
		{
			val=*cvw->val;
			return;
		}else{
			val.SetType(CType(2));
			val.m_String="userdata";
			return;
			//TODO: сделать конструктор LuaRef на основании userdata
		}
	default:
		val.SetType(CType(2));
		val.m_String=lua_tostring(state,index);
		return;
	}
}

void CLuaRef::pushCValue(lua_State* state, const CValue* val )
{
	switch(val->type)
	{
	case 0: //Пустое
		lua_pushnil(state);
		return;
	case 1: //Число
		lua_pushnumber(state,(double)val->m_Number);
		return;
	case 2: //Строка
		lua_pushstring(state,val->m_String);
		return;
	case 100: //Таблица Lua
		if(!strcmp(val->GetTypeString(),"LuaRef")){
			lua_rawgeti(state,LUA_REGISTRYINDEX,((CLuaRef*)(val->GetContext()))->refIndex);
			return;
		}
	}
	if(val->type>=10) //Контекст
	{
		CValueWrapper::pushCValueWrapper(state,*val);
	}else{
		lua_pushstring(state,val->GetString());
	}
}

void CLuaRef::Init()
{
	nParams=0;
	lastCalledMeth=-1;
	lua_pushnil(L);
	while (lua_next(L, -2) != 0) {
		if(lua_type(L,-1)==LUA_TFUNCTION)
		{
			vMethods.push_back(lua_tostring(L,-2));
		}else{
			vProps.push_back(lua_tostring(L,-2));
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
}

CLuaRef::CLuaRef(void):CBLContext(1)
{
	refIndex=0;
	L=lua_open();
	//L=lua_newstate(l_alloc,NULL);
	luaL_openlibs(L);
	lua_register(L,"print",CLuaRef::printFunction);
	lua_register(L,"dofile",CLuaRef::dofileFunction);
	lua_register(L,"dostring",CLuaRef::dostringFunction);
	lua_register(L,"create1sobject",CLuaRef::createobjectFunction);
	
	CValueWrapper::setupMetaTables(L);
	lua_getglobal(L,"_G");
	Init();
}

CLuaRef::CLuaRef( lua_State* state, int rIndex, CLuaRef* pParent ):CBLContext(1)
{
	L=state;
	parent=pParent;
	if(parent) parent->IncrRef();
	refIndex=rIndex;
	lua_rawgeti(L,LUA_REGISTRYINDEX,refIndex);
	Init();
}
CLuaRef::~CLuaRef(void)
{
	if(refIndex)
	{
		luaL_unref(L,LUA_REGISTRYINDEX,refIndex);
		if(parent) parent->DecrRef();
	}else{
		lua_gc(L,LUA_GCCOLLECT,0);
		lua_close(L);
	}
}

char const* CLuaRef::GetTypeString(void)const {	return "LuaRef"; }

char const* CLuaRef::GetPropName(int nProp, int nLang)const
{
	return vProps[nProp].c_str();
}

int CLuaRef::GetNProps( void ) const
{
	return vProps.size();
}

int CLuaRef::FindProp( char const * name) const
{
	int i;
	for(i=0;i<vProps.size();i++)
		if(!vProps[i].compare(name))
		{
			return i;
		}
	return -1;
}

int CLuaRef::GetPropVal( int nProp,CValue & Val) const
{
	Val.Reset();
	if(refIndex)
	{
		lua_rawgeti(L,LUA_REGISTRYINDEX,refIndex);
	}else{
		lua_getglobal(L,"_G");
	}
	const char* s=vProps[nProp].c_str();
	lua_pushstring(L,s);
	lua_gettable(L,-2);
	getCValue(L,-1,Val,this);
	lua_pop(L,1);
	return TRUE;
}

int CLuaRef::SetPropVal( int nProp,CValue const & val)
{
	if(refIndex)
	{
		lua_rawgeti(L,LUA_REGISTRYINDEX,refIndex);
	}else{
		lua_getglobal(L,"_G");
	}
	const char* s=vProps[nProp].c_str();
	lua_pushstring(L,s);
	pushCValue(L,&val);
	lua_settable(L,-3);
	lua_pop(L,1);
	return TRUE;
}

int CLuaRef::GetNMethods( void ) const
{
	return vMethods.size();
}

char const*	CLuaRef::GetMethodName(int nMeth, int nLang)const
{
	return vMethods[nMeth].c_str();
}

int CLuaRef::FindMethod( char const * name) const
{
	int i;
	for(i=0;i<vMethods.size();i++)
		if(!vMethods[i].compare(name))
		{
			return i;
		}
	return -1;
}

int CLuaRef::GetNParams( int nMeth) const
{
	return nParams;
}

int CLuaRef::CallAsFunc( int nMeth,CValue& retVal ,CValue** ppParams)
{
	retVal.Reset();
	lastCalledMeth=nMeth;
	const char* c;
	if(refIndex)
	{
		lua_rawgeti(L,LUA_REGISTRYINDEX,refIndex);
		c=vMethods[nMeth].c_str();
		lua_pushstring(L,c);
		lua_rawget(L,-2);
	}else{
		c=vMethods[nMeth].c_str();
		lua_getglobal(L,c);
	}
	for(int i=0;i<nParams;i++)
	{
		if(ppParams && ppParams[i])
		{
			pushCValue(L,ppParams[i]);
		}else{
			lua_pushnil(L);
		}
	}
	int res;
	res=lua_pcall(L,nParams,1,0);
	nParams=0;
	if(!res)
	{
		getCValue(L,-1,retVal,this);
		lua_settop(L,0);
		return TRUE;
	}else{
		RuntimeError(lua_tostring(L,-1));
		lua_settop(L,0);
		return FALSE;
	}
}

int CLuaRef::CallAsProc( int nMeth,CValue** ppParams)
{
	CValue r("_");
	int ret=CallAsFunc(nMeth,r,ppParams);
	return ret;
}

int CLuaRef::IsOleContext( void ) const
{
	int n;
	__asm {
		mov n, ebx // В этом регистре 1С хранит количество параметров при вызове метода
	}
	if((n>20) || (n<0)) n=0;
	//Msg("%d",n);
	((CLuaRef*)this)->nParams=n;
	return FALSE;
}

