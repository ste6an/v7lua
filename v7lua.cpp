// v7lua.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "LuaRef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE V7luaDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstance);
		TRACE0("V7LUA.DLL Initializing!\n");
/*		
		if (!AfxInitExtensionModule(V7luaDLL, hInstance))
			return 0;

		new CDynLinkLibrary(V7luaDLL);/**/
		CBLContext::RegisterContextClass(RUNTIME_CLASS(CLuaRef),"LuaRef",CType(100));
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("V7LUA.DLL Terminating!\n");
		//AfxTermExtensionModule(V7luaDLL);
		CBLContext::UnRegisterContextClass(RUNTIME_CLASS(CLuaRef));
	}
	return 1;
}
