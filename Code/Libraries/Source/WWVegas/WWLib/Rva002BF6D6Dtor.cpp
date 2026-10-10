// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// ??1Rva002BF6D6@@QAE@XZ @0x002BF6D6 57B
// Non-virtual dtor sharing the Armor hashtable layout (pad + bucket vector).
// Evidence: calls rowed hashtable clear 0x001DBCDC with this and frees bucket
// start at +4 via member dtor (rowed _free 0x00030830); EH states guard clear.
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
class Rva002BF6D6
{
public:
	~Rva002BF6D6();
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
Rva002BF6D6::~Rva002BF6D6()
{
	((ArmorHashTable *)this)->clear();
}

// Native0x002BF776..0x002BF77B tail JMP to sole rowed nonvirtual dtor
// at0x002BF6D6. Unadjusted receiver no stack args RET0; original wrapper
// name enclosing type and lifetime role remain unknown.
struct Rva002BF776CleanupForward { void cleanup(); };
void Rva002BF776CleanupForward::cleanup()
{
    reinterpret_cast<Rva002BF6D6*>(this)->~Rva002BF6D6();
}
