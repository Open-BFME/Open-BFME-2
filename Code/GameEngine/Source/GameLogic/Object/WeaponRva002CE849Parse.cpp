// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_CRTIMP=
// stlport
// The LinearTarget FieldParse row at RVA 0x008011A8 selects this parser.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "../../../Include/GameLogic/WeaponLinearTarget.h"
#include "../../../Include/Common/INI/INI.h"
// g_00BBE3C8 was the retail address alias (RVA 0x007BE3C8) of the constant "X"; the literal is the source.
// g_00BBE3C4 was the retail address alias (RVA 0x007BE3C4) of the constant "Y"; the literal is the source.
struct Rva002CE849Holder {
  char m_pad[0x4C];
  _STL::vector<WeaponLinearTarget> linearTargets;
};
void Rva002CE849Parse(INI *ini, void *instance)
{
  WeaponLinearTarget target;
  target.x = ini->scanReal(ini->getNextSubToken("X"));
  target.y = ini->scanReal(ini->getNextSubToken("Y"));
  target.delay = ini->scanUnsignedInt(ini->getNextSubToken("T"));
  ((Rva002CE849Holder *)instance)->linearTargets.push_back(target);
}
