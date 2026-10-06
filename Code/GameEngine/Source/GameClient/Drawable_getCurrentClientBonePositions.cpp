// cl: /DNDEBUG /MD /EHsc /Oy-
//
// ?getCurrentClientBonePositions@Drawable@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@H@Z,
// retail 0x002727C8, 107 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/Drawable.cpp,
// Drawable::getCurrentClientBonePositions): five-argument client bone query
// fanning out over the draw modules. The retail body matches the landed
// pristine twin (Drawable_getPristineBonePositions.cpp) minus its condition
// state and trailing extra: same +0x14C module walk, same slot-0xA4 draw
// interface, five-argument worker at slot 0x10, same homed-pointer advances.

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

class BfmeObjectDrawForCurrent
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual Int getCurrentBonePositions(const char *boneNamePrefix,
		Int startIndex, Coord3D *positions, Matrix3D *transforms,
		Int maxBones) const = 0;
};

class BfmeDrawModuleForCurrent
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
	virtual BfmeObjectDrawForCurrent *getObjectDrawInterface() = 0;
};

class Drawable
{
public:
	Int getCurrentClientBonePositions(const char *boneNamePrefix,
		Int startIndex, Coord3D *positions, Matrix3D *transforms,
		Int maxBones) const;
};

// ?getCurrentClientBonePositions@Drawable@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@H@Z
Int Drawable::getCurrentClientBonePositions(const char *boneNamePrefix,
	Int startIndex, Coord3D *positions, Matrix3D *transforms,
	Int maxBones) const
{
	BfmeDrawModuleForCurrent **modules =
		*reinterpret_cast<BfmeDrawModuleForCurrent ***>((unsigned char *)this + 0x14C);
	Int count = 0;
	for (BfmeDrawModuleForCurrent **dm = modules; *dm; ++dm) {
		if (maxBones <= 0) {
			break;
		}
		BfmeObjectDrawForCurrent *di = (*dm)->getObjectDrawInterface();
		if (di) {
			Int subcount = di->getCurrentBonePositions(boneNamePrefix,
				startIndex, positions, transforms, maxBones);
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
