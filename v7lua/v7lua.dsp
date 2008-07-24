# Microsoft Developer Studio Project File - Name="v7lua" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=v7lua - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "v7lua.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "v7lua.mak" CFG="v7lua - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "v7lua - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "v7lua - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "v7lua - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 SHLWAPI.LIB /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "v7lua - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MD /GX /Z7 /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SHLWAPI.LIB /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "v7lua - Win32 Release"
# Name "v7lua - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\LuaRef.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\v7lua.cpp
# End Source File
# Begin Source File

SOURCE=.\v7lua.def
# End Source File
# Begin Source File

SOURCE=.\v7lua.rc
# End Source File
# Begin Source File

SOURCE=.\ValueWrapper.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\luacom.h
# End Source File
# Begin Source File

SOURCE=.\LuaRef.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ValueWrapper.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\v7lua.rc2
# End Source File
# End Group
# Begin Group "Lua"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Lua\src\lapi.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lapi.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lauxlib.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\lauxlib.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lauxlib.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lbaselib.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lcode.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lcode.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\ldblib.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\ldebug.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\ldebug.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\ldo.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\ldo.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\ldump.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lfunc.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lfunc.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lgc.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lgc.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\linit.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\liolib.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\llex.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\llex.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\llimits.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lmathlib.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lmem.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lmem.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\loadlib.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lobject.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lobject.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lopcodes.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lopcodes.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\loslib.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lparser.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lparser.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lpeg.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lstate.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lstate.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lstring.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lstring.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lstrlib.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\ltable.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\ltable.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\ltablib.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\ltm.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\ltm.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lua.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Lua\lua.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lua.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\luac.c

!IF  "$(CFG)" == "v7lua - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "v7lua - Win32 Debug"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lua\luaconf.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\luaconf.h
# End Source File
# Begin Source File

SOURCE=.\Lua\lualib.h

!IF  "$(CFG)" == "v7lua - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "v7lua - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lua\src\lualib.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lundump.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lundump.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lvm.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lvm.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lzio.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Lua\src\lzio.h
# End Source File
# Begin Source File

SOURCE=.\Lua\src\print.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "luacom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\luacom\LuaAux.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\LuaAux.h
# End Source File
# Begin Source File

SOURCE=.\luacom\luabeans.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\luabeans.h
# End Source File
# Begin Source File

SOURCE=.\luacom\luacom.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\luacom.h
# End Source File
# Begin Source File

SOURCE=.\luacom\luacom_internal.h
# End Source File
# Begin Source File

SOURCE=.\luacom\LuaCompat.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\LuaCompat.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tCOMUtil.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tCOMUtil.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOM.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOM.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOMClassFactory.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOMClassFactory.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOMConnPoints.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOMConnPoints.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOMEnumerator.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOMEnumerator.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOMException.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOMException.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOMTypeHandler.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaCOMTypeHandler.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaControl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaControl.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaDispatch.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaDispatch.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaObject.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaObject.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaObjList.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaObjList.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaTLB.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaTLB.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaVector.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tLuaVector.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tStringBuffer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tStringBuffer.h
# End Source File
# Begin Source File

SOURCE=.\luacom\tUtil.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\luacom\tUtil.h
# End Source File
# End Group
# End Target
# End Project
