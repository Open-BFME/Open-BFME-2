// cl: /O1 /G7 /arch:SSE /GX /DNDEBUG /MD
//
// Three ObjectCreationList nugget parse callbacks, reached from the OCL
// FieldParse table at 0x007E07F0 ("FireWeapon", "Attack", "ApplyRandomForce").
// BFME2 news them with plain operator new rather than Zero Hour's pools; two
// construct inline (vtable plus zeroed fields), Attack runs an out-of-line
// ctor. Each is then filled by INI::initFromINI and handed to
// ObjectCreationList::addObjectCreationNugget. Class names are Zero Hour's and
// BFME1's for the same keywords.
//
// The FireWeapon and ApplyRandomForce destructors are implicit: retail's one
// deleting dtor for both vtables (0x001F03ED) calls the empty base dtor
// 0x001F0409 directly, so each derived dtor inlined the base one and folded
// onto it. Each class's field table is defined here from retail's records.

class INI;

struct FieldParse
{
	const char *token;
	void (*parse)(INI *, void *, void *, const void *);
	const void *userData;
	int offset;
};

struct LookupListRec;
extern const LookupListRec TheWeaponSlotTypeNamesLookupList[];

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseInt(INI *, void *, void *, const void *);
	static void parseReal(INI *, void *, void *, const void *);
	static void parseAngleReal(INI *, void *, void *, const void *);
	static void parseLookupList(INI *, void *, void *, const void *);
	static void parseWeaponTemplate(INI *, void *, void *, const void *);
};

class RadiusDecalTemplate
{
public:
	static void parseRadiusDecalTemplate(INI *, void *, void *, const void *);
};

class ObjectCreationNugget
{
public:
	// ??1ObjectCreationNugget@@UAE@XZ is rowed at 0x001F0409 in
	// GenericObjectCreationNuggetDtor.cpp; this inline copy is select-any.
	virtual ~ObjectCreationNugget() {}
};

class ObjectCreationList
{
public:
	void addObjectCreationNugget(ObjectCreationNugget *nugget);
};

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

const FieldParse FireWeaponNugget::s_fieldParse[] =
{
	{ "Weapon", &INI::parseWeaponTemplate, 0, 0x04 },
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

const FieldParse AttackNugget::s_fieldParse[] =
{
	{ "NumberOfShots", &INI::parseInt, 0, 0x3C },
	{ "WeaponSlot", &INI::parseLookupList, TheWeaponSlotTypeNamesLookupList, 0x40 },
	{ "DeliveryDecal", &RadiusDecalTemplate::parseRadiusDecalTemplate, 0, 0x04 },
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

// Retail's records name the four floats at +0x04..+0x10 MinForceMagnitude,
// MaxForceMagnitude, MinForcePitch and MaxForcePitch; no SpinRate field.
const FieldParse ApplyRandomForceNugget::s_fieldParse[] =
{
	{ "MinForceMagnitude", &INI::parseReal, 0, 0x04 },
	{ "MaxForceMagnitude", &INI::parseReal, 0, 0x08 },
	{ "MinForcePitch", &INI::parseAngleReal, 0, 0x0C },
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
