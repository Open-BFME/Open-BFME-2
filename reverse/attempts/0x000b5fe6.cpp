// ?rva000B5FE6@Rva000B5FE6@@QAEXXZ
// partial score=0.7057558617893611 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native000B5FE6..000B61AB RET0; WB949620 expands same kind/status tests.
// Existing W3DScriptedModelDraw siblings establish drawable8/render50;
// WB symbol mapper names an inlined BitFlags helper, not this function.
// Neutral module spelling; target offsets and virtual slots observed directly.
class Team;
enum Relationship { NEUTRAL=0, ENEMIES=1, ALLIES=2 };
class Player {public:Relationship getRelationship(const Team*)const;};
class PlayerList {public:char pad[0x10];Player*local;};extern PlayerList*ThePlayerList;
struct NativeB5Template {char pad[0x108];unsigned char kinds[0x1B];char rest[0x632-0x123];bool b632;};
class Object {public:bool isLocallyControlled()const;char pad[4];NativeB5Template*type;char gap[0x304-8];Team*team;char gap2[0x437-0x308];unsigned char status437,status438;};
struct NativeB5Drawable {char pad[4];NativeB5Template*type;char gap[0xFC-8];Object*object;char gap2[0x258-0x100];unsigned int flags258;};
class NativeB5Render {public:
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
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual void slot85();
 virtual void slot86();
 virtual void slot87();
 virtual void slot88();
 virtual void slot89();
 virtual void slot90();
 virtual void slot91();
 virtual void slot92();
 virtual void slot93();
 virtual void slot94();
 virtual void slot95();
 virtual void slot96();
 virtual void slot97();
 virtual void slot98();
 virtual void slot99();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void slot104();
 virtual void slot105();
 virtual void slot106();
 virtual void slot107();
 virtual void slot108();
 virtual void slot109();
 virtual void slot110();
 virtual void slot111();
 virtual void slot112();
 virtual void slot113();
 virtual void slot114();
 virtual void slot115();
 virtual void slot116();
 virtual void slot117();
 virtual void slot118();
 virtual void slot119();
 virtual unsigned int getFlags();virtual void setFlags(unsigned int,bool);
};
struct NativeB5ModuleData {char pad[0x6A];bool b6A;};
class Rva000B5FE6 {public:void rva000B5FE6();void*head;NativeB5ModuleData*data;NativeB5Drawable*drawable;char gap[0x50-0xC];NativeB5Render*render;char gap2[0x214-0x54];int shadowType;};
void Rva000B5FE6::rva000B5FE6(){
 NativeB5Drawable*draw=drawable;NativeB5Template*type=draw->type;if(!type)return;
 if(shadowType==-1){if((type->kinds[0]&2)||(type->kinds[7]&0x10))render->setFlags(4,true);}else if(shadowType==1)render->setFlags(4,true);
 if(type->kinds[0]&0x40)render->setFlags(8,true);else if((type->kinds[12]&2)||(type->kinds[17]&1))render->setFlags(0x200,true);
 Object*obj=draw->object;
 if(render->getFlags()&4){
 unsigned int flags=4;
 if((type->kinds[11]&4)||(type->kinds[1]&4)||(type->kinds[21]&0x10))flags=0x84;
 if(obj){Relationship r=ThePlayerList->local->getRelationship(obj->team);if(obj->isLocallyControlled())flags|=0x100;else if(r==NEUTRAL&&!(obj->type->kinds[7]&0x10))flags|=0x10;}
 render->setFlags(flags,true);
 }
 if(type->kinds[8]&0x10)render->setFlags(0x20,true);
 if(type->kinds[9]&0x10)render->setFlags(0,true);
 if(obj){
 if(obj->status437&0x10)render->setFlags(0x40,true);
 NativeB5Template*t=obj->type;
 if(!(*(unsigned int*)t->kinds&0x1400000)&&!t->b632){
 if(((t->kinds[0]&0x80)&&((draw->flags258>>5)&1))||(obj->status438&1))render->setFlags(0,true);
 }
 }
 if(data->b6A)render->setFlags(0,true);
}
