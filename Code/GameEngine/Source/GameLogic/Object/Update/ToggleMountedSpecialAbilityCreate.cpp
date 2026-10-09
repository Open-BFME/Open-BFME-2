// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii /I.
// Native004ADD8D..004ADF0B RET0; WB1228F20 names createMountedTemplate.
// ModuleFactory24F68A and ctor4ADAB5 establish owning class and module prefix.
// No clean ZH/BF1 donor exists for the mounted extension: native defines each
// field and call contract; matched sibling toggles guide the update pattern.
// Native player score record3BC uses the existing neutral39CBCE binding;
// Object angle44/id74/name88/experience264/record468 and body254 are explicit.
// BuildAssistant slot14 is independently recovered buildObjectNow3952D8.
// Selection slots66/67 retain neutral names. Drawable selected43C is tested
// for nonzero; retaining replacementBody across source virtual slot4 keeps
// native destination receiver at ebp-8. No new pins or shared headers.
#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
class Object; class Player; class ThingTemplate;
enum ObjectID { ID_UNKNOWN=0 };
template<int N> class MountedCreateSlots : public MountedCreateSlots<N-1> { public: virtual void gap(char(*)[N])=0; };
template<> class MountedCreateSlots<0> {};
class Drawable { public: void fadeIn(unsigned); char pad[0x43C]; unsigned char selected; };
class Rva0039CBCE {public:void rva0039CBCE(Object*,int);};
class Player {public:char pad[0x3BC];Rva0039CBCE score;};
class Rva003BD306Target {public:void rva0039B3D1(float,bool);char pad[0x10];float experience;char pad14[0x28];bool enabled;};
class Rva001EAFC1 {public:Rva001EAFC1 &operator=(const Rva001EAFC1&);char bytes[24];};
class MountedBodyView : public MountedCreateSlots<4> {public: virtual float slot4() const=0;
virtual void b5()=0;
virtual void b6()=0;
virtual void b7()=0;
virtual void b8()=0;
virtual void b9()=0;
virtual void b10()=0;
virtual void b11()=0;
virtual void b12()=0;
virtual void b13()=0;
virtual void b14()=0;
virtual void b15()=0;
virtual void b16()=0;
virtual void b17()=0;
virtual void b18()=0;
virtual void b19()=0;
virtual void b20()=0;
virtual void b21()=0;
virtual void b22()=0;
virtual void b23()=0;
virtual void b24()=0;
virtual void b25()=0;
virtual void b26()=0;
virtual void b27()=0;
virtual void b28()=0;
virtual void b29()=0;
virtual void b30()=0;
virtual void b31()=0;
virtual void b32()=0;
virtual void b33()=0;
virtual void b34()=0;
virtual void b35()=0;
virtual void b36()=0;
virtual void b37()=0;
virtual void b38()=0;
virtual void b39()=0;
virtual void b40()=0;
virtual void b41()=0;
virtual void slot42(float)=0;};
class Object {public:Drawable *getDrawable() const; Player *getControllingPlayer() const;
char pad0[0x38];Coord3D position;float angle;char pad48[0x74-0x48];ObjectID id;
char pad78[0x88-0x78];StringBase<char> name;char pad8C[0x254-0x8C];MountedBodyView *body;
char pad258[0x264-0x258];Rva003BD306Target *experience;char pad268[0x468-0x268];Rva001EAFC1 record;};
class ThingFactory {public:const ThingTemplate *findTemplate(const AsciiString&);}; extern ThingFactory *TheThingFactory;
class BuildAssistant : public MountedCreateSlots<14> {public:virtual Object* buildObjectNow(Object*,const ThingTemplate*,const Coord3D*,float,Player*)=0;};extern BuildAssistant *TheBuildAssistant;
class InGameUI : public MountedCreateSlots<66> {public:virtual void slot66(Drawable*)=0;virtual void slot67(Drawable*)=0;};extern InGameUI *TheInGameUI;
class GameMessage {public:void appendBooleanArgument(bool);void appendObjectIDArgument(ObjectID);};
class MessageStream : public MountedCreateSlots<18> {public:virtual GameMessage *appendMessage(int)=0;};extern MessageStream *TheMessageStream;
struct MountedCreateData {char pad[0xD0];AsciiString mountedTemplate;};
class Rva004ADCE8 {public:void rva004ADCE8(const Object*);};
class ToggleMountedSpecialAbilityUpdate {public:void createMountedTemplate();int opaque;MountedCreateData *data;Object *owner;char padC[0x8C-0xC];bool changed;};
void ToggleMountedSpecialAbilityUpdate::createMountedTemplate(){
 const ThingTemplate *what=TheThingFactory->findTemplate(data->mountedTemplate);
 if(!what)return;
 Object *original=owner;
 bool selected=original->getDrawable()->selected!=0;
 float angle=original->angle;
 Player *player=original->getControllingPlayer();
 Object *replacement=TheBuildAssistant->buildObjectNow(original,what,&original->position,angle,player);
 if(!replacement)return;
 player->score.rva0039CBCE(original,-1);
 replacement->name.set(original->name);
 replacement->record=original->record;
 replacement->experience->enabled=false;
 replacement->experience->rva0039B3D1(original->experience->experience,true);
 replacement->experience->enabled=true;
 MountedBodyView *replacementBody=replacement->body;
 replacementBody->slot42(original->body->slot4());
 replacement->getDrawable()->fadeIn(10);
 if(selected){
 TheInGameUI->slot67(original->getDrawable());
 GameMessage *message=TheMessageStream->appendMessage(1001);
 message->appendBooleanArgument(true);
 message->appendObjectIDArgument(replacement->id);
 TheInGameUI->slot66(replacement->getDrawable());
 }
 ((Rva004ADCE8*)this)->rva004ADCE8(replacement);
 changed=true;
}
