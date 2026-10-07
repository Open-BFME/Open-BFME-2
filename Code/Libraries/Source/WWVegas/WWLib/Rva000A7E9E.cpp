// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Retail 0x000A7E9E, 92B. Target evidence: copies the input AsciiString at
// +0, constructs the 8B TreeKey with the input word at +0x38, erases that key
// from the tree at this+0x20 through rowed 0x000A7E31, then subtracts input
// +0x30 from this+0x3C. The const-reference spelling models the observed
// single stack pointer ABI; target bytes do not resolve pointer versus
// reference or the owning class and input identities.
// Retail 0x000A8127, 151B. Target evidence: constructs the rowed mutex guard
// over this+0x50, tests the slot at item+0x44, inserts a rowed TreeKey made
// from item+0x38 and its AsciiString through 0x000A7DCE, then adds item+0x30
// to this+0x3C. The false branch calls rowed 0x000A80A8(item, 1). Manager and
// item identities remain address-derived.

#include <set>
#include <list>
#include "ascii_string.h"

struct TreeKey00242F5E
{
	unsigned int m_id;
	AsciiString m_name;
	TreeKey00242F5E(unsigned int id, AsciiString name);
};

// This is the address-derived template spelling already used by the row at
// 0x000A7E31. The call site passes the TreeKey object as an opaque key pointer.
struct Rva000A7E31Key
{
	int word;
	bool operator<(const Rva000A7E31Key &other) const { return word < other.word; }
	bool operator==(const Rva000A7E31Key &other) const { return word == other.word; }
};

typedef _STL::_Rb_tree<Rva000A7E31Key, Rva000A7E31Key,
	_STL::_Identity<Rva000A7E31Key>, _STL::less<Rva000A7E31Key>,
	_STL::allocator<Rva000A7E31Key> > Rva000A7E9ETree;

struct Rva000A7AA7Less
{
	bool operator()(const TreeKey00242F5E &a, const TreeKey00242F5E &b) const;
};

typedef _STL::set<TreeKey00242F5E, Rva000A7AA7Less,
	_STL::allocator<TreeKey00242F5E> > TreeKey00242F5ESet;

struct Rva000A7E9EInput
{
	AsciiString m_at00;
	unsigned char m_pad04[0x2C];
	unsigned int m_at30;
	unsigned char m_pad34[4];
	unsigned int m_at38;
};

class Rva000A7E9E
{
public:
	void rva000A7E9E(const Rva000A7E9EInput &input);
	void rva000A80A8(struct Rva000A80A8Item *item, int treeDetached);
	void rva000A8127(struct Rva000A80A8Item *item);

private:
	unsigned char m_pad00[0x20];
	Rva000A7E9ETree m_tree;
	unsigned char m_pad2C[0x10];
	unsigned int m_count;
};

void Rva000A7E9E::rva000A7E9E(const Rva000A7E9EInput &input)
{
	TreeKey00242F5E key(input.m_at38, input.m_at00);
	m_tree.erase((const Rva000A7E31Key &)key);
	register unsigned int amount = input.m_at30;
	m_count -= amount;
}

struct Rva000A80A8Slot
{
	virtual bool shouldRemove(int flags);
};

struct Rva000A80A8Item
{
	AsciiString m_name;
	unsigned char m_pad04[0x2C];
	unsigned int m_amount;
	unsigned int m_pad34;
	unsigned int m_id;
	unsigned int m_listIndex;
	unsigned int m_pad40;
	Rva000A80A8Slot m_slot;
};

class Rva00041037Mutex
{
public:
	virtual bool vf0(int x);
};

class MilesMutexGuard
{
public:
	MilesMutexGuard(void *mutex, int flags);
	~MilesMutexGuard();

private:
	Rva00041037Mutex *m_mutex;
	bool m_flag;
};

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva0010EDC2_B2
{
public:
	virtual void f2();
};

class Rva0010EDC2 : public Rva0049B47C, public MiBase1, public Rva0010EDC2_B2
{
public:
	virtual ~Rva0010EDC2()
	{
	}
};

class Rva000427195
{
public:
	int bucketIndex(const AsciiString *name);
	int rva00223429(const AsciiString *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void Rva000A7E9E::rva000A80A8(Rva000A80A8Item *item, int treeDetached)
{
	Rva000A80A8Item *entry = item;
	if (entry->m_slot.shouldRemove(0))
		*(unsigned int *)((char *)this + 0x38) -= entry->m_amount;

	if (!treeDetached)
		rva000A7E9E(*(const Rva000A7E9EInput *)(const void *)entry);

	if (!entry->m_slot.shouldRemove(0)) {
		_STL::list<int, _STL::allocator<int> > *list =
			(_STL::list<int, _STL::allocator<int> > *)((char *)this + 0x14 + entry->m_listIndex * 4);
		for (_STL::list<int, _STL::allocator<int> >::iterator it = list->begin(); it != list->end(); ++it) {
			if ((void *)(unsigned int)*it == entry) {
				*(_STL::list<int, _STL::allocator<int> >::iterator *)(void *)&item = list->erase(it);
				break;
			}
		}
	}

	((Rva000427195 *)this)->rva00223429(&entry->m_name);
	((Rva0010EDC2 *)entry)->Rva0010EDC2::~Rva0010EDC2();
	::operator delete(entry);
}

void Rva000A7E9E::rva000A8127(Rva000A80A8Item *item)
{
	MilesMutexGuard guard(*(void **)((char *)this + 0x50), 0);
	if (item->m_slot.shouldRemove(0)) {
		TreeKey00242F5E key(item->m_id, item->m_name);
		((TreeKey00242F5ESet *)((char *)this + 0x20))->insert(key);
		register unsigned int amount = item->m_amount;
		m_count += amount;
	} else {
		rva000A80A8(item, 1);
	}
}
