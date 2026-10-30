// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// ??1GameTextTable@@QAE@XZ 0x002E6158 44B
// Evidence: chain from 0x002E5E5A vector dtor; scalar dtor over +4 Rva002E5791 array via delete[] then +8 trivial array via vector delete; callers 0x002E6415 0x002E6551 0x002E6303.
#include "ascii_string.h"
#include "unicode_string.h"
#include <new>

class Rva002E5791
{
public:
	~Rva002E5791();

private:
	StringBase<char> m_narrow;
	StringBase<unsigned short> m_wide;
};

typedef bool Bool;
struct StringInfo;
struct StringLookUp;

class GameTextTable
{
public:
	GameTextTable() : m_count(0), m_info(0), m_lookup(0) {}
	~GameTextTable();
	Bool load(const char *strFile, const char *csfFile, Bool *usedCSF);
	// Compiler-only receiver read for the inactive EH state in load.
	unsigned dormantCount() const { return m_count; }
	Bool readSTR(const char *filename);
	Bool readCSF(const char *filename);

	unsigned int m_count;	// +0x00
	StringInfo *m_info;		// +0x04
	StringLookUp *m_lookup;	// +0x08
};

GameTextTable::~GameTextTable()
{
	if (m_info)
	{
		delete[] reinterpret_cast<Rva002E5791 *>(m_info);
		m_info = 0;
	}
	if (m_lookup)
	{
		delete[] reinterpret_cast<char *>(m_lookup);
		m_lookup = 0;
	}
	m_count = 0;
}
