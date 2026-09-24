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

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <hash_map>

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

struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);
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
	void m009EC970(int which);
	void m009EC9A0(int which);
	void m009ECA30(int value);
	void m009F0D40(int value);
	void m009F0E50(int value);
	void m009F19E0(int source);
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
	unsigned char m_unmodelled_078[0x174];
	bool m_flag0;
	bool m_flag1;
	bool m_flag2;
};

void Q1Receiver0134FAAC::m009EC970(int which)
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

void Q1Receiver0134FAAC::m009EC9A0(int which)
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

void Q1Receiver0134FAAC::m009F0D40(int value)
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

// Sibling of m009F0D40: copy the argument set with 0x009EE8E0, hand the local
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
