// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void *&vector<void*>::operator[](size_t); }
// bfme link decl-only begin
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
// bfme link decl-only end



struct Rva002BFA86Record { char bytes[1]; };


// Retail 0x002BFA86 hashes the key through 0x00223149 and frees the node through
// 0x002BF75A, both rowed as plain methods (PlayerXferStringMaps.cpp,
// Rva002BF75AFree.cpp). Instantiating erase over this unit's record emitted
// non-retail _M_bkt_num_key/_M_delete_node copies and left the record's hash
// and dtor unresolved, so erase is defined here as an explicit specialization
// that calls those rows.
class AsciiString;
class Rva000411084;
class Rva000427195
{
public:
	void *first(Rva000411084 *);
	int bucketIndex(const AsciiString *name);
	void rva00212858(unsigned int n);
};
struct Rva002C00C1Element
{
public:
	bool operator<(const Rva002C00C1Element&)const;
	bool operator==(const Rva002C00C1Element&)const;
	char bytes[1]; // +0x00
};

typedef _STL::hash_map<int, Rva002C00C1Element, _STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, Rva002C00C1Element> > > LivingWorldTable;

struct Rva002BF75A { LivingWorldTable m_table; ~Rva002BF75A(); void rva002BF75A(void *p); void rva002BF7BE(); };
// _M_buckets read as its storage: retail's operator[] is expanded inline here.
struct Rva002BFA86Buckets { void **m_start; };
namespace _STL {
typedef pair<Rva002BFA86Record const, Rva002BFA86Record> Rva002BFA86Pair;
template <>
void hashtable<Rva002BFA86Pair, Rva002BFA86Record, hash<Rva002BFA86Record>, _Select1st<Rva002BFA86Pair>, equal_to<Rva002BFA86Record>, allocator<Rva002BFA86Pair> >::erase(const const_iterator &it)
{
    _Node *p = it._M_cur;
    if (p) {
        const size_type n = ((Rva000427195 *)this)->bucketIndex((const AsciiString *)&p->_M_val.first);
        _Node *cur = (_Node *)((Rva002BFA86Buckets *)&_M_buckets)->m_start[n];
        if (cur == p) {
            ((Rva002BFA86Buckets *)&_M_buckets)->m_start[n] = cur->_M_next;
            ((Rva002BF75A *)this)->rva002BF75A(cur);
            --_M_num_elements._M_data;
        } else {
            _Node *next = cur->_M_next;
            while (next) {
                if (next == p) {
                    cur->_M_next = next->_M_next;
                    ((Rva002BF75A *)this)->rva002BF75A(next);
                    --_M_num_elements._M_data;
                    break;
                } else {
                    cur = next;
                    next = cur->_M_next;
                }
            }
        }
    }
}
}
