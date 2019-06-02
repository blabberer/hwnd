hwnd windbg extension

skywing aka ken johnsons's windbg extension sdbgext's command hwnd
recompiled for x64

compile the src ( vs 2017 community )or use at your risk the precompiled hwnd.dll

copy hwnd.dll to windbg\winext directory
.load hwnd.dll
.chain to verify if it has loaded 

!hwnd or !hwnd {specifc window handle}

0:000> !hwnd c045c
Window    00000000000c045c
Name      "C:\Program Files (x86)\Windows Kits\10\Debuggers\x64\windbg.exe" - WinDbg:10.0.17763.132 AMD64 
Class     WinDbgFrameClass
WndProc   00007ff6a450ab00
Style     WS_OVERLAPPED 
ExStyle   WS_EX_WINDOWEDGE WS_EX_LEFT WS_EX_LTRREADING WS_EX_RIGHTSCROLLBAR 
HInstance 00007ff6a44e0000
ParentWnd 0000000000000000
Id        00000000069503f5
UserData  0000000000000000
Unicode   TRUE
ThreadId  00000000000017b8
ProcessId 0000000f00000d6c