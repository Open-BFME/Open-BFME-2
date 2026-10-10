// cl: /O1 /G7 /MD /EHsc
// WB1190470 names GiantBirdSlowDeathBehavior::update; native461F12..461F34.
// Target ctor461E58 installs the update-interface table at+10. This method's
// owner is -8, native physics pointer Object+25C (WB264), landed byte+5E.
// Slow-death flags full3C and needsLanding full40 match the established base.
// The method marks landing, delegates only after activation bit0, and returns1.
// Partial accessed inheritance prefix only; no vtable emitted here.
struct PhysicsBehavior {char prefix[0x5e];bool landed;};
class Object {public:char prefix[0x25c];PhysicsBehavior *physics;};
class ObjectModule {public:virtual ~ObjectModule();const void *data;Object *object;};
class BehaviorInterface {public:virtual void unknownBehaviorSlot();};
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };
class UpdateModuleInterface {public:virtual UpdateSleepTime update()=0;};
class SlowDeathBehavior:public ObjectModule,public BehaviorInterface,public UpdateModuleInterface {
public:virtual UpdateSleepTime update();
 char gap[0x3c-0x14];unsigned flags;bool needsLanding;
};
class GiantBirdSlowDeathBehavior:public SlowDeathBehavior {
public:virtual UpdateSleepTime update();
};
UpdateSleepTime GiantBirdSlowDeathBehavior::update(){
 PhysicsBehavior *physics=object->physics;
 if(physics->landed)needsLanding=true;
 if(flags&1)SlowDeathBehavior::update();
 return UPDATE_SLEEP_NONE;
}
