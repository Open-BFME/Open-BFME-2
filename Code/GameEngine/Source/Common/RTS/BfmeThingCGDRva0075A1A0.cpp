// ?rva0075A1A0@CollisionManagerImpl@@QAEXXZ
// cl: /O2 /G6 /MD /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Retail 0x0075A1A0..0x0075A48E (750 B; Ghidra's 747 cut the add esp,0x18 / ret epilogue), thiscall, EH.
// Sited just before the rowed Update driver 0x0075A490 (BfmeConv597.cpp); the object is the 0xC070-byte
// collision data the constructor 0x0075A000 builds (RetailCollisionManagerDataCtorRva0075A000.cpp): two
// bucket tables (0x2B7B and 0x493 buckets) with their active/index/cursor words. WorldBuilder twin
// 0x018062E0 is the same walk with "collisionmanager_stat" / "Contacts:" / "max on obj " debug output;
// retail keeps only the counting: every node's two sub-object pointers are counted in a local map, the
// unsigned maximum is scanned (result unused) and the map is cleared between the tables.
// Codegen facts: no /arch:SSE (retail's max scans use jbe/mov, SSE gives cmova); /EHs, not /EHsc (with
// /EHsc ~_Rb_tree drops the inlined first _M_erase level: 114 B vs retail 122 B); the retail tree insert
// layout define. The map<Rva009A2FE0Sub*, unsigned> instantiation this unit emits is byte-identical to
// retail's folded bodies: operator[] 0x0075A120, insert_unique 0x00759DB0 / 0x00759C80, _M_insert
// 0x00759BC0, _Construct 0x006204B0, _M_erase 0x007590B0, ~_Rb_tree 0x00759B40 (fold-proof pins).
// The key/value spelling and all names are address-derived placeholders; retail folds every
// pointer->int map onto these bodies.

struct Rva009A2FE0Node;

struct Rva009A2FE0Sub
{
	unsigned char m_pad0[4];
	unsigned m_bfme04;
	unsigned char m_pad8[8];
	unsigned m_bfme10;
};

struct Rva009A2FE0Node
{
	Rva009A2FE0Sub *m_bfme00;
	Rva009A2FE0Sub *m_bfme04;
	unsigned char m_pad8[8];
	unsigned m_bfme10;
	unsigned char m_pad14[0x18];
	Rva009A2FE0Node **m_backSlot;
	Rva009A2FE0Node *m_next;
};

class CollisionManagerImpl
{
public:
	void bfmeOneCGD();
	void bfmeTwoCGD();
	void Update();
	void rva0075A1A0();
	Rva009A2FE0Node *nextNode();
	Rva009A2FE0Node *nextNode2();
	void *m_bfmeFirst;
	unsigned char m_bfmeGap[0x18 - 4];
	Rva009A2FE0Node *m_buckets2[0x2b7b];
	Rva009A2FE0Node *m_active2;
	int m_index2;
	Rva009A2FE0Node *m_cur2;
	Rva009A2FE0Node *m_buckets[0x493];
	Rva009A2FE0Node *m_active;
	int m_index;
	Rva009A2FE0Node *m_cur;
	unsigned char m_bfmeGap1[0xc06d - 0xc068];
	bool m_bfmeBusy;
};

void bfmeGlobalCGD();

// Retail 0x0075A1A0 (747B, RET0 thiscall), sited just before the rowed
// Update driver 0x0075A490. WorldBuilder twin 0x018062E0 (1212B) is the
// same walk with "collisionmanager_stat" / "Contacts:" / "max on obj "
// debug output; retail keeps only the counting. Target instruction facts:
// both bucket tables are walked through their +0xC060/+0xC064 and
// +0xAE08/+0xAE0C cursors, every node's two sub-object pointers (+0, +4) are
// counted in a local map (find, else operator[] 0x0075A120 = 1), the unsigned
// maximum is scanned (result unused) and the map is cleared between tables
// (_M_erase 0x007590B0) and destroyed at exit (0x00759B40). The key type is
// the address-named sub-object view; the original key/value spelling is
// unproven (retail folds every pointer->unsigned map onto those bodies).

#include <map>

typedef _STL::map<Rva009A2FE0Sub *, unsigned int> Rva0075A1A0Counts;

// The two cursor helpers below exist only as inlined walks. Their out-of-line
// COMDATs (72 B and 69 B, no relocations) have no caller here, and no copy of
// either occurs in retail .text (exact byte search; place_bodies places neither).
// Retail reads the 0x493 table's cursor words +0xC060/+0xC064 only inside
// 0x00758D10, 0x00758DE0, the constructor 0x0075A000 and 0x0075A1A0, and the
// 0x2B7B table's +0xAE08 only in 0x0075A000 and 0x0075A1A0 (0x00759220 only
// steps +0xAE0C past an unlinked node). The out-of-line table-relative twins
// are the rowed 0x00758B80 and 0x00758A50.
// ?CollisionManagerImpl::nextNode absent-from-retail (inlined into rva0075A1A0; no standalone retail body)
inline Rva009A2FE0Node *CollisionManagerImpl::nextNode()
{
	while (m_cur == 0)
	{
		int i = m_index + 1;

		if (i == 0x493)
			return 0;
		m_index = i;
		m_cur = m_buckets[i];
	}
	Rva009A2FE0Node *n = m_cur;
	m_cur = m_cur->m_next;
	return n;
}

// ?CollisionManagerImpl::nextNode2 absent-from-retail (inlined into rva0075A1A0; no standalone retail body)
inline Rva009A2FE0Node *CollisionManagerImpl::nextNode2()
{
	while (m_cur2 == 0)
	{
		int i = m_index2 + 1;

		if (i == 0x2b7b)
			return 0;
		m_index2 = i;
		m_cur2 = m_buckets2[i];
	}
	Rva009A2FE0Node *n = m_cur2;
	m_cur2 = m_cur2->m_next;
	return n;
}

static inline void rva0075A1A0Count(Rva0075A1A0Counts &counts, Rva009A2FE0Sub *const &key)
{
	Rva0075A1A0Counts::iterator it = counts.find(key);
	if (it == counts.end())
		counts[key] = 1;
	else
		++(*it).second;
}

static inline unsigned int rva0075A1A0Max(Rva0075A1A0Counts &counts)
{
	unsigned int most = 0;
	for (Rva0075A1A0Counts::iterator it = counts.begin(); it != counts.end(); ++it)
		if ((*it).second > most)
			most = (*it).second;
	return most;
}

void CollisionManagerImpl::rva0075A1A0()
{
	Rva0075A1A0Counts counts;
	Rva009A2FE0Node *n;

	m_index = 0;
	m_cur = m_buckets[0];
	while ((n = nextNode()) != 0)
	{
		rva0075A1A0Count(counts, n->m_bfme00);
		rva0075A1A0Count(counts, n->m_bfme04);
	}
	{
		unsigned int most = 0;
		for (Rva0075A1A0Counts::iterator it = counts.begin(); it != counts.end(); ++it)
			if ((*it).second > most)
				most = (*it).second;
	}
	counts.clear();

	m_index2 = 0;
	m_cur2 = m_buckets2[0];
	while ((n = nextNode2()) != 0)
	{
		rva0075A1A0Count(counts, n->m_bfme00);
		rva0075A1A0Count(counts, n->m_bfme04);
	}
	rva0075A1A0Max(counts);
}
