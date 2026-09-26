// cl: /O1 /DNDEBUG /MD /GX- /arch:SSE
// Rva0048B97A_InitObject (retail 0x0048B97A, 58 bytes). Builds a
// single-entry MultiIniFieldParse list from the FireWeapon table at
// 0xC4C0C0 (WeaponName, FireDelay, OneShot, Offset) through the rowed
// ctor at 0x002BAA0 and add at 0x002BC6E, then fills the object through
// the pinned INI::initFromINIMulti at 0x002D7A8. The two trailing
// parameters are unread by retail. Serves the FireWeaponNugget entry of
// the table at 0x84C210 together with the parser below.

struct FieldParse;

class MultiIniFieldParse
{
	const void *m_fieldParse[16];
	unsigned m_extraOffset[16];
	int m_count;

public:
	MultiIniFieldParse();
	void add(const FieldParse *fields, unsigned extraOffset);
};

class INI
{
public:
	void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
};

// ?Rva0048B97A_InitObject@@YAXPAVINI@@PAXHH@Z
void Rva0048B97A_InitObject(INI *ini, void *obj, int, int)
{
	MultiIniFieldParse parse;
	parse.add(reinterpret_cast<const FieldParse *>(0x00C4C0C0), 0);
	ini->initFromINIMulti(obj, parse);
}

// ?Rva0049CBA0_InitObject@@YAXPAVINI@@PAXHH@Z, retail 0x0049CBA0, 58 bytes.
// Same recipe as Rva0048B97A_InitObject above: single-entry parse list from
// the table at 0x00C51380 through rowed ctor 0x002BAA0 and rowed add
// 0x002BC6E, then pinned INI::initFromINIMulti 0x002D7A8. Trailing params
// unread. Sole caller at 0x0049DEA5 (news 0x14 plus ctor 0x0049D7B3, then
// list push_back 0x0005548F).
void Rva0049CBA0_InitObject(INI *ini, void *obj, int, int)
{
	MultiIniFieldParse parse;
	parse.add(reinterpret_cast<const FieldParse *>(0x00C51380), 0);
	ini->initFromINIMulti(obj, parse);
}
