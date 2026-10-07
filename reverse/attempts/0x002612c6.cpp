// ?rva002612C6@Rva002612C6@@QAE_NPAVObject@@@Z
// partial score=0.96 date=2026-10-07
// ?rva002612C6@Rva002612C6@@QAE_NPAVObject@@@Z
// partial score=0.94 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native 002612C6..00261353, 141B, RET4. Object readers and callback are
// already rowed; ActionManager ABI is the verified BFME six-argument view.
// Receiver owner+8/flag+C, Object interface+250, slots10/110 and an 8-byte
// callback state (owner+0, bool+4) are target facts. Original method names unknown.
class Object
{
public:
    int rva0028D481() const;
    bool rva0028D4C4() const;
};
void iterRel001DCF20(Object *object, void *state);
enum CommandSourceType { CMD_FROM_AI = 2 };
enum CanEnterType { ENTER_MODE_ZERO = 0 };
class BFMEActionManager
{
public:
    bool canEnterObject(const Object *owner, const Object *target,
        CommandSourceType source, CanEnterType mode, int options, bool *outFlag);
};
class ActionManager;
extern ActionManager *TheActionManager;
template<int N> class Rva002612C6PrefixSlots : public Rva002612C6PrefixSlots<N-1>
{
public:
    virtual void unused(char (*)[N]) = 0;
};
template<> class Rva002612C6PrefixSlots<0> {};
class Rva002612C6ReadySlot : public Rva002612C6PrefixSlots<4>
{
public:
    virtual bool ready() = 0;
};
template<int N> class Rva002612C6MiddleSlots : public Rva002612C6MiddleSlots<N-1>
{
public:
    virtual void middle(char (*)[N]) = 0;
};
template<> class Rva002612C6MiddleSlots<0> : public Rva002612C6ReadySlot {};
class Rva002612C6ContainView : public Rva002612C6MiddleSlots<63>
{
public:
    virtual void iterate(void (*callback)(Object *, void *), void *state, int mode) = 0;
};
struct Rva002612C6ObjectView
{
    char unknown00[0x250];
    Rva002612C6ContainView *contain;
};
struct Rva002612C6State { Object *owner; unsigned char bad; };
class Rva002612C6
{
public:
    bool rva002612C6(Object *candidate);
private:
    char unknown00[8];
    Object *owner;
    bool skipRelationship;
};
bool Rva002612C6::rva002612C6(Object *candidate)
{
    if (!static_cast<unsigned char>(candidate->rva0028D481()) || !candidate->rva0028D4C4())
        return false;
    Rva002612C6ContainView *contain = reinterpret_cast<Rva002612C6ObjectView *>(candidate)->contain;
    if (!contain || !contain->ready())
        return false;
    if (!reinterpret_cast<BFMEActionManager *>(TheActionManager)
        ->canEnterObject(owner, candidate, CMD_FROM_AI, ENTER_MODE_ZERO, 1, 0))
        return false;
    if (skipRelationship)
        return true;
    Rva002612C6State state;
    state.owner = owner;
    contain->iterate(iterRel001DCF20, (state.bad = 0, &state), 1);
    return state.bad ? false : true;
}
