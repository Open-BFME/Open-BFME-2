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
#include "ascii_string.h"

class Player;

class Rva002AA8BF
{
public:
	bool testBit(int bit) const;
};

class Object
{
public:
	bool rva0028D9E5(int bit) const;
	Player *getControllingPlayer() const;
	bool isSignificantlyAboveTerrain() const;
	char m_pad00[0x38];
	float m_position[3];	// +0x38
	float m_pad44;		// +0x44 orientation
};

class UpgradeTemplate
{
public:
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
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

struct Coord3D;
class Matrix3D;

// reallyCreate's by-value result: three words torn down through the 5-byte
// thunk at 0x001F22A3.
struct NuggetCreated
{
	~NuggetCreated();
	char m_data[12];
};

class GenericObjectCreationNugget
{
public:
	virtual void v0();
	virtual void v1();
	virtual void create(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const;
	bool rva001F1513(const Object *obj) const;
	NuggetCreated reallyCreate(const Coord3D *pos, const Matrix3D *transform, float orientation,
		const Object *sourceObj, unsigned int lifetimeFrames) const;	// 0x001F1634
private:
	char m_pad04[0xAF - 4];
	bool m_skipIfSignificantlyAirborne;	// +0xAF
	char m_padB0[0x114 - 0xB0];
	NuggetNameList m_114;	// +0x114
	NuggetNameList m_120;	// +0x120
};

bool GenericObjectCreationNugget::rva001F1513(const Object *obj) const
{
	for (unsigned int i = 0; i < m_120.size(); ++i) {
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(m_120.m_begin[i]);
		if (upgrade) {
			int bit = upgrade->m_38;
			if (obj->rva0028D9E5(bit))
				return false;
			if (((Rva002AA8BF *)obj->getControllingPlayer())->testBit(bit))
				return false;
		}
	}
	if (m_114.size() == 0)
		return true;
	for (unsigned int i = 0; i < m_114.size(); ++i) {
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(m_114.m_begin[i]);
		if (upgrade) {
			int bit = upgrade->m_38;
			if (obj->rva0028D9E5(bit))
				return true;
			if (((Rva002AA8BF *)obj->getControllingPlayer())->testBit(bit))
				return true;
		}
	}
	return false;
}

void GenericObjectCreationNugget::create(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const
{
	if (primary) {
		if (m_skipIfSignificantlyAirborne && primary->isSignificantlyAboveTerrain())
			return;
		if (rva001F1513(primary))
			reallyCreate((const Coord3D *)primary->m_position, (const Matrix3D *)((const char *)primary + 8),
				primary->m_pad44, primary, lifetimeFrames);
	}
}
