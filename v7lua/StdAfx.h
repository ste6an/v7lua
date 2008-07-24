// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__21F8237D_9E63_4451_A564_8D8E5484B76A__INCLUDED_)
#define AFX_STDAFX_H__21F8237D_9E63_4451_A564_8D8E5484B76A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define _STLP_USE_MFC
//#define _STLP_USE_NEWALLOC
//#define _DLL
//#define _STLP_USE_STATIC_LIB
//#define _STLP_USE_NO_IOSTREAMS
//#define _STLP_DONT_USE_AUTO_LINK
//#define _STLP_USE_MALLOC
#include "../1cheaders/1cheaders.h"

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

/*
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
/**/

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

extern "C" {
#include "lua/src/lauxlib.h"
#include "lua/src/lualib.h"
}
void RuntimeError(const char *msg, ...);
void Msg(const char *msg, ...);
CString GetRuntimeErrorString();


#endif // !defined(AFX_STDAFX_H__21F8237D_9E63_4451_A564_8D8E5484B76A__INCLUDED_)
