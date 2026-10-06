// ?rva00171128@Rva00170BFF@@QAEPAURva00170999Data@@ABVAssetReference@@@Z
// partial score=0.95 date=2026-10-06
// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva0017110B@Rva00170BFF@@QAE?AURva00170EFEIter@@U2@ABVRva00170999@@@Z
// Candidate 0x0017110B, 29B. Forwards hint-insert (position, value) to the
// rowed worker 0x00170EFE on the same Rva00170BFF tree; caller 0x00171128
// passes this through in ecx with hidden return pointer. Boundary from int3
// padding; byte verification decides.
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
	~Rva00170999();
};

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
};

class Rva00170BFF
{
	Rva00170EFENode *m_00Head;
	unsigned int m_04Flag;
public:
	Rva00170EFEIter rva00170EFE(Rva00170EFEIter position,
		const Rva00170999 &value);
	Rva00170EFEIter rva0017110B(Rva00170EFEIter position,
		const Rva00170999 &value);
	Rva00170999Data *rva00171128(const AssetReference &ref);
};

// ??1Rva00170999@@QAE@XZ present-unmatched
Rva00170999::~Rva00170999()
{
	if (m_ptr) {
		m_ptr->Release_Ref();
	}
}

Rva00170EFEIter Rva00170BFF::rva0017110B(Rva00170EFEIter position,
	const Rva00170999 &value)
{
	return rva00170EFE(position, value);
}

// ?rva00171128@Rva00170BFF@@QAEPAURva00170999Data@@ABVAssetReference@@@Z present-unmatched
Rva00170999Data *Rva00170BFF::rva00171128(const AssetReference &ref)
{
	typedef _STL::map<unsigned, void *> MapIntPtr;
	const unsigned &key = *(const unsigned *)&ref;
	MapIntPtr &m = *(MapIntPtr *)this;
	MapIntPtr::iterator it = m.lower_bound(key);
	if (it == m.end()) {
		goto insert;
	}
	if (key >= it->first) {
		goto found;
	}
insert:
	{
		Rva00170999 tmp(ref, Rva00170999Data());
		Rva00170EFEIter pos((Rva00170EFENode *)it._M_node);
		Rva00170EFEIter res = rva0017110B(pos, tmp);
		it._M_node = (MapIntPtr::iterator::_Base_ptr)res.node;
	}
found:
	return (Rva00170999Data *)((char *)it._M_node + 0x14);
}
