// cl: /O1 /EHsc /MD /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
//
// WeaponSet::xfer and the WeaponSetFlags transfer it calls, from Zero Hour's
// GameLogic/Object/WeaponSet.cpp and Common/BitFlags.h:
//   0x002C8872 572B WeaponSet::xfer (slot 3 of the WeaponSet vftable 0x00C0089C)
//   0x002914AF 315B BitFlags<104>::xfer
//   0x0028F6EB  72B BitFlags<104>::count
//
// Target evidence. WeaponSet's layout is the one its rowed ctor 0x002C72D5
// clears: template set +0x04, six weapons +0x08, current slot and lock status
// +0x20/+0x24, filled-slot mask +0x28, anti mask +0x2C, damage-type mask +0x30,
// the pitch-limit and damage-weapon flags +0x34/+0x35, six per-slot bytes
// +0x36 and the owner ObjectID +0x3C (setWeaponLock 0x002C8AAE). WeaponSetFlags
// is the 104-bit set: its transfer loops 0x68 names, sets them through the
// rowed 0x0028F733 (BitFlags<104>::getSingleBitFromName, whose name table
// starts at VETERAN), names a set bit through 0x0028C725 and sends the raw
// bits through 0x0028F808 on a light CRC. The template set keeps its
// ThingTemplate at +0x00, the flags at +0x04 and the six weapon templates at
// +0x14; the template's name is the AsciiString at +0x64.
//
// BFME 2 changes against Zero Hour: xfer returns at once on a light CRC and
// versions through Xfer::Version1; the mode test is a plain load/else; a slot
// saved empty deletes the weapon a load finds there; the six per-slot bytes
// follow the weapons; the damage-type mask is a plain word; both flags are
// transferred (Zero Hour sends m_hasDamageWeapon twice) and the owner's
// ObjectID closes the record. INI_INVALID_DATA and XFER_UNKNOWN_STRING are
// thrown as XferException tags 5 and 0. The ThingTemplate lookup is the
// pinned ThingFactory::findTemplate 0x002D06CA; findWeaponTemplateSet is the
// pinned 0x0033DCD1 spelling, whose flags argument the pin types BitFlags<117>.
// Donor-carried: the names and the Zero Hour bodies.

#include <string.h>
#include "ascii_string.h"
#include "Common/Snapshot.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *value);

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	WEAPONSLOT_COUNT = 6
};

enum WeaponLockType
{
	NOT_LOCKED = 0
};

// Rowed BitFlags<104> helpers under address names.
class Rva0028C725
{
public:
	void *rva0028C725(UnsignedInt i);
};
class Rva0028F733
{
public:
	Bool rva0028F733(const char *token);
};
struct Iface0028F808;
class Rva0028F808
{
public:
	void rva0028F808(Iface0028F808 *xfer);
};

template <int NUMBITS> class BitFlags
{
public:
	enum { NUMWORDS = 4 };

	BitFlags() { memset(m_bits, 0, sizeof(m_bits)); }

	Int count() const;
	const char *getBitNameIfSet(Int i) { return (const char *)((Rva0028C725 *)this)->rva0028C725(i); }
	Bool setBitByName(const char *token) { return ((Rva0028F733 *)this)->rva0028F733(token); }
	void clear() { memset(m_bits, 0, sizeof(m_bits)); }
	void xfer(Xfer *xfer);

private:
	UnsignedInt m_bits[NUMWORDS];
};
typedef BitFlags<104> WeaponSetFlags;

//-------------------------------------------------------------------------------------------------
template <int NUMBITS>
Int BitFlags<NUMBITS>::count() const
{
	Int c = 0;
	for (UnsignedInt i = 0; i < NUMWORDS; ++i)
	{
		UnsignedInt v = m_bits[i];
		UnsignedInt pairs = v - ((v >> 1) & 0x55555555u);
		UnsignedInt nibbles = (pairs & 0x33333333u) + ((pairs >> 2) & 0x33333333u);
		UnsignedInt bytes = (nibbles + (nibbles >> 4)) & 0x0F0F0F0Fu;
		c += (bytes * 0x01010101u) >> 24;
	}
	return c;
}

//-------------------------------------------------------------------------------------------------
template <int NUMBITS>
void BitFlags<NUMBITS>::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;

	if (xfer->IsLightCRC())
	{
		((Rva0028F808 *)this)->rva0028F808((Iface0028F808 *)xfer);
	}
	else if (xfer->IsStoring())
	{
		Int c = count();
		*xfer == c;
		for (Int i = 0; i < NUMBITS; ++i)
		{
			const char *bitName = getBitNameIfSet(i);
			if (bitName == 0)
				continue;
			AsciiString bitNameA = bitName;
			*xfer == bitNameA;
			--c;
		}
	}
	else
	{
		clear();
		Int c;
		*xfer == c;
		AsciiString string;
		for (Int i = 0; i < c; ++i)
		{
			*xfer == string;
			Bool ok = setBitByName(string.str());
			if (ok == false)
				throw XferException(0, 0);
		}
	}
}

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	const class WeaponTemplateSet *findWeaponTemplateSet(const BitFlags<117> &t) const;

private:
	unsigned char m_unmodelled00[0x64];
	AsciiString m_name;																												///< 0x64
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class WeaponTemplate;

class WeaponTemplateSet
{
public:
	const ThingTemplate *friend_getThingTemplate() const { return m_thingTemplate; }
	const WeaponSetFlags &friend_getWeaponSetFlags() const { return m_types; }
	const WeaponTemplate *getNth(WeaponSlotType n) const { return m_template[n]; }

private:
	const ThingTemplate *m_thingTemplate;																			///< 0x00
	WeaponSetFlags m_types;																										///< 0x04
	const WeaponTemplate *m_template[WEAPONSLOT_COUNT];												///< 0x14
};

class Weapon : public Snapshot
{
};

class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType wslot) const;
};

extern WeaponStore *TheWeaponStore;

class WeaponSet : public Snapshot
{
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);

private:
	const WeaponTemplateSet *m_curWeaponTemplateSet;													///< 0x04
	Weapon *m_weapons[WEAPONSLOT_COUNT];																			///< 0x08
	WeaponSlotType m_curWeapon;																								///< 0x20
	WeaponLockType m_curWeaponLockedStatus;																		///< 0x24
	UnsignedInt m_filledWeaponSlotMask;																				///< 0x28
	Int m_totalAntiMask;																											///< 0x2C
	UnsignedInt m_totalDamageTypeMask;																				///< 0x30
	Bool m_hasPitchLimit;																											///< 0x34
	Bool m_hasDamageWeapon;																										///< 0x35
	Bool m_slotFlags[WEAPONSLOT_COUNT];																				///< 0x36
	ObjectID m_ownerID;																												///< 0x3C
};

//-------------------------------------------------------------------------------------------------
void WeaponSet::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	// version
	xfer->Version1();

	if (xfer->IsLoading())
	{
		AsciiString ttName;
		WeaponSetFlags wsFlags;

		*xfer == ttName;
		wsFlags.xfer(xfer);

		if (ttName.isEmpty())
		{
			m_curWeaponTemplateSet = 0;
		}
		else
		{
			const ThingTemplate *tt = TheThingFactory->findTemplate(ttName);
			if (tt == 0)
				throw XferException(5, 0);

			m_curWeaponTemplateSet = tt->findWeaponTemplateSet(*(const BitFlags<117> *)&wsFlags);
			if (m_curWeaponTemplateSet == 0)
				throw XferException(5, 0);
		}
	}
	else
	{
		AsciiString ttName;				// leave 'em empty in case we're null
		WeaponSetFlags wsFlags;
		if (m_curWeaponTemplateSet != 0)
		{
			const ThingTemplate *tt = m_curWeaponTemplateSet->friend_getThingTemplate();
			if (tt == 0)
				throw XferException(5, 0);

			ttName = tt->getName();
			wsFlags = m_curWeaponTemplateSet->friend_getWeaponSetFlags();
		}
		*xfer == ttName;
		wsFlags.xfer(xfer);
	}

	for (Int i = 0; i < WEAPONSLOT_COUNT; ++i)
	{
		Bool hasWeaponInSlot = (m_weapons[i] != 0);
		*xfer == hasWeaponInSlot;
		if (hasWeaponInSlot)
		{
			if (xfer->IsLoading() && m_weapons[i] == 0)
			{
				const WeaponTemplate *wt = m_curWeaponTemplateSet->getNth((WeaponSlotType)i);
				if (wt == 0)
					wt = m_curWeaponTemplateSet->getNth((WeaponSlotType)0);
				m_weapons[i] = TheWeaponStore->allocateNewWeapon(wt, (WeaponSlotType)i);
			}
			*xfer == *m_weapons[i];
		}
		else if (m_weapons[i] != 0)
		{
			::delete m_weapons[i];
			m_weapons[i] = 0;
		}
	}
	for (Int j = 0; j < WEAPONSLOT_COUNT; ++j)
		*xfer == m_slotFlags[j];
	xfer->XferRawBytes(&m_curWeapon, sizeof(m_curWeapon));
	xfer->XferRawBytes(&m_curWeaponLockedStatus, sizeof(m_curWeaponLockedStatus));
	*xfer == m_filledWeaponSlotMask;
	*xfer == m_totalAntiMask;
	*xfer == m_totalDamageTypeMask;
	*xfer == m_hasDamageWeapon;
	*xfer == m_hasPitchLimit;
	XferObjectID(xfer, &m_ownerID);
}

template class BitFlags<104>;
