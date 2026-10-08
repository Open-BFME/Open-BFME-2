// cl: /O1 /MD /EHs /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB 0x015280E0 names AIUnitUpgrader::Register (asserts 83..89).
// Native 0x00599151..0x00599264 allocates a 0x34-byte upgrade record,
// copies its object/command/name/cost and schedules the integer random delay.
// Opaque accessed fields and existing provider names do not assert full layouts.
// The unused second stack word is intentionally untyped; native RET8 proves its ABI.
#include <vector>
#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Player;
class AsciiString;
template<class C> class StringBase { public: void set(const StringBase &); void *data; };
class Object { public: const AsciiString *rva00290E67() const; int rva00294ADD(int); char pad[0x74]; unsigned int id; };
class UpgradeTemplate { public: unsigned int rva0026EF50(Player *,Object *) const; char pad[8]; StringBase<char> name; };
class CommandButton { public: char pad[0x24]; UpgradeTemplate *upgrade; };
class CommandSet { public: const CommandButton *getCommandButton(int) const; };
class Rva0031D5F8 { public: void *rva0031D5F8(const AsciiString *); };
class ControlBar;
extern ControlBar *TheControlBar;
struct UpgradeConfigView { char pad[0xc4]; float probability; char padC8[0xd8-0xc8]; float minDelay,maxDelay; };
struct Rva002A8AB1Record { char pad[0x160]; UpgradeConfigView *config; char pad164[8]; int enabled; };
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


// WB 0x01528530 asserts140..154. This receiver has owner+20 and only
// two vectors; Register/UnRegister use the distinct owner+2C view.
// Keep its neutral address name until a complete class relationship is proven.
class Rva00506FE9Hit { public: void rva0055ADBA(void *); };
class Rva004E9378 { public: bool rva004E9378(); };
class Rva005975C0 { public: void rva005975C0(); };
class ModuleData;
struct UnitUpgradeRecordView {
 virtual void *destroy(int);
 virtual void slot04(); virtual void slot08(); virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void beginUpgrade(void *,int);
 float delay; ObjectID object; char pad0C[0x30-0x0c]; int command;
};
float GetGameLogicRandomValueReal(float,float,char *,int);
class Rva00599264 {
 char pad[8]; _STL::vector<void *> waiting; _STL::vector<const ModuleData *> upgrading; void *owner;
public: void update();
};
void Rva00599264::update()
{
 Rva002A8AB1Record *ai=g_00DFEEF8->rva002A8AB1(owner);
 if (ai->enabled>0) {
   _STL::vector<void *>::iterator i=waiting.begin();
   while (i!=waiting.end()) {
     UnitUpgradeRecordView *item=(UnitUpgradeRecordView *)*i;
     ObjectID id=item->object;
     bool remove=false;
     if (TheGameLogic->findObjectByID(id)) {
       if (!TheGameLogic->findObjectByID(id)->rva00294ADD(item->command)) {
       float random=GetGameLogicRandomValueReal(0.0f,1.0f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIUpgrade\\AIUnitUpgrader\\AIUnitUpgrader.cpp",154);
       if (random<=ai->config->probability) {
         item->beginUpgrade(owner,0);
         upgrading.push_back((const ModuleData *const &)item);
       }
         remove=true;
       }
     } else remove=true;
     if (remove) i=waiting.erase(i); else ++i;
   }
 }
 _STL::vector<const ModuleData *> *vec=&upgrading;
 _STL::vector<const ModuleData *>::iterator i=vec->begin();
 while (i!=upgrading.end()) {
   UnitUpgradeRecordView *item=(UnitUpgradeRecordView *)*i;
   if (!TheGameLogic->findObjectByID(item->object) || ((Rva004E9378 *)item)->rva004E9378()) {
     ((Rva00506FE9Hit *)item)->rva0055ADBA(owner);
     UnitUpgradeRecordView *gone=(UnitUpgradeRecordView *)*i;
     operator delete(gone ? gone->destroy(0) : 0);
     i=(const ModuleData **)((_STL::vector<void *> *)vec)->erase((void **)i);
   } else ++i;
 }
 _STL::vector<const ModuleData *>::iterator end=upgrading.end();
 for (i=vec->begin();i!=end;++i) ((Rva005975C0 *)*i)->rva005975C0();
}

