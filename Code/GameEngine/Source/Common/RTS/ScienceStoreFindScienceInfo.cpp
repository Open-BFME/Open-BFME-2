// cl: /O1 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f ScienceStoreFriendGetScienceNames semantic donor.
// Retail1FFCA3..1FFD2C keeps the donor's name-collection purpose and loop.
// Native: ScienceStore vector+C/+10, ScienceInfo key+10, override pointer+4;
// keyToName148C95 returns a reference, so BFME2 constructs no string temporary.
// Return vector copyBC07E and cleanup2CC70 are existing verified providers.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include <map>
#include <vector>
#include "ascii_string.h"

// Retail already provides these concrete string-vector operations. Declare
// them here so this caller uses those providers with their established ABI.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> > &);
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString &);
}

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

typedef _STL::pair<const ScienceType, bool> ScienceMemoValue;
typedef _STL::_Rb_tree<ScienceType, ScienceMemoValue, _STL::_Select1st<ScienceMemoValue>, _STL::less<ScienceType>, _STL::allocator<ScienceMemoValue> > ScienceMemoTree;
namespace _STL {
template <> map<ScienceType, bool>::map();
template <> void ScienceMemoTree::clear();
template <> _Rb_tree_base<ScienceMemoValue, allocator<ScienceMemoValue> >::~_Rb_tree_base();
template <> ScienceType *vector<ScienceType, allocator<ScienceType> >::erase(ScienceType *, ScienceType *);
template <> void vector<ScienceType, allocator<ScienceType> >::push_back(const ScienceType &);
// Canonical emitted cleanup and existing map ctor must stay out of line.
template <> ScienceMemoTree::~_Rb_tree();
// The concrete memo insertion provider is already byte-verified at1FF875.
template <> pair<ScienceMemoTree::iterator, bool> ScienceMemoTree::insert_unique(const ScienceMemoValue &);
}

class NameKeyGenerator
{
public:
	const AsciiString &keyToName( NameKeyType key );
};

extern NameKeyGenerator *TheNameKeyGenerator;

// Retail next-override hop uses the established address-derived view at1E35DF.
// The donor calls this base Overridable; the target spelling remains unproven.
class Rva001E35DFView
{
public:
	const Rva001E35DFView *getFinalOverride( void ) const
	{
		if ( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

public:
	void *m_unmodelled00;
	Rva001E35DFView *m_nextOverride;
	bool m_isOverride;
};

// Preserve the existing wrapper's opaque parameter spelling. No Player
// layout is asserted here; native only exposes the virtual science-query ABI.
class Player;
class Rva0043D3A8 {
public:
    virtual bool v00(ScienceType science) const;
};

class ScienceInfo : public Rva001E35DFView
{
public:
	Int m_unmodelled0c;
	ScienceType m_science;
	char m_nameAndDescription[8];
	std::vector<std::vector<ScienceType> > m_prereqGroups;
};

typedef std::vector<ScienceInfo *> ScienceInfoVec;

class ScienceStore
{
public:
	std::vector<AsciiString> friend_getScienceNames() const;
	bool playerHasPrereqsForScience(const Rva0043D3A8 *holder, ScienceType st) const;
	int getSciencePurchaseCost(ScienceType) const;
	void getPurchasableSciences(const Player *, std::vector<ScienceType> &, std::vector<ScienceType> &) const;
private:
	const ScienceInfo *findScienceInfo(ScienceType st) const;
	bool rva000E7C20SciencePrereqMemo(const Player *opaqueQuery, ScienceType st, void *memo) const;

private:
	void *m_unmodelled00;
	Int m_unmodelled04;
	Int m_unmodelled08;
	ScienceInfoVec m_sciences;
};

std::vector<AsciiString> ScienceStore::friend_getScienceNames() const
{
	std::vector<AsciiString> v;
	for ( ScienceInfoVec::const_iterator it = m_sciences.begin(); it != m_sciences.end(); ++it )
	{
		const ScienceInfo *si = (const ScienceInfo *)( *it )->getFinalOverride();
		NameKeyType nk = (NameKeyType)( si->m_science );
		v.push_back( TheNameKeyGenerator->keyToName( nk ) );
	}
	return v;
}

// Existing 47-byte lookup keeps the same null-guarded native override hop.
const ScienceInfo *ScienceStore::findScienceInfo(ScienceType st) const
{
    ScienceInfo *const *begin = m_sciences.begin();
    ScienceInfo *const *end = m_sciences.end();
    for (ScienceInfo *const *it = begin; it != end; ++it) {
        const ScienceInfo *si = (const ScienceInfo *)(*it)->getFinalOverride();
        if (si->m_science == st)
            return si;
    }
    return 0;
}

// BFME1 Science.cpp nested prerequisite groups guide; retail1FF47D..1FF4D3
// tests each group through the holder's virtual slot0 and accepts any full group.
bool ScienceStore::playerHasPrereqsForScience(const Rva0043D3A8 *holder, ScienceType st) const
{
    const ScienceInfo *si = findScienceInfo(st);
    if (si) {
        if (si->m_prereqGroups.size() == 0)
            return true;
        for (std::vector<std::vector<ScienceType> >::const_iterator g = si->m_prereqGroups.begin(); g != si->m_prereqGroups.end(); ++g) {
            for (std::vector<ScienceType>::const_iterator p = g->begin();; ++p) {
                if (p == g->end())
                    return true;
                // Native captures the science key before reading the holder vtable.
                // Keep that evaluation order without runtime instructions.
                ScienceType key = *p;
                _ReadWriteBarrier();
                if (!holder->v00(key))
                    break;
            }
        }
    }
    return false;
}

// Native1FFAA1..1FFB64 memoizes the recursive ANY-group/ALL-key predicate.
// Its virtual query uses the same slot0 ABI witnessed in1FF47D. The original
// callback-interface and private-helper spellings remain unproven.
bool ScienceStore::rva000E7C20SciencePrereqMemo(const Player *opaqueQuery, ScienceType st,
	void *memo) const
{
	const Rva0043D3A8 *holder = reinterpret_cast<const Rva0043D3A8 *>(opaqueQuery);
	std::map<ScienceType, bool> *values = (std::map<ScienceType, bool> *)memo;
	std::map<ScienceType, bool>::iterator found = values->find(st);
	if (found._M_node != values->end()._M_node)
		return found->second;

	bool result;
	if (holder->v00(st))
	{
		result = true;
	}
		else
		{
			result = false;
			const ScienceInfo *science = findScienceInfo(st);
			if (science)
			{
			int numGroups = science->m_prereqGroups.size();
			result = (numGroups == 0);
				for (std::vector<std::vector<ScienceType> >::const_iterator group = science->m_prereqGroups.begin();
					group != science->m_prereqGroups.end(); ++group)
				{
					std::vector<ScienceType>::const_iterator item = group->begin();
					if (item == group->end())
						goto group_satisfied;
					do
					{
						if (!rva000E7C20SciencePrereqMemo(opaqueQuery, *item, memo))
							goto next_group;
						++item;
					} while (item != group->end());
group_satisfied:
					result = true;
next_group:
					if (result)
						break;
				}
			}
		}

	values->insert(std::make_pair(st, result));
	return result;
}

void ScienceStore::getPurchasableSciences(const Player *player, std::vector<ScienceType> &purchasable,
    std::vector<ScienceType> &potentiallyPurchasable) const
{
    std::map<ScienceType, bool> memo;
    purchasable.erase(purchasable.begin(), purchasable.end());
    potentiallyPurchasable.erase(potentiallyPurchasable.begin(), potentiallyPurchasable.end());
    const Rva0043D3A8 *holder = reinterpret_cast<const Rva0043D3A8 *>(player);
    for (ScienceInfoVec::const_iterator it = m_sciences.begin(); it != m_sciences.end(); ++it) {
        const ScienceInfo *si = (const ScienceInfo *)(*it)->getFinalOverride();
        if (!getSciencePurchaseCost(si->m_science))
            continue;
        ScienceType key = si->m_science;
        _ReadWriteBarrier();
        if (holder->v00(key))
            continue;
        if (playerHasPrereqsForScience(holder, si->m_science))
            purchasable.push_back(si->m_science);
        else if (rva000E7C20SciencePrereqMemo(player, si->m_science, &memo))
            potentiallyPurchasable.push_back(si->m_science);
    }
}

// Native pooled teardown1FF55F uses only node links. Reuse that verified
// operation; its address-derived view does not assert an original class name.
struct Rva001FF6D7Node;
class Rva001FF6D7 {
public:
    void rva001FF55F(Rva001FF6D7Node *);
};
// Native base cleanup pushes the header into the pool's free-node head.
#include "../../../Include/Common/Rva002E8548Pool.h"
namespace _STL {
template <> void ScienceMemoTree::clear() {
    if (_M_node_count != 0) {
        reinterpret_cast<Rva001FF6D7 *>(this)->rva001FF55F(reinterpret_cast<Rva001FF6D7Node *>(_M_root()));
        _M_leftmost() = _M_header._M_data;
        _M_root() = 0;
        _M_rightmost() = _M_header._M_data;
        _M_node_count = 0;
    }
}
template <> _Rb_tree_base<ScienceMemoValue, allocator<ScienceMemoValue> >::~_Rb_tree_base() {
    void *node = _M_header._M_data;
    if (node) {
        *reinterpret_cast<void **>(node) = g_Va00DB9440.m_head;
        g_Va00DB9440.m_head = node;
    }
}
}

namespace _STL {
template <> ScienceMemoTree::~_Rb_tree() { clear(); }
}
