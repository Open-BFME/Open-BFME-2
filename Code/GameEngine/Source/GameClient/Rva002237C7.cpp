// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva002237C7@Rva00223591@@QAEPAXPBX@Z @0x002237C7 68B
// Hashtable insert for 16-byte node (4 next + 12 BfmeStringRecord00222E08): grow via pinned 0x00212858 then bucket via rowed 0x00223149 then new-node via rowed 0x0022356C then link and return node+4.
// Evidence: same shape as rowed Rva00223591::rva00223854 in Rva00223591Free.cpp; neighbours 0x00223736 erase and 0x0022380B clear share layout +4 buckets +0x10 count; unblocks 0x0022402A.
#include "ascii_string.h"

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *name);
};

class Rva0022356C
{
public:
	void *rva0022356C(const void *obj);
};

class Rva00223591
{
public:
	void *rva002237C7(const void *arg);
private:
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void *Rva00223591::rva002237C7(const void *arg)
{
	((Rva000427195 *)this)->rva00212858(m_numElements + 1);
	int b = ((Rva000427195 *)this)->bucketIndex((const AsciiString *)arg);
	void *old = m_beginBuckets[b];
	void *n = ((Rva0022356C *)this)->rva0022356C(arg);
	*(void **)n = old;
	m_beginBuckets[b] = n;
	++m_numElements;
	return (char *)n + 4;
}

// Native22402A..2240CB RET4; WB and the existing insert provider establish
// name lookup/default insertion of {reference pointer, index}. Native clears
// both value words, constructs a 12-byte record at22407F through22307F, and
// destroys it through the existing pair cleanup222C5A. That cleanup reads
// key+0 and ref-pointer+4; the POD index at+8 requires no cleanup. Keep the
// existing constructor/destructor owners rather than inventing alias pins.
struct TargetRef00217D4C { virtual void *destroy(unsigned); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva00056F61;
struct Rva0041534BIter {
    void *m_node; Rva00056F61 *m_table;
    Rva0041534BIter(void *n,Rva00056F61 *t):m_node(n),m_table(t){}
};
class Rva00056F61 { public: __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *); };
class Rva00468520 {
public:
    TargetRef00217D4C *m_ptr; int m_index;
    Rva00468520():m_ptr(0),m_index(0){}
    Rva00468520 *set(const Rva00468520 *) throw();
    ~Rva00468520() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
// Call-only projection of the existing cleanup: it reads the string at +0
// and reference pointer at +4; the extra index at +8 needs no destruction.
struct TreeHintRef00222C5A;
namespace _STL { template<class A,class B> struct pair { ~pair(); }; }
typedef _STL::pair<const AsciiString,TreeHintRef00222C5A> NativeCleanupPair;
class Rva0022307F {
    union { unsigned int m_align; unsigned char m_native[12]; };
public:
    Rva0022307F(const AsciiString &,const Rva00468520 &);
    __forceinline ~Rva0022307F() { ((NativeCleanupPair *)this)->~NativeCleanupPair(); }
};

class Rva0022402A { public: Rva00468520 &rva0022402A(const AsciiString &); };
Rva00468520 &Rva0022402A::rva0022402A(const AsciiString &key)
{
    void *node;
    {
        Rva0041534BIter found=((Rva00056F61 *)this)->rva0041534B(&key);
        node=found.m_node;
    }
    return *(Rva00468520 *)(node==0
        ? (char *)((Rva00223591 *)this)->rva002237C7(
            &static_cast<const Rva0022307F &>(Rva0022307F(key,Rva00468520())))+4
        : (char *)node+8);
}
