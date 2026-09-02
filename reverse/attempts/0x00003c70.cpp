// ?Cross_Product@Vector3@@QAEXABV1@0@Z
// partial score=0.96 date=2026-09-02
// cl: /O2 /arch:SSE /DNDEBUG /MD
//
// WWMath Vector3 cross product, the SSE scalar form: three movss/mulss pairs
// and a subss each, written straight through to the destination in ecx.
// The arithmetic is the upstream body from WWMath/vector3.h -
//   X = a.Y * b.Z - a.Z * b.Y
//   Y = a.Z * b.X - a.X * b.Z
//   Z = a.X * b.Y - a.Y * b.X
// with the destination as `this` rather than a third pointer parameter, which
// is what the `ret 8` and the two stack arguments say.
//
// 93 bytes against 97, and the four are one register choice. Retail copies the
// destination out of ecx into eax and pushes esi to hold the second source;
// MSVC 7.1 keeps the destination in ecx and gets by with eax and edx, so it
// spends no push, no pop and no mov. /G5, /G6, /G7, /O1, /Ox, /arch:SSE2 and
// aliasing `this` into a named local all give the same 93.
//
// The name is a hypothesis. The arithmetic is verbatim from WWMath's
// vector3.h, but that header declares Cross_Product as a STATIC taking the
// destination as a third pointer - which would be __cdecl and `ret 0`. Nothing
// in the image calls this body directly, so the two-argument member form is
// inferred from the calling convention alone.

class Vector3
{
public:
	void Cross_Product(const Vector3 &a, const Vector3 &b);

	float X;
	float Y;
	float Z;
};

void Vector3::Cross_Product(const Vector3 &a, const Vector3 &b)
{
	X = (a.Y * b.Z - a.Z * b.Y);
	Y = (a.Z * b.X - a.X * b.Z);
	Z = (a.X * b.Y - a.Y * b.X);
}
