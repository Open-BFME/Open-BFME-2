// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// ??1Rva004271D9@@QAE@XZ @0x004271D9 57B
// Non-virtual dtor sharing the Armor hashtable layout (pad + bucket vector).
// Evidence: calls rowed hashtable clear 0x001DBCDC with this and frees bucket
// start at +4 via member dtor (rowed _free 0x00030830); EH states guard clear.
// Caller 0x00427374 in 0x00427311 passes esi+0x0c; landing unblocks 0x00427311.
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
struct BucketVec004271D9
{
	void *_start;
	void *_finish;
	void *_end;
	~BucketVec004271D9() { if (_start) free(_start); }
};
class Rva004271D9
{
public:
	~Rva004271D9();
private:
	char m_pad[4];
	BucketVec004271D9 m_buckets;
};
typedef _STL::hashtable<
	_STL::pair<const NameKeyType, ArmorTemplate>,
	NameKeyType,
	rts::hash<NameKeyType>,
	_STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate> >,
	_STL::equal_to<NameKeyType>,
	_STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHashTable004271D9;
Rva004271D9::~Rva004271D9()
{
	((ArmorHashTable004271D9 *)this)->clear();
}
