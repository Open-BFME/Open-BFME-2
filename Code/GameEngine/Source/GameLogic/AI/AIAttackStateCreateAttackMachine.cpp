// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME 1 semantic donor: 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameLogic/AI/AIAttackState_createAttackMachine.cpp.
// Target identity: WB E22790 names AIAttackState::createAttackMachine; its
// control-flow and constructors correspond to retail 34B1E9..34B3C0 RET4.
// Target deltas: +24 machine, +40/+41/+42 flags, +4C selector; 3C-byte
// allocations; scalar name keys in place of donor strings; two added kinds.
// Constructor spellings preserve the existing owners or neutral banked views.
// Original names of the concrete machine classes remain unproven here.
class Object;
class Rva00343367Attack;
class Rva00346D17Attack;
class Rva003438C7Host;
class Rva003435FB
{
public:
    Rva003435FB(Object*,int,unsigned);
private:
    char body[0x3C]; // allocation extent established separately at every case
};
class Rva0034316A
{
public:
    Rva0034316A(Object*,int,unsigned);
private:
    char body[0x3C]; // allocation extent established separately at every case
};
class Rva00343756
{
public:
    Rva00343756(Object*,int,unsigned);
private:
    char body[0x3C]; // allocation extent established separately at every case
};
class Rva00343A86
{
public:
    Rva00343A86(Object*,int,unsigned);
private:
    char body[0x3C]; // allocation extent established separately at every case
};
class Rva00343838
{
public:
    Rva00343838(Object*,int,unsigned,bool);
private:
    char body[0x3C]; // allocation extent established separately at every case
};
class Rva003438C7
{
public:
    Rva003438C7(Object*,Rva003438C7Host*,unsigned);
private:
    char body[0x3C]; // allocation extent established separately at every case
};
class Rva00343367
{
public:
    Rva00343367(Object*,Rva00343367Attack*,unsigned,bool,bool,bool);
private:
    char body[0x3C]; // allocation extent established separately at every case
};
class Rva00346D17
{
public:
    Rva00346D17(Object*,Rva00346D17Attack*,unsigned,bool,bool,bool);
private:
    char body[0x3C]; // allocation extent established separately at every case
};
// Declaration-only virtual view: owner+258, slot+1A0 in the reuse case.
// No instance or vtable is emitted for this view.
template<int N>
class AttackOwnerSlots : public AttackOwnerSlots<N-1>
{
public:
    virtual void unused(char (*)[N]) = 0;
};
template<> class AttackOwnerSlots<0> {};
class AttackOwnerAIView : public AttackOwnerSlots<104> { public: virtual void *getAttackMachine()=0; };
struct AttackOwnerPrefixView { char prefix[0x258]; AttackOwnerAIView *ai; };
class AIAttackState
{
protected:
    void createAttackMachine(Object *owner);
private:
    char prefix[0x24];
    void *machine;
    char unknown28[0x18];
    bool follow, attackingObject, forceAttacking;
    char unknown43[9];
    unsigned kind;
};
void AIAttackState::createAttackMachine(Object *owner)
{
    if (kind == 1)
        machine = new Rva003435FB(owner, reinterpret_cast<int>(this), 0x3d3b7898);
    else if (kind == 2)
        machine = new Rva0034316A(owner, reinterpret_cast<int>(this), 0xbaaacfcb);
    else if (kind == 6)
        machine = new Rva00343367(owner, reinterpret_cast<Rva00343367Attack*>(this), 0xeeba4547, follow, attackingObject, forceAttacking);
    else if (kind == 5)
        machine = new Rva00343756(owner, reinterpret_cast<int>(this), 0x30c4498f);
    else if (kind == 8)
        machine = new Rva00343838(owner, reinterpret_cast<int>(this), 0x8b6172cb, true);
    else if (kind == 0)
        machine = reinterpret_cast<AttackOwnerPrefixView*>(owner)->ai->getAttackMachine();
    else if (kind == 4)
        machine = new Rva003438C7(owner, reinterpret_cast<Rva003438C7Host*>(this), 0x3c81e213);
    else if (kind == 7)
        machine = new Rva00343A86(owner, reinterpret_cast<int>(this), 0x79565b18);
    else
        machine = new Rva00346D17(owner, reinterpret_cast<Rva00346D17Attack*>(this), 0xd30e2fb3, follow, attackingObject, forceAttacking);
}
