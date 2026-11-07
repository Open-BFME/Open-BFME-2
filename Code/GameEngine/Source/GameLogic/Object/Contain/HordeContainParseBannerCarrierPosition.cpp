// cl: /O1 /Oy- /MD /EHs /Oi- /D_STLP_USE_STATIC_LIB
// stlport
//
// ?parseBannerCarrierPosition@@YAXPAVINI@@PAX1PBX@Z, retail 0x0046F179 (270 bytes).
// INI field parser registered as "BannerCarrierPosition" in the parse table at
// 0x00C45530: news a HordeContainUnitSlot (rowed ctor 0x0046AA2F), reads
// "UnitType" <name> and "Pos" <coord2d> with the colon separators (INI +0x420,
// rowed getNextTokenOrNull / getNextToken / parseCoord2D), stores the slot in
// the vector<HordeBannerSlot> field and raises an INIException otherwise.
// The raise is `throw INIException(3, ...)` with FieldParse.h's class
// (constructor 0x0002F681), naming the compiler's __TI1?AVINIException@@
// (retail .rdata 0x008FE2FC). An earlier private POD view made cl copy the
// object first (292 bytes), so the raise was a hand-made _CxxThrowException
// through a zero throw-info anchor.
// Semantic donor: BFME1 reverse/attempts/0x0023e280.cpp.
//
// Byte lever (2026-10-01): the HordeBannerSlot local lives in a block opened
// after the new expression, so the frame slot of the new temporary (held
// across the ctor call for the EH cleanup) is reused by the slot value at
// [ebp-0x10]; declared in the same block as the new, the value owns -0x10 and
// the temporary is pushed to -0x14 (the 1-byte near miss in re_attempts.log).
#include <vector>
#include <string.h>
template<class T> class StringBase {
    void *data;
public:
    void set(const T *);
};
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
class INI {
public:
    char unknown[0x420];
    const char *sepsColon;
    const char *getNextToken(const char *);
    const char *getNextTokenOrNull(const char *);
    static void parseCoord2D(INI *,void *,void *,const void *);
};
class HordeContainUnitSlot {
public:
    StringBase<char> unitType;
    Coord2D pos;
    HordeContainUnitSlot();
};
struct HordeBannerSlot { HordeContainUnitSlot *value; };
namespace _STL {
template <> void vector<HordeBannerSlot>::push_back(const HordeBannerSlot &);
}
#include "../../../../Include/Common/INI/FieldParse.h"
void parseBannerCarrierPosition(INI *ini, void *instance, void *store, const void *userData)
{
  {
    HordeContainUnitSlot *slot = new HordeContainUnitSlot;
    {
      HordeBannerSlot value;
      value.value = slot;
      const char *token = ini->getNextTokenOrNull(ini->sepsColon);
      if (!token || strcmp(token,"UnitType") != 0) goto badUnit;
      slot->unitType.set(ini->getNextToken(ini->sepsColon));
      token = ini->getNextTokenOrNull(ini->sepsColon);
      if (!token || strcmp(token,"Pos") != 0) goto badPos;
      {
        Coord2D pos;
        INI::parseCoord2D(ini,0,&pos,0);
        slot->pos.x = pos.x;
        slot->pos.y = pos.y;
      }
      ((_STL::vector<HordeBannerSlot> *)store)->push_back(value);
      return;
    }
  }
badUnit:
  throw INIException(3,"UnitType expected");
badPos:
  throw INIException(3,"'Pos' expected");
}

