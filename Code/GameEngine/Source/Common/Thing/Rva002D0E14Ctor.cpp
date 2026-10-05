// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
// ??0Rva002D0E14@@QAE@XZ @0x002D0E14 85B: SubsystemInterface base via 0x001B4E63 vtable 0x00C0233C member Rva002D0C71 at +0x14 plus +0xC zero plus +0x10 one plus reserve 0x3000 via pinned rva00212858. Evidence: caller 0x0004CA01 revtables to 0x007C4858; calls baseConstruct and hashtable ctor.
#include <hash_map>
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

namespace Rva002D0C71Twin
{
template <typename T> struct equal_to
{
	bool operator()(const T &a, const T &b) const;
};
}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

typedef _STL::hashtable<_STL::pair<const NameKeyType, ArmorTemplate>, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate> >, Rva002D0C71Twin::equal_to<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHt002D0C71;

class Rva002D0C71
{
public:
	Rva002D0C71();
private:
	ArmorHt002D0C71 m_ht;
};

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
private:
	unsigned char m_pad[8];
};

class Rva002D0E14 : public SubsystemInterface
{
public:
	Rva002D0E14();
	void init() { }
	void reset() { }
	void update() { }
private:
	int m_unk0C;
	unsigned short m_unk10;
	char m_pad12[2];
	Rva002D0C71 m_thing;
};

Rva002D0E14::Rva002D0E14()
{
	m_unk0C = 0;
	m_unk10 = 1;
	((Rva000427195 *)&m_thing)->rva00212858(0x3000);
}
