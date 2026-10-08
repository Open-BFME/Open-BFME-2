// cl: /O1 /Oy /DNDEBUG /MD
// Native0046E740..0046E7C2 RET4: measured module receiver+8, countdown27C,
// state26C, owner AI258, owner definition264 count24, and owner query24C.
// Existing caller0046E7C2 passes zero through the int-address-view pin;
// this entry consumes only its low byte. Preserve that measured ABI.
// Target providers28AF76 (Object getter) and4B0FA0 (Gen_0028EF10 bool
// getter) are independently rowed. Full567B callee46CF21..46D158 uses this
// state26C and resets countdown27C on its successful paths; plain RET,
// no incoming stack arguments. Its semantic name remains unestablished.
#include "../../../Common/GameLogicObjectLookupView.h"
class Gen_0028EF10 {
public:
    bool rva004B0FA0();
};
struct Rva0046E740Definition {
    char unknown00[0x24];
    int count;
};
class Object {
public:
    int rva0028AF76() const;
    char unknown00[0x24C];
    Gen_0028EF10 *query;
    char unknown250[8];
    void *ai;
    char unknown25C[8];
    Rva0046E740Definition *definition;
};
struct Rva0046E740Countdown {
    unsigned int value;
    __forceinline void advance() { if (value) --value; }
    __forceinline bool active() const { return value > 0; }
};
extern GameLogic *TheGameLogic;
extern int g_00DBA4E4;
class Rva0046E740 {
public:
    void rva0046E740(int);
    void rva0046CF21();
    char unknown00[8];
    Object *owner;
    char unknown0C[0x26C - 0x0C];
    int state;
    char unknown270[0x27C - 0x270];
    Rva0046E740Countdown countdown;
};
void Rva0046E740::rva0046E740(int flags)
{
    Object *object = owner;
    if (!object->ai)
        return;
    countdown.advance();
    if (countdown.active() || state != 0 || object->definition->count <= 1)
        return;
    Gen_0028EF10 *query = object->query;
    if (query ? query->rva004B0FA0() : false)
        return;
    if ((unsigned char)flags == 0) {
        unsigned int frame = TheGameLogic->getFrame();
        if ((unsigned int)object->rva0028AF76() >= frame - g_00DBA4E4 * 4)
            return;
    }
    rva0046CF21();
}
