// stdafx.cpp : source file that includes just the standard includes
//	v7lua.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "../1cheaders/1cheaders.inl"

//Функция сообщает об ошибке, и информирует 1С что произошло исключение
void RuntimeError(const char *msg, ...)
{
	CString str;
	va_list ap;
	va_start(ap, msg);
	str.FormatV(msg, ap);
	va_end(ap);
	if (CBLModule::GetExecutedModule())
		CBLModule::RaiseExtRuntimeError(str.operator LPCTSTR(), mmRedErr);
	else
		GetBkEndUI()->DoMessageLine(str.operator LPCTSTR(), mmRedErr);
}

void Msg(const char *msg, ...)
{
	CString str;
	va_list ap;
	va_start(ap, msg);
	str.FormatV(msg, ap);
	va_end(ap);
	
	GetBkEndUI()->DoMessageLine(str.operator LPCTSTR(), mmBlueTriangle);
}

CString GetRuntimeErrorString()
{
	CString strGetRuntimeErrDescr;
	CBLModule* m =CBLModule::GetExecutedModule();
	m->GetRuntimeErrDescr(m->GetRuntimeErrCode(),strGetRuntimeErrDescr);
	CString strRuntimeErrorInfo = "Ошибка выполнения: ";
	strRuntimeErrorInfo += strGetRuntimeErrDescr +"\r\n";
	return strRuntimeErrorInfo;
}
