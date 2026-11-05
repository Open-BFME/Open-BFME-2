#define _STLP_USE_MALLOC 1
#define _STLP_NO_CSTD_FUNCTION_IMPORTS 1
namespace _STL { void __cdecl free(void *); }
// Recovered asset-manager bodies grouped by reciprocal WorldBuilder placement.
// Retail RVA 0x009F0D40, 265 bytes; identity is address-derived.
// The matched Rva009EBB20 forwarder in Q1GlobalGuardedForwarders.cpp proves
// this receiver and one-argument ABI. No original game class name is claimed.
// The copied set is 12 bytes (header/count/comparator); the local wrapper's
// zero and true fields are at +0xC/+0x10. Locks are at receiver +0x60/+0x2C.
// The hash map at +0x44 uses integer keys and pointer payloads; retail updates
// payload +4, not the key. Its const_iterator retains both node and table.
// The copy constructor is 0x009EE8E0; the tree destructor is called through
// ILT 0x00015D7A -> 0x00140950. Existing Gen_t names describe those ABI types.

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// platformsdk
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
// The game's byte allocator (0x000307F0): a static cdecl (bytes, hint) on
// allocator<char> that every retail node allocation funnels through.
namespace _STL {
template <class _Tp> class allocator;
template <> class allocator<char> {
public:
	typedef char value_type;
	static char *allocate(unsigned int __n, const void *__p);
};
}
#include <set>
#include <hash_map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

#include <cstddef>

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

struct Gen_t_009ee8e0_k4
{
	int a[1];
	Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &);
	~Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &);
};

bool operator<(const Gen_t_009ee8e0_k4 &, const Gen_t_009ee8e0_k4 &);
typedef _STL::set<Gen_t_009ee8e0_k4> Q1ReceiverSet;

// m009F0E50 walks the copied set with builtin pointer compares (retail
// inlines the tree descent: cmp/jb/jae, no operator< call), so it views the
// same 12-byte set through a pointer element type. The copy constructor,
// destructor thunk and layout stay the TU's own.
struct Rva001408C0Target;
typedef Rva001408C0Target *Q1ReceiverKey;
typedef _STL::set<Q1ReceiverKey> Q1ReceiverPtrSet;
// Every empty() test on the pointer set is inlined; imported force-inline stock
// bodies keep this unit from emitting its own first-in-link-order copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool _Rb_tree<Q1ReceiverKey, Q1ReceiverKey, _Identity<Q1ReceiverKey>, less<Q1ReceiverKey>, allocator<Q1ReceiverKey> >::empty() const
{ return _M_node_count == 0; }
template <> __declspec(dllimport) __forceinline
bool set<Q1ReceiverKey, less<Q1ReceiverKey>, allocator<Q1ReceiverKey> >::empty() const
{ return _M_t.empty(); }
typedef _Rb_tree<Q1ReceiverKey, Q1ReceiverKey, _Identity<Q1ReceiverKey>, less<Q1ReceiverKey>, allocator<Q1ReceiverKey> > Q1ReceiverPtrTree;
// Node allocation inlines the game's byte allocator, as retail's does.
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<Rva001408C0Target *> *allocator<_Rb_tree_node<Rva001408C0Target *> >::allocate(size_t __n, const void *) const
{ return __n != 0 ? (_Rb_tree_node<Rva001408C0Target *> *)allocator<char>::allocate(__n * sizeof(_Rb_tree_node<Rva001408C0Target *>), 0) : 0; }
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<Rva001408C0Target *> *_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Target *> *, _Rb_tree_node<Rva001408C0Target *>, allocator<_Rb_tree_node<Rva001408C0Target *> > >::allocate(size_t __n)
{ return __stl_alloc_rebind(static_cast<_Base &>(*this), (_Rb_tree_node<Rva001408C0Target *> *)0).allocate(__n, 0); }
// This unit is first in link order for the pointer set's out-of-line insert
// path, but retail's copies (0x004ABD36, 0x00422047, 0x00080691) are the
// game's /O1 bodies. Template members take the optimize state of the TU end,
// so the stock bodies are spelled as explicit specializations in a gsy region.
#pragma optimize("gsy", on)
// _M_create_node is retail's /O1 body too (0x004ABCC9): the byte allocator
// inlined through the allocator and proxy members, the caller popping its
// two arguments.
template <> inline
_Rb_tree_node<Q1ReceiverKey> *Q1ReceiverPtrTree::_M_create_node(const Q1ReceiverKey &__x)
{
	_Link_type __tmp = this->_M_header.allocate(1);
	_Construct(&__tmp->_M_value_field, __x);
	return __tmp;
}
template <> inline
Q1ReceiverPtrTree::iterator _Rb_tree<Q1ReceiverKey, Q1ReceiverKey, _Identity<Q1ReceiverKey>, less<Q1ReceiverKey>, allocator<Q1ReceiverKey> >::_M_insert(_Rb_tree_node_base *__x_, _Rb_tree_node_base *__y_, const Q1ReceiverKey &__v,
	_Rb_tree_node_base *__w_)
{
	_Link_type __w = (_Link_type) __w_;
	_Link_type __x = (_Link_type) __x_;
	_Link_type __y = (_Link_type) __y_;
	_Link_type __z;

	if (__y == this->_M_header._M_data ||
	    (__w == 0 && (__x != 0 || _M_key_compare(_Identity<Q1ReceiverKey>()(__v), _S_key(__y))))) {
		__z = _M_create_node(__v);
		_S_left(__y) = __z;
		if (__y == this->_M_header._M_data) {
			_M_root() = __z;
			_M_rightmost() = __z;
		}
		else if (__y == _M_leftmost())
			_M_leftmost() = __z;
	}
	else {
		__z = _M_create_node(__v);
		_S_right(__y) = __z;
		if (__y == _M_rightmost())
			_M_rightmost() = __z;
	}
	_S_parent(__z) = __y;
	_S_left(__z) = 0;
	_S_right(__z) = 0;
	_Rb_global_inst::_Rebalance(__z, this->_M_header._M_data->_M_parent);
	++_M_node_count;
	return iterator(__z);
}
template <> inline
pair<Q1ReceiverPtrTree::iterator, bool> _Rb_tree<Q1ReceiverKey, Q1ReceiverKey, _Identity<Q1ReceiverKey>, less<Q1ReceiverKey>, allocator<Q1ReceiverKey> >::insert_unique(const Q1ReceiverKey &__v)
{
	_Link_type __y = this->_M_header._M_data;
	_Link_type __x = _M_root();
	bool __comp = true;
	while (__x != 0) {
		__y = __x;
		__comp = _M_key_compare(_Identity<Q1ReceiverKey>()(__v), _S_key(__x));
		__x = __comp ? _S_left(__x) : _S_right(__x);
	}
	iterator __j = iterator(__y);
	if (__comp && __j == begin())
		return pair<iterator, bool>(_M_insert(__y, __y, __v), true);
	if (__comp)
		--__j;
	if (_M_key_compare(_S_key(__j._M_node), _Identity<Q1ReceiverKey>()(__v)))
		return pair<iterator, bool>(_M_insert(__x, __y, __v), true);
	return pair<iterator, bool>(__j, false);
}
template <> inline
pair<Q1ReceiverPtrSet::iterator, bool> Q1ReceiverPtrSet::insert(const Q1ReceiverKey &__x)
{
	pair<Q1ReceiverPtrTree::iterator, bool> __p = _M_t.insert_unique(__x);
	return pair<iterator, bool>(reinterpret_cast<const iterator &>(__p.first), __p.second);
}
#pragma optimize("", on)
}

void j_00015d7a();

// ABI view of the canonical 12-byte STL set. The externally compiled copy
// constructor is 0x009EE8E0. Destruction uses the already-named ILT thunk;
// no new template identity is asserted for its generated destination row.
struct Q1ReceiverTreeStorage
{
	Q1ReceiverTreeStorage(const Q1ReceiverSet &source);
	~Q1ReceiverTreeStorage()
	{
		// MSVC x86 single-inheritance member-pointer ABI: ECX is this and
		// the verified thunk has no stack arguments. No numeric code address.
		typedef void (Q1ReceiverSet::*TreeDestructor)();
		union { void (*raw)(); TreeDestructor member; } destroy;
		destroy.raw = j_00015d7a;
		(get().*destroy.member)();
	}
	Q1ReceiverSet &get() { return *(Q1ReceiverSet *)m_storage; }
	int m_storage[sizeof(Q1ReceiverSet) / sizeof(int)];
};

typedef char Q1ReceiverSetSizeCheck[sizeof(Q1ReceiverSet) == 12 ? 1 : -1];

struct Q1ReceiverLocalSet
{
	Q1ReceiverTreeStorage m_set;
	int m_zero;
	bool m_one;
};

struct Q1ReceiverSetNode : public _STL::_Rb_tree_node_base
{
	int m_key;
};

struct Q1ReceiverHashPayload
{
	int m_unused;
	int m_flags;
	Q1ReceiverKey m_key;			// +0x08
	Q1ReceiverKey *m_dependencies;	// +0x0C, null-terminated
};

// Hash payload as m009F0E50 sees it: the flag dword at +4 carries bit 26 as
// a bitfield, and the key pointer lives at +8. Same object, donor's view.
struct Q1ReceiverFlagPayload
{
	int m_unused;
	unsigned int m_bits00 : 26;
	unsigned int m_inSet : 1;
	unsigned int m_bits27 : 5;
	Q1ReceiverKey m_key;
};

typedef _STL::hash_map<int, Q1ReceiverHashPayload *> Q1ReceiverHashTable;

// Pointer-set group at receiver +0x198 (donor view +0x190, BFME2 +8): the
// tree the merge methods count into and insert into, with its count/active
// trailer maintained alongside.
struct Q1ReceiverSetGroup198
{
	Q1ReceiverPtrSet m_tree;
	volatile unsigned int m_count;
	volatile bool m_active;
};

#include <windows.h>
extern volatile bool g_q1Flag0134FAA8;

class Q1ReceiverLockGuard
{
public:
	explicit Q1ReceiverLockGuard(int lock) : m_lock(lock)
	{
		EnterCriticalSection((CRITICAL_SECTION *)m_lock);
	}
	~Q1ReceiverLockGuard()
	{
		LeaveCriticalSection((CRITICAL_SECTION *)m_lock);
	}

	int m_lock;
};

// BFME1 donor view of the record at receiver +0x190 (BFME2 +0x198): step the
// record from the source record, flag it active, copy its value, refresh.
class BfmeThingBVA
{
public:
	void bfmeStepBVA(BfmeThingBVA *other);
	void set_value(int value)
	{
		m_value = value;
	}

	unsigned char m_unmodelled_000[0x0C];
	int m_value;
	bool m_active;
};

class Q1Receiver0134FAAC
{
public:
	void Enable(int which);
	void Disable(int which);
	void m009ECA30(int value);
	void AddStickyAssets(int value);
	void m009F0E50(int value);
	void m009F19E0(int source);
	void m009F1A60(int source);
	void m009F0CC0(int source);
	void m009F0BD0(int value);
	void m009EFD40(Q1ReceiverLocalSet *set);
	void refresh();

private:
	unsigned char m_unmodelled_000[0x24];
	int m_value;
	unsigned char m_unmodelled_028[0xC];	// BFME2: +8 here; every later field sits 8 bytes deeper than in BFME1
	unsigned char m_lock_02C[0x18];
	Q1ReceiverHashTable m_table;
	// Retail lock is at +0x60; the STL hash map at +0x44 occupies 20 bytes.
	unsigned char m_unmodelled_058[8];
	unsigned char m_lock_060[0x18];
	unsigned char m_unmodelled_080[0x118];
	Q1ReceiverSetGroup198 m_set198;
	unsigned char m_unmodelled_1AC[0x48];
	bool m_flag0;
	bool m_flag1;
	bool m_flag2;
};

void Q1Receiver0134FAAC::Enable(int which)
{
	switch (which)
	{
		case 0:
			m_flag0 = true;
			break;
		case 1:
			m_flag1 = true;
			break;
		case 2:
			m_flag2 = true;
			break;
	}
}

void Q1Receiver0134FAAC::Disable(int which)
{
	switch (which)
	{
		case 0:
			g_q1Flag0134FAA8 = false;
			if (g_q1Flag0134FAA8)
			{
				m_flag0 = false;
				break;
			}
			m_flag0 = false;
		spin:
			Sleep(1);
			if (!g_q1Flag0134FAA8)
				goto spin;
			break;
		case 1:
			m_flag1 = false;
			break;
		case 2:
			m_flag2 = false;
			break;
	}
}

// Q1Receiver0134FAAC::m009ECA30 (BFME1's clamped m_value setter) is not carried
// over: its body occurs nowhere in this image at any nearby field offset.

void Q1Receiver0134FAAC::AddStickyAssets(int value)
{
	Q1ReceiverLocalSet set = { *(Q1ReceiverSet *)value, 0, true };
	m009EFD40(&set);

	Q1ReceiverLockGuard lock60((int)m_lock_060);
	Q1ReceiverLockGuard lock2c((int)m_lock_02C);

	Q1ReceiverSet::iterator current = set.m_set.get().begin();
	while (current != set.m_set.get().end())
	{
		Q1ReceiverHashTable *table = &m_table;
		Q1ReceiverSetNode *node =
			(Q1ReceiverSetNode *)current._M_node;
		Q1ReceiverHashTable::const_iterator found = table->find(node->m_key);
		if (found != table->end())
			found->second->m_flags |= 0x04000000;

		++current;
	}
}

// WB 0x01678D00 AssetManagerImpl::AddDependentAssets, retail 0x006217F0
// (513 bytes, ret 4): grows the caller's key set to its dependency closure.
// Each pass copies the frontier (0x009EE8E0), clears the frontier, and for
// every non-null key of the copy looks its payload up in the +0x4C table
// (the key read straight from the tree node, as AddStickyAssets does) and adds
// every listed dependency not yet in the caller's set to both sets.
void Q1Receiver0134FAAC::m009EFD40(Q1ReceiverLocalSet *source)
{
	Q1ReceiverLocalSet frontier = { source->m_set.get(), 0, true };
	Q1ReceiverPtrSet &sourceKeys = (Q1ReceiverPtrSet &)source->m_set.get();
	Q1ReceiverPtrSet &frontierKeys = (Q1ReceiverPtrSet &)frontier.m_set.get();
	while (!frontierKeys.empty())
	{
		Q1ReceiverLocalSet previous = { frontier.m_set.get(), 0, true };
		frontierKeys.clear();
		frontier.m_one = true;
		Q1ReceiverPtrSet &previousKeys = (Q1ReceiverPtrSet &)previous.m_set.get();
		for (Q1ReceiverPtrSet::const_iterator it = previousKeys.begin();
			it != previousKeys.end(); ++it)
		{
			Q1ReceiverSetNode *node = (Q1ReceiverSetNode *)it._M_node;
			if (!node->m_key)
				continue;
			Q1ReceiverHashTable::const_iterator found = m_table.find(node->m_key);
			if (found == m_table.end())
				continue;
			Q1ReceiverHashPayload *asset = found->second;
			if (!asset->m_dependencies)
				continue;
			for (int n = 0; asset->m_dependencies[n]; ++n)
			{
				Q1ReceiverKey dependency = asset->m_dependencies[n];
				if (sourceKeys.find(dependency) == sourceKeys.end())
				{
					frontierKeys.insert(dependency);
					sourceKeys.insert(dependency);
				}
			}
		}
	}
}

// Sibling of AddStickyAssets: copy the argument set with 0x009EE8E0, hand the local
// group to 0x009EFD40, then under the +0x68 and +0x34 locks walk the +0x4C
// hash map and store, per payload, whether its key is in the copied set.
// BFME1 donor Q1Receiver0134FAAC_m009F0E50.cpp with the TU's +8 layout repair.
void Q1Receiver0134FAAC::m009F0E50(int value)
{
	Q1ReceiverLocalSet set = { *(Q1ReceiverSet *)value, 0, true };
	m009EFD40(&set);

	Q1ReceiverLockGuard lock60((int)m_lock_060);
	Q1ReceiverLockGuard lock2c((int)m_lock_02C);

	for (Q1ReceiverHashTable::iterator it = m_table.begin();
		it != m_table.end(); ++it)
	{
		Q1ReceiverFlagPayload *payload = (Q1ReceiverFlagPayload *)it->second;
		Q1ReceiverKey key = payload->m_key;
		payload->m_inSet = ((Q1ReceiverPtrSet &)set.m_set.get()).count(key);
	}
}

// BFME1 donor Q1Receiver0134FAAC_m009F19E0.cpp: guard the receiver lock, step
// this receiver's record from the source record when they differ, refresh.
void Q1Receiver0134FAAC::m009F19E0(int source)
{
	Q1ReceiverLockGuard lock((int)m_lock_060);
	BfmeThingBVA *record = (BfmeThingBVA *)((char *)this + 0x198);
	BfmeThingBVA &source_record = *(BfmeThingBVA *)(unsigned int)source;

	if (record != &source_record)
	{
		record->bfmeStepBVA(&source_record);
		record->m_active = true;
		record->set_value(source_record.m_value);
	}
	refresh();
}

// BFME1 donor Q1Receiver0134FAAC_m009F1A60.cpp: same step pattern as m009F19E0
// against the record at +0x1AC (donor view +0x1A4 with the extra gap).
void Q1Receiver0134FAAC::m009F1A60(int source)
{
	Q1ReceiverLockGuard lock((int)m_lock_060);
	BfmeThingBVA *record = (BfmeThingBVA *)((char *)this + 0x1AC);
	BfmeThingBVA &source_record = *(BfmeThingBVA *)(unsigned int)source;

	if (record != &source_record)
	{
		record->bfmeStepBVA(&source_record);
		record->m_active = true;
		record->set_value(source_record.m_value);
	}
	refresh();
}

// BFME1 donor Q1Receiver0134FAAC_m009F0CC0.cpp: same step pattern against the
// record at +0x1C0 (donor view +0x1B8).
void Q1Receiver0134FAAC::m009F0CC0(int source)
{
	Q1ReceiverLockGuard lock((int)m_lock_060);
	BfmeThingBVA *record = (BfmeThingBVA *)((char *)this + 0x1C0);
	BfmeThingBVA &source_record = *(BfmeThingBVA *)(unsigned int)source;

	if (record != &source_record)
	{
		record->bfmeStepBVA(&source_record);
		record->m_active = true;
		record->set_value(source_record.m_value);
	}
	refresh();
}

// BFME1 donor Q1Receiver0134FAAC_m009F0BD0.cpp: merge every non-null key of
// the argument pointer set that is missing from the +0x198 group set, then
// refresh when anything was inserted.
void Q1Receiver0134FAAC::m009F0BD0(int value)
{
	Q1ReceiverLockGuard lock((int)m_lock_060);
	bool changed = false;
	const Q1ReceiverPtrSet &source = *(const Q1ReceiverPtrSet *)value;

	for (Q1ReceiverPtrSet::const_iterator it = source.begin();
		it != source.end(); ++it)
	{
		Q1ReceiverKey key = *it;
		if (m_set198.m_tree.count(key) == 0 && key != 0)
		{
			if (!changed)
				changed = true;
			m_set198.m_tree.insert(*it);
		}
	}

	if (!changed)
		return;
	refresh();
}

class BfmeThingXS
{
public:
	unsigned char bfmeMarkXS(int which) const;

private:
	unsigned char m_bfmeHead[0x1f4];	// BFME1 0x1ec
	unsigned char m_bfmeFirst;
	unsigned char m_bfmeSecond;
	unsigned char m_bfmeThird;
};

unsigned char BfmeThingXS::bfmeMarkXS(int which) const
{
	switch (which)
	{
		case 0:
			return m_bfmeFirst;
		case 1:
			return m_bfmeSecond;
		case 2:
			return m_bfmeThird;
	}
	return 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeAskEME@BfmeObjEME@@QAE_NPAX@Z=?bfmeMarkXS@BfmeThingXS@@QBEEH@Z")

// Whole-file reference transfer: clean BFME1 BfmeConv1024.cpp
// Clean BFME1 90fffa62857c131831171802121eef7e6604eb58 BfmeConv1024.cpp
// UnloadAsset semantic donor. WB1679210 independently names UnloadAsset.
// Preserve existing BfmeP1024 binding called by the already owned forwarder.
// Native widened counter20/24 shifts lock68 and seven40-byte queues80.
// TLS scope uses owned30980/309B0; DX8 recursive lock release/reacquire is
// present in both native and WB. Complete native RET4 ends622169; switch
// table62216C..622188 follows three bytes of padding: full extent1320.

#include <deque>

int bfmeRva0011F600();
bool BFME_DX8_Thread_Assert();
void BFME_DX8_Thread_Lock();

class Rva000309B0 {
    void *m_previous;
public:
    Rva000309B0(unsigned tag);
    ~Rva000309B0();
};

class BfmeE1024 {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual unsigned slot38();
    union { unsigned m_bfmeFlags; volatile unsigned m_bfmeFlagsShared; };
    void *m_bfmeEntry;
};

class BfmeP1024 {
public:
    void bfmeReg1024(BfmeE1024 *item);
    char m_unmodelled_000[0x20];
    __int64 m_bfmeCount;
    char m_unmodelled_028[0x40];
    CRITICAL_SECTION m_bfmeLock;
    _STL::deque<int> m_bfmeQueues[7];
};

void BfmeP1024::bfmeReg1024(BfmeE1024 *item)
{
	if (!item->m_bfmeEntry || (item->m_bfmeFlagsShared & 0xff0000) == 0x70000)
		return;

	EnterCriticalSection(&m_bfmeLock);
	while (((item->m_bfmeFlagsShared & 0xff0000) == 0x10000 ||
		(item->m_bfmeFlagsShared & 0xff0000) == 0x50000) &&
		m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].front() == (int)item)
	{
		int held = 0;
        if ((unsigned char)bfmeRva0011F600())
            do { ++held; } while (!BFME_DX8_Thread_Assert());
        LeaveCriticalSection(&m_bfmeLock);
        Sleep(1);
        EnterCriticalSection(&m_bfmeLock);
        while (held) { BFME_DX8_Thread_Lock(); --held; }
	}
	while ((item->m_bfmeFlagsShared & 0xff0000) == 0x80000)
	{
		int held = 0;
        if ((unsigned char)bfmeRva0011F600())
            do { ++held; } while (!BFME_DX8_Thread_Assert());
        LeaveCriticalSection(&m_bfmeLock);
        Sleep(1);
        EnterCriticalSection(&m_bfmeLock);
        while (held) { BFME_DX8_Thread_Lock(); --held; }
	}

	unsigned int i = 0;
	for (; i < m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].size(); ++i)
	{
		if (m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].begin()[i] == (int)item)
			break;
	}
	m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff][i] = m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff][m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].size() - 1];
	m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].pop_back();
	LeaveCriticalSection(&m_bfmeLock);

	item->m_bfmeFlags &= 0xfdffffff;
    Rva000309B0 heap(0x61737374);
	if ((item->m_bfmeFlagsShared & 0xff0000) == 0x30000)
	{
		m_bfmeCount -= item->slot38();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff04ffff) | 0x40000;
		if (m_bfmeCount < 0)
			m_bfmeCount = 0;
	}

	switch ((item->m_bfmeFlagsShared >> 16) & 0xff)
	{
	case 0:
		item->slot04();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff01ffff) | 0x10000;
	case 1:
		item->slot08();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff02ffff) | 0x20000;
		m_bfmeCount += item->slot38();
	case 2:
		item->slot0C();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff04ffff) | 0x40000;
		m_bfmeCount -= item->slot38();
		if (m_bfmeCount < 0)
			m_bfmeCount = 0;
	case 4:
		item->slot14();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff05ffff) | 0x50000;
	case 5:
		item->slot18();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff06ffff) | 0x60000;
	case 6:
		item->slot1C();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff07ffff) | 0x70000;
	}
}


// BFME 2 complete bodies 0x0061F910..0x0061FA91 and 0x0061FAA0..0x0061FC21.
// Native comparisons establish an unsigned four-byte key, 12-byte set at +0,
// an untouched word at +0xC and changed flag +0x10. Source guide: BFME 1
// game/GameEngine/Source/Common/Bfme/Rva009EC5B0Set.cpp and Rva009EC770Set.cpp
// at committed donor 575ba2b04. The original wrapper/key names remain unknown.
// Native vector overflow reaches 0x002DFCF6, iterator increment 0x00024250,
// erase range 0x0061F7B0 and temporary-buffer release 0x00030830. Current
// source now reuses full verified typed helper aliases and the existing free provider.

#include <cstdlib>
extern void __cdecl Rva00030830FreeAllocation(void *);
#include <set>
#include <vector>
// Bind vector<unsigned int>::push_back to the kept retail copy (0x004DFCB0).
namespace _STL { template <> void vector<unsigned int, allocator<unsigned int> >::push_back(const unsigned int &); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline _Vector_base<unsigned int,allocator<unsigned int> >::_Vector_base(allocator<unsigned int> const &a) : _M_start(0), _M_finish(0), _M_end_of_storage(a, 0) {} }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }

// Retail clears EH state before the opaque buffer release at 0x30830.
// The allocator<unsigned> and proxy members are imported force-inline: every
// use here is inlined, and without dllimport this unit also emitted its own
// non-retail copies of them, the first ones in link order.
namespace _STL {
template <> __declspec(dllimport) __forceinline void allocator<unsigned int>::deallocate(unsigned int *p, size_t) const
{
	if (p != 0) Rva00030830FreeAllocation(p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<unsigned int *, unsigned int, allocator<unsigned int> >::deallocate(unsigned int *__p, size_t __n)
{ __stl_alloc_rebind(static_cast<allocator<unsigned int>&>(*this), (unsigned int *)0).deallocate(__p, __n); }
template <> __declspec(dllimport) __forceinline
unsigned int *_STLP_alloc_proxy<unsigned int *, unsigned int, allocator<unsigned int> >::allocate(size_t __n)
{ return __stl_alloc_rebind(static_cast<allocator<unsigned int>&>(*this), (unsigned int *)0).allocate(__n, 0); }
template <> __declspec(dllimport) __forceinline
void vector<unsigned int, allocator<unsigned int> >::_M_clear()
{
	_Destroy(this->_M_start, this->_M_finish);
	this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
}
}

// The rows inline STLport's push_back. Spelling it through this view keeps that
// expansion without emitting vector<unsigned>::push_back, whose 50-byte copy here
// came first in link order and is not retail's 49-byte 0x4DFCB0.
struct Rva0061F910Found : _STL::vector<unsigned int>
{
	void append(const unsigned int &__x)
	{
		if (this->_M_finish != this->_M_end_of_storage._M_data) {
			_STL::_Construct(this->_M_finish, __x);
			++this->_M_finish;
		}
		else
			_M_insert_overflow(this->_M_finish, __x, _IsPODType(), 1UL, true);
	}
};

struct Rva0061F910Key
{
	unsigned int a;
};

inline bool operator<(const Rva0061F910Key &left,
	const Rva0061F910Key &right)
{
	return left.a < right.a;
}

typedef _STL::set<Rva0061F910Key> Rva0061F910Tree;

typedef _STL::_Rb_tree<Rva0061F910Key,Rva0061F910Key,_STL::_Identity<Rva0061F910Key>,_STL::less<Rva0061F910Key>,_STL::allocator<Rva0061F910Key> > NativeTree;
namespace _STL {
// Tree cleanup uses the separately verified providers. The vector body stays
// visible so MSVC removes its unused empty-tag argument temporary; its strong
// size-profile instantiation is verified in UnsignedSetHelpersBFME2.cpp.
template <> void NativeTree::erase(NativeTree::iterator,NativeTree::iterator);
template <> void NativeTree::_M_erase(_Rb_tree_node<Rva0061F910Key> *);
}
class Rva0061F910Set
{
public:
	Rva0061F910Set &subtract(const Rva0061F910Set &other);
	Rva0061F910Set &retain(const Rva0061F910Set &other);

private:
	Rva0061F910Tree m_set;
	int dword_C;
	bool m_changed;
};

// ?subtract@Rva0061F910Set@@QAEAAV1@ABV1@@Z
Rva0061F910Set &Rva0061F910Set::subtract(const Rva0061F910Set &other)
{
	_STL::vector<unsigned int> found;
	for (Rva0061F910Tree::iterator it = m_set.begin(); it != m_set.end(); ++it)
	{
		if (other.m_set.find(*it) != other.m_set.end())
			static_cast<Rva0061F910Found &>(found).append(it->a);
	}
	if (!found.empty())
	{
		for (_STL::vector<unsigned int>::iterator v = found.begin();
			v != found.end(); ++v)
		{
			m_set.erase(reinterpret_cast<const Rva0061F910Key &>(*v));
		}
		m_changed = true;
	}
	return *this;
}

// ?retain@Rva0061F910Set@@QAEAAV1@ABV1@@Z
Rva0061F910Set &Rva0061F910Set::retain(const Rva0061F910Set &other)
{
	_STL::vector<unsigned int> found;
	for (Rva0061F910Tree::iterator it = m_set.begin(); it != m_set.end(); ++it)
	{
		if (other.m_set.find(*it) == other.m_set.end())
			static_cast<Rva0061F910Found &>(found).append(it->a);
	}
	if (!found.empty())
	{
		for (_STL::vector<unsigned int>::iterator v = found.begin();
			v != found.end(); ++v)
		{
			m_set.erase(reinterpret_cast<const Rva0061F910Key &>(*v));
		}
		m_changed = true;
	}
	return *this;
}

// Keep STLport's inline operations without emitting competing external copies.
namespace _STL {
typedef Rva001408C0Target *Q1LinkKey;
typedef _Rb_tree_node<Q1LinkKey> Q1LinkNode;
typedef _Rb_tree<Q1LinkKey, Q1LinkKey, _Identity<Q1LinkKey>, less<Q1LinkKey>, allocator<Q1LinkKey> > Q1LinkTree;
template <> __declspec(dllimport) __forceinline
void allocator<Q1LinkNode>::deallocate(Q1LinkNode *__p, size_t __n) const
{ if (__p != 0) __sgi_alloc::deallocate((void *)__p, __n * sizeof(Q1LinkNode)); }

template <> template <> __declspec(dllimport) __forceinline
_Rb_tree_node<Rva001408C0Target *> *Q1LinkTree::_M_find<Rva001408C0Target *>(Rva001408C0Target * const &__k) const
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
template <> template <> __declspec(dllimport) __forceinline
Q1LinkTree::const_iterator Q1LinkTree::find<Rva001408C0Target *>(Rva001408C0Target * const &__x) const
{ return const_iterator(_M_find(__x)); }
}

namespace _STL {
template <> __declspec(dllimport) __forceinline
unsigned int *fill_n<unsigned int *, unsigned int, unsigned int>(unsigned int *__first, unsigned int __n, const unsigned int &__val)
{
    for (; __n > 0; --__n, ++__first)
        *__first = __val;
    return __first;
}
}
