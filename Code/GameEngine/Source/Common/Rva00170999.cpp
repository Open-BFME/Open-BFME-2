// cl: /O1 /EHs /MD
// Retail 0x00170999 33B: Rva00170999 ctor copying AssetReference at +0 via
// rowed ??0AssetReference@@QAE@ABV0@@Z and 16 bytes at +4 from second arg.
// Evidence: callees rowed; callers 0x00170A58 (by-value wrapper) and 0x00171128
// (stack temp from zeroed AssetReference plus 16-byte value, then map insert
// with TextureClass Release_Ref at 0x0061ED10).
// Retail 0x00170A58 27B: ?Rva00170A58Get@@YA?AVRva00170999@@ABVAssetReference@@ABURva00170999Data@@@Z
// return-by-value wrapper constructing in hidden buffer via 0x00170999.
// Evidence: caller 0x001710A6 pushes hidden buffer plus refs then copy-constructs via 0x001709D7.
// Retail 0x001709D7 33B: ??0Rva00170999@@QAE@ABV0@@Z copy ctor via rowed AssetReference copy plus 16B pod copy.
// Retail 0x001709F8 28B: ??_GRva001709F8@@QAEPAXI@Z deleting dtor calling
// ICF-twin ??1Rva001709F8@@QAE@XZ (byte-identical to rowed RefCountPtr TextureClass dtor 0x0017098D)
// then conditional operator delete. Evidence: gap shape push esi plus flag test plus ret 4.

class TextureClass
{
public:
	void Release_Ref();
};

class Rva001709F8
{
public:
	~Rva001709F8();
private:
	TextureClass *m_texture;
};

// ??1Rva001709F8@@QAE@XZ present-unmatched
Rva001709F8::~Rva001709F8()
{
	if (m_texture) {
		m_texture->Release_Ref();
	}
}

// ?Rva001709F8Delete@@YAXPAVRva001709F8@@@Z present-unmatched
void Rva001709F8Delete(Rva001709F8 *p) { delete p; }

class CountedAsset;
class AssetReference
{
public:
	AssetReference(const AssetReference &that);
	~AssetReference();
private:
	CountedAsset *m_object;
};

struct Rva00170999Data
{
	unsigned int w;
	unsigned int x;
	unsigned int y;
	unsigned int z;
};

class Rva00170999
{
public:
	Rva00170999(const AssetReference &a, const Rva00170999Data &d);
	Rva00170999(const Rva00170999 &that);
private:
	AssetReference m_asset;
	Rva00170999Data m_data;
};

Rva00170999::Rva00170999(const AssetReference &a, const Rva00170999Data &d)
	: m_asset(a)
	, m_data(d)
{
}

Rva00170999::Rva00170999(const Rva00170999 &that)
	: m_asset(that.m_asset)
	, m_data(that.m_data)
{
}

Rva00170999 __cdecl Rva00170A58Get(const AssetReference &a, const Rva00170999Data &d)
{
	return Rva00170999(a, d);
}

class Rva00151DAB
{
public:
	Rva00151DAB(const Rva00151DAB &that);
	Rva00151DAB(const unsigned int &key, const AssetReference &ref);
	~Rva00151DAB();
private:
	unsigned int _key;
	AssetReference _ref;
};

Rva00151DAB::Rva00151DAB(const Rva00151DAB &that)
	: _key(that._key)
	, _ref(that._ref)
{
}

Rva00151DAB::Rva00151DAB(const unsigned int &key, const AssetReference &ref)
	: _key(key)
	, _ref(ref)
{
}

Rva00151DAB __cdecl Rva00170A3DGet(const unsigned int &key, const AssetReference &ref)
{
	return Rva00151DAB(key, ref);
}

namespace _STL
{
template <class _T1, class _T2> void _Construct(_T1 *__p, const _T2 &__val);
}

template <> void _STL::_Construct<Rva00151DAB, Rva00151DAB>(Rva00151DAB *p, const Rva00151DAB &v)
{
	if (p == 0) {
		return;
	}
	p->Rva00151DAB::Rva00151DAB(v);
}

// Retail 0x00170A85..0x00170A97: nullable placement-copy wrapper.
// The native call at 0x00170A91 targets the rowed copy constructor 0x001709D7;
// the adjacent Rva00151DAB _Construct specialization establishes the STL shape.
// Rva00170999 remains an address-derived type; its original name is unknown.
template <> void _STL::_Construct<Rva00170999, Rva00170999>(Rva00170999 *p, const Rva00170999 &v)
{
	if (p == 0) {
		return;
	}
	p->Rva00170999::Rva00170999(v);
}
