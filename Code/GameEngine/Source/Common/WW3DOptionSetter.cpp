// WW3D dword option setter with change notification, retail 0x00117BB0.
// Dedicated TU (ww3d.cpp is another lane; the setter must not capture globals
// or the notify pin locally): `mov eax,[esp+4]; cmp [glob],eax; je; cmp-flag;
// mov-glob; je; jmp notify` -- the flag cmp schedules above the store while
// the je still tests it (mov preserves flags).

// cl: /MD

extern int g_Va00DEC40C;
extern unsigned char g_WW3D_IsInitted;

void rva001171B0Notify();

void Rva00117BB0SetOption(int value)
{
	if (g_Va00DEC40C != value) {
		g_Va00DEC40C = value;
		if (g_WW3D_IsInitted != 0) {
			rva001171B0Notify();
		}
	}
}
