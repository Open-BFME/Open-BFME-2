// cl: /DNDEBUG /MD /EHs-c-
// stlport
// ?Rva002CE849Parse@@YAXPAVINI@@PAX@Z @0x002CE849 97B: INI X/Y float plus unsigned parse pushing Coord3D to vector at +0x4C via rowed push_back 0x002CE7DC.
// Evidence: chain lane calls 0x002CE7DC; callees rowed getNextSubToken 0x2E06B scanReal 0x2EDA5 scanUnsignedInt 0x2ED3A; no callers.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
struct Coord3D {
  float x, y, z;
};
// Declaration-only _Construct: retail's push_back calls the pinned out-of-line
// helper (0x002CA82C) instead of inlining the element copy (row 35 family-LK3).
namespace _STL {
template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &);
}
class INI {
public:
  const char *getNextSubToken(const char *expected);
  float scanReal(const char *token);
  unsigned int scanUnsignedInt(const char *token);
};
extern const char g_00BBE3C8[];
extern const char g_00BBE3C4[];
extern const char g_00C02174[];
struct Rva002CE849Holder {
  char m_pad[0x4C];
  _STL::vector<Coord3D> m_vec;
};
void Rva002CE849Parse(INI *ini, void *instance)
{
  Coord3D tmp;
  tmp.x = ini->scanReal(ini->getNextSubToken(g_00BBE3C8));
  tmp.y = ini->scanReal(ini->getNextSubToken(g_00BBE3C4));
  *(unsigned int *)&tmp.z = ini->scanUnsignedInt(ini->getNextSubToken(g_00C02174));
  ((Rva002CE849Holder *)instance)->m_vec.push_back(tmp);
}
