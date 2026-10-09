// ?rva0004F29B@@YAXPAXHHHHHQAY01$$CBE@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// stlport
// Donor f98983a7d: W3DRadarAlphaBlob6x6 and W3DRadarBlendBlip2x2.
// Target caller00050125 passes two quarter alpha tables at BC4E84/BC4E80.
// Independent target loops prove radius3/2 mirroring and rowed lock43B,
// unlock20B, blend253B provider contracts. Original private names unknown.
#include <algorithm>
typedef int Int;
typedef int Color;
typedef unsigned char UnsignedByte;
class Member0C00739C70 { public: void clear(); };
class Rva0004D729 {
public:
 Rva0004D729 *rva0004D729(void *,void **,int *,int,int,int,int);
 Member0C00739C70 *surface;
};
class NativeRadarSurfaceLock {
public:
 NativeRadarSurfaceLock(void *surface,void *&bits,int *pitch,int left,int top,int right,int bottom) {
  m_lock.rva0004D729(surface,&bits,pitch,left,top,right,bottom);
 }
 ~NativeRadarSurfaceLock() { m_lock.surface->clear(); }
private:
 Rva0004D729 m_lock;
};
Color Rva0004DE72Blend(Color *color, Color source, UnsignedByte alpha);
static void rva0004F037(void *surface, Int width, Int height,
	Int x, Int y, Color color, const UnsignedByte *alpha)
{
	Int blobLeft = x - 3;
	Int blobTop = y - 3;
	Int blobRight = x + 3;
	Int blobBottom = y + 3;
	Int left = (blobLeft > 0) ? blobLeft : 0;
	Int startY = (blobTop > 0) ? blobTop : 0;
	Int right = (blobRight < width) ? blobRight : width;
	Int endY = (blobBottom < height) ? blobBottom : height;

	int pitch;
	void *bits;
	NativeRadarSurfaceLock lock(surface, bits, &pitch, left, startY, right, endY);
	if (bits)
	{
		Int row;
		Int col;
		for (row = startY; row < y && row < endY; ++row)
		{
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			Int dy = row - blobTop;
			for (col = left; col < x && col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[(col - blobLeft) * 3 + dy]);
			for (col = std::max(x, left); col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[(blobRight - col - 1) * 3 + dy]);
		}
		if (y < endY)
		for (row = std::max(y, startY); row < endY; ++row)
		{
			Int dy = blobBottom - row - 1;
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			for (col = left; col < x && col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[(col - blobLeft) * 3 + dy]);
			for (col = std::max(x, left); col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[(blobRight - col - 1) * 3 + dy]);
		}
	}
}

static void rva0004F29B(void *surface, int width, int height, int x, int y,
	int color, const unsigned char alpha[][2])
{
	int x0 = x - 2;
	int x1 = x + 2;
	int y0 = y - 2;
	int y1 = y + 2;
	int left = __max(x0, 0);
	int top = __max(y0, 0);
	int right = __min(x1, width);
	int bottom = __min(y1, height);
	int pitch;
	void *bits;
	NativeRadarSurfaceLock lock(surface, bits, &pitch, left, top, right, bottom);
	if (bits == NULL)
		return;

	int i, j, dy;

	// upper half: rows above the centre, alpha rows counting in from the edge
	for (j = top; j < y && j < bottom; ++j)
	{
		int *row = (int *)((char *)bits + (j - top) * pitch);
		dy = j - y0;
		for (i = left; i < x && i < right; ++i)
			Rva0004DE72Blend(&row[i - left], color, alpha[i - x0][dy]);
		for (i = std::max(x, left); i < right; ++i)
			Rva0004DE72Blend(&row[i - left], color, alpha[x1 - i - 1][dy]);
	}

	if (y >= bottom)
		return;

	// lower half: the same table mirrored
	for (j = std::max(y, top); j < bottom; ++j)
	{
		dy = y1 - j - 1;
		int *row = (int *)((char *)bits + (j - top) * pitch);
		for (i = left; i < x && i < right; ++i)
			Rva0004DE72Blend(&row[i - left], color, alpha[i - x0][dy]);
		for (i = std::max(x, left); i < right; ++i)
			Rva0004DE72Blend(&row[i - left], color, alpha[x1 - i - 1][dy]);
	}
}


// ?Rva0004F037Caller absent-from-retail
void Rva0004F037Caller(void *surface,int width,int height,int x,int y,int color,const unsigned char *alpha) {
 rva0004F037(surface,width,height,x,y,color,alpha);
}
// ?Rva0004F29BCaller absent-from-retail
void Rva0004F29BCaller(void *surface,int width,int height,int x,int y,int color,const unsigned char alpha[][2]) {
 rva0004F29B(surface,width,height,x,y,color,alpha);
}
