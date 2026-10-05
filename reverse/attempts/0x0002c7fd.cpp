// ?rehash@Rva0002C7FD@@QAEXI@Z
// partial score=0.981 date=2026-10-05
// ?rehash@Rva0002C7FD@@QAEXI@Z
// partial score=0.981 date=2026-10-04
// cl: /O1 /G5 /EHsc /MD
// Native STLport rehash at 0x0002C7FD..0x0002C8D3 (RET4).
// Algorithm: STLport 4.5.3 stl/_hashtable.c at BFME1 1281192f68.
// Target facts: bucket vector at +4; node next at +0, AsciiString key at +4;
// calls existing next-size 5571B, hash 2BF8C and vector helpers. The owning
// container and mapped payload are unknown, so retain an address-derived name.
class Rva0002C7FD;
class AsciiString;
class ArmorTemplate;
enum NameKeyType { NAMEKEY_INVALID = 0 };
void __cdecl free(void *);
namespace rts {
template<class T> struct hash {};
template<> struct hash<AsciiString> { unsigned int operator()(const AsciiString &) const; };
template<class T> struct equal_to {};
}
namespace _STL {
template<class A,class B> struct pair {};
template<class T> struct _Select1st {};
template<class T> class allocator { public: allocator() {} allocator(const allocator &) {} };
template<class V,class K,class H,class S,class E,class A> class hashtable {
friend class ::Rva0002C7FD;
private: unsigned int _M_next_size(unsigned int) const;
};
template<class T,class A> class vector {
public:
    T *first, *last, *end;
    vector(unsigned int, const T &, const A &);
    A get_allocator() const;
    unsigned int size() const { return last-first; }
    T &operator[](unsigned int n) { return first[n]; }
    T *data() { return first; }
    void swap(vector &);
    ~vector() { if (first) free(first); }
};
}
typedef _STL::pair<const NameKeyType,ArmorTemplate> ArmorPair;
typedef _STL::hashtable<ArmorPair,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<ArmorPair>,rts::equal_to<NameKeyType>,_STL::allocator<ArmorPair> > GrowthTable;
typedef _STL::vector<void *,_STL::allocator<void *> > Buckets;
struct RehashNode0002C7FD { RehashNode0002C7FD *next; };
class Rva0002C7FD {
    char prefix[4];
    Buckets buckets;
public: void rehash(unsigned int);
};
void Rva0002C7FD::rehash(unsigned int hint)
{
    const unsigned int old_count = buckets.size();
    if (hint > old_count) {
        const unsigned int count = reinterpret_cast<const GrowthTable *>(this)->_M_next_size(hint);
        if (count > old_count) {
            union { void *zero; unsigned int bucket; } scratch;
            scratch.zero = 0;
            Buckets tmp(count, scratch.zero, buckets.get_allocator());
            for (scratch.bucket=0; scratch.bucket<old_count; ++scratch.bucket) {
                RehashNode0002C7FD *node = (RehashNode0002C7FD *)buckets[scratch.bucket];
                while (node) {
                    unsigned int next_bucket = (*reinterpret_cast<const rts::hash<AsciiString> *>(this))(*reinterpret_cast<const AsciiString *>(node+1)) % count;
                    *(buckets.first + scratch.bucket) = node->next;
                    void **head = tmp.data() + next_bucket;
                    node->next = (RehashNode0002C7FD *)*head;
                    *head = node;
                    node = (RehashNode0002C7FD *)buckets[scratch.bucket];
                }
            }
            buckets.swap(tmp);
        }
    }
}
