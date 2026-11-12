// cl: /O2 /DNDEBUG /MD /EHsc
// Native Apt text-format callback 006EF920..006EFB6E (590B, RET at 6EFB6D,
// CC pad to the next row 0x006EFB70). Offsets measured from this body; the
// callback identity is inferred from the argc<=2 test, the 32B text-format
// state allocation/copy (rowed ctors 0x006EB4B0 and 0x006ECEC0) and the
// character-definition font lookup. Names remain address-derived.
// The AptCIH.h:0xA5 isCharacterInst() assertion is an inline accessor of the
// handle (header file and line from the retail literal); written inline at
// the call site instead, the context and temporaries swap ESI/EDI.
void __debugbreak();
#pragma intrinsic(__debugbreak)
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
static __forceinline void aptAssert(const char *test,const char *file,int line){
 g_bfmeAptAssertAtE17734(test,file,line);
 if(g_bfmeAptBreakOnAssertAtDDC01C){__debugbreak();}
}
#include "EAStringC.h"
#include "../../../GameEngine/Include/Common/Rva006DB160.h"
#include "../../../GameEngine/Include/Common/Rva006DB270.h"
class Rva006DB270;extern Rva006DB270 *g_pChainBlockAllocator;
#include "Rva006D2A60.h"
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class AptValue;
extern AptValue *gpUndefinedValue;
class Rva006EB4B0 {
 char unknown00[32];public:
 Rva006EB4B0(AptValue*,float,int,int,int,int,int,int,AptValue*,int,int,int,int);
 static void *operator new(unsigned int size){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(size);}
 static void operator delete(void *p,unsigned int size){((Rva006DB270*)g_pChainBlockAllocator)->freeBlock(p,size);}
};
class Rva006D6470Owner {
 char unknown00[32];
public:
 static void operator delete(void *p,unsigned int size){g_pChainBlockAllocatorF4->freeBlock(p,size);}
};
class Rva006ECFC0Owner:public Rva006D6470Owner {
public:
 EAStringC font;int size,color,align;
 char unknown30[16];
 Rva006ECFC0Owner(const Rva006EB4B0&);
 static void *operator new(unsigned int size){return g_pChainBlockAllocatorF4->allocBlock(size);}
};
struct NativeFrame {int type,unknown04;const char *font;};
struct NativeFrameList {char unknown00[12];int count;NativeFrame **items;};
struct NativeAnimation {int unknown00;char *frameList;};
struct NativeCharacter {char unknown00[12];NativeAnimation *definition;};
struct TextDefinition {char unknown00[24];int fontIndex;};
struct TextInstance {char unknown00[12];TextDefinition *definition;char unknown10[20];int color;char unknown28[20];int align;char unknown40[32];int size;int unknown64;Rva006EB4B0 *format;};
#include "BfmeAptValue006DCD20.h"
#include "AptCIHClass.h"
static __forceinline NativeCharacter *getCharacter(AptCIH *cih){if(!cih->IsCharacterInst())aptAssert("isCharacterInst()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xA5);return (NativeCharacter*)cih->field4C;}
static __forceinline TextInstance *text(AptValue *context){return (TextInstance*)((const BfmeAptValue006DCD20*)context->c_cih(false))->rva006E0F40();}
AptValue *Rva006EF920TextFormat(AptValue *context,int argc){
 if(argc>2)return gpUndefinedValue;
 if(!text(context)->format){
  Rva006EB4B0 *format=new Rva006EB4B0(gpUndefinedValue,-1.0f,-1,-1,-1,-1,0,0,gpUndefinedValue,-1,-1,-1,-1);
  text(context)->format=format;
 }
 Rva006ECFC0Owner *value=new Rva006ECFC0Owner(*text(context)->format);
 if(value->color==-1)value->color=text(context)->color;
 NativeFrameList *frames=(NativeFrameList*)(getCharacter(context->c_cih(false))->definition->frameList+8);
 if(text(context)->definition->fontIndex<frames->count && text(context)->definition->fontIndex!=-1 && frames->items[text(context)->definition->fontIndex]->type==3){
  EAStringC tmp(frames->items[text(context)->definition->fontIndex]->font);value->font=tmp;
 }else{EAStringC tmp("");value->font=tmp;}
 value->align=text(context)->align;
 value->size=text(context)->size;
 return (AptValue*)value;
}
