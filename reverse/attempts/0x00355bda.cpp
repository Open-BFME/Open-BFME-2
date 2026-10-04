// ??1Rva00355BDA@@UAE@XZ
// partial score=0.91 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ??1Rva00355BDA@@UAE@XZ @0x00355BDA 85B
// MI dtor over GameEngineDeletingBase primary plus Snapshot secondary at +0xC
// plus two ArmorTemplateMap members at +0x10 and +0x24 via rowed hashtable
// dtor 0x00355257. Evidence: pin ??1Rva00355BDA@@UAE@XZ, deleting dtor
// 0x00355BBE calls here, vtable 0x00C14E14#0, Snapshot base BBB554,
// base dtor 0x001B4E74 rowed, dup_00355257 rowed twice, EH prolog B7D517.
#include <cstddef>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{

template <typename T> struct hash
{
	size_t operator()(const T &value) const;
};

}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

namespace _STL
{

template <class _T1, class _T2> struct pair
{
	_T1 first;
	_T2 second;
};

template <class _Pair> struct _Select1st
{
	const typename _Pair::first_type &operator()(const _Pair &x) const { return x.first; }
};

template <class _Tp> struct equal_to
{
	bool operator()(const _Tp &x, const _Tp &y) const { return x == y; }
};

template <class _Tp> class allocator
{
public:
	typedef _Tp value_type;
};

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
class hashtable
{
public:
	~hashtable();
private:
	char m_pad[0x14];
};

}

typedef _STL::hashtable<
	_STL::pair<const NameKeyType, ArmorTemplate>,
	NameKeyType,
	rts::hash<NameKeyType>,
	_STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate> >,
	_STL::equal_to<NameKeyType>,
	_STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHashtable;

extern const void *const g_00BBB554[];

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = (const void *)g_00BBB554;
}

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[4];
	int m_member08;
};

class __declspec(novtable) Rva00355BDA : public GameEngineDeletingBase, public Snapshot
{
public:
	virtual ~Rva00355BDA();
private:
	ArmorHashtable m_map10;
	ArmorHashtable m_map24;
};

// ??1Rva00355BDA@@UAE@XZ present-unmatched
Rva00355BDA::~Rva00355BDA()
{
}
