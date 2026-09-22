// cl: /O1 /G7 /arch:SSE /GX /DNDEBUG /MD
//
// Three ObjectCreationList nugget parse callbacks, reached from the OCL
// FieldParse table at 0x007E07F0 ("FireWeapon", "Attack", "ApplyRandomForce").
// BFME2 news them with plain operator new rather than Zero Hour's pools; two
// construct inline (vtable plus zeroed fields), Attack runs an out-of-line
// ctor. Each is then filled by INI::initFromINI and handed to
// ObjectCreationList::addObjectCreationNugget. Class names are Zero Hour's and
// BFME1's for the same keywords.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class ObjectCreationNugget
{
public:
	virtual ~ObjectCreationNugget();
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
	virtual ~FireWeaponNugget();
	static void parse(INI *ini, void *instance, void *, const void *);
	static const FieldParse s_fieldParse[];		// 0x00BE1060
private:
	const void *m_weapon;
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
	virtual ~ApplyRandomForceNugget();
	static void parse(INI *ini, void *instance, void *, const void *);
	static const FieldParse s_fieldParse[];		// 0x00BE1110
private:
	float m_spinRate;
	float m_minForceMag;
	float m_maxForceMag;
	float m_minForcePitch;
};

// ?parse@ApplyRandomForceNugget@@SAXPAVINI@@PAX1PBX@Z
void ApplyRandomForceNugget::parse(INI *ini, void *instance, void *, const void *)
{
	ApplyRandomForceNugget *nugget = new ApplyRandomForceNugget;
	ini->initFromINI(nugget, s_fieldParse);
	((ObjectCreationList *)instance)->addObjectCreationNugget(nugget);
}
