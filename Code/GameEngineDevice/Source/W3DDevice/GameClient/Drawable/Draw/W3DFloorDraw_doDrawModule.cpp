// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
//
// ?doDrawModule@W3DFloorDraw@@UAEXPBVMatrix3D@@@Z, retail 0x000CF3BA (94
// bytes, RET 4): slot 11 (+0x2C) of W3DFloorDraw's vtable 0x007CD4E0, the
// DrawModule slot that is _purecall in DrawModule's own table and
// doDrawModule(const Matrix3D *) in W3DDebrisDraw, W3DRopeDraw, W3DLightDraw
// and W3DProjectileStreamDraw; the transform is unused. With module data (+4) and a drawable (+8), a non-zero module value
// at +0x20 and a drawable whose Object (+0xFC) is effectively dead (+0x438
// bit 0), the terrain render object gets the drawable, a copy of the module
// data's name at +0x08 and that value (rowed 0x0006B7BF, which hands them to
// its +0x3860 member). The name travels by value: the private StringBase
// copy constructor builds it in the argument slot, reached through an inline
// two-argument wrapper so the slot address is recorded before the call setup,
// as in retail.
template <typename T> class StringBase
{
public:
	~StringBase();
	__forceinline StringBase(const StringBase &other, int) { this->StringBase<T>::StringBase(other); }
private:
	StringBase(const StringBase &other);
	friend class W3DFloorDraw;
	T *m_data;
};

class Rva0055A88BDwordField;

#include "../../../../../Include/W3DDevice/GameClient/BaseHeightMap.h"
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

#include "../../../../../../GameEngine/Source/GameLogic/Object/object.h"

#include "../../../../../../GameEngine/Include/GameClient/Drawable.h"

struct W3DFloorDrawModuleData
{
	unsigned char m_pad00[0x08];
	StringBase<char> m_name;	// +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
	float m_value;			// +0x20
};

class Matrix3D;
class W3DFloorDraw
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10();
	virtual void doDrawModule(const Matrix3D *transformMtx);	// +0x2C
private:
	const W3DFloorDrawModuleData *m_moduleData;	// +0x04
	Drawable *m_drawable;				// +0x08
};

void W3DFloorDraw::doDrawModule(const Matrix3D *transformMtx)
{
	const W3DFloorDrawModuleData *data = m_moduleData;
	Drawable *draw = m_drawable;
	if (data && draw && data->m_value != 0.0f)
	{
		Object *obj = draw->m_object;
		if (obj && (obj->m_privateStatus & 1))
			TheTerrainRenderObject->rva0006B7BF((const Rva0055A88BDwordField *)draw, StringBase<char>(data->m_name, 0), data->m_value);
	}
}
