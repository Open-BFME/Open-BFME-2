// cl: /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /DNDEBUG /MD /GX- /O2 /Ob2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// platformsdk
// stlport
//
// Add_Prototype thin wrapper (BFME1 Add_Prototype.cpp pattern).
// Null-check the global resource enumerator at VA 0x00E09C0C,
// then thiscall into Add_Prototype_Impl at 0x00621710.
//
// The enumerator itself lives here too: Begin (retail 0x00621480, 69 bytes)
// snapshots the prototype registry's hash table under the enumerator lock,
// entering the critical section at +0x34, copying the begin() iterator of
// the int->int table at +0x4C into the +0x60/+0x64 cursor, recording the
// tag at +0x1F0 and leaving the lock. The table is stlport's raw hashtable
// (retail calls hashtable::begin at 0x00620A80 directly).

#include <hash_map>
#include <windows.h>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> void hashtable<pair<int const, int>, int, hash<int>, _Select1st<pair<int const, int> >, equal_to<int>, allocator<pair<int const, int> > >::resize(unsigned int); }
// bfme link decl-only end

typedef _STL::hashtable<_STL::pair<const int, int>, int, _STL::hash<int>,
	_STL::_Select1st<_STL::pair<const int, int> >, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, int> > > BfmePrototypeTable;

typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, int> > > BfmePrototypeMap;

// The iterator equality test is always inlined in the bodies below; keep the
// unit from emitting its own out-of-line, non-retail copy.
namespace _STL {
typedef _Ht_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> >, int,
	hash<int>, _Select1st<pair<const int, int> >, equal_to<int>,
	allocator<pair<const int, int> > > BfmePrototypeIterator;
template <> __declspec(dllimport) __forceinline
bool operator==(const BfmePrototypeIterator &__x, const BfmePrototypeIterator &__y)
{ return __x._M_cur == __y._M_cur; }
}

// String-interning name table holding the 45007-bucket registry that
// Add_Prototype_Impl queries. Retail 0x00620500 (187B) hashes the name
// case-insensitively (tolower fold, times 33), buckets via div 0xAFCF,
// compares with strcmp and allocates 12-byte nodes via operator new;
// it returns the interned integer ID, or 0 for a null name.
enum NameKeyType
{
    NAMEKEY_INVALID = 0,
    NAMEKEY_MAX = 1 << 23,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

#include "../../../../GameEngine/Include/Common/NameKeyGenerator.h"

// Prototype template handed to Add_Prototype_Impl. The allocating caller
// (Create_Rva00972880_Prototype at 0x00181130) builds a 20-byte
// GenBase-derived object, installs vtable 0xBD5090 whose slot 0 returns
// the "NULL" name, then forwards here. Retail proves three members:
// the vptr, a 16-bit reference count at +4 (inc word) and the interned
// integer ID at +8.
struct BfmeAddedPrototype
{
	virtual const char *GetPrototypeName() const;
	short m_referenceCount; // +4
	short m_padding06; // +6: aligns m_prototypeId
	int m_prototypeId; // +8
};

// Raw-critical-section RAII guard. The constructor stores the section
// pointer then enters it; the destructor leaves it. Normal paths inline
// both to direct Enter/Leave imports while the stored pointer plus the
// EH state drive the out-of-line unwind that leaves on throw.
struct BfmeCriticalSectionGuard
{
	CRITICAL_SECTION *m_guardedSection;
	BfmeCriticalSectionGuard(CRITICAL_SECTION *section) : m_guardedSection(section)
	{
		EnterCriticalSection(section);
	}
	~BfmeCriticalSectionGuard()
	{
		LeaveCriticalSection(m_guardedSection);
	}
};

#include "../../../Include/W3DDevice/GameClient/BfmeResourceEnumerator.h"

extern class Q1Receiver0134FAAC *TheQ1Receiver;

// ?Add_Prototype@@YAXPAX@Z
void Add_Prototype(void *prototype)
{
	if (((BfmeResourceEnumerator *)TheQ1Receiver))
		((BfmeResourceEnumerator *)TheQ1Receiver)->Add_Prototype_Impl(prototype);
}

void BfmeResourceEnumerator::Begin(unsigned tag)
{
	EnterCriticalSection(&m_lock);
	BfmePrototypeTable::iterator iter = m_prototypes.begin();
	m_cachedNode = iter._M_cur;
	m_cachedTable = iter._M_ht;
	m_tag = tag;
	LeaveCriticalSection(&m_lock);
}

// ?Add_Prototype_Impl@BfmeResourceEnumerator@@QAEXPAX@Z
void BfmeResourceEnumerator::Add_Prototype_Impl(void *prototype)
{
	BfmeAddedPrototype *addedPrototype = (BfmeAddedPrototype *)prototype;
	if (!addedPrototype)
		return;
	BfmeCriticalSectionGuard registryGuard(&m_lock);
	const char *prototypeName = addedPrototype->GetPrototypeName();
	int prototypeId = m_nameTable->nameToLowercaseKey(prototypeName);
	if (prototypeId == 0)
		return;
	BfmePrototypeTable::iterator foundIter = m_prototypes.find(prototypeId);
	if (foundIter._M_cur != 0)
		return;
	++addedPrototype->m_referenceCount;
	BfmePrototypeMap &prototypeMap = (BfmePrototypeMap &)m_prototypes;
	prototypeMap[prototypeId] = (int)addedPrototype;
	addedPrototype->m_prototypeId = prototypeId;
	BfmePrototypeTable::iterator beginIter = m_prototypes.begin();
	m_cachedNode = beginIter._M_cur;
	m_cachedTable = beginIter._M_ht;
}
