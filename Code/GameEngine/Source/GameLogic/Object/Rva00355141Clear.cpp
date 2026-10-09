// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva00355141@Rva00355B61@@UAEXXZ @0x00355141 20B: clears two ArmorTemplate maps at +0x10 and +0x24 via rowed hashtable clear 0x001DBCDC.
// Evidence: retail lea ecx [esi+0x24] call clear then lea ecx [esi+0x10] jmp clear; offsets match Rva00355B61Ctor maps; slot 9 of vtable 0x00814E14.

enum NameKeyType { NAMEKEY_DUMMY };
class ArmorTemplate;
namespace rts { template <class T> struct hash; }
namespace _STL {
template <class T1, class T2> struct pair;
template <class P> struct _Select1st;
template <class T> struct equal_to;
template <class T> class allocator;
template <class V, class K, class H, class S, class E, class A>
class hashtable
{
public:
	void clear();
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
	_STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHashTable;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
private:
	unsigned char m_bfme04[8];
};

class SnapshotBase
{
public:
	virtual ~SnapshotBase();
};

class Rva00355B61 : public SubsystemInterface, public SnapshotBase
{
public:
	virtual void rva00355141();
private:
	ArmorHashTable m_map1;
	ArmorHashTable m_map2;
};

void Rva00355B61::rva00355141()
{
	m_map2.clear();
	m_map1.clear();
}
