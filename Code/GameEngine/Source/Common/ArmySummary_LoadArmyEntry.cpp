// cl: /O1 /arch:SSE /G7 /Oy- /MD
// stlport46
// Native Ghidra 40E534..40E589 RET16. The original receiver identity is
// unresolved. Target accesses establish the +1C index and argument wrapper.
class Player;
class Object;
Player *Rva0040C94ALookup(int);
#define _STLP_USE_STATIC_LIB 1
#include <list>
// push_back stays an out-of-line call, as in retail.
namespace _STL { template <> void list<Object *, allocator<Object *> >::push_back(Object *const &); }
#include "../../Include/Common/ArmySummaryEntry.h"
#include "../../Include/Common/Rva0040E534Input.h"
#include "../../Include/GameLogic/ArmySummary.h"
void ArmySummary::LoadArmyEntry(Rva0040E534Input *input, int count,
    _STL::list<Object *, _STL::allocator<Object *> > *out, int overrideIndex)
{
    Player *player = Rva0040C94ALookup(field1C);
    if (player) {
        int selected = overrideIndex ? overrideIndex : field1C;
        for (; count > 0; --count) {
            Object *object = input->value->rva0040C495(player, selected);
            if (object)
                out->push_back(object);
        }
    }
}
