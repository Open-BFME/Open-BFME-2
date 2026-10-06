// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
class GameWindow;
class WinInstanceData;

// BFME 1 W3DControlBar.cpp names this empty callback. BFME 2 callback table
// 0x9B3E78 +0x30 points to 0xB3FD0; Ghidra boundary is 0xB3FD0/1.
void W3DNoDraw(GameWindow *, WinInstanceData *)
{
}
