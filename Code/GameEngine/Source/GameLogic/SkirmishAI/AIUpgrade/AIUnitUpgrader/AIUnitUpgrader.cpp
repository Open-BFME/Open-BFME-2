// cl: /O1 /MD /EHs /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB 0x015280E0 names AIUnitUpgrader::Register (asserts 83..89).
// Native 0x00599151..0x00599264 allocates a 0x34-byte upgrade record,
// copies its object/command/name/cost and schedules the integer random delay.
// Opaque accessed fields and existing provider names do not assert full layouts.
// The unused second stack word is intentionally untyped; native RET8 proves its ABI.
#include <vector>
class Player;
class AsciiString;
template<class C> class StringBase { public: void set(const StringBase &); void *data; };
class Object { public: const AsciiString *rva00290E67() const; char pad[0x74]; unsigned int id; };
class UpgradeTemplate { public: unsigned int rva0026EF50(Player *,Object *) const; char pad[8]; StringBase<char> name; };
class CommandButton { public: char pad[0x24]; UpgradeTemplate *upgrade; };
class CommandSet { public: const CommandButton *getCommandButton(int) const; };
class Rva0031D5F8 { public: void *rva0031D5F8(const AsciiString *); };
class ControlBar;
extern ControlBar *TheControlBar;
struct UpgradeConfigView { char pad[0xd8]; float minDelay,maxDelay; };
struct Rva002A8AB1Record { char pad[0x160]; UpgradeConfigView *config; };
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); };
extern Rva002A8F24 *g_00DFEEF8;
class Rva005DAFD7 { public: Rva005DAFD7(); void *vtable; float delay; unsigned int id; StringBase<char> name; char pad[0x2c-0x10]; unsigned int cost; const CommandButton *command; };
class ModuleData;
int GetGameLogicRandomValue(int,int,char *,int);
class AIUnitUpgrader {
 char pad[0x14]; _STL::vector<const ModuleData *> upgrading; char tail[0x2c-0x20]; Player *owner;
public: void Register(Object *, void *);
};
void AIUnitUpgrader::Register(Object *object, void *)
{
 CommandSet *commands=(CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(object->rva00290E67());
 if (!commands) return;
 for (int i=0;i<32;++i) {
   const CommandButton *command=commands->getCommandButton(i);
   if (!command) continue;
   UpgradeTemplate *upgrade=command->upgrade;
   if (!upgrade) continue;
   Rva002A8AB1Record *ai=g_00DFEEF8->rva002A8AB1(owner);
   Rva005DAFD7 *record=new Rva005DAFD7;
   record->cost=upgrade->rva0026EF50(owner,object);
   record->id=object->id;
   record->command=command;
   record->name.set(upgrade->name);
   record->delay=(float)GetGameLogicRandomValue((int)ai->config->minDelay,(int)ai->config->maxDelay,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIUpgrade\\AIUnitUpgrader\\AIUnitUpgrader.cpp",89);
   upgrading.push_back((const ModuleData *const &)record);
 }
}

