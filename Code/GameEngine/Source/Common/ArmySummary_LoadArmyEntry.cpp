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
class ArmySummaryEntry {
public:
    Object *rva0040C495(Player *, int);
};
struct Rva0040E534Input { ArmySummaryEntry *value; };
class ArmySummary {
public:
    void LoadArmyEntry(Rva0040E534Input *, int,
        _STL::list<Object *, _STL::allocator<Object *> > *, int);
private:
    char unknown[0x1c];
    int index;
};
void ArmySummary::LoadArmyEntry(Rva0040E534Input *input, int count,
    _STL::list<Object *, _STL::allocator<Object *> > *out, int overrideIndex)
{
    Player *player = Rva0040C94ALookup(index);
    if (player) {
        int selected = overrideIndex ? overrideIndex : index;
        for (; count > 0; --count) {
            Object *object = input->value->rva0040C495(player, selected);
            if (object)
                out->push_back(object);
        }
    }
}
