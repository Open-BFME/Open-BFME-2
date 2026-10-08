// cl: /O1 /arch:SSE /G7 /MD
// Native 002B2DAD..002B2DEE: ECX message, stack output/index, caller cleanup.
// Checks the byte argument count at +18, obtains the indexed argument,
// looks up its first word using LivingWorldLogic's +B0 manager, and stores
// the resulting pointer. The manager's precise lookup identity is open.
union GameMessageArgumentType { int integer; };
class GameMessage
{
public:
 const GameMessageArgumentType *getArgument(int index) const;
};
struct Rva002B2DADMessageView { char pad[0x18]; unsigned char count; };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldPendingBattle;
class LivingWorldRegionManager { public: LivingWorldPendingBattle *rva0020E5BB(int key); };
// The independently recovered20E5BB provider now supplies the lookup.
// This declaration binds the existing receiver/return ABI without another pin.
class Rva0020E5BB
{
public:
 void rva0020E63F(int key, int field3c);
 void rva0020E6AD();
private:
 char pad[0x0c];
 int currentKey;
 int lastNonzeroKey;
};
struct Rva002B2DADLogicView { char pad[0xB0]; Rva0020E5BB *manager; };

static __declspec(noinline) bool rva002B2DAD(GameMessage *message, void **out, int index)
{
 if (index < 0) return false;
 if (index >= ((Rva002B2DADMessageView *)message)->count) return false;
  const GameMessageArgumentType *argument = message->getArgument(index);
  // Native explicitly reads the word before loading the singleton.
  int key = ((const volatile GameMessageArgumentType *)argument)->integer;
 Rva0020E5BB *manager = ((Rva002B2DADLogicView *)TheLivingWorldLogic)->manager;
  void *result = ((LivingWorldRegionManager *)manager)->rva0020E5BB(key);
  *out = result;
  return result != 0;
}

// ?rva002B2DADCaller absent-from-retail
// Emission anchor for MSVC 7.1 internal calling-convention optimization.
// This wrapper is source-only; no retail identity or address is claimed.
bool rva002B2DADCaller(GameMessage *message, void **out, int index)
{
 return rva002B2DAD(message, out, index);
}

// Native 0020E63F..0020E6AD, RET8. This is the same manager passed to
// the message lookup above. Native establishes key words0c/10, entry word3c,
// player range8c/90 and the two already rowed notification calls.
// The word3c setter is folded with AnimateWindow::setAnimType at003B23B9:
// the cast reuses that verified provider ABI; it does not identify the entry
// as an AnimateWindow or give its word an animation meaning.
class Rva002E2903Player;
class Rva002E0BEB { public: void rva002E0BEB(void *); };
struct Rva0020E63FPlayerRange {
 Rva002E2903Player **first, **last;
 int size() const { return (int)(last - first); }
};
class Rva002BA8F1Logic {
public:
 Rva002E2903Player *rva002B52A8(int);
 char pad[0x8c]; Rva0020E63FPlayerRange players;
};
enum AnimTypes;
class AnimateWindow { public: void setAnimType(AnimTypes); };

void Rva0020E5BB::rva0020E63F(int key, int field3c)
{
 currentKey = key;
 if (key) lastNonzeroKey = key;
 void *entry = ((LivingWorldRegionManager *)this)->rva0020E5BB(key);
 if (entry) {
  ((AnimateWindow *)entry)->setAnimType((AnimTypes)field3c);
  for (int index = 0; index < ((Rva002BA8F1Logic *)TheLivingWorldLogic)->players.size(); ++index) {
   Rva002E2903Player *player = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B52A8(index);
   ((Rva002E0BEB *)player)->rva002E0BEB(entry);
  }
 }
}

// Native20E6AD..20E6B7 RET0: reset the same manager with zero arguments.
void Rva0020E5BB::rva0020E6AD()
{
 rva0020E63F(0,0);
}
// Native20E6B7..20E6C0 RET0: pass manager word0C to the34-key lookup.
// The receiver and result spellings already used by the rowed callers are
// preserved. This view does not identify the manager's original class.
class Rva003F468D;
class Rva0020E6B7RegionManager {
public:
 Rva003F468D *rva0020E6B7();
private:
 char pad[0x0c]; int currentKey;
};
Rva003F468D *Rva0020E6B7RegionManager::rva0020E6B7()
{
 return (Rva003F468D *)((LivingWorldRegionManager *)this)->rva0020E5BB(currentKey);
}

class Rva003F468D
{
public:
 int rva003F4DAE(int side);
};
// Native 002B2DEE..002B2E31: ECX message; stack output/index/battle/side;
// caller cleanup. GameMessage::getArgument is the independently rowed
// 0030F4EA provider. Participant count is the independently rowed 003F4DAE
// body on the established Rva003F468D battle view. Original helper name
// remains unknown; the neighboring private helper proves compiler settings.
static __declspec(noinline) bool rva002B2DEE(GameMessage *message, int *out, int index, Rva003F468D *battle, int side)
{
 if (index < 0) return false;
 if (index >= ((Rva002B2DADMessageView *)message)->count) return false;
 int value = message->getArgument(index)->integer;
 *out = value;
 return value >= 0 && value < battle->rva003F4DAE(side);
}
// ?rva002B2DEECaller absent-from-retail
// Source-only emission anchor for the same MSVC internal ABI optimization
// as the neighboring helper; no retail address is asserted for this wrapper.
bool rva002B2DEECaller(GameMessage *message, int *out, int index, Rva003F468D *battle, int side)
{
 return rva002B2DEE(message, out, index, battle, side);
}
