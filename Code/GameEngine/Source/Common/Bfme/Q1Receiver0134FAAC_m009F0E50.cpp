// ?m009F0E50@Q1Receiver0134FAAC@@QAEXH@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail RVA 0x00621B10, 327 bytes; identity is address-derived.
// Sibling of m009F0D40 in assetmanager_impl.cpp: copy the argument set with
// the 0x009EE8E0 copy constructor, hand the local group to 0x009EFD40, then
// under the +0x68 and +0x34 locks walk the +0x4C hash map and store, per
// payload, whether its key is in the copied set. The local copy is destroyed
// through the j_00015d7a thunk at 0x0006BF2A with the same member-pointer ABI
// the sibling TU uses. BFME2 layout is 8 bytes deeper past +0x28 (proven by
// the three landed siblings). The walked map's begin is the rowed
// hash_map<int, int> instantiation at 0x00620A80, so the table is viewed with
// an integer value here; the payload is recovered from that integer exactly
// as the BFME1 donor does.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <hash_map>

struct Rva001408C0Target;
typedef Rva001408C0Target *Q1ReceiverKey;
typedef _STL::set<Q1ReceiverKey> Q1ReceiverKeySet;

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

void j_00015d7a();

struct Q1ReceiverTreeStorage
{
	Q1ReceiverTreeStorage(const Q1ReceiverSet &source);
	~Q1ReceiverTreeStorage()
	{
		// MSVC x86 single-inheritance member-pointer ABI: ECX is this and
		// the verified thunk has no stack arguments. No numeric code address.
		typedef void (Q1ReceiverKeySet::*TreeDestructor)();
		union { void (*raw)(); TreeDestructor member; } destroy;
		destroy.raw = j_00015d7a;
		(get().*destroy.member)();
	}
	Q1ReceiverKeySet &get() { return *(Q1ReceiverKeySet *)m_storage; }
	int m_storage[sizeof(Q1ReceiverKeySet) / sizeof(int)];
};

struct Q1ReceiverLocalSet
{
	Q1ReceiverTreeStorage m_set;
	int m_zero;
	bool m_one;
};

// Hash payload: bit 26 of the dword at +4 records whether the key at +8 is
// in the argument set (m009F0D40 sets the same bit with an OR).
struct Q1ReceiverHashPayload
{
	int m_unmodelled_000;
	unsigned int m_bits00 : 26;
	unsigned int m_inSet : 1;
	unsigned int m_bits27 : 5;
	Q1ReceiverKey m_key;
};

typedef _STL::hash_map<int, int> Q1ReceiverHashTable;

struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

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

class Q1Receiver0134FAAC
{
public:
	void m009F0E50(int value);
	void m009EFD40(Q1ReceiverLocalSet *set);

private:
	unsigned char m_unmodelled_000[0x24];
	int m_value;
	unsigned char m_unmodelled_028[0xC];	// BFME2: +8 here; every later field sits 8 bytes deeper than in BFME1
	unsigned char m_lock_02C[0x18];
	Q1ReceiverHashTable m_table;
	unsigned char m_unmodelled_058[8];
	unsigned char m_lock_060[0x18];
};

void Q1Receiver0134FAAC::m009F0E50(int value)
{
	Q1ReceiverLocalSet set = { *(Q1ReceiverSet *)value, 0, true };
	m009EFD40(&set);

	Q1ReceiverLockGuard lock60((int)m_lock_060);
	Q1ReceiverLockGuard lock2c((int)m_lock_02C);

	for (Q1ReceiverHashTable::iterator it = m_table.begin();
		it != m_table.end(); ++it)
	{
		Q1ReceiverHashPayload *payload = (Q1ReceiverHashPayload *)it->second;
		Q1ReceiverKey key = payload->m_key;
		payload->m_inSet = set.m_set.get().count(key);
	}
}
