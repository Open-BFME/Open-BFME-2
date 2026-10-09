// cl: /O1 /G6 /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva004FD1BC@@UAE@XZ retail 0x004FD1BC..0x004FD37F (451 bytes) under the
// pinned address-derived spelling. Identity: the destructor of
// LivingWorldScenario::Scenario. Its scalar deleting destructor 0x004FD85E is
// the only slot of vtable 0x00C63564; the five pointer vectors at +0x74..+0xA4
// are the condition lists the rowed Scenario members fill (addTeamDefeatCondition
// 0x004FD3E2 pushes to +0x80 and inserts into the multimap at +0x5C;
// addTeamVictoryCondition 0x004FD448 uses +0x8C and +0x68; 0x004FD37F uses
// +0x74 and +0x50) and the vector of default start region names at +0x44 is the
// one getDefaultStartSpots 0x004FD8B8 reads. The body deletes each list entry
// through the folded for_each 0x0059E2DC with a one-byte delete functor (its
// call operator folds with W3DFileSystem::Return_File 0x004FC957); members then
// unwind in reverse: five pointer vectors freed inline; three multimaps by their
// rowed tree destructors 0x004FCC48/0x004FCC80/0x004FCCB8; three AsciiString
// vectors by the rowed vector destructor 0x0002CC70; eight AsciiStrings through
// releaseBuffer 0x00036410 (ints sit at +0x20 and +0x24).
// WorldBuilder twin 0x130D660 (1248 bytes) has the same five for_each loops.
// The condition pointer lists are viewed as vector<int>: retail unwinds them
// through the folded vector<int> destructor 0x0007FAB3 and the loops pass
// their bounds to the FileClass-typed for_each placeholder.
#include "ascii_string.h"
#include <vector>

class FileClass;

// The one-byte delete functor for_each receives by value.
struct Rva0059E2DCBox
{
};

bool __cdecl rva0059E2DC(FileClass **first, FileClass **last, Rva0059E2DCBox box);

// Placeholder-named multimap<int and int> holders with rowed destructors.
class Rva004FCA9C
{
public:
	~Rva004FCA9C();
	void *m_header;
	int m_nodeCount;
	int m_compare;
};

class Rva004FCAC9
{
public:
	~Rva004FCAC9();
	void *m_header;
	int m_nodeCount;
	int m_compare;
};

class Rva004FCAF6
{
public:
	~Rva004FCAF6();
	void *m_header;
	int m_nodeCount;
	int m_compare;
};

// The multimap members: their implicit destructors (retail 0x004FCD5E,
// 0x004FCD63 and 0x004FCD68, each a jmp to the tree destructor) are what the
// unwind funclets call, while the destructor body expands them inline.
class Rva004FCD5E
{
public:
	Rva004FCA9C m_tree;
};

class Rva004FCD63
{
public:
	Rva004FCAC9 m_tree;
};

class Rva004FCD68
{
public:
	Rva004FCAF6 m_tree;
};

class Rva004FD1BC
{
public:
	virtual ~Rva004FD1BC();

	AsciiString m_name;										///< +0x04
	AsciiString m_08;										///< +0x08
	AsciiString m_0C;										///< +0x0C
	AsciiString m_10;										///< +0x10
	AsciiString m_14;										///< +0x14
	AsciiString m_18;										///< +0x18
	AsciiString m_1C;										///< +0x1C
	int m_20;												///< +0x20
	int m_24;												///< +0x24
	AsciiString m_28;										///< +0x28
	_STL::vector<AsciiString> m_2C;							///< +0x2C
	_STL::vector<AsciiString> m_38;							///< +0x38
	_STL::vector<AsciiString> m_defaultStartRegions;		///< +0x44
	Rva004FCD5E m_playerDefeatMap;							///< +0x50
	Rva004FCD63 m_teamDefeatMap;							///< +0x5C
	Rva004FCD68 m_teamVictoryMap;							///< +0x68
	_STL::vector<int> m_playerDefeats;				///< +0x74
	_STL::vector<int> m_teamDefeats;				///< +0x80
	_STL::vector<int> m_teamVictories;				///< +0x8C
	_STL::vector<int> m_98;							///< +0x98
	_STL::vector<int> m_A4;							///< +0xA4
};

Rva004FD1BC::~Rva004FD1BC()
{
	rva0059E2DC((FileClass **)m_playerDefeats.begin(), (FileClass **)m_playerDefeats.end(), Rva0059E2DCBox());
	rva0059E2DC((FileClass **)m_teamDefeats.begin(), (FileClass **)m_teamDefeats.end(), Rva0059E2DCBox());
	rva0059E2DC((FileClass **)m_teamVictories.begin(), (FileClass **)m_teamVictories.end(), Rva0059E2DCBox());
	rva0059E2DC((FileClass **)m_98.begin(), (FileClass **)m_98.end(), Rva0059E2DCBox());
	rva0059E2DC((FileClass **)m_A4.begin(), (FileClass **)m_A4.end(), Rva0059E2DCBox());
}
