// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// ?moveTeamsToNewOwner@TeamsInfoRec@@QAEXABVAsciiString@@0@Z, retail
// 0x0032DB1B, 357 bytes.
//
// Identity (target): WorldBuilder's debug twin TeamsInfoRec::moveTeamsToNewOwner
// (wb 0xa89810, SidesList.cpp asserts 2467..2481) aligns call for call:
// lower_bound on (oldOwner, ""), then per index entry the next iterator, the
// team name copy, insert of (newOwner, teamName) -> id, the teamOwner set on
// every team of the entry's override chain and erase of the old entry.
//
// Layout (target): the index map<pair<AsciiString, AsciiString>, int> at +0x00
// (SidesListTeamsInfoRecClear.cpp) and the 16-byte team entries at +0x0C. The
// asserts name the entry's iterator at +8 (indexIt) and overriddenByID at +6;
// the chain this body walks is the short at +4, which addToIndex 0x0032D103
// links to the previous team of the same key.
//
// Folded callees, each byte-verified from this TU against its own address:
// the index tree's _M_lower_bound 0x0032C4A4, insert_unique 0x0032C4F3,
// _M_insert 0x0032BFE8, _M_create_node 0x0032B62F, the node value _Construct
// 0x0032AF6F and pair copy 0x0032ACB4 are held under the TreeOpaqueMapped0032CB55
// spelling of the same tree (stlport_rb_tree_hint_0032cb55.cpp, whose
// _BFME_RETAIL_TREE_INSERT_LAYOUT this unit shares); erase(iterator) 0x0032B4B2
// is held under an int-keyed tree's name. The int mapped value here is the
// team id this body reads from each entry.

#include <map>
#include <vector>

#include "ascii_string.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

class StaticNameKey
{
public:
	NameKeyType key() const;			// 0x00148F5E
	operator NameKeyType() const { return key(); }

private:
	mutable NameKeyType m_key;
	const char *m_name;
};

extern const StaticNameKey TheKey_teamOwner;	// VA 0x00DBD9FC

class Dict
{
public:
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

class TeamsInfoRec
{
public:
	void moveTeamsToNewOwner(const AsciiString &oldOwner, const AsciiString &newOwner);

private:
	TeamIndex m_index;			// +0x00
	_STL::vector<BfmeThingUBB> m_entries;	// +0x0C
	short m_numActive;
	short m_freeHead;
};

// Every index entry keyed by the old owner is re-keyed to the new one, and
// every team overridden through that entry takes the new owner and iterator.
void TeamsInfoRec::moveTeamsToNewOwner(const AsciiString &oldOwner, const AsciiString &newOwner)
{
	if (newOwner == oldOwner)
		return;
	TeamIndex::iterator end = m_index.end();
	TeamIndex::iterator it = m_index.lower_bound(TeamKey(oldOwner, AsciiString::TheEmptyString));
	while (it != end && (*it).first.first == oldOwner) {
		TeamIndex::iterator next = it;
		++next;
		AsciiString teamName = (*it).first.second;
		int id = (*it).second;
		TeamKey newKey(newOwner, teamName);
		TeamIndex::iterator newIt = m_index.insert(_STL::make_pair(newKey, id)).first;
		for (; id != 0; id = m_entries[id].m_overridesID) {
			BfmeThingUBB &entry = m_entries[id];
			entry.m_dict.setAsciiString(TheKey_teamOwner, newOwner);
			entry.m_indexIt = newIt;
		}
		m_index.erase(it);
		it = next;
	}
}
