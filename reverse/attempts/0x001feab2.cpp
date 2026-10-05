// ??0Rva001FEAB2@@QAE@XZ
// partial score=0.99 date=2026-10-05
// stlport
// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
#include <hash_map>
enum NameKeyType { NAMEKEY_INVALID = 0, NAMEKEY_MAX = 1 << 23, FORCE_NAMEKEYTYPE_LONG = 0x7fffffff };
namespace rts {
template <class K> struct hash { };
template <> struct hash<NameKeyType> { unsigned int operator()(const NameKeyType &k) const { const unsigned int *w=(const unsigned int*)&k; return (w[1]<<16)+w[0]; } };
template <class K> struct equal_to { bool operator()(const K &l, const K &r) const { return l == r; } };
}
class ArmorTemplate { public: float m_damageCoefficient[38]; };
inline bool operator==(const ArmorTemplate &x, const ArmorTemplate &y) { return x.m_damageCoefficient[0]==y.m_damageCoefficient[0]; }
typedef _STL::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > ArmorTemplateMap;
class Rva001FEAB2 { public: Rva001FEAB2(); private: ArmorTemplateMap m_map; };
// ??0Rva001FEAB2@@QAE@XZ present-unmatched
Rva001FEAB2::Rva001FEAB2() : m_map(100, rts::hash<NameKeyType>(), rts::equal_to<NameKeyType>(), _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> >()) {}
