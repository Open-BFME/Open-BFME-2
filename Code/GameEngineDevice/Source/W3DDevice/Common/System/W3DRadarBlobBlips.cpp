// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// stlport
// ?rva0004F037@@YAXPAXHHHHHPBE@Z  Native 0x0004F037..0x0004F29B (612 bytes)
// ?rva0004F29B@@YAXPAXHHHHHQAY01$$CBE@Z  Native 0x0004F29B..0x0004F4F8 (605 bytes)
// W3DRadar 6x6 alpha blob (height ECX width EDX) and 2x2 blend blip (width ECX)
// statics; standalone fallback with a dummy caller marked absent-from-retail.
// Both exact including EH .xdata. Preferred home is the combined unit.
#include <algorithm>
#include "Coord3D.h"

typedef int Int;
typedef int Color;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

extern "C" __declspec(dllimport) double __cdecl floor(double);

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

struct ICoord2D { Int x, y; };
struct Region3D { Coord3D lo, hi; Real width() const { return hi.x - lo.x; } Real height() const { return hi.y - lo.y; } };

class GeometryInfo {
public:
	bool bfmeIntersects(const Coord3D &pos, Real angle, const GeometryInfo &other,
		const Coord3D &otherPos, Real otherAngle) const;
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
	char m_pad00[0x10];
	Real m_boundingCircleRadius;
};

class ThingTemplate;
class Player { public: Int getPlayerIndex() const { return m_playerIndex; } char m_pad00[0x54]; Int m_playerIndex; };
class PlayerList { public: Player *getLocalPlayer() { return m_local; } char m_pad00[0x10]; Player *m_local; };
extern PlayerList *ThePlayerList;
class Rva002A7DD0 { public: bool rva002A7DD0(); };
class Rva00373EC6 { public: char m_pad00[0x3c]; const ThingTemplate *m_template; };
class Rva0028E58E { public: Int rva0028E58E(); };
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED };
enum ObjectStatusTypes { OBJECT_STATUS_BFME_17 = 0x11 };

class ThingTemplate {
public:
	char m_pad000[0x108];
	UnsignedInt m_108_lo : 17;
	UnsignedInt m_108_bit17 : 1;
	UnsignedInt m_108_hi : 14;
	char m_pad10c[0x110 - 0x10c];
	UnsignedInt m_110_lo : 26;
	UnsignedInt m_110_bit26 : 1;
	UnsignedInt m_110_hi : 5;
	char m_pad114[0x11c - 0x114];
	UnsignedInt m_11c_lo : 29;
	UnsignedInt m_11c_bit29 : 1;
	UnsignedInt m_11c_hi : 2;
};

class Object {
public:
	Color getIndicatorColor() const;
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
	Player *getControllingPlayer() const;
	Rva00373EC6 *rva0028F4BC();
	bool rva002943B2(const Player *player);
	Int rva002933CD();
	bool testStatus(ObjectStatusTypes status) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_angle; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	char m_pad00[4];
	const ThingTemplate *m_template;
	char m_pad08[0x38 - 8];
	Coord3D m_pos;
	Real m_angle;
	char m_pad48[0xa8 - 0x48];
	GeometryInfo m_geometryInfo;
};

class RadarObject {
public:
	Object *friend_getObject() const { return m_object; }
	RadarObject *friend_getNext() const { return m_next; }
	Color getColor() const { return m_color; }
	char m_pad00[4];
	Object *m_object;
	RadarObject *m_next;
	Color m_color;
};

class SurfaceClass { public: void DrawPixel(UnsignedInt x, UnsignedInt y, UnsignedInt color); };
class W3DRadarResetSurface { public: ~W3DRadarResetSurface(); void *m_surface; };
class CursorTextureSlot { public: W3DRadarResetSurface Get_Surface_Level(); void *m_texture; };

struct HorizontalLine { Int yPos; Int xStart; Int xEnd; };
void free(void *);
class DiscreteCircle {
public:
	DiscreteCircle(Int xCenter, Int yCenter, Int radius);
	~DiscreteCircle() { if (m_begin) free(m_begin); }
	HorizontalLine *m_begin;
	HorizontalLine *m_end;
	HorizontalLine *m_capacity;
	Int m_yPos;
	Int m_yPosDoubled;
};

class GameClient {
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
	virtual void v70(); virtual void v74(); virtual void v78();
	virtual UnsignedInt getFrame();
};
extern GameClient *TheGameClient;
extern int g_009BA4E8;

class W3DRadar {
public:
	void rva00050125(const RadarObject *listHead, const CursorTextureSlot *texture, Int alpha);
	char m_pad0000[0x1434];
	Region3D m_mapExtent;
	char m_pad144c[0x149c - 0x144c];
	Int m_textureWidth;
	Int m_textureHeight;
};

Color Rva0004DE72Blend(Color *color, Color source, UnsignedByte alpha);
Color Rva0004D76EBlend(Color color, Int alpha);
unsigned char __fastcall Rva002D7682Check(void *radarObject);
void GameGetColorComponents(Color color, UnsignedByte *red, UnsignedByte *green, UnsignedByte *blue, UnsignedByte *alpha);
inline Color GameMakeColor(UnsignedByte r, UnsignedByte g, UnsignedByte b, UnsignedByte a) {
	return (a << 24) | (r << 16) | (g << 8) | (b);
}
inline Bool legalRadarPoint(Int px, Int py)
{
	if (px < 0 || py < 0 || px >= 128 || py >= 128)
		return false;
	return true;
}
extern UnsignedInt RadarEndpointColor;
extern unsigned int g_Va00DE1D00;
extern unsigned int g_Va00DE1D60;
extern const UnsignedByte g_Va00BC4E84[];
extern const unsigned char g_Va00BC4E80[][2];

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

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
	if (!bits)
		return;
	{
		Int row;
		for (row = startY; row < y && row < endY; ++row)
		{
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			Int dy = row - blobTop;
			Int col;
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
			Int col;
			for (col = left; col < x && col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[(col - blobLeft) * 3 + dy]);
			for (col = std::max(x, left); col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[(blobRight - col - 1) * 3 + dy]);
		}
	}
}

static void rva0004F29B(void *surface, Int width, Int height,
	Int x, Int y, Color color, const UnsignedByte alpha[][2])
{
	Int blobLeft = x - 2;
	Int blobTop = y - 2;
	Int blobRight = x + 2;
	Int blobBottom = y + 2;
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
		for (row = startY; row < y && row < endY; ++row)
		{
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			Int dy = row - blobTop;
			Int col;
			for (col = left; col < x && col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[col - blobLeft][dy]);
			for (col = std::max(x, left); col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[blobRight - col - 1][dy]);
		}
		if (y < endY)
		for (row = std::max(y, startY); row < endY; ++row)
		{
			Int dy = blobBottom - row - 1;
			Color *dst = (Color *)((char *)bits + (row - startY) * pitch);
			Int col;
			for (col = left; col < x && col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[col - blobLeft][dy]);
			for (col = std::max(x, left); col < right; ++col)
				Rva0004DE72Blend(&dst[col - left], color, alpha[blobRight - col - 1][dy]);
		}
	}
}

// ?rva0004F037Caller absent-from-retail
void rva0004F037Caller(void *surface, Int width, Int height, Int x, Int y, Color c, Color light)
{
	rva0004F037(surface, width, height, x, y, c, g_Va00BC4E84);
	rva0004F29B(surface, width, height, x, y, light, g_Va00BC4E80);
}
