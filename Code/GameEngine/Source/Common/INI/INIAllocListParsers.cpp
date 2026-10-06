// cl: /O1 /GX- /arch:SSE /DNDEBUG /MD
//
// ?Rva0048E022Parse@@YAXPAVINI@@PAX1PBX@Z, retail 0x0048E022 (125B): the
// FloodMember FieldParse proc (row 0x00C4C9A8). News a zeroed 0x38-byte member
// record (an int then thirteen floats stored through SSE; no unwinding around
// the new), fills it through initFromINI with the table at VA 0x00C4C850 and
// appends the pointer to the int list at instance + 8 (rowed
// list<int>::push_back 0x0005548F), as Rva0048BCBBParse does for its nugget.
//
// ?Rva0041F524_ParseArmyMember@INI@@SAXPAV1@PAX1PBX@Z, retail 0x0041F524
// (75B): the ArmyMemberDefinition FieldParse proc (row 0x00C3B648) of the same
// shape: a zeroed 0x10-byte member (int, three floats), table 0x00C3B000, and
// the pointer appended to the vector at instance + 4 (4-byte pointer
// push_back fold 0x004DFCB0).

struct FieldParse;

class ModuleData;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
	static void Rva0041F524_ParseArmyMember(INI *ini, void *instance, void *store, const void *userData);
};

extern const FieldParse g_00C4C850[];
extern const FieldParse g_00C3B000[];

struct Rva0041F524Member
{
	Rva0041F524Member() : m_00(0), m_04(0.0f), m_08(0.0f), m_0C(0.0f) {}
	int m_00;
	float m_04;
	float m_08;
	float m_0C;
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class list;
template <class T, class A> class vector;
template <> class vector<const ModuleData *, allocator<const ModuleData *> >
{
public:
	void push_back(const ModuleData *const &x);
private:
	const ModuleData **m_start;
	const ModuleData **m_finish;
	const ModuleData **m_endOfStorage;
};
template <> class list<int, allocator<int> >
{
public:
	void push_back(const int &x);
private:
	void *m_node;
};
}

struct Rva0048E022Member
{
	Rva0048E022Member()
		: m_00(0), m_04(0.0f), m_08(0.0f), m_0C(0.0f), m_10(0.0f), m_14(0.0f), m_18(0.0f), m_1C(0.0f),
		  m_20(0.0f), m_24(0.0f), m_28(0.0f), m_2C(0.0f), m_30(0.0f), m_34(0.0f)
	{
	}
	int m_00;
	float m_04, m_08, m_0C, m_10, m_14, m_18, m_1C, m_20, m_24, m_28, m_2C, m_30, m_34;
};

struct Rva0048E022Owner
{
	unsigned char m_unreconstructed_00[8];
	_STL::list<int, _STL::allocator<int> > m_members;	// +0x08
};

struct Rva0041F524Army
{
	unsigned char m_unreconstructed_00[4];
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_members;	// +0x04
};

void *__cdecl operator new(unsigned int size);

// ?Rva0048E022Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva0048E022Parse(INI *ini, void *instance, void *, const void *)
{
	Rva0048E022Member *member = new Rva0048E022Member;
	int entry = (int)member;
	ini->initFromINI(member, g_00C4C850);
	((Rva0048E022Owner *)instance)->m_members.push_back(entry);
}

// ?Rva0041F524_ParseArmyMember@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva0041F524_ParseArmyMember(INI *ini, void *instance, void *, const void *)
{
	Rva0041F524Member *member = new Rva0041F524Member;
	const Rva0041F524Member *entry = member;
	ini->initFromINI(member, g_00C3B000);
	((Rva0041F524Army *)instance)->m_members.push_back(*(const ModuleData * const *)&entry);
}
