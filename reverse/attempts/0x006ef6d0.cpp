// ?Rva006EF6D0TextFormat@@YAPAVAptValue@@PAV1@H@Z
// partial score=0.8764593201448871 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?Rva006EF6D0TextFormat@@YAPAVAptValue@@PAV1@H@Z
// partial score=0.8764593201 date=2026-10-09
// cl: /O2 /DNDEBUG /MD /EHsc
// Native Apt text-format callback at 006EF6D0..006EF920. Offsets measured
// from this body; callback identity inferred from text-format allocation,
// copying and character-definition strings. Names remain address-derived.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
static __forceinline void aptAssert(const char *test,const char *file,int line){
 g_bfmeAptAssertAtE17734(test,file,line);
 if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
}
class EAStringC {void *data;public:EAStringC(const char*);~EAStringC();EAStringC &operator=(const EAStringC&);};
class Rva006DB160 {public:void *allocBlock(int);};
class Rva006D2A60 {public:void *allocBlock(int);};
extern Rva006DB160 *g_aptPoolAllocator;
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class AptValue;
extern AptValue *gpUndefinedValue;
class Rva006EB4B0 {
 char unknown00[32];public:
 Rva006EB4B0(AptValue*,float,int,int,int,int,int,int,AptValue*,int,int,int,int);
 static void *operator new(unsigned int size){return g_aptPoolAllocator->allocBlock(size);}
};
class Rva006ECFC0Owner {
public:
 char unknown00[32];EAStringC font;int size,color,align;
 char unknown30[16];
 Rva006ECFC0Owner(const Rva006EB4B0&);
 static void *operator new(unsigned int size){return g_pChainBlockAllocatorF4->allocBlock(size);}
};
struct NativeFrame {int type,unknown04;const char *font;};
struct NativeFrameList {char unknown00[12];int count;NativeFrame **items;};
struct NativeAnimation {int unknown00;char *frameList;};
struct NativeCharacterDefinition {char unknown00[12];NativeAnimation *animation;};
struct NativeCharacter {char unknown00[12];NativeAnimation *definition;};
struct TextDefinition {char unknown00[24];int fontIndex;};
struct TextInstance {char unknown00[12];TextDefinition *definition;char unknown10[20];int color;char unknown28[20];int align;char unknown40[32];int size;int unknown64;Rva006EB4B0 *format;};
class BfmeAptValue006DCD20 {public: void *rva006E0F40()const;};
class AptCIH {public:bool IsCharacterInst()const;char unknown00[0x4C];NativeCharacter *character;};
class AptValue {public:AptCIH *c_cih(bool);};
static __forceinline TextInstance *text(AptValue *context){return (TextInstance*)((const BfmeAptValue006DCD20*)context->c_cih(false))->rva006E0F40();}
AptValue *Rva006EF6D0TextFormat(AptValue *context,int argc){
 if(argc>0)return gpUndefinedValue;
 if(!text(context)->format){
  Rva006EB4B0 *format=new Rva006EB4B0(gpUndefinedValue,-1.0f,-1,-1,-1,-1,0,0,gpUndefinedValue,-1,-1,-1,-1);
  text(context)->format=format;
 }
 Rva006ECFC0Owner *value=new Rva006ECFC0Owner(*text(context)->format);
 if(value->color==-1)value->color=text(context)->color;
 AptCIH *cih=context->c_cih(false);
 if(!cih->IsCharacterInst())aptAssert("isCharacterInst()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xA5);
 NativeFrameList *frames=(NativeFrameList*)(cih->character->definition->frameList+8);
 if(text(context)->definition->fontIndex<frames->count && text(context)->definition->fontIndex!=-1 && frames->items[text(context)->definition->fontIndex]->type==3){
  EAStringC tmp(frames->items[text(context)->definition->fontIndex]->font);value->font=tmp;
 }else{EAStringC tmp("");value->font=tmp;}
 value->align=text(context)->align;
 value->size=text(context)->size;
 return (AptValue*)value;
}
