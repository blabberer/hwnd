//original source code is from userobj.cpp by skywing aka ken johnsons sdbgext windbg extension 
//some warnings fixed /analyze and /w4 enabled // removed the completely 
//unofficial ntnative header dependency and introduced a slighly modified 
//winternl.h for _TEB,_PEB,_CLIENT_ID structs (filecompare winternl.h in windows sdk
// versus modwinternl.h  recompiled with vs 2017 for 64 bit architecture
#define _CRT_SECURE_NO_WARNINGS
#include <Richedit.h>
#include <string>
#include "modwinternl.h"
#define KDEXT_64BIT
#include <wdbgexts.h>


using namespace std;


EXT_API_VERSION         ApiVersion = { 1, 0, EXT_API_VERSION_NUMBER64, 0 };
WINDBG_EXTENSION_APIS   ExtensionApis;
ULONG SavedMajorVersion;
ULONG SavedMinorVersion;

int DllInit(HANDLE hModule, DWORD  dwReason, DWORD  dwReserved)
{
	UNREFERENCED_PARAMETER(dwReserved);
	UNREFERENCED_PARAMETER(hModule);
	switch (dwReason) {
	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;

	case DLL_PROCESS_ATTACH:
		break;
	}

	return TRUE;
}


VOID WinDbgExtensionDllInit(PWINDBG_EXTENSION_APIS lpExtensionApis, USHORT MajorVersion, USHORT MinorVersion)
{
	ExtensionApis = *lpExtensionApis;
	SavedMajorVersion = MajorVersion;
	SavedMinorVersion = MinorVersion;
	return;
}

LPEXT_API_VERSION ExtensionApiVersion(VOID)
{
	return &ApiVersion;
}

VOID
CheckVersion(VOID)
{
	return;
}

VOID
WINAPI
GetWindowStyleStr(
	IN ULONG64 Style,
	IN CONST WCHAR* ClassName,
	OUT std::string& StyleStr,
	IN BOOLEAN Dialog
)
{
	StyleStr.clear();

	if (Style & WS_CHILD) {
		if (Style & WS_TABSTOP)
			StyleStr += "WS_TABSTOP ";
		if (Style & WS_GROUP)
			StyleStr += "WS_GROUP ";
	}
	else {
		if (Style & WS_MINIMIZEBOX)
			StyleStr += "WS_MINIMIZEBOX ";
		if (Style & WS_MAXIMIZEBOX)
			StyleStr += "WS_MAXIMIZEBOX ";
	}

	if (Style & WS_THICKFRAME)
		StyleStr += "WS_THICKFRAME ";
	if (Style & WS_SYSMENU)
		StyleStr += "WS_SYSMENU ";
	if (Style & WS_HSCROLL)
		StyleStr += "WS_HSCROLL ";
	if (Style & WS_VSCROLL)
		StyleStr += "WS_VSCROLL ";
	if (Style & WS_DLGFRAME)
		StyleStr += "WS_DLGFRAME ";
	if (Style & WS_BORDER)
		StyleStr += "WS_BORDER ";
	if (Style & WS_MAXIMIZE)
		StyleStr += "WS_MAXIMIZE ";
	if (Style & WS_MINIMIZE)
		StyleStr += "WS_MINIMIZE ";
	if (Style & WS_CLIPCHILDREN)
		StyleStr += "WS_CLIPCHILDREN ";
	if (Style & WS_CLIPSIBLINGS)
		StyleStr += "WS_CLIPSIBLINGS ";
	if (Style & WS_DISABLED)
		StyleStr += "WS_DISABLED ";
	if (Style & WS_VISIBLE)
		StyleStr += "WS_VISIBLE ";
	if (Style & WS_MINIMIZE)
		StyleStr += "WS_MINIMIZE ";
	if (Style & WS_CHILD)
		StyleStr += "WS_CHILD ";
	if (Style & WS_POPUP)
		StyleStr += "WS_POPUP ";

	if (!(Style & 0xFFFF))
		StyleStr = "WS_OVERLAPPED ";

	if (!_wcsicmp(ClassName, L"EDIT") || !_wcsicmp(ClassName, L"RICHEDIT") || !_wcsicmp(ClassName, L"RichEditCEA") || !_wcsicmp(ClassName, L"RichEditCEW")
		|| !_wcsicmp(ClassName, L"RichEdit20A") || !_wcsicmp(ClassName, L"RichEdit20W") || !_wcsicmp(ClassName, L"RICHEDIT50W")) {
		BOOLEAN IsEdit = !_wcsicmp(ClassName, L"EDIT");

		if (!(Style & ES_RIGHT))
			StyleStr += "ES_LEFT ";
		if (Style & ES_CENTER)
			StyleStr += "ES_CENTER ";
		if (Style & ES_RIGHT)
			StyleStr += "ES_RIGHT ";
		if (Style & ES_MULTILINE)
			StyleStr += "ES_MULTILINE ";
		if (Style & ES_UPPERCASE)
			StyleStr += "ES_UPPERCASE ";
		if (Style & ES_LOWERCASE)
			StyleStr += "ES_LOWERCASE ";
		if (Style & ES_PASSWORD)
			StyleStr += "ES_PASSWORD ";
		if (Style & ES_AUTOVSCROLL)
			StyleStr += "ES_AUTOVSCROLL ";
		if (Style & ES_AUTOHSCROLL)
			StyleStr += "ES_AUTOHSCROLL ";
		if (Style & ES_NOHIDESEL)
			StyleStr += "ES_NOHIDESEL ";
		if (Style & ES_OEMCONVERT)
			StyleStr += "ES_OEMCONVERT ";
		if (Style & ES_READONLY)
			StyleStr += "ES_READONLY ";
		if (Style & ES_WANTRETURN)
			StyleStr += "ES_WANTRETURN ";
		if (Style & ES_NUMBER)
			StyleStr += "ES_NUMBER ";

		if (!IsEdit) {
			if (Style & ES_SAVESEL)
				StyleStr += "ES_SAVESEL ";
			if (Style & ES_SUNKEN)
				StyleStr += "ES_SUNKEN ";
			if (Style & ES_DISABLENOSCROLL)
				StyleStr += "ES_DISABLENOSCROLL ";
		}
	}
	else if (!_wcsicmp(ClassName, L"COMBOBOX")) {
		if (Style & CBS_SIMPLE)
			StyleStr += "CBS_SIMPLE ";
		if (Style & CBS_DROPDOWN)
			StyleStr += "CBS_DROPDOWN ";
		if (Style & CBS_DROPDOWNLIST)
			StyleStr += "CBS_DROPDOWNLIST ";
		if (Style & CBS_OWNERDRAWFIXED)
			StyleStr += "CBS_OWNERDRAWFIXED ";
		if (Style & CBS_OWNERDRAWVARIABLE)
			StyleStr += "CBS_OWNERDRAWVARIABLE ";
		if (Style & CBS_AUTOHSCROLL)
			StyleStr += "CBS_AUTOHSCROLL ";
		if (Style & CBS_OEMCONVERT)
			StyleStr += "CBS_OEMCONVERT ";
		if (Style & CBS_SORT)
			StyleStr += "CBS_SORT ";
		if (Style & CBS_HASSTRINGS)
			StyleStr += "CBS_HASSTRINGS ";
		if (Style & CBS_NOINTEGRALHEIGHT)
			StyleStr += "CBS_NOINTEGRALHEIGHT ";
		if (Style & CBS_DISABLENOSCROLL)
			StyleStr += "CBS_DISABLENOSCROLL ";
		if (Style & CBS_UPPERCASE)
			StyleStr += "CBS_UPPERCASE ";
		if (Style & CBS_LOWERCASE)
			StyleStr += "CBS_LOWERCASE ";
	}
	else if (!_wcsicmp(ClassName, L"BUTTON")) {
		if (Style & BS_DEFPUSHBUTTON)
			StyleStr += "BS_DEFPUSHBUTTON ";
		if (Style & BS_CHECKBOX)
			StyleStr += "BS_CHECKBOX ";
		if (Style & BS_RADIOBUTTON)
			StyleStr += "BS_RADIOBUTTON ";
		if (Style & BS_USERBUTTON)
			StyleStr += "BS_USERBUTTON ";
		if (Style & BS_LEFTTEXT)
			StyleStr += "BS_LEFTTEXT ";
		if (Style & BS_ICON)
			StyleStr += "BS_ICON ";
		if (Style & BS_BITMAP)
			StyleStr += "BS_BITMAP ";
		if (Style & BS_LEFT)
			StyleStr += "BS_LEFT ";
		if (Style & BS_RIGHT)
			StyleStr += "BS_RIGHT ";
		if (Style & BS_TOP)
			StyleStr += "BS_TOP ";
		if (Style & BS_BOTTOM)
			StyleStr += "BS_BOTTOM ";
		if (Style & BS_PUSHLIKE)
			StyleStr += "BS_PUSHLIKE ";
		if (Style & BS_MULTILINE)
			StyleStr += "BS_MULTILINE ";
		if (Style & BS_NOTIFY)
			StyleStr += "BS_NOTIFY ";
		if (Style & BS_FLAT)
			StyleStr += "BS_FLAG ";
	}
	else if (!_wcsicmp(ClassName, L"SCROLLBAR")) {
		if (Style & SBS_VERT)
			StyleStr += "SBS_VERT ";
		else if (Style & SBS_SIZEBOX)
			StyleStr += "SBS_SIZEBOX ";
		else
			StyleStr += "SBS_HORZ ";

		if (Style & SBS_VERT) {
			if (Style & SBS_TOPALIGN)
				StyleStr += "SBS_TOPALIGN ";
			if (Style & SBS_BOTTOMALIGN)
				StyleStr += "SBS_BOTTOMALIGN ";
		}
		else if (Style & SBS_SIZEBOX) {
			if (Style & SBS_SIZEBOXTOPLEFTALIGN)
				StyleStr += "SBS_SIZEBOXTOPLEFTALIGN ";
			if (Style & SBS_SIZEBOXBOTTOMRIGHTALIGN)
				StyleStr += "SBS_SIZEBOXBOTTOMRIGHTALIGN ";
		}
		else {
			if (Style & SBS_LEFTALIGN)
				StyleStr += "SBS_LEFTALIGN ";
			if (Style & SBS_RIGHTALIGN)
				StyleStr += "SBS_RIGHTALIGN ";
		}

		if (Style & SBS_SIZEGRIP)
			StyleStr += "SBS_SIZEGRIP ";
	}
	else if (!_wcsicmp(ClassName, L"LISTBOX")) {
		if (Style & LBS_NOTIFY)
			StyleStr += "LBS_NOTIFY ";
		if (Style & LBS_SORT)
			StyleStr += "LBS_SORT ";
		if (Style & LBS_NOREDRAW)
			StyleStr += "LBS_NOREDRAW ";
		if (Style & LBS_MULTIPLESEL)
			StyleStr += "LBS_MULTIPLESEL ";
		if (Style & LBS_OWNERDRAWFIXED)
			StyleStr += "LBS_OWNERDRAWFIXED ";
		if (Style & LBS_OWNERDRAWVARIABLE)
			StyleStr += "LBS_OWNERDRAWVARIABLE ";
		if (Style & LBS_HASSTRINGS)
			StyleStr += "LBS_HASSTRINGS ";
		if (Style & LBS_USETABSTOPS)
			StyleStr += "LBS_USETABSTOPS ";
		if (Style & LBS_NOINTEGRALHEIGHT)
			StyleStr += "LBS_NOINTEGRALHEIGHT ";
		if (Style & LBS_MULTICOLUMN)
			StyleStr += "LBS_MULTIPLECOLUMN ";
		if (Style & LBS_WANTKEYBOARDINPUT)
			StyleStr += "LBS_WANTKEYBOARDINPUT ";
		if (Style & LBS_EXTENDEDSEL)
			StyleStr += "LBS_EXTENDEDSEL ";
		if (Style & LBS_DISABLENOSCROLL)
			StyleStr += "LBS_DISABLENOSCROLL ";
		if (Style & LBS_NODATA)
			StyleStr += "LBS_NODATA ";
		if (Style & LBS_NOSEL)
			StyleStr += "LBS_NOSEL ";
		if (Style & LBS_COMBOBOX)
			StyleStr += "LBS_COMBOBOX ";
	}
	else if (!_wcsicmp(ClassName, L"SkywingNotifyWindowW") || !_wcsicmp(ClassName, L"SkywingNotifyWindowA")) {
		if (Style & 0x0001)
			StyleStr += "NWS_NOTIFY ";
		if (Style & 0x0002)
			StyleStr += "NWS_DEFERDISPLAY ";
	}
	else if (Dialog) {
		if (Style & DS_ABSALIGN)
			StyleStr += "DS_ABSALIGN ";
		if (Style & DS_SYSMODAL)
			StyleStr += "DS_SYSMODAL ";
		if (Style & DS_LOCALEDIT)
			StyleStr += "DS_LOCALEDIT ";
		if (Style & DS_SETFONT)
			StyleStr += "DS_SETFONT ";
		if (Style & DS_MODALFRAME)
			StyleStr += "DS_MODALFRAME ";
		if (Style & DS_NOIDLEMSG)
			StyleStr += "DS_NOIDLEMSG ";
		if (Style & DS_SETFOREGROUND)
			StyleStr += "DS_SETFOREGROUND ";
		if (Style & DS_3DLOOK)
			StyleStr += "DS_3DLOOK ";
		if (Style & DS_FIXEDSYS)
			StyleStr += "DS_FIXEDSYS ";
		if (Style & DS_NOFAILCREATE)
			StyleStr += "DS_NOFAILCREATE ";
		if (Style & DS_CONTROL)
			StyleStr += "DS_CONTROL ";
		if (Style & DS_CENTER)
			StyleStr += "DS_CENTER ";
		if (Style & DS_CENTERMOUSE)
			StyleStr += "DS_CENTERMOUSE ";
		if (Style & DS_CONTEXTHELP)
			StyleStr += "DS_CONTEXTHELP ";
		if (Style & 0x8000L)
			StyleStr += "DS_USEPIXELS ";
	}

	if (StyleStr.size())
		StyleStr.erase(StyleStr.rbegin().base());
}

VOID
WINAPI
GetWindowExStyleStr(
	IN ULONG64 ExStyle,
	IN CONST WCHAR* ClassName,
	OUT std::string& ExStyleStr
)
{
	ExStyleStr.clear();

	if (ExStyle & WS_EX_DLGMODALFRAME)
		ExStyleStr += "WS_EX_DLGMODALFRAME ";
	if (ExStyle & WS_EX_NOPARENTNOTIFY)
		ExStyleStr += "WS_EX_NOPARENTNOTIFY ";
	if (ExStyle & WS_EX_TOPMOST)
		ExStyleStr += "WS_EX_TOPMOST ";
	if (ExStyle & WS_EX_ACCEPTFILES)
		ExStyleStr += "WS_EX_ACCEPTFILES ";
	if (ExStyle & WS_EX_TRANSPARENT)
		ExStyleStr += "WS_EX_TRANSPARENT ";
	if (ExStyle & WS_EX_MDICHILD)
		ExStyleStr += "WS_EX_MDICHILD ";
	if (ExStyle & WS_EX_TOOLWINDOW)
		ExStyleStr += "WS_EX_TOOLWINDOW ";
	if (ExStyle & WS_EX_WINDOWEDGE)
		ExStyleStr += "WS_EX_WINDOWEDGE ";
	if (ExStyle & WS_EX_CLIENTEDGE)
		ExStyleStr += "WS_EX_CLIENTEDGE ";
	if (ExStyle & WS_EX_CONTEXTHELP)
		ExStyleStr += "WS_EX_CONTEXTHELP ";
	if (ExStyle & WS_EX_RIGHT)
		ExStyleStr += "WS_EX_RIGHT ";
	else
		ExStyleStr += "WS_EX_LEFT ";
	if (ExStyle & WS_EX_RTLREADING)
		ExStyleStr += "WS_EX_RTLREADING ";
	else
		ExStyleStr += "WS_EX_LTRREADING ";
	if (ExStyle & WS_EX_LEFTSCROLLBAR)
		ExStyleStr += "WS_EX_LEFTSCROLLBAR ";
	else
		ExStyleStr += "WS_EX_RIGHTSCROLLBAR ";
	if (ExStyle & WS_EX_CONTROLPARENT)
		ExStyleStr += "WS_EX_CONTROLPARENT ";
	if (ExStyle & WS_EX_STATICEDGE)
		ExStyleStr += "WS_EX_STATICEDGE ";
	if (ExStyle & WS_EX_APPWINDOW)
		ExStyleStr += "WS_EX_APPWINDOW ";

	if (ExStyleStr.size())
		ExStyleStr.erase(ExStyleStr.rbegin().base());

	UNREFERENCED_PARAMETER(ClassName);
}

typedef int (WINAPI * InternalGetWindowTextProc)(IN HWND hWnd, IN LPWSTR lpString, IN int nMaxCount);

BOOL
CALLBACK
EnumChildWindowsForWindow(
	IN HWND hwnd,
	IN LPARAM lparam
)
{
	WCHAR WindowName[256];
	WCHAR ClassName[256];
	InternalGetWindowTextProc InternalGetWindowText = (InternalGetWindowTextProc)lparam;

	if (InternalGetWindowText) {
		if (!InternalGetWindowText(hwnd, WindowName, 256) && GetLastError())
			wcscpy(WindowName, L"<unavail>");
	}
	else
		wcscpy(WindowName, L"<unavail>");

	if (!GetClassNameW(hwnd, ClassName, 256))
		wcscpy(ClassName, L"<unavail>");

	dprintf(
		"ChildWindow %p\n"
		"Name        %S\n"
		"Class       %S\n"
		, (ULONG64)hwnd, WindowName, ClassName);
	return TRUE;
}

BOOL
CALLBACK
EnumWindowsForThread(
	IN HWND hwnd,
	IN LPARAM lparam
)
{
	WCHAR WindowName[256];
	WCHAR ClassName[256];
	InternalGetWindowTextProc InternalGetWindowText = (InternalGetWindowTextProc)lparam;

	if (InternalGetWindowText) {
		if (!InternalGetWindowText(hwnd, WindowName, 256) && GetLastError())
			wcscpy(WindowName, L"<unavail>");
	}
	else
		wcscpy(WindowName, L"<unavail>");

	if (!GetClassNameW(hwnd, ClassName, 256))
		wcscpy(ClassName, L"<unavail>");

	dprintf(
		"Window      %p\n"
		"Name        %S\n"
		"Class       %S\n"
		, (ULONG64)hwnd, WindowName, ClassName);
	EnumChildWindows(hwnd, EnumChildWindowsForWindow, lparam);
	return TRUE;
}

BOOLEAN
WINAPI
GetClientTeb(
	IN HANDLE,
	OUT PTEB Teb
)
{
	ULONGLONG TebBase;
	ULONG Size;

	GetTebAddress(&TebBase);

	if (!TebBase)
		return FALSE;

	if (!ReadMemory((ULONG64)TebBase, (PVOID)Teb, sizeof(TEB), &Size) || Size != sizeof(TEB))
		return FALSE;

	return TRUE;
}

VOID
WINAPI
DisplayWindowsForThread(
	IN HANDLE Thread
)
{
	TEB Teb;

	if (!GetClientTeb(Thread, &Teb)) {
		dprintf("Can't access Teb\n");
		return;
	}
	HMODULE hmod = GetModuleHandleW(L"USER32.DLL");
	if (hmod != 0) {
		FARPROC lpfn = GetProcAddress(hmod, "InternalGetWindowText");
		if (lpfn != 0) {
			EnumThreadWindows(HandleToUlong(Teb.ClientId.UniqueThread), EnumWindowsForThread, (LPARAM)lpfn);
		}
	}
}


DECLARE_API(help)
{
	UNREFERENCED_PARAMETER(args);
	UNREFERENCED_PARAMETER(hCurrentThread);
	UNREFERENCED_PARAMETER(hCurrentProcess);
	UNREFERENCED_PARAMETER(dwProcessor);
	UNREFERENCED_PARAMETER(dwCurrentPc);


	dprintf(
		"Help for extension dll hwnd.dll\n"
		"   help               - Shows this help\n"
		"   hwnd               - sdbgexthwnd\n"
	);

}

DECLARE_API(hwnd)
{
	UNREFERENCED_PARAMETER(hCurrentProcess);
	UNREFERENCED_PARAMETER(dwProcessor);
	UNREFERENCED_PARAMETER(dwCurrentPc);
	typedef int (WINAPI * InternalGetWindowTextProc)(IN HWND hWnd, IN LPWSTR lpString, IN int nMaxCount);
	InternalGetWindowTextProc InternalGetWindowText;
	WCHAR windowname[256];
	WCHAR classname[256];
	HMODULE user32;
	ULONG64 hwnd;
	ULONG64 flags;
	ULONG64 windowproc;
	ULONG64 style;
	ULONG64 exstyle;
	ULONG64 instance;
	ULONG64 parent;
	ULONG64 id;
	ULONG64 userdata;
	LONG_PTR dlgproc = NULL;
	LONG_PTR msgresult = NULL;
	LONG_PTR dlguser = NULL;
	ULONG64 isunicode;
	ULONG64 processid;
	ULONG64 threadid;
	string stylestr;
	string exstylestr;

	if (!args[0]) {
		DisplayWindowsForThread(hCurrentThread);
		return;
	}

	if (!GetExpressionEx(args, &hwnd, &args)) {
		dprintf("Syntax error or couldn't resolve expression\n");
		return;
	}

	if (!GetExpressionEx(args, &flags, &args))
		flags = 0;

	user32 = LoadLibraryW(L"user32.dll");

	if (!user32) {
		dprintf("Couldn't load user32\n");
		return;
	}

	InternalGetWindowText = (InternalGetWindowTextProc)GetProcAddress(user32, "InternalGetWindowText");

	if (InternalGetWindowText) {
		if (!InternalGetWindowText((HWND)hwnd, windowname, 256)) {
			if (GetLastError()) {
				if (!IsWindow((HWND)hwnd)) {
					dprintf("Invalid window handle %p\n", hwnd);
					FreeLibrary(user32);
					return;
				}

				wcscpy(windowname, L"<unavail>");
			}
		}
	}
	else {
		if (!IsWindow((HWND)hwnd)) {
			dprintf("Invalid window handle %p\n", hwnd);
			FreeLibrary(user32);
			return;
		}

		wcscpy(windowname, L"<unavail>");
	}

	if (!GetClassNameW((HWND)hwnd, classname, 256))
		wcscpy(classname, L"<unavail>");

	if (!_wcsicmp(classname, L"Dialog"))
		flags |= 0x01;

	threadid = (ULONG64)GetWindowThreadProcessId((HWND)hwnd, (LPDWORD)&processid);

	if (IsWindowUnicode((HWND)hwnd)) {
		isunicode = TRUE;
		windowproc = GetWindowLongPtrW((HWND)hwnd, GWLP_WNDPROC);
		style = GetWindowLongPtrW((HWND)hwnd, GWL_STYLE);
		exstyle = GetWindowLongPtrW((HWND)hwnd, GWL_EXSTYLE);
		instance = GetWindowLongPtrW((HWND)hwnd, GWLP_HINSTANCE);
		parent = GetWindowLongPtrW((HWND)hwnd, GWLP_HWNDPARENT);
		id = GetWindowLongPtrW((HWND)hwnd, GWLP_ID);
		userdata = GetWindowLongPtrW((HWND)hwnd, GWLP_USERDATA);

		if (flags & 0x01) {
			dlgproc = GetWindowLongPtrW((HWND)hwnd, DWLP_DLGPROC);
			msgresult = GetWindowLongPtrW((HWND)hwnd, DWLP_MSGRESULT);
			dlguser = GetWindowLongPtrW((HWND)hwnd, DWLP_USER);
		}
	}
	else {
		isunicode = FALSE;
		windowproc = GetWindowLongPtrA((HWND)hwnd, GWLP_WNDPROC);
		style = GetWindowLongPtrA((HWND)hwnd, GWL_STYLE);
		exstyle = GetWindowLongPtrA((HWND)hwnd, GWL_EXSTYLE);
		instance = GetWindowLongPtrA((HWND)hwnd, GWLP_HINSTANCE);
		parent = GetWindowLongPtrA((HWND)hwnd, GWLP_HWNDPARENT);
		id = GetWindowLongPtrA((HWND)hwnd, GWLP_ID);
		userdata = GetWindowLongPtrA((HWND)hwnd, GWLP_USERDATA);

		if (flags & 0x01) {
			dlgproc = GetWindowLongPtrA((HWND)hwnd, DWLP_DLGPROC);
			msgresult = GetWindowLongPtrA((HWND)hwnd, DWLP_MSGRESULT);
			dlguser = GetWindowLongPtrA((HWND)hwnd, DWLP_USER);
		}
	}

	GetWindowStyleStr(style, classname, stylestr, (flags & 0x01) ? TRUE : FALSE);
	GetWindowExStyleStr(exstyle, classname, exstylestr);

	if (flags & 0x01)
		dprintf(
			"Window    %p\n"
			"Name      %S\n"
			"Class     %S\n"
			"WndProc   %p\n"
			"Style     %s\n"
			"ExStyle   %s\n"
			"HInstance %p\n"
			"ParentWnd %p\n"
			"Id        %p\n"
			"UserData  %p\n"
			"DlgProc   %p\n"
			"MsgResult %p\n"
			"DlgUser   %p\n"
			"Unicode   %s\n"
			"ThreadId  %p\n"
			"ProcessId %p\n"
			, hwnd, windowname, classname, windowproc, stylestr.c_str(), exstylestr.c_str(), instance, parent, id, userdata, dlgproc, msgresult, dlguser,
			isunicode ? "TRUE" : "FALSE", threadid, processid
		);
	else
		dprintf(
			"Window    %p\n"
			"Name      %S\n"
			"Class     %S\n"
			"WndProc   %p\n"
			"Style     %s\n"
			"ExStyle   %s\n"
			"HInstance %p\n"
			"ParentWnd %p\n"
			"Id        %p\n"
			"UserData  %p\n"
			"Unicode   %s\n"
			"ThreadId  %p\n"
			"ProcessId %p\n"
			, hwnd, windowname, classname, windowproc, stylestr.c_str(), exstylestr.c_str(), instance, parent, id, userdata, isunicode ? "TRUE" : "FALSE", threadid,
			processid
		);

	FreeLibrary(user32);
}