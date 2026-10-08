// ?rva0047DE6C@@YAXPAVObject@@0@Z
// partial score=0.9 date=2026-10-08
// cl: /O1 /arch:SSE /G6 /DNDEBUG /MD /EHsc
// Retail 0x0047DF81, 88 bytes, RET. Object +8 and pending +9E5 are
// fixed by native loads. The controlling Player supplies a TunnelTracker
// at +2E8; the containment interface at +20 dispatches slots 42 and 68.
// TunnelContain identity follows the rowed ctor/dtor, xfer state +9E5,
// approved TU map and adjacent containment overrides; method name unresolved.
// ZH TunnelContain/TunnelTracker sources corroborate unregister/iteration flow.
// Callback 0x0047DE6C
// has a complete 117-byte cdecl boundary and reads two Object pointers.
class Player;
class Object;
class Rva0047DF81Interface;
class StateMachine
{
public:
 Object *getGoalObject();
};
struct Rva0047DE6CAIView
{
 char unknown00[0x30];
 StateMachine *machine;
};
struct Rva0047DE6CTemplateView
{
 char unknown00[0x115];
 unsigned char flags;
};
class Object
{
public:
 Player *getControllingPlayer() const;
 char unknown00[4];
 Rva0047DE6CTemplateView *objectTemplate;
 char unknown08[0x250-8];
 Rva0047DF81Interface *contain;
 void *unknown254;
 Rva0047DE6CAIView *ai;
};
class TunnelTracker
{
public:
 bool rva004F571B(Object *object);
};
void __cdecl rva0047DE6C(Object *object, Object *container);
struct Rva0047DF81PlayerView
{
 char unknown00[0x2E8];
 TunnelTracker *tracker;
};
// Native slot 31 supplies this checked interface; slot 61 returns a bool.
class Rva0047DE6CCheck
{
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual bool dispatch61();
};
class Rva0047DF81Interface
{
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual Rva0047DE6CCheck *dispatch31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void dispatch41(Object *object, bool flag);
 virtual void dispatch42(bool flag);
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void dispatch68(void (__cdecl *callback)(Object *, Object *), Object *object, bool flag);
};
class TunnelContain
{
public:
 void rva0047DF81();
private:
 char unknown00[8];
 Object *object;
 char unknown0C[0x20-0xC];
 Rva0047DF81Interface contain;
 char unknown24[0x9E5-0x24];
 bool pending;
};
void TunnelContain::rva0047DF81()
{
 if (pending)
 {
  Player *player = object->getControllingPlayer();
  if (player == 0)
   return;
  TunnelTracker *tracker = reinterpret_cast<Rva0047DF81PlayerView *>(player)->tracker;
  if (tracker != 0)
  {
   if (tracker->rva004F571B(object))
    contain.dispatch42(false);
   else
    contain.dispatch68(rva0047DE6C, object, true);
  }
  pending = false;
 }
}

// A native contain-interface pointer is +20 from its whole module. The
// null-preserving address adjustment precedes slot 41 dispatch.
struct Rva0047DE6CBase00 { virtual void slot00(); char unknown04[8]; };
struct Rva0047DE6CBase0C { virtual void slot0C(); };
struct Rva0047DE6CBase10 { virtual void slot10(); char unknown14[12]; };
class Rva0047DE6CWhole : public Rva0047DE6CBase00, public Rva0047DE6CBase0C,
 public Rva0047DE6CBase10, public Rva0047DF81Interface
{
};

// 0x0047DE6C, 117B cdecl RET. The rowed 88B dispatcher passes this
// callback and its Object to slot 68. Native Object offsets +4/+250/+258,
// AI state machine +30, template flag +115 and slots 31/61/41 establish
// the checks and final containment dispatch; original callback name unknown.
void __cdecl rva0047DE6C(Object *object, Object *container)
{
 if (object != 0 && container != 0 && object->ai != 0 &&
  object->ai->machine->getGoalObject() == container &&
  (object->objectTemplate->flags & 0x20) != 0)
 {
  Rva0047DF81Interface *contain = object->contain;
  if (contain == 0)
   return;
  Rva0047DE6CCheck *check = contain->dispatch31();
  if (check != 0 && !check->dispatch61())
  {
   Rva0047DE6CWhole *whole = static_cast<Rva0047DE6CWhole *>(container->contain);
   whole->dispatch41(object, true);
  }
 }
}
