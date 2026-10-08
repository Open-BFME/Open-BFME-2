// cl: /O1 /G7 /arch:SSE /EHsc /Ireference/shims/bfme2_ascii
// stlport
// Team entries: genuine pair<AsciiString, AsciiString> index, 16-byte entry
// vector, two reciprocal short links, Dict, and free-list head.
// Typed views match the already verified SidesListTeamsInfoRecMoveTeams.cpp.

#include <map>

#include <vector>
#include "ascii_string.h"

typedef _STL::pair<AsciiString, AsciiString> TeamKey;
typedef _STL::pair<const TeamKey, int> TeamIndexValue;
typedef _STL::map<TeamKey, int> TeamIndex;
typedef _STL::_Rb_tree<TeamKey, TeamIndexValue, _STL::_Select1st<TeamIndexValue>, _STL::less<TeamKey>, _STL::allocator<TeamIndexValue> > TeamTree;
template<> void TeamTree::erase(TeamTree::iterator);

class Dict { public: void clear(); private: void *m_data; };
struct BfmeIndexedNodeFM
{
	short m_previous;
	short m_next;
	short m_chainNext;
	short m_chainPrevious;
	TeamIndex::iterator m_entry;
	Dict m_extra;
};

class TeamsInfoRec
{
public:
	__declspec(noinline) void removeFromIndex(int index);
	void bfmeRelease(int index);

private:
	TeamIndex m_tree;
	_STL::vector<BfmeIndexedNodeFM> m_nodes;
	short m_count;
	short m_freeHead;
};

// ?bfmeRelease@TeamsInfoRec@@QAEXH@Z
void TeamsInfoRec::bfmeRelease(int index)
{
	removeFromIndex(index);

	BfmeIndexedNodeFM *node = &m_nodes[index];
	node->m_extra.clear();
	m_nodes[node->m_previous].m_next = node->m_next;
	m_nodes[node->m_next].m_previous = node->m_previous;
	short oldFreeHead = m_freeHead;
	--m_count;
	node->m_previous = oldFreeHead;
	m_freeHead = static_cast<short>(index);
}

// Target 0x0032C1F7, 118 bytes. WorldBuilder TeamsInfoRec::removeFromIndex
// at 0x00A888C0 (SidesList.cpp:2285..2316) proves the method and override links.
// The map key and iterator agree with SidesListTeamsInfoRecMoveTeams.cpp;
// replacing the old opaque payload puts the actual team ID in iterator->second.
// Donor provenance: the original BFME 1 indexed-node transfer; target types
// and identity are independently established by the WB twin and matched siblings.
// The separately rowed 0x0032C2C4 outlines removeTeam; the BFME 1-only inline
// clearChainedNodesAt00197860 copy is not a separate BFME 2 recovery.
void TeamsInfoRec::removeFromIndex(int index)
{
	BfmeIndexedNodeFM *node = &m_nodes[index];
	short previous = node->m_chainPrevious;
	if (!previous)
	{
		if (node->m_chainNext)
		{
			node->m_entry->second = node->m_chainNext;
			m_nodes[node->m_chainNext].m_chainPrevious = 0;
		}
		else
		{
			m_tree.erase(node->m_entry);
		}
	}
	else
	{
		m_nodes[previous].m_chainNext = node->m_chainNext;
		if (node->m_chainNext)
			m_nodes[node->m_chainNext].m_chainPrevious = node->m_chainPrevious;
	}
}
