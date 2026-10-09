// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// STLport hashtable teardown guide: clear the chains while the bucket vector
// is live, then destroy that vector. Native 0041EBD2..0041EC0B establishes
// clear(0041EA88), bucket storage at +4, and throwing free(00030830).
// Rva0041EA88Clear.cpp establishes the matching +4/+8/+10 table view.
// The source names are address-derived; original container identity is unknown.
extern "C" void __cdecl free(void *);
struct OwnedBucketStorage
{
    void **begin;
    void **end;
    void **capacity;
    ~OwnedBucketStorage();
};
// ?OwnedBucketStorage::~OwnedBucketStorage present-unmatched
inline OwnedBucketStorage::~OwnedBucketStorage()
{
    if (begin)
        free(begin);
}
class Rva0041EA88
{
public:
    void rva0041EA88();
    ~Rva0041EA88();
private:
    int m_functors;
    OwnedBucketStorage m_buckets;
    unsigned int m_count;
};
Rva0041EA88::~Rva0041EA88()
{
    rva0041EA88();
}

// Native 0x00057AEE: clear 0x00056DA2 and release the bucket allocation.
class Rva00056DA2
{
public:
    void rva00056DA2();
    ~Rva00056DA2();
private:
    int m_functors;
    OwnedBucketStorage m_buckets;
    unsigned int m_count;
};
Rva00056DA2::~Rva00056DA2() { rva00056DA2(); }

// Native 0x002895BF: clear 0x00289371 and release the bucket allocation.
class Rva00289371HashTable
{
public:
    void clear();
    ~Rva00289371HashTable();
private:
    int m_functors;
    OwnedBucketStorage m_buckets;
    unsigned int m_count;
};
Rva00289371HashTable::~Rva00289371HashTable() { clear(); }

// Native 0x002A91DD: clear 0x002A8FE0 and release the bucket allocation.
class Rva002A8FE0
{
public:
    void rva002A8FE0();
    ~Rva002A8FE0();
private:
    int m_functors;
    OwnedBucketStorage m_buckets;
    unsigned int m_count;
};
Rva002A8FE0::~Rva002A8FE0() { rva002A8FE0(); }

// Native 0x002BFA4D: clear 0x002BF7BE and release the bucket allocation.
class Rva002BF75A
{
public:
    void rva002BF7BE();
    ~Rva002BF75A();
private:
    int m_functors;
    OwnedBucketStorage m_buckets;
    unsigned int m_count;
};
Rva002BF75A::~Rva002BF75A() { rva002BF7BE(); }

// Native 00216B80: rowed 00216AF6 clear, then free the bucket vector.
class Rva00216AF6
{
public:
    void clear();
    ~Rva00216AF6();
private:
    int m_functors;
    OwnedBucketStorage m_buckets;
    unsigned int m_count;
};
Rva00216AF6::~Rva00216AF6() { clear(); }

// Native 002A4052: rowed 002A1D02 clear, then free the bucket vector.
class Rva002A1D02
{
public:
    void clear();
    ~Rva002A1D02();
private:
    int m_functors;
    OwnedBucketStorage m_buckets;
    unsigned int m_count;
};
Rva002A1D02::~Rva002A1D02() { clear(); }

class Rva0041EC0B
{
public:
    void rva0041EC0B();
};
void Rva0041EC0B::rva0041EC0B()
{
    ((Rva0041EA88 *)this)->~Rva0041EA88();
}

class Rva002A9216
{
public:
    void rva002A9216();
};
void Rva002A9216::rva002A9216()
{
    ((Rva002A8FE0 *)this)->~Rva002A8FE0();
}

class Rva002BFB28
{
public:
    void rva002BFB28();
};
void Rva002BFB28::rva002BFB28()
{
    ((Rva002BF75A *)this)->~Rva002BF75A();
}

class Rva000581F5
{
public:
    void rva000581F5();
};
void Rva000581F5::rva000581F5()
{
    ((Rva00056DA2 *)this)->~Rva00056DA2();
}

class Rva00216BF0
{
public:
    void rva00216BF0();
};
void Rva00216BF0::rva00216BF0()
{
    ((Rva00216AF6 *)this)->~Rva00216AF6();
}

class Rva00289706
{
public:
    void rva00289706();
};
void Rva00289706::rva00289706()
{
    ((Rva00289371HashTable *)this)->~Rva00289371HashTable();
}

// Native 2A9140..2A91D8 RET4: look up an integer key and return the mapped
// string reference, inserting a default string when absent. The existing
// table operations prove the iterator/node and returned value addresses;
// ctor523DB7 independently proves the eight-byte int/string record. These
// element spellings bind the already rowed table views, not original types.
// Named record construction also avoids MSVC7.1's crash on a nested template
// temporary. Both string temporaries survive the conditional expression,
// matching the complete native two-state EH graph and guard-bit cleanups.
#include "ascii_string.h"
#include <hash_map>
struct Rva00148B27Element { char bytes[1]; };
struct Rva002A9029Element { char bytes[1]; };
typedef _STL::pair<const int, Rva00148B27Element> StringMapFindValue;
typedef _STL::hashtable<StringMapFindValue, int, _STL::hash<int>,
    _STL::_Select1st<StringMapFindValue>, _STL::equal_to<int>,
    _STL::allocator<StringMapFindValue> > StringMapFindTable;
typedef _STL::pair<const int, Rva002A9029Element> StringMapInsertValue;
typedef _STL::hashtable<StringMapInsertValue, int, _STL::hash<int>,
    _STL::_Select1st<StringMapInsertValue>, _STL::equal_to<int>,
    _STL::allocator<StringMapInsertValue> > StringMapInsertTable;
class Rva00523DB7
{
public:
    Rva00523DB7(const int *, const StringBase<char> &);
    int key;
    AsciiString mapped;
};
class Rva002A9140
{
public:
    AsciiString &rva002A9140(const int &key);
};
AsciiString &Rva002A9140::rva002A9140(const int &key)
{
    void *node;
    {
        StringMapFindTable::iterator it = reinterpret_cast<StringMapFindTable *>(this)->find(key);
        node = it._M_cur;
    }
    return *reinterpret_cast<AsciiString *>(!node ?
        reinterpret_cast<char *>(&reinterpret_cast<StringMapInsertTable *>(this)->_M_insert(
            reinterpret_cast<const StringMapInsertValue &>(Rva00523DB7(&key,
                reinterpret_cast<const StringBase<char> &>(AsciiString()))))) + 4 :
        reinterpret_cast<char *>(node) + 8);
}

