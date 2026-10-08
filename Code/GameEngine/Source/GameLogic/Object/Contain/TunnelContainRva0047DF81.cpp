// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0047DF81, 88 bytes, RET. Object +8 and pending +9E5 are
// fixed by native loads. The controlling Player supplies a TunnelTracker
// at +2E8; the containment interface at +20 dispatches slots 42 and 68.
// TunnelContain identity follows the rowed ctor/dtor, xfer state +9E5,
// approved TU map and adjacent containment overrides; method name unresolved.
// ZH TunnelContain/TunnelTracker sources corroborate unregister/iteration flow.
// Callback 0x0047DE6C
// has a complete 117-byte cdecl boundary and reads two Object pointers.
class Player;
class Object
{
public:
 Player *getControllingPlayer() const;
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
