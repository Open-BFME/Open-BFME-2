// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/vendor/stlport/stl
// stlport
// The member at XferSave+0x18 is opaque in the target declaration. Retail
// calls the matched NameKeyType/FXList hashtable clear body on this object,
// then frees its bucket array at +4. This is a layout/operation view; the
// member's higher-level owner and purpose remain unclaimed.
#define _STLP_USE_NEWALLOC 1
#include <stddef.h>
#include <hash_map>
#include <list>

extern "C" void __cdecl free(void *block) throw(...);

enum NameKeyType
{
    NAMEKEY_INVALID = 0,
    NAMEKEY_MAX = 1 << 23,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class FXNugget;
class FXListStore;
class INI;
class Object;
class Matrix3D;
class Coord3D;
typedef float Real;

// Exact FXList declaration from reference/open-bfme-1/.../GameClient/FXList.h
// (class definition, lines 123-186); this body only calls its rowed map clear.
class FXList
{
public:
    FXList();
    virtual ~FXList();
    void clear();
    void addFXNugget(FXNugget *fxn) { m_nuggets.push_back(fxn); }
    inline static void doFXPos(const FXList *fx, const Coord3D *primary,
        const Matrix3D *primaryMtx = NULL, const Real primarySpeed = 0.0f,
        const Coord3D *secondary = NULL, const Real overrideRadius = 0.0f)
    {
        if (fx) fx->doFXPos(primary, primaryMtx, primarySpeed, secondary, overrideRadius);
    }
    inline static void doFXObj(const FXList *fx, const Object *primary,
        const Object *secondary = NULL)
    {
        if (fx)
        {
            fx->doFXObj(primary, secondary);
        }
    }

protected:
    void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx,
        const Real primarySpeed, const Coord3D *secondary,
        const Real overrideRadius) const;
    void doFXObj(const Object *primary, const Object *secondary) const;

private:
    typedef std::list<FXNugget *> FXNuggetList;
    FXNuggetList m_nuggets;
};

typedef bool Bool;
typedef unsigned int UnsignedInt;

namespace rts
{
    template <typename T> struct hash
    {
        size_t operator()(const T& __t) const
        {
            std::hash<T> tmp;
            return tmp(__t);
        }
    };
    template <typename T> struct equal_to
    {
        Bool operator()(const T& __t1, const T& __t2) const
        {
            return (__t1 == __t2);
        }
    };
    template <> struct hash<NameKeyType>
    {
        size_t operator()(NameKeyType nkt) const
        {
            std::hash<UnsignedInt> tmp;
            return tmp((UnsignedInt)nkt);
        }
    };
}

typedef std::hash_map<NameKeyType, FXList, rts::hash<NameKeyType>,
    rts::equal_to<NameKeyType> > Rva0060D031Map;

struct Rva0060D031BucketArray
{
    void *begin;
    void *end;
    void *capacity;
    __forceinline ~Rva0060D031BucketArray()
    {
        if (begin) free(begin);
    }
};

struct Rva0060D031Member
{
    // The rowed hashtable clear uses buckets at +4 and its count at +0x10.
    unsigned char opaque[4];
    Rva0060D031BucketArray buckets;
    unsigned int count;
    __declspec(noinline) ~Rva0060D031Member();
};

// ??1Rva0060D031Member@@QAE@XZ
Rva0060D031Member::~Rva0060D031Member()
{
    ((Rva0060D031Map *)this)->clear();
}
