#pragma once
//#include <hash_map>

#define CVW_MT "v7lua_CVW_MT"

class CValueWrapper
{
public:
	static CValueWrapper* toCValueWrapper(lua_State* state, int index);
	static int pushCValueWrapper(lua_State* state, const CValue v);
	static void setupMetaTables(lua_State* state);
	~CValueWrapper(void);
	CValue* val;
private:
	CValueWrapper();
	//stdext::hash_map<std::string,int> mMethods;
	//stdext::hash_map<std::string,int> mProps;

	static int indexContextFunction(lua_State* state);
	static int newindexContextFunction(lua_State* state);
	static int callAsFunction( lua_State* state );
	static int gcFunction( lua_State* state );
};

struct contextCallInfo
{
	contextCallInfo(int mn, int hrv, int np, CValue* v):methNum(mn),hasRetVal(hrv),numParams(np),val(v){}
	int methNum;
	int hasRetVal;
	int numParams;
	CValue* val;
};