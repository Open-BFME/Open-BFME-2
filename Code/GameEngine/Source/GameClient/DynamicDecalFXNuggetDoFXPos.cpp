// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// ?doFXPos@DynamicDecalFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
// Retail 0x001E0E43..0x001E107A (567 bytes); slot 1 of the DynamicDecal
// nugget vtable (entry at 0x007DD7A8), WB DynamicDecalFXNugget::doFXPos in
// FXList.cpp. Layout from the rowed ctor (DynamicDecalFXNuggetCtor.cpp).
//
// Adds a decal through TheProjectedShadowManager (slot 2) for the nugget's
// texture (shader 1 -> type 0x800, else 0x400; size, world-align and update
// flags), at the primary position plus the nugget offset (rotated by the
// matrix when OrientToObject) dropped to the ground; sets its angle, its
// colour (RGBColor::getAsInt), position, initial opacity (0 while a starting
// delay remains, else OpacityStart) and the opacity fade frames (seconds
// times the 0.03 frames-per-millisecond global g_00DBA500).
// Donor: Open-BFME-1 DynamicDecalFXNuggetDoFXPos.cpp (same flow; BFME 2's
// decal description, Shadow::ShadowTypeInfo, holds AsciiStrings and is the
// rowed 0x00079514 ctor / 0x000793FA dtor).
// The fade setter's frame counts are converted as UnsignedInt (retail goes
// through x87 and __ftol2, which only an unsigned target produces under
// /arch:SSE); its placeholder row 0x00330A37 is spelled with int parameters,
// so this call needs the pin ?rva00330A37@Rva00330A37@@QAEXIIIIIIII@Z.
#include "ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

class Matrix3D
{
public:
	Real Get_Z_Rotation() const;
};

void adjustVector(Coord3D *vec, const Matrix3D *mtx);

struct RGBColor
{
	__forceinline Int getAsInt() const
	{
		return ((Int)(red * 255.0) << 16) | ((Int)(green * 255.0) << 8) | ((Int)(blue * 255.0));
	}
	Real red;
	Real green;
	Real blue;
};

class Shadow
{
public:
	// The decal's shadow-type description: Shadow::ShadowTypeInfo, rowed
	// default ctor 0x00079514 and dtor 0x000793FA.
	struct ShadowTypeInfo
	{
		ShadowTypeInfo();
		~ShadowTypeInfo();

		AsciiString m_name;		// +0x00
		AsciiString m_second;		// +0x04
		Int m_type;			// +0x08
		Real m_sizeX;			// +0x0C
		Real m_sizeY;			// +0x10
		Real m_offsetX;			// +0x14
		Real m_offsetY;			// +0x18
		Real m_float1C;			// +0x1C
		Real m_float20;			// +0x20
		Bool m_byte24;			// +0x24
		Bool m_allowUpdates;		// +0x25
		Bool m_allowWorldAlign;		// +0x26
	};

	void setOpacity(Int value);			// 0x003308F6
	void rva00330995(Int color);			// 0x00330995

	unsigned char m_pad00[0x08];
	Coord3D m_position;				// +0x08
	unsigned char m_pad14[0x20 - 0x14];
	Real m_angle;					// +0x20
};

class Rva00330A37
{
public:
	void rva00330A37(UnsignedInt delay, UnsignedInt lifetime, UnsignedInt opacityStart, UnsignedInt fadeOne,
		UnsignedInt opacityPeak, UnsignedInt peakTime, UnsignedInt fadeTwo, UnsignedInt opacityEnd);	// 0x00330A37	// opacity fade frames
};

class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const;	// +0x18
};
extern TerrainLogic *TheTerrainLogic;

class ProjectedShadowManager
{
public:
	virtual void v00(); virtual void v01();
	virtual Shadow *addDecal(Shadow::ShadowTypeInfo *shadowInfo);	// +0x08
};
extern void *g_00DEC2D4;	// TheProjectedShadowManager

extern float g_00DBA500;	// seconds to frames

class Object;

class FXNugget
{
public:
	virtual ~FXNugget();
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary) const = 0;
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	unsigned char m_pad04[0x148 - 4];
};

class DynamicDecalFXNugget : public FXNugget
{
public:
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary) const;

private:
	AsciiString m_decalName;	// +0x148
	Int m_shader;			// +0x14C
	Real m_size;			// +0x150
	RGBColor m_color;		// +0x154
	Coord2D m_offset;		// +0x160
	Bool m_orientToObject;		// +0x168
	UnsignedInt m_opacityStart;	// +0x16C
	Real m_opacityFadeTimeOne;	// +0x170
	Int m_opacityPeak;		// +0x174
	Real m_opacityPeakTime;		// +0x178
	Real m_opacityFadeTimeTwo;	// +0x17C
	Int m_opacityEnd;		// +0x180
	Real m_startingDelay;		// +0x184
	Real m_lifetime;		// +0x188
};

void DynamicDecalFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, Real, const Coord3D *) const
{
	if (!primary)
		return;

	Shadow::ShadowTypeInfo decalInfo;
	decalInfo.m_name = m_decalName;
	decalInfo.m_type = (m_shader == 1) ? 0x800 : 0x400;
	decalInfo.m_allowUpdates = true;
	decalInfo.m_allowWorldAlign = true;
	decalInfo.m_sizeX = m_size;
	decalInfo.m_sizeY = m_size;
	decalInfo.m_offsetX = 0.0f;
	decalInfo.m_offsetY = 0.0f;

	Real offsetY = m_offset.y;
	Real offsetX = m_offset.x;
	Coord3D offset;
	offset.x = offsetX;
	offset.y = offsetY;
	offset.z = 0.0f;
	if (primaryMtx && m_orientToObject)
		adjustVector(&offset, primaryMtx);

	Coord3D pos;
	pos.x = primary->x;
	pos.y = primary->y;
	pos.x += offset.x;
	pos.y += offset.y;
	pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);

	Shadow *shadow = ((ProjectedShadowManager *)g_00DEC2D4)->addDecal(&decalInfo);
	if (shadow)
	{
		if (primaryMtx && m_orientToObject)
			shadow->m_angle = primaryMtx->Get_Z_Rotation();
		else
			shadow->m_angle = 0.0f;

		shadow->rva00330995(m_color.getAsInt());
		shadow->m_position = pos;

		Real initialOpacity = (m_startingDelay > 0.0f) ? 0.0f : (Real)m_opacityStart;
		shadow->setOpacity((Int)initialOpacity);
		((Rva00330A37 *)shadow)->rva00330A37(
			(UnsignedInt)(m_startingDelay * g_00DBA500),
			(UnsignedInt)(m_lifetime * g_00DBA500),
			m_opacityStart,
			(UnsignedInt)(m_opacityFadeTimeOne * g_00DBA500),
			m_opacityPeak,
			(UnsignedInt)(m_opacityPeakTime * g_00DBA500),
			(UnsignedInt)(m_opacityFadeTimeTwo * g_00DBA500),
			m_opacityEnd);
	}
}
