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
 if (index < 0) return false;
 if (index >= ((Rva002B2DADMessageView *)message)->count) return false;
  const GameMessageArgumentType *argument = message->getArgument(index);
  // Native explicitly reads the word before loading the singleton.
  int key = ((const volatile GameMessageArgumentType *)argument)->integer;
 Rva0020E5BB *manager = ((Rva002B2DADLogicView *)TheLivingWorldLogic)->manager;
  void *result = manager->rva0020E5BB(key);
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
