// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// ??1Rva005982AC@@QAE@XZ @0x005982AC 57B via Armor hashtable clear plus bucket free
// Evidence: thiscall ret0 non-virtual dtor; rowed hashtable clear 0x001DBCDC at +0; frees +4 via BucketVec dtor through rowed _free 0x00030830; same 57B shape as rowed ??1Rva002BF6D6 0x002BF6D6; caller dtor 0x00598CFD at +0x18
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
};
}
extern "C" void __cdecl free(void *);
struct BucketVec
{
	void *_start;
	void *_finish;
	void *_end;
	~BucketVec() { if (_start) free(_start); }
};
class Rva005982AC
{
public:
	~Rva005982AC();
private:
	char m_pad[4];
	BucketVec m_buckets;
};
typedef _STL::hashtable<
	_STL::pair<const NameKeyType, ArmorTemplate>,
	NameKeyType,
	rts::hash<NameKeyType>,
	_STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate> >,
	_STL::equal_to<NameKeyType>,
	_STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHashTable;
Rva005982AC::~Rva005982AC()
{
	((ArmorHashTable *)this)->clear();
}
