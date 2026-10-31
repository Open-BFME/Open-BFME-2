// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// GenericObjectCreationNugget members that gate and forward a create (retail
// 0x001F1513 and 0x001F14B6; ObjectCreationList.cpp in the debug build).
// The nugget keeps two upgrade-name lists, +0x114 and +0x120, 4-byte
// AsciiString entries each (the dtor TU's three tail vectors).
//
//   rva001F1513  the object may be created for: no +0x120 upgrade is
//                present on the primary or its player, and when the
//                +0x114 list is not empty at least one of its upgrades is
//   create       slot 2 of the nugget vftable (the object-pair create):
//                skip airborne primaries when +0xAF is set, check the
//                upgrades, then really create at the primary's position
//                (+0x38), transform (+0x08) and orientation (+0x44) and
//                drop the result
// reallyCreate's by-value result: three words torn down through the 5-byte
// thunk at 0x001F22A3.
#include "ascii_string.h"

class Player;
struct Coord3D;
class Matrix3D;

class Rva002AA8BF
{
public:
	bool testBit(int bit) const;
};

class Object
{
public:
	bool hasUpgradeMask(int bit) const;
	Player *getControllingPlayer() const;
	bool isSignificantlyAboveTerrain() const;
	const Coord3D *getPosition() const { return (const Coord3D *)m_position; }
	const Matrix3D *getTransformMatrix() const { return (const Matrix3D *)m_transform; }
	float getOrientation() const { return m_angle; }
private:
	char m_pad00[0x08];
	char m_transform[0x30];	// +0x08
	float m_position[3];	// +0x38
	float m_angle;		// +0x44 orientation
};

class UpgradeTemplate;

struct UpgradeTemplateBitView
{
	char m_pad00[0x38];
	int m_38;		// +0x38 the bit the object and player test
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

struct NuggetNameList
{
	unsigned int size() const { return m_end - m_begin; }
	const AsciiString &operator[](unsigned int i) const { return m_begin[i]; }
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

struct Coord3D;
class Matrix3D;

class GenericObjectCreationNugget
{
public:
	virtual void v0();
	virtual void v1();
	virtual void create(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const;
	bool rva001F1513(const Object *obj) const;
private:
	char m_pad04[0xAF - 4];
	bool m_skipIfSignificantlyAirborne;	// +0xAF
	char m_padB0[0x114 - 0xB0];
	NuggetNameList m_tailVec114;	// +0x114
	NuggetNameList m_tailVec120;	// +0x120
};

bool GenericObjectCreationNugget::rva001F1513(const Object *obj) const
{
	for (unsigned int i = 0; i < m_tailVec120.size(); ++i) {
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(m_tailVec120[i]);
		if (upgrade) {
			int bit = ((const UpgradeTemplateBitView *)upgrade)->m_38;
			if (obj->hasUpgradeMask(bit))
				return false;
			if (((Rva002AA8BF *)obj->getControllingPlayer())->testBit(bit))
				return false;
		}
	}
	if (m_tailVec114.size() == 0)
		return true;
	for (unsigned int i = 0; i < m_tailVec114.size(); ++i) {
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(m_tailVec114[i]);
		if (upgrade) {
			int bit = ((const UpgradeTemplateBitView *)upgrade)->m_38;
			if (obj->hasUpgradeMask(bit))
				return true;
			if (((Rva002AA8BF *)obj->getControllingPlayer())->testBit(bit))
				return true;
		}
	}
	return false;
}

