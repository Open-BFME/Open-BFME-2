// cl: /DNDEBUG /MD /GX-
// Rva0048B97A_InitObject (retail 0x0048B97A, 58 bytes). Builds a
// single-entry MultiIniFieldParse list from the FireWeapon table at
// 0xC4C0C0 (WeaponName, FireDelay, OneShot, Offset) through the rowed
// ctor at 0x002BAA0 and add at 0x002BC6E, then fills the object through
// the pinned INI::initFromINIMulti at 0x002D7A8. The two trailing
// parameters are unread by retail. Serves the FireWeaponNugget entry of
// the table at 0x84C210 together with the parser below.
//
// ?Rva0048BCBBParse@@YAXPAVINI@@PAX1PBX@Z, retail 0x0048BCBB, 86 bytes: the
// FireWeaponNugget FieldParse proc (row 0x00C4C210). News a zeroed 0x18-byte
// nugget (int, int, bool, three floats stored through SSE; no EH under
// /GX-), fills it through Rva0048B97A_InitObject and appends the pointer to
// the int list at instance + 8 (rowed list<int>::push_back 0x0005548F).

struct FieldParse;

extern const int s_fireWeaponNuggetFieldTableA[];
extern const int s_fireWeaponNuggetFieldTableB[];
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

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class list;
template <> class list<int, allocator<int> >
{
public:
	void push_back(const int &x);
private:
	void *m_node;
};
}

struct Rva0048BCBBNugget
{
	Rva0048BCBBNugget() : m_00(0), m_04(0), m_08(false), m_0C(0.0f), m_10(0.0f), m_14(0.0f) {}
	int m_00;
	int m_04;
	bool m_08;
	float m_0C;
	float m_10;
	float m_14;
};

struct Rva0048BCBBOwner
{
	unsigned char m_unreconstructed_00[8];
	_STL::list<int, _STL::allocator<int> > m_nuggets;	// +0x08
};

void *__cdecl operator new(unsigned int size);
void Rva0048B97A_InitObject(INI *ini, void *obj, int, int);

// ?Rva0048B97A_InitObject@@YAXPAVINI@@PAXHH@Z
void Rva0048B97A_InitObject(INI *ini, void *obj, int, int)
{
	MultiIniFieldParse parse;
	parse.add(reinterpret_cast<const FieldParse *>(s_fireWeaponNuggetFieldTableA), 0);
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
	parse.add(reinterpret_cast<const FieldParse *>(s_fireWeaponNuggetFieldTableB), 0);
	ini->initFromINIMulti(obj, parse);
}

// ?Rva0048BCBBParse@@YAXPAVINI@@PAX1PBX@Z
void Rva0048BCBBParse(INI *ini, void *instance, void *, const void *)
{
	Rva0048BCBBNugget *nugget = new Rva0048BCBBNugget;
	Rva0048B97A_InitObject(ini, nugget, 0, 0);
	int entry = (int)nugget;
	((Rva0048BCBBOwner *)instance)->m_nuggets.push_back(entry);
}
