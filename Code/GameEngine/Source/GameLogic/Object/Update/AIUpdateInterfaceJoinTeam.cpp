// cl: /O1 /Oy- /DNDEBUG /MD
// These declarations use the native call-site spellings. Existing kept
// definition covers the same iterator operation.
#pragma comment(linker, "/alternatename:?advance@?$DLINK_ITERATOR@VObject@@@@QAEXXZ=?advance@?$Rva001705A0DlinkIterator@VObject@@@@QAEXXZ")
// Reference: GeneralsMD AIUpdate.cpp at BFME1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24.
// Target 0x0026D478..0x0026D56C: catch up with an eligible team member.
// Native offsets and call/virtual-slot sequence are target evidence; the
// joinTeam purpose comes from the corresponding reference algorithm.
// BFME2 searches before resetting the locomotor and state-machine goal.
struct Coord3D { float x, y, z; };
class Object;
class Waypoint;
class Team;
class AIUpdateInterface;
template<class T> class DLINK_ITERATOR {
public:
    // Nontrivial copy semantics enable direct construction through the
    // hidden return pointer; the native iterator occupies 24 stack bytes.
    DLINK_ITERATOR(const DLINK_ITERATOR &);
    T *current;
    char opaque[20];
    void advance();
};
class Team {
public: DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class Object {
public:
    char pad0[0x38];
    Coord3D position;
    char pad44[0x1c8-0x44];
    unsigned char disabled;
    char pad1c9[0x258-0x1c9];
    AIUpdateInterface *ai;
    char pad25c[0x304-0x25c];
    Team *team;
    bool rva002907A1();
};
class TurretStateMachine {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void clear();
    virtual void slot6(); virtual void slot7(); virtual int setState(int);
    virtual void slot9(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void setGoalObject(Object *);
    char pad04[0x24-4];
    Coord3D goal;
    Object *getGoalObject();
    void setGoalPosition(const Coord3D *);
};
class AIStateMachine {
public: void setGoalWaypoint(const Waypoint *);
};
class AICommandInterface {
public: void rva0026C26D(const Coord3D *, int);
};
class AIUpdateInterface {
public:
    virtual void slot000();
    virtual void slot001();
    virtual void slot002();
    virtual void slot003();
    virtual void slot004();
    virtual void slot005();
    virtual void slot006();
    virtual void slot007();
    virtual void slot008();
    virtual void slot009();
    virtual void slot010();
    virtual void slot011();
    virtual void slot012();
    virtual void slot013();
    virtual void slot014();
    virtual void slot015();
    virtual void slot016();
    virtual void slot017();
    virtual void slot018();
    virtual void slot019();
    virtual void slot020();
    virtual void slot021();
    virtual void slot022();
    virtual void slot023();
    virtual void slot024();
    virtual void slot025();
    virtual void slot026();
    virtual void slot027();
    virtual void slot028();
    virtual void slot029();
    virtual void slot030();
    virtual void slot031();
    virtual void slot032();
    virtual void slot033();
    virtual void slot034();
    virtual void slot035();
    virtual void slot036();
    virtual void slot037();
    virtual void slot038();
    virtual void slot039();
    virtual void slot040();
    virtual void slot041();
    virtual void slot042();
    virtual void slot043();
    virtual void slot044();
    virtual void slot045();
    virtual void slot046();
    virtual void slot047();
    virtual void slot048();
    virtual void slot049();
    virtual void slot050();
    virtual void slot051();
    virtual void slot052();
    virtual void slot053();
    virtual void slot054();
    virtual void slot055();
    virtual void slot056();
    virtual void slot057();
    virtual void slot058();
    virtual void slot059();
    virtual void slot060();
    virtual void slot061();
    virtual void slot062();
    virtual void slot063();
    virtual void slot064();
    virtual void slot065();
    virtual void slot066();
    virtual void slot067();
    virtual void slot068();
    virtual void slot069();
    virtual void slot070();
    virtual void slot071();
    virtual void slot072();
    virtual void slot073();
    virtual void slot074();
    virtual void slot075();
    virtual void slot076();
    virtual void slot077();
    virtual void slot078();
    virtual void slot079();
    virtual void slot080();
    virtual void slot081();
    virtual void slot082();
    virtual void slot083();
    virtual void slot084();
    virtual void slot085();
    virtual void slot086();
    virtual void slot087();
    virtual void slot088();
    virtual void slot089();
    virtual void slot090();
    virtual void slot091();
    virtual void slot092();
    virtual void slot093();
    virtual void slot094();
    virtual void slot095();
    virtual void slot096();
    virtual void slot097();
    virtual void slot098();
    virtual void slot099();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual bool isIdle();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual void slot128();
    virtual void slot129();
    virtual void slot130();
    virtual void slot131();
    virtual void slot132();
    virtual void slot133();
    virtual void slot134();
    virtual void slot135();
    virtual void slot136();
    virtual void slot137();
    virtual void slot138();
    virtual void slot139();
    virtual void slot140();
    virtual void slot141();
    virtual void chooseLocomotorSet(int);
    char pad04[4];
    Object *object;
    char pad0c[0x20-0xc];
    AICommandInterface command;
    char pad21[0x30-0x21];
    TurretStateMachine *machine;
    char pad34[0x48-0x34];
    int commandSource;
    char pad4c[0x3bd-0x4c];
    bool dead;
    TurretStateMachine *getStateMachine() { return machine; }
    int rva00260DED() const;
    void rva0026D478();
};
void AIUpdateInterface::rva0026D478()
{
    if (dead || !object->rva002907A1()) return;
    Object *obj = object;
    Object *other = 0;
    for (DLINK_ITERATOR<Object> it = obj->team->iterate_TeamMemberList(); it.current; it.advance()) {
        Object *member = it.current;
        if (obj == member) continue;
        if (member->ai && !(member->disabled & 8)) { other = member; break; }
    }
    if (other) {
        chooseLocomotorSet(0);
        machine->clear();
        reinterpret_cast<AIStateMachine *>(machine)->setGoalWaypoint(0);
        AIUpdateInterface *ai = other->ai;
        if (ai->isIdle()) { command.rva0026C26D(&other->position, 2); return; }
        if (ai->getStateMachine()->getGoalObject()) getStateMachine()->setGoalObject(ai->getStateMachine()->getGoalObject());
        else machine->setGoalPosition(&ai->machine->goal);
        int state = rva00260DED();
        commandSource = 2;
        machine->setState(state);
    }
}
