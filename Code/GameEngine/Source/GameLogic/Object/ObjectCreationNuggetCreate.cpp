// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Two Object Creation List nugget create() bodies, ported from the
// Open-BFME-1 donor game/GameEngine/Source/GameLogic/Object/
// Rva001D5EA0Dispatch.cpp (1281192f68; donor flags plus BFME 2's /O1). The
// donor's TU compiled that way places both bodies uniquely on unclaimed
// .text by masked whole-.text search (tools/donor_sweep.py).
//
// The names are recovered from retail, not carried from the donor (which
// uses address-derived ones):
//   * vtable 0x007E09D0 is ObjectCreationNugget's: its slot 0 is the rowed
//     ??_GObjectCreationNugget (0x001F010B) and the base dtor 0x001F0409
//     stores it. Slot 2 is 0x001F0132, which turns two objects into their
//     positions (+0x38) and calls slot 3; slot 1 (0x001F0163, rowed under
//     a donor name) forwards a five-argument create to slot 3, dropping the
//     fourth argument. That is Zero Hour's ObjectCreationNugget::create
//     overload set with BFME 2's four-argument coordinate create in slot 3.
//   * vtable 0x007E09E8 is FireWeaponNugget's: FireWeaponNugget::parse
//     (rowed 0x001F0D61) news 8 bytes and stores it. Its slot 3,
//     0x001F0188, is Zero Hour's FireWeaponNugget::create: with all three
//     pointers and the weapon template (+4) present, fire a temporary weapon
//     from the primary object at the secondary position through
//     WeaponStore::createAndFireTempWeapon (rowed 0x002CE904).
// Both return nothing (RET 0xC / RET 0x10, eax not set).

typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord3D
{
	float x, y, z;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }

private:
	char m_pad00[0x38];
	Coord3D m_cachedPos; // +0x38
};

class WeaponTemplate;

class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *weapon, const Object *source, const Coord3D *pos);
};

extern WeaponStore *TheWeaponStore;

// MSVC lists a virtual overload set in reverse declaration order, so these
// declarations give slot 1 the five-argument create, slot 2 the object pair
// and slot 3 the coordinate create.
class ObjectCreationNugget
{
public:
	virtual ~ObjectCreationNugget();
	virtual void create(const Object *primaryObj, const Coord3D *primary, const Coord3D *secondary, UnsignedInt lifetimeFrames) const = 0;
	virtual void create(const Object *primary, const Object *secondary, UnsignedInt lifetimeFrames) const;
	virtual void create(const Object *primaryObj, const Coord3D *primary, const Coord3D *secondary, Bool createOwner, UnsignedInt lifetimeFrames) const;
};

// ?create@ObjectCreationNugget@@UBEXPBVObject@@0I@Z
void ObjectCreationNugget::create(const Object *primary, const Object *secondary, UnsignedInt lifetimeFrames) const
{
	create(primary, primary ? primary->getPosition() : 0,
		secondary ? secondary->getPosition() : 0, lifetimeFrames);
}

class FireWeaponNugget : public ObjectCreationNugget
{
public:
	virtual void create(const Object *primaryObj, const Coord3D *primary, const Coord3D *secondary, UnsignedInt lifetimeFrames) const;

private:
	const WeaponTemplate *m_weapon; // +4
};

// ?create@FireWeaponNugget@@UBEXPBVObject@@PBUCoord3D@@1I@Z
void FireWeaponNugget::create(const Object *primaryObj, const Coord3D *primary, const Coord3D *secondary, UnsignedInt lifetimeFrames) const
{
	if (!primaryObj || !primary || !secondary)
		return;

	if (m_weapon)
		TheWeaponStore->createAndFireTempWeapon(m_weapon, primaryObj, secondary);
}
