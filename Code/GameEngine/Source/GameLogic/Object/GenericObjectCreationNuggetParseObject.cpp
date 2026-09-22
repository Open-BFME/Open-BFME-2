// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?parseObject@GenericObjectCreationNugget@@SAXPAVINI@@PAX1PBX@Z,
// retail 0x001F311B (142 bytes). Dedicated TU.
//
// BFME2 object-nugget parser: builds a two-table MultiIniFieldParse on the
// stack, allocates a 0x12C-byte GenericObjectCreationNugget, marks it
// nameAreObjects (+0xA8) and runs it through INI::initFromINIMulti, then
// registers it on the ObjectCreationList. Ported from Open-BFME-1
// (Code/GameEngine/Source/GameLogic/Object/
// GenericObjectCreationNuggetParseObject.cpp), whose 191-byte body is the
// same shape; every BFME2 delta below is read from the retail bytes:
//
// - The nugget is 0x12C bytes (retail `push 0x12C` ahead of operator new)
//   with m_nameAreObjects at +0xA8 (retail `mov byte [esi+0xA8],1`), not
//   BFME1's +0x114 layout.
// - The two FieldParse tables live at 0x7E0CC0/0x7E1360 (8+ real entries
//   each: token literals plus INI parse-function pointers). Only their
//   addresses are emitted (`push table`), so the TU keeps BFME1's
//   single-terminator shape; the DIR32 sites take retail's addresses.
// - MultiIniFieldParse ctor/add and the nugget ctor/dtor stay out-of-line
//   (declared, never defined) and resolve through pins/new rows:
//   ??0MultiIniFieldParse @0x2BAA0, add @0x2BC6E (pre-existing pin),
//   ??0GenericObjectCreationNugget @0x1F0E32,
//   ??1GenericObjectCreationNugget (protected, BFME1-attested MAE) @0x1F31C6
//   for the `new` unwind funclet, operator new/delete via the matched
//   mem_ops rows, initFromINIMulti via its pre-existing pin, and
//   addObjectCreationNugget via its matched row.

struct FieldParse
{
	const char *token;
	void *parse;
	const void *userData;
	int offset;
};

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	void add(const FieldParse *, unsigned int = 0);

private:
	const FieldParse *m_fieldParse[16];
	unsigned int m_extraOffset[16];
	int m_count;
};

class INI
{
public:
	void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
};

class ObjectCreationNugget
{
};

class GenericObjectCreationNugget : public ObjectCreationNugget
{
public:
	GenericObjectCreationNugget();
	static void parseObject(INI *ini, void *instance, void *, const void *);
	static void parseDebris(INI *ini, void *instance, void *, const void *);

protected:
	~GenericObjectCreationNugget();

private:
	char m_pad[0xA8];
	bool m_nameAreObjects; // +0xA8
	char m_tail[0x12C - 0xA8 - 1];
};

class ObjectCreationList
{
public:
	void addObjectCreationNugget(ObjectCreationNugget *nugget);
};

static const FieldParse s_commonFieldParse[] =
{
	{ 0, 0, 0, 0 }
};

static const FieldParse s_objectFieldParse[] =
{
	{ 0, 0, 0, 0 }
};

// ?parseObject@GenericObjectCreationNugget@@SAXPAVINI@@PAX1PBX@Z
void GenericObjectCreationNugget::parseObject(INI *ini, void *instance,
	void *, const void *)
{
	MultiIniFieldParse fields;
	fields.add(s_commonFieldParse);
	fields.add(s_objectFieldParse);

	GenericObjectCreationNugget *nugget = new GenericObjectCreationNugget;
	nugget->m_nameAreObjects = true;

	ini->initFromINIMulti(nugget, fields);
	((ObjectCreationList *)instance)->addObjectCreationNugget(nugget);
}

// Debris table, 0x7E14A8 (the "CreateDebris" row of the OCL FieldParse).
static const FieldParse s_debrisFieldParse[] =
{
	{ 0, 0, 0, 0 }
};

// ?parseDebris@GenericObjectCreationNugget@@SAXPAVINI@@PAX1PBX@Z
// retail 0x001F340A (148 bytes): parseObject's twin with the debris table and
// m_nameAreObjects cleared.
void GenericObjectCreationNugget::parseDebris(INI *ini, void *instance,
	void *, const void *)
{
	MultiIniFieldParse fields;
	fields.add(s_commonFieldParse);
	fields.add(s_debrisFieldParse);

	GenericObjectCreationNugget *nugget = new GenericObjectCreationNugget;
	nugget->m_nameAreObjects = false;

	ini->initFromINIMulti(nugget, fields);
	((ObjectCreationList *)instance)->addObjectCreationNugget(nugget);
}
