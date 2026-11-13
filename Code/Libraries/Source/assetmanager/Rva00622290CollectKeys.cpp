// cl: /O2 /G6 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/sweep
// stlport
// AssetManagerImpl::LoadAsset, retail RVA 0x00623600..0x006240DC (2780 B).
// WB 0x0167B5C0 names the method; retail owns the layouts, phase chain,
// wait protocol, profiling globals and seven-entry phase table at 0x006240C0.
// Adapted from the BFME 1 phase-machine donor at 0x009F0FA0; the element
// keeps its established opaque name because its original class is unproven.
// Resumes the compiler-matched bank and its independent frame/volatile-field
// findings: reverse/attempt_support/0x00623600-loadasset-20261020-w3.md and
// reverse/attempt_support/0x00623600-loadasset-20261020-w5.md.
#define _STLP_USE_MALLOC 1
#define _STLP_NO_CSTD_FUNCTION_IMPORTS 1
namespace _STL { void __cdecl free(void *); }

#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <deque>
#include <hash_map>
#include <map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>


// ?collectKeys@Rva00622290@@QAE?AURva00622290SetGroup@@XZ
// cl: /O2 /G6 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/sweep
// stlport
// Donor: Open-BFME-1 575ba2b04743 AssetRegistryKeySet009EF7D0.cpp.
// Donor supplies the lock/collect/copy algorithm; its original registry name
// and globals do not establish this target receiver's original identity.
// Native622290..6223BB RET4: lock+34; hash table+4C; iterator620A80;
// integer keys at node+4; insertion422047; returned tree copy620CA0.
// The local/returned group is20B, with count+0C=0 and flag+10=1.
// Existing pointer-set ABI serves the scalar-key insert/destruction callees;
// the return copies through the independently recovered set<int> tree.
// G6 preserves native hash bucket iteration loads and INC scheduling.

#define _STLP_USE_STATIC_LIB 1

#include <hash_map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>

#include <cstddef>
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@HHU?$_Identity@H@_STL@@U?$less@H@2@V?$allocator@H@2@@_STL@@AAEXPAU?$_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _Rb_tree<int,int,_Identity<int>,less<int>,allocator<int> >::_M_erase(_Rb_tree_node<int> *); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@PAURva001408C0Target@@V?$allocator@PAURva001408C0Target@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_base<Rva001408C0Target *,allocator<Rva001408C0Target *> >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEXPAU?$_Rb_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> void allocator<_Rb_tree_node<Rva001408C0Target *> >::deallocate(_Rb_tree_node<Rva001408C0Target *> *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *_Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::_M_create_node(Rva001408C0Target *const &); }
// Suppress this TU's non-retail copy of ?_M_insert@?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::iterator _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *, Rva001408C0Target *const &, _Rb_tree_node_base *); }

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;
typedef _STL::_Rb_tree<Rva001408C0Key,Rva001408C0Key,_STL::_Identity<Rva001408C0Key>,_STL::less<Rva001408C0Key>,_STL::allocator<Rva001408C0Key> > PointerTree;
typedef _STL::_Rb_tree<int,int,_STL::_Identity<int>,_STL::less<int>,_STL::allocator<int> > IntSetTreeCopyView;
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<Rva001408C0Target *> *allocator<_Rb_tree_node<Rva001408C0Target *> >::allocate(size_t __n, const void *) const {
    return __n != 0 ? reinterpret_cast<value_type *>(allocator<char>::allocate(__n * sizeof(value_type), 0)) : 0;
}
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<Rva001408C0Target *> *_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Target *> *, _Rb_tree_node<Rva001408C0Target *>, allocator<_Rb_tree_node<Rva001408C0Target *> > >::allocate(size_t __n) {
    return __stl_alloc_rebind(static_cast<_Base &>(*this), (_Rb_tree_node<Rva001408C0Target *> *)0).allocate(__n, 0);
}
template <> __declspec(dllimport) __forceinline
void IntSetTreeCopyView::clear() {
    if (_M_node_count != 0) {
        _M_erase(_M_root());
        _M_leftmost() = this->_M_header._M_data;
        _M_root() = 0;
        _M_rightmost() = this->_M_header._M_data;
        _M_node_count = 0;
    }
}

}

namespace _STL {
template<> PointerTree::~_Rb_tree();
template<> IntSetTreeCopyView::~_Rb_tree();
template<> IntSetTreeCopyView::_Rb_tree(const IntSetTreeCopyView&);
template<> pair<Rva001408C0Set::iterator, bool> Rva001408C0Set::insert(const Rva001408C0Key &);
template<> pair<PointerTree::iterator, bool> PointerTree::insert_unique(const Rva001408C0Key &);
}
// The out-of-line set::insert (0x00080691) and insert_unique (0x00422047) are other
// units' retail copies; this TU's /G6 builds of them differ, so both are declared only.
// insertKeyInline is set::insert's own STLport body for the call sites retail inlines.
static __forceinline _STL::pair<Rva001408C0Set::iterator, bool>
insertKeyInline(Rva001408C0Set &keys, const Rva001408C0Key &x)
{
	_STL::pair<PointerTree::iterator, bool> p = ((PointerTree &)keys).insert_unique(x);
	return _STL::pair<Rva001408C0Set::iterator, bool>(reinterpret_cast<const Rva001408C0Set::iterator &>(p.first), p.second);
}

// Keep STLport's pointer-set construction inline without competing external copies.
namespace _STL {
typedef _Rb_tree<Rva001408C0Key, Rva001408C0Key, _Identity<Rva001408C0Key>,
    less<Rva001408C0Key>, allocator<Rva001408C0Key> > AssetPointerLinkTree;
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Key> *, _Rb_tree_node<Rva001408C0Key>, allocator<_Rb_tree_node<Rva001408C0Key> > >::_STLP_alloc_proxy(
    const allocator<_Rb_tree_node<Rva001408C0Key> > &__a, _Rb_tree_node<Rva001408C0Key> *__p)
    : allocator<_Rb_tree_node<Rva001408C0Key> >(__a), _M_data(__p) {}
template <> __declspec(dllimport) __forceinline
_Rb_tree_base<Rva001408C0Key, allocator<Rva001408C0Key> >::_Rb_tree_base(const allocator_type &__a)
    : _M_header(_STLP_CONVERT_ALLOCATOR(__a, _Node), (_Node *)0)
{ _M_header._M_data = _M_header.allocate(1); }
// ?AssetPointerLinkTree::_M_empty_initialize present-unmatched
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
void AssetPointerLinkTree::_M_empty_initialize()
{
    _S_color(this->_M_header._M_data) = _S_rb_tree_red;
    _M_root() = 0;
    _M_leftmost() = this->_M_header._M_data;
    _M_rightmost() = this->_M_header._M_data;
}
// ?AssetPointerLinkTree::_Rb_tree present-unmatched
template <> __declspec(dllimport) __forceinline
AssetPointerLinkTree::_Rb_tree(const less<Rva001408C0Key> &__comp, const allocator_type &__a)
    : _Rb_tree_base<Rva001408C0Key, allocator<Rva001408C0Key> >(__a),
      _M_node_count(0), _M_key_compare(__comp)
{ _M_empty_initialize(); }
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
set<Rva001408C0Key>::set() : _M_t(less<Rva001408C0Key>(), allocator<Rva001408C0Key>()) {}
}

struct Rva00622290SetGroup
{
	IntSetTreeCopyView m_tree;
	unsigned int m_count;
	bool m_active;
	unsigned char m_padding[3];

	explicit Rva00622290SetGroup(const IntSetTreeCopyView &tree)
		: m_tree(tree)
	{
		clear();
	}

	void clear()
	{
		m_count = 0;
		m_active = true;
	}
};

struct Q1ReceiverLocalSet
{
	Rva001408C0Set m_tree;
	unsigned int m_count;
	bool m_active;
	unsigned char m_padding[3];

	__forceinline Q1ReceiverLocalSet() { clear(); }

	void clear()
	{
		m_count = 0;
		m_active = true;
	}
};

typedef _STL::hash_map<int, int> ScalarHashMap622290;

class Q1ReceiverLockGuard
{
public:
	explicit Q1ReceiverLockGuard(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
	}
	~Q1ReceiverLockGuard()
	{
		LeaveCriticalSection(m_lock);
	}

	CRITICAL_SECTION *m_lock;
};

class Rva00622290
{
public:
	Rva00622290SetGroup collectKeys();

private:
	unsigned char m_unmodelled_000[0x34];
	CRITICAL_SECTION m_lock34;
	ScalarHashMap622290 m_map4c;
};

Rva00622290SetGroup Rva00622290::collectKeys()
{
	Q1ReceiverLockGuard lock(&m_lock34);
	Q1ReceiverLocalSet keys;
	ScalarHashMap622290::iterator it;
	for (it = m_map4c.begin(); it != m_map4c.end(); ++it)
	{
		insertKeyInline(keys.m_tree, *(const Rva001408C0Key *)&(*it).first);
	}
	return Rva00622290SetGroup(
		*(const IntSetTreeCopyView *)&keys.m_tree);
}

namespace _STL {
static __forceinline int **copyAssetDequeNodes(int **first, int **last, int **result) {
    return last == first ? result : (int **)((char *)memmove(result, first,
        (char *)last - (char *)first) + ((char *)last - (char *)first));
}
static __forceinline int **copyAssetDequeNodesBackward(int **first, int **last, int **result) {
    int bytes = (char *)last - (char *)first;
    return bytes > 0 ? (int **)memmove((char *)result - bytes, first, bytes) : result;
}
template <> inline void deque<int>::_M_reallocate_map(unsigned nodesToAdd, bool addAtFront) {
    unsigned oldNumNodes = _M_finish._M_node - _M_start._M_node + 1;
    unsigned newNumNodes = oldNumNodes + nodesToAdd;
    int **newStart;
    if (_M_map_size._M_data > 2 * newNumNodes) {
        newStart = _M_map._M_data + (_M_map_size._M_data - newNumNodes) / 2
            + (addAtFront ? nodesToAdd : 0);
        if (newStart < _M_start._M_node)
            copyAssetDequeNodes(_M_start._M_node, _M_finish._M_node + 1, newStart);
        else
            copyAssetDequeNodesBackward(_M_start._M_node, _M_finish._M_node + 1, newStart + oldNumNodes);
    } else {
        unsigned newMapSize = _M_map_size._M_data + (max)(_M_map_size._M_data, nodesToAdd) + 2;
        int **newMap = newMapSize ? (int **)allocator<char>::allocate(newMapSize * 4, 0) : 0;
        newStart = newMap + (newMapSize - newNumNodes) / 2 + (addAtFront ? nodesToAdd : 0);
        copyAssetDequeNodes(_M_start._M_node, _M_finish._M_node + 1, newStart);
        if (_M_map._M_data) free(_M_map._M_data);
        _M_map._M_data = newMap;
        _M_map_size._M_data = newMapSize;
    }
    _M_start._M_set_node(newStart);
    _M_finish._M_set_node(newStart + oldNumNodes - 1);
}
template <> inline void deque<int>::_M_push_back_aux_v(const int &value) {
    int copy = value;
    if (2 > _M_map_size._M_data - (unsigned)(_M_finish._M_node - _M_map._M_data))
        _M_reallocate_map(1, false);
    *(_M_finish._M_node + 1) = (int *)allocator<char>::allocate(0x80, 0);
    if (_M_finish._M_cur) *_M_finish._M_cur = copy;
    _M_finish._M_set_node(_M_finish._M_node + 1);
    _M_finish._M_cur = _M_finish._M_first;
}
template <> inline void deque<int>::_M_push_front_aux_v(const int &value) {
    int copy = value;
    if (1 > (unsigned)(_M_start._M_node - _M_map._M_data))
        _M_reallocate_map(1, true);
    *(_M_start._M_node - 1) = (int *)allocator<char>::allocate(0x80, 0);
    _M_start._M_set_node(_M_start._M_node - 1);
    _M_start._M_cur = _M_start._M_last - 1;
    if (_M_start._M_cur) *_M_start._M_cur = copy;
}
template <> inline void deque<int>::_M_pop_back_aux() {
    if (_M_finish._M_first) free(_M_finish._M_first);
    _M_finish._M_set_node(_M_finish._M_node - 1);
    _M_finish._M_cur = _M_finish._M_last - 1;
}
template <> inline void deque<int>::_M_pop_front_aux() {
    if (_M_start._M_first) free(_M_start._M_first);
    _M_start._M_set_node(_M_start._M_node + 1);
    _M_start._M_cur = _M_start._M_first;
}
}
#include <windows.h>
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@H@_STL@@U12@V?$allocator@U?$_Rb_tree_no:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _STLP_alloc_proxy<_Rb_tree_node<int> *,_Rb_tree_node<int>,allocator<_Rb_tree_node<int> > >::deallocate(_Rb_tree_node<int> *,unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@H@_STL@@@_STL@@QBEXPAU?$_Rb_tree_node@H@2@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<_Rb_tree_node<int> >::deallocate(_Rb_tree_node<int> *,unsigned int) const; }

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;
typedef _STL::_Rb_tree<Rva001408C0Key,Rva001408C0Key,_STL::_Identity<Rva001408C0Key>,_STL::less<Rva001408C0Key>,_STL::allocator<Rva001408C0Key> > AssetKeyTree;
typedef _STL::hash_map<int, void *> AssetHash;
typedef _STL::map<int, void *> AssetKeyMap;

struct AssetSetGroup
{
	__forceinline AssetSetGroup() : m_count(0), m_active(true) {}
	Rva001408C0Set m_tree;
	unsigned int m_count;
	bool m_active;
	unsigned char m_padding[3];
};

class Rva009EF0D0Element
{
public:
	virtual const char *slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10(AssetSetGroup *keys);
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual unsigned slot34();
	virtual unsigned slot38();

	union
	{
		volatile unsigned int m_bfmeFlags;
		volatile unsigned int m_bfmeFlagsShared;
		struct
		{
			volatile unsigned int m_bfmeLow : 16;
			volatile unsigned int m_bfmeState : 8;
			unsigned int m_bfmeBit24 : 1;
			unsigned int m_bfmeQueued : 1;
			unsigned int m_bfmeBit26 : 1;
			unsigned int m_bfmeHigh : 5;
		};
	};
	Rva001408C0Key m_assetID;	// +0x08
	Rva001408C0Key *m_bfmeKeys;	// +0x0C
};

typedef _STL::deque<int> AssetQueue;

class Rva000309B0
{
public:
    Rva000309B0(unsigned tag);
    ~Rva000309B0();
private:
    void *m_value;
};


int bfmeRva0011F600();
bool BFME_DX8_Thread_Assert();
void BFME_DX8_Thread_Lock();

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04(void);
	virtual void Slot08(void);
	virtual void Slot0C(void);
	virtual void Slot10(void);
	virtual void Slot14(void);
	virtual void Slot18(void);
	virtual void Slot1C(void);
	virtual void Slot20(void);
	virtual void Slot24(void);
	virtual void Slot28(void);
	virtual void Slot2C(void);
	virtual void Slot30(void);
	virtual void Slot34(void);
	virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
	virtual void Slot3C(void);
	virtual void Slot40(void);
	virtual void Slot44(void);
	virtual void Slot48(void);
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(void); virtual void Slot04(void); virtual void Slot08(void); virtual void Slot0C(void);
	virtual void Slot10(void); virtual void Slot14(void); virtual void Slot18(void); virtual void Slot1C(void);
	virtual void Slot20(void); virtual void Slot24(void); virtual void Slot28(void); virtual void Slot2C(void);
	virtual void Slot30(void); virtual void Slot34(void); virtual void Slot38(void); virtual void Slot3C(void);
	virtual void Slot40(void); virtual void Slot44(void); virtual void Slot48(void); virtual void Slot4C(void);
	virtual void Slot50(void); virtual void Slot54(void); virtual void Slot58(void); virtual void Slot5C(void);
	virtual void Begin_Report(void);
	virtual void Slot64(void); virtual void Slot68(void);
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context, void *extra);
};

class Debug;
extern Debug *theDebug;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);


// Asset load profiling state (BFME2-only; retail VAs 0xE09B08/0xE09A08/
// 0xE09A00/0xE09C20/0xE09DB0/0xE09C10/0xE09C18).
char g_00E09B08[256];	// retail VA 0x00E09B08 (.bss), defined here
char g_bfmeProfilePrevFile[256];	// retail VA 0x00E09A08 (.bss), defined here
extern int g_00E09A00;
Rva009EF0D0Element *g_bfmeProfileAssets[100];	// retail VA 0x00E09C20 (.bss), defined here
int g_bfmeProfileCount;	// retail VA 0x00E09DB0 (.bss), defined here
extern __int64 g_bfmeProfileFreq;
extern char g_bfmeProfileFreqInit;
__int64 rva0061FCE0GetClockCyclesFast(void) throw();
// Same helper as the committed Rva0061FFD0Cluster.cpp / BFME1 profile.cpp:
// inline rdtsc is compiler machinery (the retail bytes are this exact body).
__forceinline void ProfileGetTime(__int64 &t)
{
	_asm
	{
		mov ecx,[t]
		push eax
		push edx
		rdtsc
		mov [ecx],eax
		mov [ecx+4],edx
		pop edx
		pop eax
	};
}

class AssetManagerImpl
{
public:
	void Worker_Thread_00622480();
	void LoadAsset(Rva009EF0D0Element *asset);
	__forceinline void WaitForQueue()
	{
		int count = 0;
		if ((char)bfmeRva0011F600() != 0)
		{
			do
			{
				++count;
			} while (BFME_DX8_Thread_Assert() == 0);
		}
		LeaveCriticalSection(&m_lock68);
		Sleep(1);
		EnterCriticalSection(&m_lock68);
		while (count != 0)
		{
			BFME_DX8_Thread_Lock();
			--count;
		}
	}

private:
	unsigned int m_thread;
	unsigned int m_threadId;
	bool m_flag08;
	unsigned char m_unmodelled_009[0x17];
	__int64 m_totalCount;
	unsigned char m_unmodelled_028[0x24];
	AssetHash m_map4c;
	unsigned char m_unmodelled_060[8];
	CRITICAL_SECTION m_lock68;
	AssetQueue m_deques80[7];
	AssetSetGroup m_set198;
	AssetSetGroup m_set1ac;
	AssetSetGroup m_set1c0;
	AssetSetGroup m_set1d4;
	unsigned int m_field1e8;
	unsigned int m_field1ec;
	unsigned int m_unmodelled_1f0;
	bool m_flag1f4;
	bool m_flag1f5;
	bool m_flag1f6;
	unsigned char m_padding1f7;
};

// Ledger owner of the key-queue body at 0x00622680 (WorldBuilder: AssetManagerImpl::AddRequiredAssets).
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/AssetRegistry.h"

class CriticalSectionLock {
public:
    explicit CriticalSectionLock(CRITICAL_SECTION *lock) : m_lock(lock) { EnterCriticalSection(m_lock); }
    ~CriticalSectionLock() { LeaveCriticalSection(m_lock); }
    CRITICAL_SECTION *m_lock;
};
void AssetManagerImpl::LoadAsset(Rva009EF0D0Element *asset)
{
	if (!asset->m_assetID || asset->m_bfmeState == 3)
		return;

	__int64 tStart;
	if (g_00E09B08[0])
	{
		ProfileGetTime(tStart);
		g_bfmeProfileAssets[g_bfmeProfileCount++] = asset;
	}

	EnterCriticalSection(&m_lock68);
	if (((AssetKeyMap *)&m_set198)->find((int)(size_t)asset->m_assetID) == ((AssetKeyMap *)&m_set198)->end() &&
		!asset->m_bfmeBit26)
	{
		m_set1d4.m_tree.insert(asset->m_assetID);
		if (!m_flag1f5)
			return;
		if (m_flag1f6)
		{
			const char *name = asset->slot00();
			if (name && name[0] != '#' &&
				_strnicmp(name, "apt_", 4) != 0 &&
				_strnicmp(name, "sfe_", 4) != 0 &&
				bfmeRva000387C0())
			{
				_bfme_debugRecordCallsite(1);
				reinterpret_cast<BFMEIndexBufferDebugClass *>(theDebug)->Begin_Report();
				reinterpret_cast<BFMEIndexBufferDebugClass *>(theDebug)->Get_Stream(0, 0, 0)
					->Put_String("[info] Demand load: ")
					->Put_String(name)
					->Finish(2);
			}
		}
		m_set198.m_tree.insert(asset->m_assetID);
	}

	while ((asset->m_bfmeState == 1 ||
		asset->m_bfmeState == 5) &&
		m_deques80[asset->m_bfmeState].front() == (int)asset &&
		m_flag1f4)
	{
		WaitForQueue();
	}
	while (asset->m_bfmeState == 8)
	{
		WaitForQueue();
	}

	unsigned int queue = asset->m_bfmeState;
	if (queue != 7)
	{
		unsigned int i = 0;
		for (; i < m_deques80[queue].size(); ++i)
		{
			if (m_deques80[queue][i] == (int)asset)
				break;
		}
		if (i < m_deques80[queue].size())
		{
			m_deques80[queue][i] = m_deques80[queue][m_deques80[queue].size() - 1];
			m_deques80[queue].pop_back();
		}
	}
	LeaveCriticalSection(&m_lock68);

	__int64 t[9];
	if (g_00E09B08[0])
	{
		ProfileGetTime(t[0]);
		for (int k = 1; k < 9; ++k)
			t[k] = t[0];
	}

	asset->m_bfmeQueued = 1;
	Rva000309B0 heap(0x61737374);
	if (queue == 7)
		asset->m_bfmeState = 0;

	switch (asset->m_bfmeState)
	{
	case 4:
		m_totalCount += asset->slot38();
		asset->m_bfmeState = 3;
		break;
	case 5:
		if (g_00E09B08[0])
			ProfileGetTime(t[asset->m_bfmeState]);
		asset->slot18();
		asset->m_bfmeState = 6;
	case 6:
		if (g_00E09B08[0])
			ProfileGetTime(t[asset->m_bfmeState]);
		asset->slot1C();
		asset->m_bfmeState = 0;
	case 0:
		if (g_00E09B08[0])
			ProfileGetTime(t[asset->m_bfmeState]);
		asset->slot04();
		asset->m_bfmeState = 1;
	case 1:
		if (g_00E09B08[0])
			ProfileGetTime(t[asset->m_bfmeState]);
		asset->slot08();
		asset->m_bfmeState = 2;
		m_totalCount += asset->slot38();
	case 2:
		if (g_00E09B08[0])
			ProfileGetTime(t[asset->m_bfmeState]);
		asset->slot0C();
		{
			AssetSetGroup set;
			asset->slot10(&set);
			if (asset->m_bfmeKeys && asset->m_bfmeKeys[0])
			{
				for (int k = 0; asset->m_bfmeKeys[k]; ++k)
				{
					insertKeyInline(set.m_tree, asset->m_bfmeKeys[k]);
				}
			}
			if (set.m_tree.size() != 0)
			{
				CriticalSectionLock lock(&m_lock68);
				((AssetRegistry *)this)->Queue_Keys_00622680(true, set.m_tree);
			}
		}
		asset->m_bfmeState = 3;
		if (g_00E09B08[0])
			ProfileGetTime(t[asset->m_bfmeState]);
	default:
		break;
	}

	CriticalSectionLock lock(&m_lock68);
	m_deques80[3].push_back((int)asset);
	if (g_00E09B08[0])
	{
		static __int64 s_profileFreq = rva0061FCE0GetClockCyclesFast();
		__int64 tEnd;
		ProfileGetTime(tEnd);
		char type[5];
		unsigned code = asset->slot34();
		int n = 0;
		for (int b = 0; b < 4; ++b)
		{
			if (code >> 24)
				type[n++] = (char)(code >> 24);
			code <<= 8;
		}
		type[n] = 0;
		FILE *fILE;
		if (strcmp(g_00E09B08, g_bfmeProfilePrevFile) != 0)
		{
			strcpy(g_bfmeProfilePrevFile, g_00E09B08);
			fILE = fopen(g_00E09B08, "wt");
			fprintf(fILE, "frame,type,asset,tInit,tPreload,tLoad,tPostload,tTotal,recursion\n");
		}
		else
		{
			fILE = fopen(g_00E09B08, "at");
		}
		fprintf(fILE, "%d,%s,\"", g_00E09A00, type);
		for (int k = 0; k < g_bfmeProfileCount; ++k)
		{
			fprintf(fILE, "%s%s", k ? "/" : "", g_bfmeProfileAssets[k]->slot00());
		}
		fprintf(fILE, "\"");
		fprintf(fILE, ",%.3lf", (double)(t[8] - tStart) / ((double)s_profileFreq * 0.001));
		if (t[0] < t[1])
			fprintf(fILE, ",%.3lf", (double)(t[1] - t[0]) / ((double)s_profileFreq * 0.001));
		else
			fprintf(fILE, ",");
		if (t[1] < t[2])
			fprintf(fILE, ",%.3lf", (double)(t[2] - t[1]) / ((double)s_profileFreq * 0.001));
		else
			fprintf(fILE, ",");
		if (t[2] < t[3])
			fprintf(fILE, ",%.3lf", (double)(t[3] - t[2]) / ((double)s_profileFreq * 0.001));
		else
			fprintf(fILE, ",");
		fprintf(fILE, ",%.3lf,%i\n", (double)(tEnd - tStart) / ((double)s_profileFreq * 0.001), g_bfmeProfileCount);
		fclose(fILE);
		--g_bfmeProfileCount;
	}
}

// Preserve the native inline lookup without an external copy of the helper.
namespace _STL {
typedef _Rb_tree<int, pair<const int, void *>, _Select1st<pair<const int, void *> >,
    less<int>, allocator<pair<const int, void *> > > AssetLookupLinkTree;
template <> template <> __declspec(dllimport) __forceinline
_Rb_tree_node<pair<const int, void *> > *AssetLookupLinkTree::_M_find<int>(const int &__k) const
{
    _Link_type __y = this->_M_header._M_data;
    _Link_type __x = _M_root();
    while (__x != 0)
        if (!_M_key_compare(_S_key(__x), __k))
            __y = __x, __x = _S_left(__x);
        else
            __x = _S_right(__x);
    if (__y == this->_M_header._M_data || _M_key_compare(__k, _S_key(__y)))
        __y = this->_M_header._M_data;
    return __y;
}
}
