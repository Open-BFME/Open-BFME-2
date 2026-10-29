// FILE: thing.h //////////////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 Thing, the common base of Object and Drawable.
//
// Target facts:
//  - ??0Thing (0x0030A188, ThingConstructor.cpp) stores vftable 0x00C086E0,
//    which ~Thing (0x0030A120) restores; the table has eight slots:
//      0 calculateHeightAboveTerrain 0x0030A4AC (rowed);
//      1-4 0x000D43D0 `xor eax,eax; ret`. Object's table 0x00BFC300 overrides
//        slots 1-2 and Drawable's 0x00BFB0B4 slots 3-4 with 0x0047A6A9
//        `mov eax,ecx; ret`, so slots 1-2 return the Object and 3-4 the
//        Drawable;
//      5 __purecall, overridden by the rowed reactToTransformChange of both;
//      6 0x000B3FD0 `ret`, overridden only by Object's unnamed 0x0028B193;
//      7 ??_GThing 0x0030A243, the scalar deleting destructor.
//  - the constructor lays out the template at +4, the transform at +8, and the
//    cached position, angle, direction and altitudes up to +0x60.
// Donor (Zero Hour Thing.h) facts: the names of slots 0-5 and their
// declaration order; MSVC lays each asObjectMeth/asDrawableMeth overload pair
// out in reverse declaration order, which puts the const getters first.
// Slot 6 has no recovered name; `vslot6` is a placeholder.
// The members by value need Coord3D's and Matrix3D's definitions: the unit
// declares them before including this header. Members below follow Zero
// Hour's declarations (Thing.h); only the inline ones are defined here.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_THING_H_
#define __BFME2_THING_H_

class Drawable;
class Matrix3D;
class Object;
class ThingTemplate;
struct Coord3D;

//-------------------------------------------------------------------------------------------------
class Thing
{
public:
	Thing(const ThingTemplate *thingTemplate);

	friend inline Object *AsObject(Thing *thing) { return thing ? thing->asObjectMeth() : 0; }
	friend inline Drawable *AsDrawable(Thing *thing) { return thing ? thing->asDrawableMeth() : 0; }
	friend inline const Object *AsObject(const Thing *thing) { return thing ? thing->asObjectMeth() : 0; }
	friend inline const Drawable *AsDrawable(const Thing *thing) { return thing ? thing->asDrawableMeth() : 0; }

	const ThingTemplate *getTemplate() const;
	void setPosition(const Coord3D *pos);
	void setPositionZ(float z);
	void setOrientation(float angle);
	inline const Coord3D *getPosition() const { return &m_cachedPos; }
	inline float getOrientation() const { return m_cachedAngle; }
	const Coord3D *getUnitDirectionVector2D() const;
	void getUnitDirectionVector2D(Coord3D &dir) const;
	const Matrix3D *getTransformMatrix() const { return &m_transform; }

protected:
	virtual float calculateHeightAboveTerrain() const;													// slot 0
	virtual Object *asObjectMeth() { return 0; }															// slot 2
	virtual Drawable *asDrawableMeth() { return 0; }														// slot 4
	virtual const Object *asObjectMeth() const { return 0; }												// slot 1
	virtual const Drawable *asDrawableMeth() const { return 0; }										// slot 3
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, float oldAngle) = 0;	// slot 5
	virtual void vslot6() {}																				// slot 6
	virtual ~Thing();																						// slot 7

public:
	// Zero Hour keeps these private behind inline accessors that are not
	// recovered yet; a data member's access changes no symbol.
	const ThingTemplate *m_template;				// +0x04
	Matrix3D m_transform;							// +0x08
	Coord3D m_cachedPos;							// +0x38
	float m_cachedAngle;							// +0x44
	Coord3D m_cachedDirVector;						// +0x48
	float m_cachedAltitudeAboveTerrain;				// +0x54
	float m_cachedAltitudeAboveTerrainOrWater;		// +0x58
	int m_cacheFlags;								// +0x5C
};

#endif // __BFME2_THING_H_
