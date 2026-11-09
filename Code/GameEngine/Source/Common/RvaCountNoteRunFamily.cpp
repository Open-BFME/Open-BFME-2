// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Five pre-increment-then-two-call members (36B each): push esi,
// mov esi, ecx, mov eax, [esi+0x10], inc eax, push eax, call <note>,
// push [esp+0x0C], mov ecx, esi, push [esp+0x0C], call <run>,
// mov eax, [esp+8], pop esi, ret 8. Each passes m_count+1 (loaded, not
// stored) to its note helper, then (a, b) to its run helper, and returns
// a. /O1 keeps the argument reads on the stack slots.
// 0x00057B27 (note 0x00056BFE, run 0x00054BC3),
// 0x00057D38 (note 0x0053F1EC-opaque-alias of the rowed Armor hashtable
//   resize, run 0x000556AB),
// 0x000E0536 (note 0x000E0322, run 0x000E0298),
// 0x003EF34A (note 0x00212858, run 0x003EF264),
// 0x0052B7F8 (note 0x00212858, run 0x0052B737).
// Helper identities unproven (opaque pins); owner names address-derived.
// One ledger row per member.

#pragma comment(linker, "/alternatename:??1Rva0052B7B3Dtor@@QAE@XZ=?j_0052b7b3@@YAXXZ")
#pragma comment(linker, "/alternatename:?note@Rva00056BFESub@@QAEXH@Z=?resize@?$hashtable@PAURva00051107AudioRequest@@PAU1@URva00051B89Hash@@U?$_Identity@PAURva00051107AudioRequest@@@_STL@@URva00050E1CEqualTo@@V?$allocator@PAURva00051107AudioRequest@@@4@@_STL@@QAEXI@Z")
#pragma comment(linker, "/alternatename:?note@Rva0053F1ECSub@@QAEXH@Z=?resize@?$hashtable@U?$pair@$$CBH_N@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBH_N@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBH_N@_STL@@@2@@_STL@@QAEXI@Z")
#pragma comment(linker, "/alternatename:?run@Rva00054BC3Sub@@QAEXHH@Z=?insert_unique_noresize@?$hashtable@PAURva00051107AudioRequest@@PAU1@URva00051B89Hash@@U?$_Identity@PAURva00051107AudioRequest@@@_STL@@URva00050E1CEqualTo@@V?$allocator@PAURva00051107AudioRequest@@@4@@_STL@@QAE?AU?$pair@U?$_Ht_iterator@PAURva00051107AudioRequest@@U?$_Nonconst_traits@PAURva00051107AudioRequest@@@_STL@@PAU1@URva00051B89Hash@@U?$_Identity@PAURva00051107AudioRequest@@@3@URva00050E1CEqualTo@@V?$allocator@PAURva00051107AudioRequest@@@3@@_STL@@_N@2@ABQAURva00051107AudioRequest@@@Z")
#pragma comment(linker, "/alternatename:?run@Rva000556ABSub@@QAEXHH@Z=?insert_unique_noresize@?$hashtable@URva000556ABRecord@@U1@U?$hash@URva000556ABRecord@@@_STL@@U?$_Identity@URva000556ABRecord@@@3@U?$equal_to@URva000556ABRecord@@@3@V?$allocator@URva000556ABRecord@@@3@@_STL@@QAE?AU?$pair@U?$_Ht_iterator@URva000556ABRecord@@U?$_Nonconst_traits@URva000556ABRecord@@@_STL@@U1@U?$hash@URva000556ABRecord@@@3@U?$_Identity@URva000556ABRecord@@@3@U?$equal_to@URva000556ABRecord@@@3@V?$allocator@URva000556ABRecord@@@3@@_STL@@_N@2@ABURva000556ABRecord@@@Z")
#pragma comment(linker, "/alternatename:?run@Rva000E0298Sub@@QAEXHH@Z=?rva000E0298@Rva000E01B0@@QAE?AUNativeInsertResult@@ABURva000E007DPair@@@Z")


class Rva00056BFESub
{
public:
	void note(int value);
};

class Rva00054BC3Sub
{
public:
	void run(int a, int b);
};

class Rva0053F1ECSub
{
public:
	void note(int value);
};

class Rva000556ABSub
{
public:
	void run(int a, int b);
};

class Rva000E0322
{
public:
	void rva000E0322(unsigned int value);
};

class Rva000E0298Sub
{
public:
	void run(int a, int b);
};

#include "../../Include/GameLogic/Rva000427195.h"

struct InsertRet003EF264;
class Rva003EF264Sub
{
public:
    InsertRet003EF264 *run(int resultAddress, int keyAddress);
    void *unused;
    void **buckets;
    void **bucketEnd;
    void **storageEnd;
    unsigned count;
};

struct InsertRet0052B737
{
    void *node;
    void *owner;
    unsigned char inserted;
    InsertRet0052B737 *set(void *nodeValue, void *ownerValue, unsigned char insertionFlag)
    {
        node = nodeValue;
        owner = ownerValue;
        inserted = insertionFlag;
        return this;
    }
};
class Rva0052B737Sub
{
public:
    InsertRet0052B737 *run(int resultAddress, int keyAddress);
    void *unused;
    void **buckets;
    void **bucketEnd;
    void **storageEnd;
    unsigned count;
};

class Rva00057B27Owner
{
public:
	int fwd(int resultAddress, int entryAddress);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva00057D38Owner
{
public:
	int fwd(int resultAddress, int entryAddress);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva000E0536Owner
{
public:
	int fwd(int resultAddress, int entryAddress);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva003EF34AOwner
{
public:
	int fwd(int resultAddress, int entryAddress);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva0052B7F8Owner
{
public:
	int fwd(int resultAddress, int entryAddress);

private:
	char m_pad[0x10];
	int m_count;
};

int Rva00057B27Owner::fwd(int resultAddress, int entryAddress)
{
	int nextCount = m_count + 1;
	((Rva00056BFESub *)this)->note(nextCount);
	((Rva00054BC3Sub *)this)->run(resultAddress, entryAddress);
	return resultAddress;
}

int Rva00057D38Owner::fwd(int resultAddress, int entryAddress)
{
	int nextCount = m_count + 1;
	((Rva0053F1ECSub *)this)->note(nextCount);
	((Rva000556ABSub *)this)->run(resultAddress, entryAddress);
	return resultAddress;
}

int Rva000E0536Owner::fwd(int resultAddress, int entryAddress)
{
	int nextCount = m_count + 1;
	((Rva000E0322 *)this)->rva000E0322(nextCount);
	((Rva000E0298Sub *)this)->run(resultAddress, entryAddress);
	return resultAddress;
}

int Rva003EF34AOwner::fwd(int resultAddress, int entryAddress)
{
	int nextCount = m_count + 1;
	((Rva000427195 *)this)->rva00212858(nextCount);
	((Rva003EF264Sub *)this)->run(resultAddress, entryAddress);
	return resultAddress;
}

int Rva0052B7F8Owner::fwd(int resultAddress, int entryAddress)
{
	int nextCount = m_count + 1;
	((Rva000427195 *)this)->rva00212858(nextCount);
	((Rva0052B737Sub *)this)->run(resultAddress, entryAddress);
	return resultAddress;
}

// cl: /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Native Ghidra 0x0052B894..0x0052B8ED: 89B RET4 constructor.
// It writes the base vptr, copies the input AsciiString into an 8B
// (name, this) entry, inserts it through the registry, then destroys the
// temporary. Result storage is the observed 12B iterator/result area.
// The owner and registry identities remain unknown; names describe their
// measured addresses and operations. The base vtable is already provided
// as ??_7Rva0052B668@@6B@, its data-ledger name.
#include "ascii_string.h"
extern "C" const void *const __identifier("??_7Rva0052B668@@6B@")[];
extern Rva0052B7F8Owner *rva0052B84F();
class Rva0052B668
{
public:
    Rva0052B668(const AsciiString &name);
private:
    const void *const *m_vtable;
};
struct Rva0052B894Entry
{
    AsciiString name;
    Rva0052B668 *registration;
    Rva0052B894Entry(const AsciiString &key, Rva0052B668 *value)
        : name(key), registration(value) {}
};
Rva0052B668::Rva0052B668(const AsciiString &name)
{
    m_vtable = __identifier("??_7Rva0052B668@@6B@");
    Rva0052B894Entry entry(name, this);
    int result[3];
    Rva0052B7F8Owner *registry = rva0052B84F();
    registry->fwd((int)result, (int)&entry);
}

// stlport
#include <hash_map>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
// The native getter at 0x0052B84F..0x0052B894 constructs one 20B local
// static registry through the existing hash_map constructor at 0x0052B81C.
// Its atexit thunk at 0x007B9298 destroys the registry through 0x0052B7B3.
// Reuse the rowed constructor's ABI view; its int key and element type are
// donor inferences, not established identities of the registration table.
// STLport 4.5.3 comes from the unchanged vendor subtree at BFME 1 revision
// 7dff0a4a9e937818d2731f9861ade1815663b9db.
struct Rva0052B81CElement
{
    char bytes[1];
    bool operator<(const Rva0052B81CElement &) const;
    bool operator==(const Rva0052B81CElement &) const;
};
namespace _STL
{
    template<> struct hash<Rva0052B81CElement>
    {
        unsigned operator()(const Rva0052B81CElement &) const;
    };
}
typedef _STL::hash_map<int, Rva0052B81CElement> Rva0052B84FRegistry;
// The destructor retail reaches here is 0x0052B7B3, a jump to this row; it takes this object in ecx.
extern "C" { void __identifier("??1Rva0052B6FE@@QAE@XZ")(); }
class Rva0052B7B3Dtor
{
public:
    __declspec(noinline) ~Rva0052B7B3Dtor() { __identifier("??1Rva0052B6FE@@QAE@XZ")(); }
};
namespace _STL
{
    // Leave construction to the independently rowed 31B provider. The
    // measured destructor thunk also avoids instantiating inferred element
    // operations when destroying this opaque registry.
    template<> Rva0052B84FRegistry::hash_map();
    template<> inline Rva0052B84FRegistry::~hash_map()
    {
        reinterpret_cast<Rva0052B7B3Dtor *>(this)->~Rva0052B7B3Dtor();
    }
}
Rva0052B7F8Owner *rva0052B84F()
{
    static Rva0052B84FRegistry registry;
    return reinterpret_cast<Rva0052B7F8Owner *>(&registry);
}

// Native 0x0052B737..0x0052B7B3: 124B RET8 unique insertion. The caller
// at 0x0052B7F8 supplies a 12B result area and an 8B entry. Registration
// construction at 0x0052B894 establishes (AsciiString, registration pointer).
// Compare 0x000069D6 and bucketIndex 0x00223149 prove the string key; node
// allocation at 0x0052B6D9 proves next at +0 and the copied entry at +4.
// Reuse the already rowed node provider's nominal STLport ABI view below.
// Its int/element spelling is an inference; this routine treats that view
// only as the 8B entry passed to its externally defined copy operation.
// The control flow also agrees with the independently recovered 124B
// sibling at 0x00212A5A and STLport 4.5.3 insert_unique_noresize.
struct Rva0052B6D9Element { char bytes[1]; bool operator<(const Rva0052B6D9Element&) const; bool operator==(const Rva0052B6D9Element&) const; };
namespace _STL {
template<> struct hash<Rva0052B6D9Element> { unsigned operator()(const Rva0052B6D9Element&) const; };
typedef pair<int const, Rva0052B6D9Element> Rva0052B6D9Pair;
template<> class hashtable<Rva0052B6D9Pair, int, hash<int>, _Select1st<Rva0052B6D9Pair>, equal_to<int>, allocator<Rva0052B6D9Pair> >
{
friend class ::Rva0052B737Sub;
    _Hashtable_node<Rva0052B6D9Pair> *_M_new_node(const Rva0052B6D9Pair &value);
};
typedef hashtable<Rva0052B6D9Pair, int, hash<int>, _Select1st<Rva0052B6D9Pair>, equal_to<int>, allocator<Rva0052B6D9Pair> > Rva0052B6D9Provider;
}
InsertRet0052B737 *Rva0052B737Sub::run(int resultAddress, int keyAddress)
{
    InsertRet0052B737 *result=(InsertRet0052B737*)resultAddress;
    const void *key=(const void*)keyAddress;
    int bucket=((Rva000427195*)this)->bucketIndex((const AsciiString*)key);
    void *head=buckets[bucket];
    void *currentNode=head;
    if(currentNode!=0)
    {
        do
        {
            if(((const StringBase<char>*)((const char*)currentNode+4))->compare(*(const StringBase<char>*)key)==0)
                return result->set(currentNode,this,0);
            currentNode=*(void**)currentNode;
        } while(currentNode!=0);
    }
    void *node=((_STL::Rva0052B6D9Provider*)this)->_M_new_node(*(const _STL::Rva0052B6D9Pair*)key);
    *(void**)node=head;
    buckets[bucket]=node;
    ++count;
    return result->set(node,this,1);
}

// Native 003EF264..003EF2E0: target insertion entry constructed by
// region parser003EF467 is (AsciiString, manager pointer). Calls223149,
// 69D6 and003EF066 prove hashing, string comparison and node creation.
// Existing node provider has an address-derived nominal STL ABI view;
// use it only for the observed copied 8B entry, preserving its uncertainty.
struct InsertRet003EF264
{
    void *node;
    void *owner;
    unsigned char inserted;
    InsertRet003EF264 *set(void *nodeValue, void *ownerValue, unsigned char insertionFlag)
    {
        node = nodeValue;
        owner = ownerValue;
        inserted = insertionFlag;
        return this;
    }
};
struct Rva003EF066Element { char bytes[1]; bool operator<(const Rva003EF066Element&) const; bool operator==(const Rva003EF066Element&) const; };
namespace _STL {
template<> struct hash<Rva003EF066Element> { unsigned operator()(const Rva003EF066Element&) const; };
typedef pair<int const, Rva003EF066Element> Rva003EF066Pair;
template<> class hashtable<Rva003EF066Pair, int, hash<int>, _Select1st<Rva003EF066Pair>, equal_to<int>, allocator<Rva003EF066Pair> >
{
friend class ::Rva003EF264Sub;
    _Hashtable_node<Rva003EF066Pair> *_M_new_node(const Rva003EF066Pair &value);
};
typedef hashtable<Rva003EF066Pair, int, hash<int>, _Select1st<Rva003EF066Pair>, equal_to<int>, allocator<Rva003EF066Pair> > Rva003EF066Provider;
}

InsertRet003EF264 *Rva003EF264Sub::run(int resultAddress, int keyAddress)
{
    InsertRet003EF264 *result=(InsertRet003EF264*)resultAddress;
    const void *key=(const void*)keyAddress;
    int bucket=((Rva000427195*)this)->bucketIndex((const AsciiString*)key);
    void *head=buckets[bucket];
    void *currentNode=head;
    if(currentNode!=0)
    {
        do
        {
            if(((const StringBase<char>*)((const char*)currentNode+4))->compare(*(const StringBase<char>*)key)==0)
                return result->set(currentNode,this,0);
            currentNode=*(void**)currentNode;
        } while(currentNode!=0);
    }
    void *node=((_STL::Rva003EF066Provider*)this)->_M_new_node(*(const _STL::Rva003EF066Pair*)key);
    *(void**)node=head;
    buckets[bucket]=node;
    ++count;
    return result->set(node,this,1);
}

// Native 3EF3F7..3EF40B (20B, ret 8), after Rva003EF34AOwner::fwd: one more
// level of the same hidden-result forwarding - pass both words to that fwd
// on the same object and return the first (the result slot). Orphan .text
// hole with no surviving reference; owner and name are address-derived.
class Rva003EF3F7Owner
{
public:
	int fwd(int resultAddress, int entryAddress);
};

int Rva003EF3F7Owner::fwd(int resultAddress, int entryAddress)
{
	((Rva003EF34AOwner *)this)->fwd(resultAddress, entryAddress);
	return resultAddress;
}

// Names this unit references that no unit defines under that spelling. Each is
// bound to the row that owns the pinned retail address (same address, same
// body); the pin keeps the name, the row supplies the definition.
#pragma comment(linker, "/alternatename:??1Rva0052B7B3Dtor@@QAE@XZ=?j_0052b7b3@@YAXXZ")
#pragma comment(linker, "/alternatename:?note@Rva00056BFESub@@QAEXH@Z=?resize@?$hashtable@PAURva00051107AudioRequest@@PAU1@URva00051B89Hash@@U?$_Identity@PAURva00051107AudioRequest@@@_STL@@URva00050E1CEqualTo@@V?$allocator@PAURva00051107AudioRequest@@@4@@_STL@@QAEXI@Z")
#pragma comment(linker, "/alternatename:?note@Rva0053F1ECSub@@QAEXH@Z=?resize@?$hashtable@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@_STL@@QAEXI@Z")
#pragma comment(linker, "/alternatename:?run@Rva00054BC3Sub@@QAEXHH@Z=?insert_unique_noresize@?$hashtable@PAURva00051107AudioRequest@@PAU1@URva00051B89Hash@@U?$_Identity@PAURva00051107AudioRequest@@@_STL@@URva00050E1CEqualTo@@V?$allocator@PAURva00051107AudioRequest@@@4@@_STL@@QAE?AU?$pair@U?$_Ht_iterator@PAURva00051107AudioRequest@@U?$_Nonconst_traits@PAURva00051107AudioRequest@@@_STL@@PAU1@URva00051B89Hash@@U?$_Identity@PAURva00051107AudioRequest@@@3@URva00050E1CEqualTo@@V?$allocator@PAURva00051107AudioRequest@@@3@@_STL@@_N@2@ABQAURva00051107AudioRequest@@@Z")
#pragma comment(linker, "/alternatename:?run@Rva000556ABSub@@QAEXHH@Z=?insert_unique_noresize@?$hashtable@URva000556ABRecord@@U1@U?$hash@URva000556ABRecord@@@_STL@@U?$_Identity@URva000556ABRecord@@@3@U?$equal_to@URva000556ABRecord@@@3@V?$allocator@URva000556ABRecord@@@3@@_STL@@QAE?AU?$pair@U?$_Ht_iterator@URva000556ABRecord@@U?$_Nonconst_traits@URva000556ABRecord@@@_STL@@U1@U?$hash@URva000556ABRecord@@@3@U?$_Identity@URva000556ABRecord@@@3@U?$equal_to@URva000556ABRecord@@@3@V?$allocator@URva000556ABRecord@@@3@@_STL@@_N@2@ABURva000556ABRecord@@@Z")
#pragma comment(linker, "/alternatename:?run@Rva000E0298Sub@@QAEXHH@Z=?rva000E0298@Rva000E01B0@@QAE?AUNativeInsertResult@@ABURva000E007DPair@@@Z")
