// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// Retail 0x005473F7, 57 bytes: clear the bucket chains, then free their array.
// Entry calls at 0x00547479, 0x0054749C and 0x00547BA8; the EH prologue and
// complete epilogue end immediately before Ghidra entry 0x00547430.
// Initializer 0x00547875 independently proves the 20-byte table prefix:
// bucket begin/finish/end at +4/+8/+0xC and the count at +0x10.
// Key/value identities and the first four bytes remain unknown in this view.
//
// Reference lead: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/INI/INIWater.cpp. The WaterTransparencySetting
// destructor has this caller shape, but its name is refuted by the target's
// different member/base callees. This recovery adapts the already-verified
// Rva004271D9Dtor.cpp table-destructor expression and its /O1 /EHs settings.
//
// The Armor template spelling below is only the existing clear-call binding
// at 0x001DBCDC. Retail's 72-byte clear frees nodes without key/value calls;
// its providers reproduce those bytes. No Armor element identity is asserted.
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
struct BucketVec005473F7
{
    void *begin;
    void *finish;
    void *end;
    // ?BucketVec005473F7::~BucketVec005473F7 present-unmatched
    ~BucketVec005473F7() { if (begin) free(begin); }
};
class Rva005473F7
{
public:
    ~Rva005473F7();
private:
    unsigned char opaque0[4];
    BucketVec005473F7 buckets;
    unsigned int count;
};
typedef _STL::hashtable<
    _STL::pair<const NameKeyType, ArmorTemplate>,
    NameKeyType,
    rts::hash<NameKeyType>,
    _STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate> >,
    _STL::equal_to<NameKeyType>,
    _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHashTable005473F7;
Rva005473F7::~Rva005473F7()
{
    reinterpret_cast<ArmorHashTable005473F7 *>(this)->clear();
}