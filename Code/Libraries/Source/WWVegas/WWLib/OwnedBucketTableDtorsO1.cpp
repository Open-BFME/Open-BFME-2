// cl: /O1 /MD /EHsc
// STLport hashtable teardown guide: clear the chains while the bucket vector
// is live, then destroy that vector. Native 0041EBD2..0041EC0B establishes
// clear(0041EA88), bucket storage at +4, and throwing free(00030830).
// Rva0041EA88Clear.cpp establishes the matching +4/+8/+10 table view.
// The source names are address-derived; original container identity is unknown.
void __cdecl free(void *);
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
