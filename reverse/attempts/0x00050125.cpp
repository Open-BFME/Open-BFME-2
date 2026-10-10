// ?rva00050125@W3DRadar@@QAEXPBVRadarObject@@PBVCursorTextureSlot@@H@Z
// partial score=0.99 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// stlport
// ?rva00050125@W3DRadar@@QAEXPBVRadarObject@@PBVCursorTextureSlot@@H@Z
// Native 0x00050125..0x0005053E (1049 bytes) RET 12: W3DRadar object-list
// render (BFME2 renderObjectList) plus the static helpers retail calls with
// private register conventions: 0x0004DF6F (object in EBX) footprint fill
// 0x0004E55B (y in ESI) circle endpoints and 0x0004E704 (object in EDI and
// colour pointer in EBX) stealth blink and 0x0004F037 / 0x0004F29B blob blits.
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

static void rva0004DF6F(const Object *obj, void *surface, Int width, Int height,
	Real scaleX, Real scaleY)
{
	if (obj == 0)
		return;

	const Coord3D *pos = obj->getPosition();
	Int radius = (Int)obj->getGeometryInfo().getBoundingCircleRadius();
	ICoord2D center;
	center.x = (Int)(pos->x * scaleX);
	center.y = (Int)(pos->y * scaleY);
	Int x0 = (Int)(center.x - radius * scaleX);
	Int y0 = (Int)(center.y - radius * scaleY);
	Int x1 = (Int)(center.x + radius * scaleX);
	Int y1 = (Int)(center.y + radius * scaleY);
	Int left = (x0 > 0) ? x0 : 0;
	Int top = (y0 > 0) ? y0 : 0;
	Int right = (x1 < width) ? x1 : width;
	Int bottom = (y1 < height) ? y1 : height;

	int pitch;
	void *bits;
	Rva0004D729 lock(surface, &bits, &pitch, left, top, right, bottom);
	if (bits)
	{
		Color color = obj->getIndicatorColor();
		Coord3D pt;
		pt.x = pos->x;
		pt.y = pos->y;
		pt.z = pos->z;
		for (Int y = top; y < bottom; ++y)
		{
			Color *row = (Color *)((char *)bits + (y - top) * pitch);
			pt.y = (center.y - y) * (1.0f / scaleY) + pos->y;
			for (Int x = left; x < right; ++x)
			{
				pt.x = (center.x - x) * (1.0f / scaleX) + pos->x;
				if (obj->getGeometryInfo().bfmeIntersects(*pos, obj->getOrientation(),
					reinterpret_cast<const GeometryInfo &>(g_Va00DE1D00), pt, 0.0f))
				{
					if (obj->getGeometryInfo().bfmeIntersects(*pos, obj->getOrientation(),
						reinterpret_cast<const GeometryInfo &>(g_Va00DE1D60), pt, 0.0f))
						Rva0004DE72Blend(&row[x - left], color, 0xff);
					else
						Rva0004DE72Blend(&row[x - left], color, 0x80);
				}
			}
		}
	}
}




static void rva0004E55B(Int firstX, Int lastX, Int y, SurfaceClass *surface)
{
	if (legalRadarPoint(firstX, y))
		surface->DrawPixel(firstX, y, RadarEndpointColor);
	if (legalRadarPoint(lastX, y))
		surface->DrawPixel(lastX, y, RadarEndpointColor);
}


static Bool rva0004E704(Object *object, Color *color)
{
	if (object->rva002943B2(0))
	{
		Rva00373EC6 *disguise = object->rva0028F4BC();
		if (disguise == 0 || disguise->m_template == 0)
		{
			if (object->getControllingPlayer() != ThePlayerList->getLocalPlayer() &&
				!(UnsignedByte)object->rva002933CD() && !object->testStatus(OBJECT_STATUS_BFME_17))
				return false;

			UnsignedByte red, green, blue, alpha;
			GameGetColorComponents(*color, &red, &green, &blue, &alpha);
			const UnsignedInt halfTransition = g_009BA4E8;
			UnsignedInt frame = TheGameClient->getFrame() % (halfTransition * 2);
			if (frame >= halfTransition)
				alpha = (UnsignedByte)(255 - ((frame - halfTransition) * 191) / halfTransition);
			else
				alpha = (UnsignedByte)(64 + (frame * 191) / halfTransition);
			*color = GameMakeColor(red, green, blue, alpha);
		}
	}
	return true;
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



void W3DRadar::rva00050125(const RadarObject *listHead, const CursorTextureSlot *texture, Int alpha)
{
	if (listHead == 0 || texture->m_texture == 0)
		return;

	W3DRadarResetSurface surfaceLevel = const_cast<CursorTextureSlot *>(texture)->Get_Surface_Level();
	SurfaceClass *surface = reinterpret_cast<SurfaceClass *>(&surfaceLevel);

	Player *player = ThePlayerList->getLocalPlayer();
	Int playerIndex = 0;
	if (player)
		playerIndex = player->getPlayerIndex();

	Real scaleX = 128.0f / m_mapExtent.width();
	Real scaleY = 128.0f / m_mapExtent.height();

	for (const RadarObject *rObj = listHead; rObj; rObj = rObj->friend_getNext())
	{
		if (Rva002D7682Check(const_cast<RadarObject *>(rObj)))
			continue;

		Object *obj = rObj->friend_getObject();
		Bool drawRadius = obj->getTemplate()->m_108_bit17;
		if (obj->getShroudStatusForPlayer(playerIndex) > CELLSHROUD_SHROUDED)
			continue;
		Bool drawFootprint = obj->getTemplate()->m_11c_bit29;
		if (!drawRadius && reinterpret_cast<Rva0028E58E *>(obj)->rva0028E58E() == 4 &&
			obj->getControllingPlayer() != ThePlayerList->getLocalPlayer() &&
			reinterpret_cast<Rva002A7DD0 *>(ThePlayerList)->rva002A7DD0())
			continue;

		ICoord2D radarPoint;
		radarPoint.x = (Int)(obj->getPosition()->x * scaleX);
		radarPoint.y = (Int)(obj->getPosition()->y * scaleY);
		Color c = Rva0004D76EBlend(rObj->getColor(), alpha);

		const ThingTemplate *tmpl = obj->getTemplate();
		Rva00373EC6 *disguise = obj->rva0028F4BC();
		if (disguise && disguise->m_template && obj->getControllingPlayer() != ThePlayerList->getLocalPlayer())
			tmpl = disguise->m_template;

		if (tmpl->m_110_bit26)
		{
			if (!rva0004E704(obj, &c))
				continue;
			UnsignedByte red, green, blue, a;
			GameGetColorComponents(c, &red, &green, &blue, &a);
			red += (255 - red) >> 1;
			green += (255 - green) >> 1;
			blue += (255 - blue) >> 1;
			Color light = GameMakeColor(red, green, blue, a);
			rva0004F037(surface, m_textureWidth, m_textureHeight, radarPoint.x, radarPoint.y, c, g_Va00BC4E84);
			rva0004F29B(surface, m_textureWidth, m_textureHeight, radarPoint.x, radarPoint.y, light, g_Va00BC4E80);
		}
		else if (drawFootprint)
		{
			rva0004DF6F(obj, surface, m_textureWidth, m_textureHeight, scaleX, scaleY);
		}
		else if (drawRadius)
		{
			Int minRadius = 2;
			Int radius = fast_float2long_round(floor(obj->getGeometryInfo().getBoundingCircleRadius() * scaleX + 0.5f));
			DiscreteCircle circle(radarPoint.x, radarPoint.y, std::max(radius, minRadius));
			RadarEndpointColor = c;
			Int twoY = radarPoint.y * 2;
			HorizontalLine *widest = circle.m_begin;
			for (HorizontalLine *it = circle.m_begin; it != circle.m_end; ++it)
			{
				rva0004E55B(it->xStart, it->xEnd, it->yPos, surface);
				rva0004E55B(it->xStart, it->xEnd, twoY - it->yPos, surface);
				if (widest->yPos < it->yPos)
					widest = it;
			}
			for (Int x = widest->xStart + 1; x < widest->xEnd; ++x)
			{
				if (legalRadarPoint(x, widest->yPos))
					surface->DrawPixel(x, widest->yPos, c);
				if (legalRadarPoint(x, twoY - widest->yPos))
					surface->DrawPixel(x, twoY - widest->yPos, c);
			}
		}
		else
		{
			if (!rva0004E704(obj, &c))
				continue;
			if (legalRadarPoint(radarPoint.x, radarPoint.y))
				surface->DrawPixel(radarPoint.x, radarPoint.y, c);
			radarPoint.x--;
			if (legalRadarPoint(radarPoint.x, radarPoint.y))
				surface->DrawPixel(radarPoint.x, radarPoint.y, c);
			radarPoint.y--;
			if (legalRadarPoint(radarPoint.x, radarPoint.y))
				surface->DrawPixel(radarPoint.x, radarPoint.y, c);
			radarPoint.x++;
			if (legalRadarPoint(radarPoint.x, radarPoint.y))
				surface->DrawPixel(radarPoint.x, radarPoint.y, c);
		}
	}
}
