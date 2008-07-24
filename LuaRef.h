#pragma once
#include <string>
#include <vector>
#include <strstream> 
#pragma warning (disable : 4786)

class CLuaRef : public CBLContext
{
public:
	DECLARE_DYNCREATE(CLuaRef)
	CLuaRef(void);
	CLuaRef(lua_State* state, int rIndex, CLuaRef* pParent);
	~CLuaRef(void);
	virtual char const*  GetCode(void)const		{return NULL;}
	virtual int  GetDestroyUnRefd(void)const	{return TRUE;}
	virtual CObjID GetID(void)const				{return CObjID();}
	virtual long  GetTypeID(void)const			{return 100;}
	virtual CType GetValueType(void)const		{return CType(100);}
	virtual int  IsExactValue(void)const		{return TRUE;}
	virtual int  IsOleContext(void)const;
	virtual int  IsSerializable(void)			{return FALSE;}
	virtual int  SaveToString(CString &)		{return FALSE;}
	virtual void InitObject(CType const &t)		{}
	virtual void InitObject(LPCSTR lpName)
	{
	}

	virtual char const*		GetTypeString(void)const;

	virtual int				GetNProps(void)const;
	virtual int				FindProp(char const *)const;
	virtual char const*		GetPropName(int,int)const;
	virtual int				GetPropVal(int,CValue &)const;
	virtual int				SetPropVal(int,CValue const &);
	virtual int				IsPropReadable(int)const	{return TRUE;}
	virtual int				IsPropWritable(int)const	{return TRUE;}

	virtual int				GetNMethods(void)const;
	virtual int				FindMethod(char const *)const;
	virtual char const*		GetMethodName(int,int)const;
	virtual int				GetNParams(int)const;
	virtual int				GetParamDefValue(int,int,CValue* v)const {v->Reset();return TRUE;}
	virtual int				HasRetVal(int)const	{return TRUE;}

	virtual int				CallAsProc(int,CValue * *);
	virtual int				CallAsFunc(int,CValue &,CValue * *);

	static void getCValue(lua_State* state, int index, CValue& val, const CBLContext* parent);
	static void pushCValue(lua_State* state, const CValue* val);
protected:
	void Init();
	int refIndex;
private:
	lua_State* L;
	CLuaRef* parent;
	typedef std::vector<std::string> stdstrvector;
	stdstrvector vMethods;
	stdstrvector vProps;
	int nParams;
	int lastCalledMeth;
	static int printFunction(lua_State* state);
	static int dofileFunction(lua_State* state);
	static int dostringFunction( lua_State* state );
	static int createobjectFunction( lua_State* state );
};

