// cl: /GX- /DNDEBUG /MD
//
// ?parseFloodMember@@YAXPAVINI@@PAX1PBX@Z, retail 0x0048E022 (125B): the
// FloodMember FieldParse proc (row 0x00C4C9A8). News a zeroed 0x38-byte member
// record (an int then thirteen floats stored through SSE; no unwinding around
// the new), fills it through initFromINI with the table at VA 0x00C4C850 and
// appends the pointer to the int list at instance + 8 (rowed
// list<int>::push_back 0x0005548F), as Rva0048BCBBParse does for its nugget.
//
// ?Rva0041F524_ParseArmyMember@INI@@SAXPAV1@PAX1PBX@Z, retail 0x0041F524
// (75B): the ArmyMemberDefinition FieldParse proc (row 0x00C3B648) of the same
// shape: a zeroed 0x10-byte member (int, three floats), table at VA 0x00C3B000 (ArmyMemberDefinitionFieldParse), and
// the pointer appended to the vector at instance + 4 (4-byte pointer
// push_back fold 0x004DFCB0).

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../Include/Common/INI/FieldParse.h"

class ModuleData;

#include "../../../Include/Common/INI/INI.h"

// Retail's FloodMember field table at RVA 0x0084C850 (.rdata, 112 bytes = six 16-byte records and the zero
// sentinel), transcribed from retail's own bytes; the member record is the 0x38-byte one allocated below.
extern const FieldParse g_00C4C850[] =
{
	{ "MemberTemplateName", INI::parseAsciiString, 0, 0x00 },
	{ "ControlPointOffsetOne", INI::parseCoord3D, 0, 0x04 },
	{ "ControlPointOffsetTwo", INI::parseCoord3D, 0, 0x10 },
	{ "ControlPointOffsetThree", INI::parseCoord3D, 0, 0x1C },
	{ "ControlPointOffsetFour", INI::parseCoord3D, 0, 0x28 },
	{ "MemberSpeed", INI::parseReal, 0, 0x34 },
	{ 0, 0, 0, 0 }
};
// Retail's ArmyMemberDefinition field table at RVA 0x0083B000 (.rdata, 64
// bytes = four records), transcribed from retail's own bytes. Retail has no
// zero sentinel after the fourth record: the token strings follow directly.
extern const FieldParse ArmyMemberDefinitionFieldParse[] =
{
	{ "Unit", INI::parseAsciiString, 0, 0x00 },
	{ "PercentageOfArmyPhase1", INI::parseReal, 0, 0x04 },
	{ "PercentageOfArmyPhase2", INI::parseReal, 0, 0x08 },
	{ "PercentageOfArmyPhase3", INI::parseReal, 0, 0x0C }
};

struct Rva0041F524Member
{
	Rva0041F524Member() : m_00(0), m_04(0.0f), m_percentageOfArmyPhase2(0.0f), m_percentageOfArmyPhase3(0.0f) {}
	int m_00;
	float m_04;
	float m_percentageOfArmyPhase2;
	float m_percentageOfArmyPhase3;
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
		: m_00(0), m_04(0.0f), m_08(0.0f), m_0C(0.0f),
		  m_controlPointOffsetTwo(0.0f), m_controlPointOffsetTwoY(0.0f), m_controlPointOffsetTwoZ(0.0f),
		  m_controlPointOffsetThree(0.0f), m_controlPointOffsetThreeY(0.0f), m_controlPointOffsetThreeZ(0.0f),
		  m_controlPointOffsetFour(0.0f), m_controlPointOffsetFourY(0.0f), m_controlPointOffsetFourZ(0.0f),
		  m_memberSpeed(0.0f)
	{
	}
	int m_00;
	// ControlPointOffsetOne occupies +0x04..+0x0C; these are coordinates.
	float m_04, m_08, m_0C;
	float m_controlPointOffsetTwo, m_controlPointOffsetTwoY, m_controlPointOffsetTwoZ;
	float m_controlPointOffsetThree, m_controlPointOffsetThreeY, m_controlPointOffsetThreeZ;
	float m_controlPointOffsetFour, m_controlPointOffsetFourY, m_controlPointOffsetFourZ;
	float m_memberSpeed;
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

#include <new>

// ?parseFloodMember@@YAXPAVINI@@PAX1PBX@Z
void parseFloodMember(INI *ini, void *instance, void *, const void *)
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
	ini->initFromINI(member, ArmyMemberDefinitionFieldParse);
	((Rva0041F524Army *)instance)->m_members.push_back(*(const ModuleData * const *)&entry);
}
