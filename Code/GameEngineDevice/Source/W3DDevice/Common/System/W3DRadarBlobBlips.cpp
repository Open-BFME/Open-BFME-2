// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// stlport
// ?rva0004F037@@YAXPAXHHHHHPBE@Z  Native 0x0004F037..0x0004F29B (612 bytes)
// ?rva0004F29B@@YAXPAXHHHHHQAY01$$CBE@Z  Native 0x0004F29B..0x0004F4F8 (605 bytes)
// W3DRadar 6x6 alpha blob (height ECX width EDX) and 2x2 blend blip (width ECX)
// statics; standalone fallback with a dummy caller marked absent-from-retail.
// Both exact including EH .xdata. Preferred home is the combined unit.
#include <algorithm>

namespace _STL
{
// Branch-form int overloads: this TU's flags compile the generic max/min ?:
// to cmov, but retail's out-of-line copies use a branch (row 57 family-LK3).
inline const int &(max)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pa < *__pb) return __b; return __a; }
inline const int &(min)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pb < *__pa) return __b; return __a; }
}

typedef int Int;
typedef int Color;
typedef unsigned char UnsignedByte;

class Member0C00739C70 { public: void clear(); };
class Rva0004D729 {
public:
	Rva0004D729(void *surface, void **bits, int *pitch, int left, int top, int right, int bottom) {
		rva0004D729(surface, bits, pitch, left, top, right, bottom);
	}
	~Rva0004D729() { m_surface->clear(); }
	Rva0004D729 *rva0004D729(void *surface, void **bits, int *pitch, int left, int top, int right, int bottom);
	Member0C00739C70 *m_surface;
};
// The bank bodies of 0x0004F037 / 0x0004F29B spell the same lock this way.
class NativeRadarSurfaceLock : public Rva0004D729 {
public:
	NativeRadarSurfaceLock(void *surface, void *&bits, int *pitch, int left, int top, int right, int bottom)
		: Rva0004D729(surface, &bits, pitch, left, top, right, bottom) {}
};

Color Rva0004DE72Blend(Color *color, Color source, UnsignedByte alpha);

static void rva0004F037(void *surface, Int width, Int height,
	Int centerX, Int centerY, Color color, const UnsignedByte *alpha)
{
	Int blobLeft = centerX - 3;
	Int blobTop = centerY - 3;
	Int blobRight = centerX + 3;
	Int blobBottom = centerY + 3;
	Int left = (blobLeft > 0) ? blobLeft : 0;
	Int startY = (blobTop > 0) ? blobTop : 0;
	Int right = (blobRight < width) ? blobRight : width;
	Int endY = (blobBottom < height) ? blobBottom : height;

	int pitch;
	void *bits;
	NativeRadarSurfaceLock lock(surface, bits, &pitch, left, startY, right, endY);
	if (!bits)
		return;
	{
		Int row;
		for (row = startY; row < centerY && row < endY; ++row)
		{
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			Int dy = row - blobTop;
			Int col;
			for (col = left; col < centerX && col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[(col - blobLeft) * 3 + dy]);
			for (col = (std::max)(centerX, left); col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[(blobRight - col - 1) * 3 + dy]);
		}
		if (centerY < endY)
		for (row = (std::max)(centerY, startY); row < endY; ++row)
		{
			Int dy = blobBottom - row - 1;
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			Int col;
			for (col = left; col < centerX && col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[(col - blobLeft) * 3 + dy]);
			for (col = (std::max)(centerX, left); col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[(blobRight - col - 1) * 3 + dy]);
		}
	}
}

static void rva0004F29B(void *surface, Int width, Int height,
	Int centerX, Int centerY, Color color, const UnsignedByte alpha[][2])
{
	Int blobLeft = centerX - 2;
	Int blobTop = centerY - 2;
	Int blobRight = centerX + 2;
	Int blobBottom = centerY + 2;
	Int left = (blobLeft > 0) ? blobLeft : 0;
	Int startY = (blobTop > 0) ? blobTop : 0;
	Int right = (blobRight < width) ? blobRight : width;
	Int endY = (blobBottom < height) ? blobBottom : height;

	int pitch;
	void *bits;
	NativeRadarSurfaceLock lock(surface, bits, &pitch, left, startY, right, endY);
	if (!bits)
		return;
	{
		Int row;
		for (row = startY; row < centerY && row < endY; ++row)
		{
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			Int dy = row - blobTop;
			Int col;
			for (col = left; col < centerX && col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[col - blobLeft][dy]);
			for (col = (std::max)(centerX, left); col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[blobRight - col - 1][dy]);
		}
		if (centerY < endY)
		for (row = (std::max)(centerY, startY); row < endY; ++row)
		{
			Int dy = blobBottom - row - 1;
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			Int col;
			for (col = left; col < centerX && col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[col - blobLeft][dy]);
			for (col = (std::max)(centerX, left); col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[blobRight - col - 1][dy]);
		}
	}
}

// ?rva0004F037Caller absent-from-retail
// The emission driver takes its tables from its caller; it owns no retail data.
void rva0004F037Caller(void *surface, Int width, Int height, Int centerX, Int centerY, Color color, Color light,
	const UnsignedByte *blobAlpha, const UnsignedByte blipAlpha[][2])
{
	rva0004F037(surface, width, height, centerX, centerY, color, blobAlpha);
	rva0004F29B(surface, width, height, centerX, centerY, light, blipAlpha);
}
