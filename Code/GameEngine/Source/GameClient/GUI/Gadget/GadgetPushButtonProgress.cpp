// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native328700..32884A RET0; WB1122410 same callgraph and button callback slot5
// establish the subsystem but do not expose a name. ZH GadgetPushButton.cpp clock
// helper and ProductionUpdate.h entry accessors guide purpose only. Target proves
// selectedDrawableFC Object; command14 and upgrade24; Object AI250 and ID74;
// Production interface slots54/58 enumerate entries and AI E8/40 queries progress.
// The palette words belong to outer Rva003284B9 arguments; progress callees take
// no color. Existing rowed providers and canonical globals are preserved.
class GameWindow {public:void *winGetUserData();};
class ThingTemplate {public:bool isEquivalentTo(const ThingTemplate*)const;};
class Rva00327C1B {public:int unknown00; int kind; const ThingTemplate *thing; void *upgrade; bool rva00327C1B()const;};
class Rva0049CBDA {public:int rva0049CBDA();};
class ButtonProductionInterface {public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot0A();
virtual void slot0B();
virtual void slot0C();
virtual void slot0D();
virtual void slot0E();
virtual void slot0F();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual Rva00327C1B *first(); virtual Rva00327C1B *next(Rva00327C1B *); };
class ButtonAIInterface {public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot0A();
virtual void slot0B();
virtual void slot0C();
virtual void slot0D();
virtual void slot0E();
virtual void slot0F();
virtual int progress(int);
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot1A();
virtual void slot1B();
virtual void slot1C();
virtual void slot1D();
virtual void slot1E();
virtual void slot1F();
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
virtual void slot2A();
virtual void slot2B();
virtual void slot2C();
virtual void slot2D();
virtual void slot2E();
virtual void slot2F();
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
virtual bool matches(class Object*);
};
class Object {public:char unknown[0x250]; ButtonAIInterface *ai; void *rva0028BC58(int);};
class ButtonDrawable {public:char unknown[0xFC]; Object *object;};
class InGameUI {public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot0A();
virtual void slot0B();
virtual void slot0C();
virtual void slot0D();
virtual void slot0E();
virtual void slot0F();
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
virtual void slot1A();
virtual void slot1B();
virtual void slot1C();
virtual void slot1D();
virtual void slot1E();
virtual void slot1F();
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
virtual void slot2A();
virtual void slot2B();
virtual void slot2C();
virtual void slot2D();
virtual void slot2E();
virtual void slot2F();
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
virtual void slot3A();
virtual void slot3B();
virtual void slot3C();
virtual void slot3D();
virtual void slot3E();
virtual void slot3F();
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
virtual void slot4A();
virtual ButtonDrawable *selected();};
extern InGameUI *TheInGameUI;
class CommandButton {public:char unknown[0x14]; int command; char unknown18[12];void *upgrade; const ThingTemplate *rva0035B570()const;};
struct ButtonUserData {char unknown[0x28];bool update;};
class ControlBar {public:Object *rva0053E754(GameWindow*);};
extern ControlBar *TheControlBar;
void *GadgetButtonGetData(GameWindow*);
void Rva00328354Update(GameWindow*);
void Rva003284B9(GameWindow*,int,int);
void Rva00328700(GameWindow *window)
{
 if(!window) return;
 ButtonUserData *data=(ButtonUserData*)window->winGetUserData();
 if(!data) return;
 if(data->update) Rva00328354Update(window);
 ButtonDrawable *drawable=TheInGameUI->selected();
 if(!drawable) return;
 Object *object=drawable->object;
 if(!object) return;
 const CommandButton *command=(const CommandButton*)GadgetButtonGetData(window);
 if(!command) return;
 ButtonProductionInterface *production=(ButtonProductionInterface*)object->rva0028BC58(0);
 if(production) {
  if(command->command==3) {
   const ThingTemplate *thing=command->rva0035B570();
   for(Rva00327C1B *entry=production->first();entry;entry=production->next(entry)) {
    if(entry->rva00327C1B() && thing->isEquivalentTo(entry->thing)) {
     Rva003284B9(window,((Rva0049CBDA*)entry)->rva0049CBDA(),0x80ffffff); return;
    }
   }
  } else if(command->command==6 || command->command==7 || command->command==8) {
   void *upgrade=command->upgrade;
   for(Rva00327C1B *entry=production->first();entry;entry=production->next(entry)) {
    if(entry->kind==2 && upgrade==entry->upgrade) {
     Rva003284B9(window,((Rva0049CBDA*)entry)->rva0049CBDA(),0x80ffffff); return;
    }
   }
  }
 } else {
  ButtonAIInterface *ai=object->ai;
  if(!ai) return;
  Object *mapped=TheControlBar->rva0053E754(window);
  if(mapped && ai->matches(mapped)) {
   int id=*(int*)((char*)mapped+0x74);
   Rva003284B9(window,ai->progress(id),0x94ffcd6c);
  }
 }
}
