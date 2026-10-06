// cl: /MD /EHs
// Descriptive donor name, not a recovered PC symbol. BFME1 banked source:
// reference/open-bfme-1/reverse/attempts/0x0023e280.cpp.
// BFME1 BannerCarrierPosition donor defines string + two floats. PC callback
// 46F179 allocates 12B and calls 46AA2F; constructor passes empty string to
// verified StringBase<char> C-string ctor37BA0 then zeroes floats at4 and8.
class HordeContainUnitSlot;
template<class T> class StringBase {
    void *data;
    StringBase(const T *);
    friend class HordeContainUnitSlot;
};
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
class HordeContainUnitSlot {
public:
    StringBase<char> unitType;
    Coord2D pos;
    HordeContainUnitSlot();
};
HordeContainUnitSlot::HordeContainUnitSlot() : unitType("")
{
    pos.x = 0;
    pos.y = 0;
}
