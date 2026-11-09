// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Native 0x0032D9A4..0x0032DA4E (170B RET4). BfmeConv1768.cpp's
// matched TeamsInfoRec assignment constructs this 28-byte temporary before
// swapping it into its destination. The existing SidesList TeamsInfoRec
// providers prove the map<pair<AsciiString,AsciiString>,int> at 0, 16-byte
// team records at 0xC and free/active shorts at 0x18/0x1A.
// Copy the records and rebuild their iterators against the newly inserted
// index nodes, following each entry's override link at +4. Retail stores
// the iterator before reading that link and reloads the vector base.
// ZH's flat-array copy constructor is not this BFME2 implementation.
// Derived from the complete bank reverse/attempts/0x0032d9a4.cpp;
// no narrowed index or assume-no-alias flag is needed.
// The five rowed STLport providers emitted here have complete native bodies
// and relocations equal to their existing folded owners; no symbol pins.

#include <map>
#include <vector>

#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<pair<AsciiString, AsciiString>, pair<pair<AsciiString, AsciiString> const, int>, _Select1st<pair<pair<AsciiString, AsciiString> const, int> >, less<pair<AsciiString, AsciiString> >, allocator<pair<pair<AsciiString, AsciiString> const, int> > >::~_Rb_tree(); }
// bfme link decl-only end

class Dict
{
public:
	// A copy shares the pair data and takes a reference, as retail's team
	// record copy 0x0032A304 does (inc word ptr [data]); without it, growing
	// the team vector freed data the new records still held (P106).
	Dict(const Dict &src) : m_data(src.m_data)
	{
		if (m_data)
			++*(unsigned short *)m_data;
	}
	~Dict() { releaseData(); }
	void setAsciiString(int key, const AsciiString &value);	// 0x0031375A

private:
	void releaseData();
	void *m_data;
};

typedef _STL::pair<AsciiString, AsciiString> TeamKey;
typedef _STL::map<TeamKey, int> TeamIndex;

class BfmeThingUBB
{
public:
	BfmeThingUBB();
	short m_next;
	short m_previous;
	short m_overridesID;		// +4
	short m_overriddenByID;		// +6
	TeamIndex::iterator m_indexIt;	// +8
	Dict m_dict;			// +0xC
};

// The shared team-vector destructor is already owned at 0x0032C3A3.
// Keep teardown out of line so this TU uses that provider during unwinding.
namespace _STL {
template <> vector<BfmeThingUBB>::~vector();
}

class TeamsInfoRec
{
public:
	TeamsInfoRec(const TeamsInfoRec &other);
	void renameTeam(int id, const AsciiString &owner, const AsciiString &name);
	void moveTeamsToNewOwner(const AsciiString &oldOwner, const AsciiString &newOwner);
	void bfmePrepareRelease(int id);	// 0x0032C1F7, WB removeFromIndex
	void addToIndex(int id);	// 0x0032D103

private:
	TeamIndex m_index;			// +0x00
	_STL::vector<BfmeThingUBB> m_entries;	// +0x0C
	short m_numActive;
	short m_freeHead;
};

TeamsInfoRec::TeamsInfoRec(const TeamsInfoRec &other)
    : m_entries(other.m_entries),
      m_numActive(other.m_numActive), m_freeHead(other.m_freeHead)
{
    TeamIndex::iterator hint = m_index.begin();
    TeamIndex::const_iterator end = other.m_index.end();
    for (TeamIndex::const_iterator it = other.m_index.begin(); it != end; ++it) {
        TeamIndex::iterator inserted = m_index.insert(hint, *it);
        int id = inserted->second;
        for (; id != 0; id = m_entries[id].m_overridesID)
            m_entries[id].m_indexIt = inserted;
        hint = inserted;
    }
}
