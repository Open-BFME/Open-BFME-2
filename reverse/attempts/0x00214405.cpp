// ??1LivingWorldManager@@UAE@XZ
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
//
// ??1LivingWorldManager@@UAE@XZ, retail 0x00214405..0x002146B8 (691 bytes);
// pinned until now as the opaque ??1Rva00214405@@UAE@XZ.
//
// Identity: the body calls the rowed ?rva0021427A@LivingWorldManager@@QAEXXZ
// on this and clears TheLivingWorldManager (0x00DFE1C8) when it is this
// object; the scalar deleting dtor 0x002146B8 that calls it is slot 0 of
// vftable 0x00BE5234.
// Layout from the body: bases SubsystemInterface (+0x00, rowed dtor
// 0x001B4E74), Snapshot (+0x0C, canonical inline dtor storing 0x00BBB554)
// and a one-slot observer interface (+0x10, inline dtor storing 0x00BE5114)
// that TheLivingWorldLogic's +0x7C list unregisters (rowed 0x002B7250).
// The body releases the +0x268 helper (rowed 0x003EF1B8), runs the rowed
// cleanup, drops +0x264, deletes the +0x2C4 object, every pointer of the
// +0x24C vector (then erases it), every value of the hash maps at +0x26C
// (non-virtual, rowed dtor 0x003FA14B) and +0x204 (virtual) and of the tree
// map at +0x2B4, clearing each (rowed 0x003A2A41 / 0x00211DD2; hash begin
// 0x00427195 and iterator step 0x00411084 under their existing spellings).
// Members then fall in reverse: +0x2CC +0x2B4 +0x2A8 +0x294 +0x280 +0x26C
// +0x258 +0x24C +0x240 +0x234 +0x22C +0x218 +0x204 +0x14.
// PINS: the hash table destructors 0x002129DD (+0x204/+0x26C/+0x280/+0x294)
// and 0x0021231B (+0x218) are rowed only as ?dup_* gen-alias placeholders
// with no thiscall spelling:
//   ??1Rva002129DD@@QAE@XZ -> 0x002129DD
//   ??1Rva0021231B@@QAE@XZ -> 0x0021231B

#include "Common/Snapshot.h"

// C++-linkage free (?free@@YAXPAX@Z, pinned at 0x00030830), as in
// Rva000427195Dtor.cpp: the decoration keeps retail's unwind state stores.
void __cdecl free(void *block);

class CreateAHeroData;

namespace _STL {
template <class T1, class T2> struct pair;
template <class T> struct hash;
template <class T> struct _Select1st;
template <class T> struct equal_to;
template <class T> class allocator;
template <class T> struct _Nonconst_traits;
template <class V, class Tr, class K, class HF, class ExK, class EqK, class A>
struct _Ht_iterator
{
	_Ht_iterator();
	void *_M_cur;
	void *_M_ht;
};
template <class V, class K, class HF, class ExK, class EqK, class A>
class hashtable
{
public:
	_Ht_iterator<V, _Nonconst_traits<V>, K, HF, ExK, EqK, A> begin();
};
struct _Rb_tree_node_base;
template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *x);
};
}

struct Gen_t_00786db0_p12cd
{
	int a[3];
	Gen_t_00786db0_p12cd();
	Gen_t_00786db0_p12cd(const Gen_t_00786db0_p12cd &);
	~Gen_t_00786db0_p12cd();
	Gen_t_00786db0_p12cd &operator=(const Gen_t_00786db0_p12cd &);
};

typedef _STL::pair<const int, Gen_t_00786db0_p12cd> HashBeginValue;
typedef _STL::hashtable<HashBeginValue, int, _STL::hash<int>, _STL::_Select1st<HashBeginValue>,
	_STL::equal_to<int>, _STL::allocator<HashBeginValue> > HashBeginTable;
typedef _STL::_Ht_iterator<HashBeginValue, _STL::_Nonconst_traits<HashBeginValue>, int, _STL::hash<int>,
	_STL::_Select1st<HashBeginValue>, _STL::equal_to<int>, _STL::allocator<HashBeginValue> > HashIterator;

// The hash iterator's step (rowed 0x00411084) and the table's clear (rowed
// 0x003A2A41) under their existing spellings.
class Rva000411084
{
public:
	void *next();
};
class Rva000427195
{
public:
	void rva003A2A41();
};

// vector<void *>::erase(first, last), rowed 0x0031BD55; called under this
// existing pin spelling.
class BfmeSlotVecG
{
public:
	void bfmeErase(void **first, void **last);
};

struct HashNodeView
{
	HashNodeView *m_next;
	int m_key;
	void *m_value; // +0x08
};

struct TreeNodeView
{
	char m_pad00[0x14];
	void *m_value; // +0x14
};

class OwnedObject
{
public:
	virtual ~OwnedObject();
};

class Rva003FA26F
{
public:
	~Rva003FA26F();
};

class Rva003EF14A
{
public:
	void rva003EF1B8();
};

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

class LivingWorldLogic
{
public:
	char m_pad00[0x7C];
	Rva002B7250 m_7C; // +0x7C
};
extern LivingWorldLogic *TheLivingWorldLogic;

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[0x0C - 0x04];
};

class LivingWorldObserver
{
public:
	virtual void onLivingWorldEvent();
protected:
	~LivingWorldObserver() {}
};

class Rva00212ED3
{
public:
	~Rva00212ED3();
private:
	char m_pad[0x204 - 0x14];
};

class Rva002129DD
{
public:
	~Rva002129DD();
	HashIterator begin() { return reinterpret_cast<HashBeginTable *>(this)->begin(); }
	void clear() { reinterpret_cast<Rva000427195 *>(this)->rva003A2A41(); }
private:
	char m_pad[0x14];
};

class Rva0021231B
{
public:
	~Rva0021231B();
private:
	char m_pad[0x14];
};

struct RefHolder
{
	~RefHolder() { if (m_ptr) m_ptr->Release_Ref(); }
	OpaqueRefCounted *m_ptr;
};

struct FreeBuffer
{
	~FreeBuffer() { if (m_start) free(m_start); }
	void *m_start;
	void *m_finish;
	void *m_end;
};

struct PtrVector
{
	~PtrVector() { if (m_start) free(m_start); }
	unsigned int size() const { return m_finish - m_start; }
	void **begin() { return m_start; }
	void **end() { return m_finish; }
	void clear() { reinterpret_cast<BfmeSlotVecG *>(this)->bfmeErase(begin(), end()); }
	void **m_start;
	void **m_finish;
	void **m_end;
};

class Rva0021397C
{
public:
	void rva0021397C();
};

struct Vector2A8
{
	~Vector2A8() { reinterpret_cast<Rva0021397C *>(this)->rva0021397C(); }
	void *m_start;
	void *m_finish;
	void *m_end;
};

class Rva0021119B
{
public:
	struct iterator
	{
		TreeNodeView *m_node;
		iterator(TreeNodeView *node) : m_node(node) {}
		bool operator!=(const iterator &other) const { return m_node != other.m_node; }
		iterator &operator++()
		{
			m_node = (TreeNodeView *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)m_node);
			return *this;
		}
	};
	iterator begin() { return iterator(*(TreeNodeView **)((char *)m_header + 8)); }
	iterator end() { return iterator(m_header); }
	void rva00211DD2();
	~Rva0021119B();
	TreeNodeView *m_header;
	int m_count;
	int m_flag;
};

struct FreePointer
{
	~FreePointer() { if (m_ptr) free(m_ptr); }
	void *m_ptr;
};

class LivingWorldManager : public SubsystemInterface, public Snapshot, public LivingWorldObserver
{
public:
	virtual ~LivingWorldManager();
	void rva0021427A();

private:
	Rva00212ED3 m_14; // +0x14
	Rva002129DD m_204; // +0x204
	Rva0021231B m_218; // +0x218
	RefHolder m_22C; // +0x22C
	int m_230;
	FreeBuffer m_234; // +0x234
	FreeBuffer m_240; // +0x240
	PtrVector m_24C; // +0x24C
	FreeBuffer m_258; // +0x258
	void *m_264; // +0x264
	Rva003EF14A *m_268; // +0x268
	Rva002129DD m_26C; // +0x26C
	Rva002129DD m_280; // +0x280
	Rva002129DD m_294; // +0x294
	Vector2A8 m_2A8; // +0x2A8
	Rva0021119B m_2B4; // +0x2B4
	bool m_2C0;
	OwnedObject *m_2C4; // +0x2C4
	int m_2C8;
	FreePointer m_2CC; // +0x2CC
};

extern LivingWorldManager *TheLivingWorldManager;

LivingWorldManager::~LivingWorldManager()
{
	if (m_268) {
		m_268->rva003EF1B8();
		m_268 = 0;
	}
	if (TheLivingWorldLogic)
		TheLivingWorldLogic->m_7C.rva002B7250((CreateAHeroData *)static_cast<LivingWorldObserver *>(this));
	rva0021427A();
	m_264 = 0;
	if (m_2C4) {
		::delete m_2C4;
		m_2C4 = 0;
	}

	for (unsigned int i = 0; i < m_24C.size(); ++i)
		::delete (OwnedObject *)m_24C.m_start[i];
	m_24C.clear();

	{
		for (HashIterator it = m_26C.begin(); it._M_cur != 0; reinterpret_cast<Rva000411084 *>(&it)->next())
			delete (Rva003FA26F *)((HashNodeView *)it._M_cur)->m_value;
	}
	m_26C.clear();

	{
		for (HashIterator it = m_204.begin(); it._M_cur != 0; reinterpret_cast<Rva000411084 *>(&it)->next())
			::delete (OwnedObject *)((HashNodeView *)it._M_cur)->m_value;
	}
	m_204.clear();

	if (TheLivingWorldManager == this)
		TheLivingWorldManager = 0;

	{
		for (Rva0021119B::iterator mit = m_2B4.begin(); mit != m_2B4.end(); ++mit)
			::delete (OwnedObject *)mit.m_node->m_value;
	}
	m_2B4.rva00211DD2();
}
