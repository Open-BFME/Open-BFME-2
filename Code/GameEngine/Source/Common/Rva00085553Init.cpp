// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// ?Rva00085553Get@@YAXHH@Z 0x00085553 44B: free function sets five globals from second arg; caller 0x00085EE6
extern int g_00DEC1BC;
extern int g_00DEC1B8;
extern int g_00DEC1B4;
extern int g_00DB5B88;
extern unsigned char g_00DEC1C4;

void Rva00085553Get(int a, int b)
{
	g_00DEC1BC = 0;
	g_00DEC1B8 = 0xC;
	g_00DEC1B4 = b;
	g_00DB5B88 = 1;
	g_00DEC1C4 = 0;
}
