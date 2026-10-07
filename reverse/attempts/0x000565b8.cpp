// ?rva000565B8@Rva0005653C@@QAEXI@Z
// partial score=0.8 date=2026-10-07
// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Semantic lead: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngineDevice/Source/MilesAudioDevice/QueueAudioReference006A2B50.cpp.
// Target Ghidra 0x0005653C and 0x000565B8, 124B each, RET4.
// Target establishes mutex imports; lookup maps BAC/BC0 (20B stride),
// node value+8; four-byte retained local and queue B94. Owner and map roles
// remain neutral. The BFME 1 source supplies the reference/RAII pattern.
#include <list>
#include <utility>

extern "C" __declspec(dllimport) void __stdcall AIL_lock_mutex();
extern "C" __declspec(dllimport) void __stdcall AIL_unlock_mutex();
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);

class OpaqueRefCounted {
public:
    virtual ~OpaqueRefCounted();
    void Release_Ref();
    long volatile references;
};

class Rva000A8C9B {
public:
    void clear();
    // Visible copy of the byte-verified 38B provider in Rva000A8CE5SetRef.cpp.
    // Keep the call while exposing its reference lifetime to MSVC 7.1.
    __declspec(noinline) void rva000A8CE5(OpaqueRefCounted *value) {
        if (value != item) {
            clear();
            item = value;
            if (value)
                InterlockedIncrement(&value->references);
        }
    }
private:
    OpaqueRefCounted *item;
};

class Rva0036CA00Str {
public:
    OpaqueRefCounted *item;
    Rva0036CA00Str() : item(0) {}
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);
    ~Rva0036CA00Str() { if (item) item->Release_Ref(); }
};

class Rva0005653CMilesMutex {
    bool locked;
public:
    Rva0005653CMilesMutex() { AIL_lock_mutex(); locked = true; }
    ~Rva0005653CMilesMutex() { if (locked) AIL_unlock_mutex(); }
};

class Rva0005653C;
namespace _STL {
template <class T> struct hash;
template <class T> struct _Select1st;
template <class T> struct equal_to;
template <class V> struct _Hashtable_node {
    _Hashtable_node<V> *_M_next;
    V _M_val;
};
// Target table view: only the proven lookup contract is needed here.
// Specializing the full header's member template ICEs MSVC 7.1.
template <class V, class K, class H, class X, class E, class A>
class hashtable {
    friend class ::Rva0005653C;
    template <class KT> _Hashtable_node<V> *_M_find(const KT &) const;
    char storage[20];
};
}
typedef _STL::pair<const unsigned int, void *> Rva0005653CValue;
typedef _STL::hashtable<Rva0005653CValue, unsigned int,
    _STL::hash<unsigned int>, _STL::_Select1st<Rva0005653CValue>,
    _STL::equal_to<unsigned int>, _STL::allocator<Rva0005653CValue> >
    Rva0005653CTable;
template <>
void _STL::list<Rva0036CA00Str>::push_back(const Rva0036CA00Str &);

class Rva0005653C {
    char reserved[0xb94];
    _STL::list<Rva0036CA00Str> pending;
    char reservedB98[0xbac - 0xb94 - sizeof(_STL::list<Rva0036CA00Str>)];
    Rva0005653CTable mapBAC;
    Rva0005653CTable mapBC0;
public:
    void rva0005653C(unsigned int key);
    void rva000565B8(unsigned int key);
};

void Rva0005653C::rva0005653C(unsigned int key)
{
    Rva0005653CMilesMutex guard;
    _STL::_Hashtable_node<Rva0005653CValue> *found = mapBAC._M_find(key);
    Rva0036CA00Str value;
    if (found) {
        reinterpret_cast<Rva000A8C9B *>(&value)->rva000A8CE5(
            static_cast<OpaqueRefCounted *>(found->_M_val.second));
        if (value.item)
            pending.push_back(value);
    }
}

void Rva0005653C::rva000565B8(unsigned int key)
{
    Rva0005653CMilesMutex guard;
    _STL::_Hashtable_node<Rva0005653CValue> *found = mapBC0._M_find(key);
    Rva0036CA00Str value;
    if (found) {
        reinterpret_cast<Rva000A8C9B *>(&value)->rva000A8CE5(
            static_cast<OpaqueRefCounted *>(found->_M_val.second));
        if (value.item)
            pending.push_back(value);
    }
}
