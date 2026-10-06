// ?rva00171067@Rva00171067@@QAEXABVAssetReference@@@Z
// partial score=0.96 date=2026-10-06
// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva00171067@Rva00171067@@QAEXABVAssetReference@@@Z
// Candidate 0x00171067, 164B. Find-or-create on the embedded Rva00170BFF tree
// at +8 (header pointer plus count, same layout as the rowed int_ptr tree so
// the rowed _M_find serves); on miss builds a zero-Data Rva00170999 via the
// rowed Get plus copy, inserts through the rowed unique-search worker at
// 0x00170DB7, then refreshes current at +0x14 to begin plus flag at +0x1C.
// Boundary from int3 padding; byte verification decides.
#include <map>

class TextureClass
{
public:
	void Release_Ref();
};

class AssetReference;

struct Rva00170999Data
{
	unsigned int w;
	unsigned int x;
	unsigned int y;
	unsigned int z;
};

class Rva00170999
{
	TextureClass *m_ptr;
	Rva00170999Data m_data;
public:
	Rva00170999(const AssetReference &a, const Rva00170999Data &d);
	Rva00170999(const Rva00170999 &that);
	~Rva00170999();
};

Rva00170999 Rva00170A58Get(const AssetReference &a, const Rva00170999Data &d);

struct Rva00170EFENode
{
	unsigned int _color;
	Rva00170EFENode *_parent;
	Rva00170EFENode *_left;
	Rva00170EFENode *_right;
	char _val10[0x14];
};

struct Rva00170EFEIter
{
	Rva00170EFENode *node;
	Rva00170EFEIter(Rva00170EFENode *p) : node(p) {}
	Rva00170EFEIter(const Rva00170EFEIter &o) : node(o.node) {}
};

struct Rva00170DB7Out
{
	Rva00170EFENode *node;
	bool inserted;
	Rva00170DB7Out(const Rva00170EFEIter &iter, bool flag)
		: node(iter.node), inserted(flag) {}
};

class Rva00170BFF
{
public:
	Rva00170EFENode *m_00Head;
	unsigned int m_04Flag;
	Rva00170DB7Out rva00170DB7(const Rva00170999 &value);
};

class Rva00171067
{
	int m_00;
	int m_04;
	Rva00170BFF m_bff;
	void *m_10;
	void *m_14;
	int m_18;
	bool m_1C;
public:
	void rva00171067(const AssetReference &ref);
};

// ??1Rva00170999@@QAE@XZ present-unmatched
Rva00170999::~Rva00170999()
{
	if (m_ptr) {
		m_ptr->Release_Ref();
	}
}

// ?rva00171067@Rva00171067@@QAEXABVAssetReference@@@Z present-unmatched
void Rva00171067::rva00171067(const AssetReference &ref)
{
	if (*(void *const *)&ref == 0) {
		return;
	}
	typedef _STL::map<unsigned, void *> MapIntPtr;
	const unsigned &key = *(const unsigned *)&ref;
	MapIntPtr &m = *(MapIntPtr *)&m_bff;
	MapIntPtr::iterator it = m.find(key);
	if (it != m.end()) {
		return;
	}
	{
		Rva00170999 tmp1 = Rva00170A58Get(ref, Rva00170999Data());
		Rva00170999 tmp2(tmp1);
		m_bff.rva00170DB7(tmp2);
	}
	m_14 = m_bff.m_00Head->_left;
	m_1C = true;
}
