// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
#include "Coord2D.h"

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) { }
	float X;
	float Y;
};

class Render2DClass
{
public:
	void Add_Tri(const Vector2 &, const Vector2 &, const Vector2 &,
		const Vector2 &, const Vector2 &, const Vector2 &, unsigned long);
};

// Native 0x001049C7..0x00104A75 ends in RET: one renderer pointer and
// six pointers to two-float coordinates, copied to six Vector2 temporaries.
// The call target 0x00045708 independently allocates three vertices and
// indices via the established 0x0011BD80 renderer helper, transforms the
// first three vectors, assigns the next three UVs and uses the final color.
// This agrees with the BFME 1 Render2DClassAddTri.cpp at revision
// 968ca36c3265b295297e6aed45a6bd89ffe59c40 and ZH Add_Tri declaration.
// Callee identity and Vector2 ABI are reference-supported; the wrapper's
// original name and the input coordinate type are unknown measured views.
void Rva001049C7AddTriangle(Render2DClass *renderer,
	const Coord2D *v0, const Coord2D *v1, const Coord2D *v2,
	const Coord2D *uv0, const Coord2D *uv1, const Coord2D *uv2)
{
	renderer->Add_Tri(Vector2(v0->x, v0->y),
		Vector2(v1->x, v1->y), Vector2(v2->x, v2->y),
		Vector2(uv0->x, uv0->y), Vector2(uv1->x, uv1->y),
		Vector2(uv2->x, uv2->y), 0xFFFFFFFFUL);
}
