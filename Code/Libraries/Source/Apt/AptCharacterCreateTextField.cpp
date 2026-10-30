// cl: /O2 /G6 /MD /EHsc
// Native entry6ED810 and RET6EDBC8:953B. Six-argument callback reached
// through6F0C07. BFME1 a7c38d3b AptCharacter.cpp and surrounding Apt
// character/reference sources reviewed; no corresponding clean callback.
// Character/type/animation offsets below are independently native-proven.
void __debugbreak();
#pragma intrinsic(__debugbreak)
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
#define CHECK(c,s,n) if(!(c)){g_bfmeAptAssertAtE17734(s,"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",n);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
class AptCIH;
class EAStringC {void *data;public:EAStringC();~EAStringC();};
class AptValue {public:AptCIH *c_cih(bool);int toInteger()const;float toFloat()const;void toString(EAStringC &)const;bool isUndefined()const;};
class Rva006DBB30SarDwordField
{
public:
	int get() const;
};
class BfmeAptValue006DCD20 {public:void *rva006E0F40()const;};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
class Rva006DB160
{
public:
	void *allocBlock(int);
};
class Rva006DB270;
extern Rva006DB270 *g_pChainBlockAllocator;
struct Character;
struct FrameList {char prefix[12];int count;Character **characters;};
struct Animation {char prefix[8];FrameList frames;};
struct Character {int type;Animation *parent;float x,y,width,height;int fontIndex;int color;int unknown20;float size;int unknown28,unknown2c,unknown30,unknown34,unknown38,unknown3c;};
struct Instance {char prefix[12];Character *character;char middle[0x24-0x10];};
struct TextInstance {char prefix[0x24];int field24;char pad28[8];int color30,color34;char pad38[4];int color3c;char pad40[4];int field44,field48;char pad4c[4];float x,y,width,height,size;int fontIndex;char pad68[4];int field6c;char pad70[4];unsigned int flags;};
class AptCIH {public:char prefix[0x4c];Instance *inst;bool IsCharacterInst()const;void factorySetProperty(int,float,bool);
 __forceinline Instance *characterInst()const {CHECK(IsCharacterInst(),"isCharacterInst()",0xa5);return inst;}
 __forceinline Instance *spriteBase()const {CHECK(this,"this",0xe2);CHECK(!((AptValue*)this)->isUndefined() && (((Rva006DBB30SarDwordField*)this)->get()==13 || ((Rva006DBB30SarDwordField*)this)->get()==18),"isSpriteInstBase()",0x7d);return inst;}
 __forceinline bool textValid()const {CHECK(this,"this",0xc4);return ((Rva006DBB30SarDwordField*)this)->get()==15 && !((AptValue*)this)->isUndefined();}
};
class BfmeSubmitter1283
{
public:
	void *bfmeSubmit1283(AptCIH *a1, int a2, int a3, int a4, int a5, int a6, int a7, float *a8, int a9, int a10, int a11, int a12);
};
class Rva006E9A40List {public:unsigned short count,capacity;AptCIH **items;void add(AptCIH*);};
class Rva006E34D0 {public:char prefix[0x20];Rva006E9A40List first,second;};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
extern unsigned char g_00E1771C;
AptValue *Rva006ED810CreateTextField(AptValue *context,int argc) {
 if(argc!=6)return gpUndefinedValue;
 AptValue *nameArg=(AptValue*)g_aptDateInterpreter.stack.At(0);
 AptValue *depthArg=(AptValue*)g_aptDateInterpreter.stack.At(1);
 AptValue *xArg=(AptValue*)g_aptDateInterpreter.stack.At(2);
 AptValue *yArg=(AptValue*)g_aptDateInterpreter.stack.At(3);
 AptValue *widthArg=(AptValue*)g_aptDateInterpreter.stack.At(4);
 AptValue *heightArg=(AptValue*)g_aptDateInterpreter.stack.At(5);
 int depth=depthArg->toInteger();
 float x=xArg->toFloat(),y=yArg->toFloat(),width=widthArg->toFloat(),height=heightArg->toFloat();
 EAStringC name;nameArg->toString(name);
 AptCIH *parent=context->c_cih(false);
 Character *character=(Character*)((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(sizeof(Character));
 if(!character){g_bfmeAptAssertAtE17734("pCharacter","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",0x3c3);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
 character->type=2;character->x=0;character->y=0;character->width=width;character->height=height;
 character->color=0;character->unknown20=0;character->size=12;character->unknown28=0;character->unknown2c=0;character->unknown30=0;character->unknown34=0;character->unknown38=0;character->fontIndex=-1;
 character->parent=context->c_cih(false)->characterInst()->character->parent;
 FrameList *animation=&context->c_cih(false)->characterInst()->character->parent->frames;
 for(int i=0;i<animation->count;++i){if(animation->characters[i]->type==3){character->fontIndex=i;break;}}
 AptCIH *child=(AptCIH*)((BfmeSubmitter1283*)((char*)parent->spriteBase()+0x24))->bfmeSubmit1283(0,depth+0x4000,(int)character,(int)&name,(int)parent,1,-1,0,0,0,0,0);
 if(child->textValid()){
  TextInstance *text=(TextInstance*)((BfmeAptValue006DCD20*)child)->rva006E0F40();
  text->flags=(text->flags&~6)|1;text->color34=0xff000000;text->color30=-1;
  text->height=character->height;text->x=character->x;text->width=character->width;text->y=character->y;
  text->field44=0;text->field48=0;text->field24=0;text->size=12;text->color3c=character->color;text->fontIndex=character->fontIndex;text->field6c=6;
  child->factorySetProperty(0,x,false);child->factorySetProperty(1,y,false);
  if(g_00E1771C){g_bfmeAptPtrAtE176D0->first.add(child);g_bfmeAptPtrAtE176D0->second.add(child);}
 }
 return gpUndefinedValue;
}
typedef char CharacterSize[sizeof(Character)==64?1:-1];
