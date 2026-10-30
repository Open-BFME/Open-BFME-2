// WW3D::Set_Texture_Reduction, retail 0x00117BB0.
// Dedicated TU (ww3d.cpp is another lane; the setter must not capture globals
// locally): `mov eax,[esp+4]; cmp [glob],eax; je; cmp-flag; mov-glob; je;
// jmp _Invalidate_Textures` -- the flag cmp schedules above the store while
// the je still tests it (mov preserves flags). BFME 2 drops ZH's min_dim
// argument and only invalidates once WW3D is initialised.

// cl: /MD

extern int g_Va00DEC40C;

class WW3D
{
public:
	static void Set_Texture_Reduction(int value);
	static void _Invalidate_Textures();	// 0x001171B0
private:
	static bool IsInitted;	// 0x00DEC3D4, defined in ww3d.cpp
};

void WW3D::Set_Texture_Reduction(int value)
{
	if (g_Va00DEC40C != value) {
		g_Va00DEC40C = value;
		if (IsInitted) {
			_Invalidate_Textures();
		}
	}
}
