// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Native Ghidra 40E534..40E589 RET16. The original receiver identity is
// unresolved. Target accesses establish the +1C index and argument wrapper.
class Player;
class Object;
Player *Rva0040C94ALookup(int);
namespace _STL {
template<class T> class allocator {};
template<class T, class A> class list {
public:
    void push_back(const T &);
};
}
class Rva0040C495 {
public:
    Object *rva0040C495(Player *, int);
};
struct Rva0040E534Input { Rva0040C495 *value; };
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
