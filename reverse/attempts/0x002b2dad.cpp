// ?rva002B2DAD@@YA_NPAVGameMessage@@PAPAXH@Z
// partial score=0.7 date=2026-10-07
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
class Rva0020E5BB { public: void *rva0020E5BB(int key); };
struct Rva002B2DADLogicView { char pad[0xB0]; Rva0020E5BB *manager; };

static __declspec(noinline) bool rva002B2DAD(GameMessage *message, void **out, int index)
{
 if (index < 0 || index >= ((Rva002B2DADMessageView *)message)->count)
  return false;
  const GameMessageArgumentType *argument = message->getArgument(index);
  int key = argument->integer;
  void *result = ((Rva002B2DADLogicView *)TheLivingWorldLogic)->manager->rva0020E5BB(key);
  *out = result;
  return result != 0;
}

// ?rva002B2DADCaller present-unmatched
bool rva002B2DADCaller(GameMessage *message, void **out, int index)
{
 return rva002B2DAD(message, out, index);
}
