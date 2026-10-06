// cl: /DNDEBUG /MD /EHsc /Oy-
//
// ?getPristineBonePositions@Drawable@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@HH@Z,
// retail 0x0027274D, 123 bytes. Dedicated TU (B2 has no Drawable.cpp).
// BFME1 twin: reference/open-bfme-1/Code/GameEngine/Source/GameClient/
// Drawable_getPristineBonePositions.cpp (BFMEDrawableBoneQuery seven-argument
// form). BFME2 adaptations, all retail-measured: draw modules at this+0x14C
// (B1 +0x150), condition state at this+0x258 (B1 +0x250), draw-module
// getObjectDrawInterface at vtable slot 0xA4, seven-argument query at slot
// 0x0C. No pins (all virtual or local); Coord3D is struct and Matrix3D is
// class per the mangling (PAU/PAV).

typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D
{
	float m[12];
};

class BfmeObjectDrawForPristine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual Int getPristineBonePositionsForConditionState(
		const void *conditionState, const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const = 0;
};

class BfmeDrawModuleForPristine
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void slot80() = 0; virtual void slot84() = 0;
	virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual void slot90() = 0; virtual void slot94() = 0;
	virtual void slot98() = 0; virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual BfmeObjectDrawForPristine *getObjectDrawInterface() = 0;
};

class Drawable
{
public:
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const;
};

// ?getPristineBonePositions@Drawable@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@HH@Z
Int Drawable::getPristineBonePositions(const char *boneNamePrefix,
	Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones,
	Int extra) const
{
	BfmeDrawModuleForPristine **modules =
		*reinterpret_cast<BfmeDrawModuleForPristine ***>((unsigned char *)this + 0x14C);
	Int count = 0;
	for (BfmeDrawModuleForPristine **dm = modules; *dm; ++dm) {
		if (maxBones <= 0) {
			break;
		}
		BfmeObjectDrawForPristine *di = (*dm)->getObjectDrawInterface();
		if (di) {
			Int subcount = di->getPristineBonePositionsForConditionState(
				(unsigned char *)this + 0x258, boneNamePrefix, startIndex,
				positions, transforms, maxBones, extra);
			if (subcount > 0) {
				count += subcount;
				if (positions) positions += subcount;
				if (transforms) transforms += subcount;
				maxBones -= subcount;
			}
		}
	}
	return count;
}
