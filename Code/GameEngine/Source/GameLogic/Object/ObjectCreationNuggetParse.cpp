// cl: /O1 /G7 /arch:SSE /GX /DNDEBUG /MD
//
// Three ObjectCreationList nugget parse callbacks, reached from the OCL
// FieldParse table at 0x007E07F0 ("FireWeapon", "Attack", "ApplyRandomForce").
// BFME2 news them with plain operator new rather than Zero Hour's pools; two
// construct inline (vtable plus zeroed fields), Attack runs an out-of-line
// ctor. Each is then filled by INI::initFromINI and handed to
// ObjectCreationList::addObjectCreationNugget. Class names are Zero Hour's and
// BFME1's for the same keywords.

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

// Zero Hour's INI field-parse record: the token, its parser, the parser's
// user data and the field offset within the nugget.
#include "../../../Include/Common/INI/FieldParse.h"

struct LookupListRec;
extern const LookupListRec TheWeaponSlotTypeNamesLookupList[];

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/GameClient/RadiusDecalTemplate.h"

class ObjectCreationNugget
{
public:
	virtual ~ObjectCreationNugget();
};

class ObjectCreationList
{
public:
	void addObjectCreationNugget(ObjectCreationNugget *nugget);
	bool rva001F0434(void*,void*);
};

// The nuggets declare no destructor of their own: retail's vtables 0x00BE09E8
// and 0x00BE0A00 share the deleting destructor 0x001F03ED, which calls
// ~ObjectCreationNugget 0x001F0409 directly.

// "FireWeapon": parse 0x001F0D61, 8 bytes, vtable 0x00BE09E8
class FireWeaponNugget : public ObjectCreationNugget
{
public:
	FireWeaponNugget() : m_weapon(0) {}
	static void parse(INI *ini, void *instance, void *, const void *);
	static const FieldParse s_fieldParse[];		// 0x00BE1060
private:
	const void *m_weapon;
};

// Retail 0x00BE1060.
const FieldParse FireWeaponNugget::s_fieldParse[] =
{
	{ "Weapon", &INI::parseWeaponTemplate, 0, 0x4 },
	{ 0, 0, 0, 0 }
};

// ?parse@FireWeaponNugget@@SAXPAVINI@@PAX1PBX@Z
void FireWeaponNugget::parse(INI *ini, void *instance, void *, const void *)
{
	FireWeaponNugget *nugget = new FireWeaponNugget;
	ini->initFromINI(nugget, s_fieldParse);
	((ObjectCreationList *)instance)->addObjectCreationNugget(nugget);
}

// "Attack": parse 0x001F0D96, 0x44 bytes, ctor 0x001F05C1
class AttackNugget : public ObjectCreationNugget
{
public:
	AttackNugget();
	virtual ~AttackNugget();
	static void parse(INI *ini, void *instance, void *, const void *);
	static const FieldParse s_fieldParse[];		// 0x00BE10C0
private:
	char m_pad[0x40];
};

// Retail 0x00BE10C0.
const FieldParse AttackNugget::s_fieldParse[] =
{
	{ "NumberOfShots", &INI::parseInt, 0, 0x3C },
	{ "WeaponSlot", &INI::parseLookupList, TheWeaponSlotTypeNamesLookupList, 0x40 },
	{ "DeliveryDecal", &RadiusDecalTemplate::parseRadiusDecalTemplate, 0, 0x4 },
	{ "DeliveryDecalRadius", &INI::parseReal, 0, 0x38 },
	{ 0, 0, 0, 0 }
};

// ?parse@AttackNugget@@SAXPAVINI@@PAX1PBX@Z
void AttackNugget::parse(INI *ini, void *instance, void *, const void *)
{
	AttackNugget *nugget = new AttackNugget;
	ini->initFromINI(nugget, s_fieldParse);
	((ObjectCreationList *)instance)->addObjectCreationNugget(nugget);
}

// "ApplyRandomForce": parse 0x001F0DE7, 0x14 bytes, vtable 0x00BE0A00
class ApplyRandomForceNugget : public ObjectCreationNugget
{
public:
	ApplyRandomForceNugget() : m_spinRate(0.0f), m_minForceMag(0.0f), m_maxForceMag(0.0f), m_minForcePitch(0.0f) {}
	static void parse(INI *ini, void *instance, void *, const void *);
	static const FieldParse s_fieldParse[];		// 0x00BE1110
private:
	float m_spinRate;
	float m_minForceMag;
	float m_maxForceMag;
	float m_minForcePitch;
};

// Retail 0x00BE1110.
const FieldParse ApplyRandomForceNugget::s_fieldParse[] =
{
	{ "MinForceMagnitude", &INI::parseReal, 0, 0x4 },
	{ "MaxForceMagnitude", &INI::parseReal, 0, 0x8 },
	{ "MinForcePitch", &INI::parseAngleReal, 0, 0xC },
	{ "MaxForcePitch", &INI::parseAngleReal, 0, 0x10 },
	{ 0, 0, 0, 0 }
};

// ?parse@ApplyRandomForceNugget@@SAXPAVINI@@PAX1PBX@Z
void ApplyRandomForceNugget::parse(INI *ini, void *instance, void *, const void *)
{
	ApplyRandomForceNugget *nugget = new ApplyRandomForceNugget;
	ini->initFromINI(nugget, s_fieldParse);
	((ObjectCreationList *)instance)->addObjectCreationNugget(nugget);
}
