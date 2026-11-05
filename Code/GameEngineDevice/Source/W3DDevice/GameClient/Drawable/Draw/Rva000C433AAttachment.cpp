// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// Native C433A..C445D291B independently establishes RenderObj references,
// renderer bone slotC8, global scene Add slot8 and record vector164.
// BF1/ZH render attachment and STLport record families supply source leads;
// this original method name and flags word semantics remain unproved.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <stdlib.h>
void Rva00030830GameFree(void*);
// Retail string allocator releases through the game allocator, not CRT free.
#include <vector>
#include <string>
// Inline _String_base<char>'s dtor everywhere so this unit emits no copy of
// its own; the kept retail copy serves any out-of-line call.
namespace _STL { template <> __declspec(dllimport) __declspec(nothrow) __forceinline
_String_base<char, allocator<char> >::~_String_base() { _M_deallocate_block(); } }
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(char const *); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(char const *, char const *); }
namespace _STL { template <> char * __char_traits_base<char, int>::copy(char *, char const *, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ if (__p != 0) Rva00030830GameFree((void *)__p); }
}
class RenderObjClass {public:
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
 virtual int Get_Bone_Index(const char*);
 int references;
 void Add_Ref(){++references;}
};
#include "../../../../../Include/W3DDevice/GameClient/RTS3DScene.h"
class W3DDisplay {public:static RTS3DScene*m_3DScene;};
class GameLODManager {public:char opaque[0x1774];int level1774;};extern GameLODManager*TheGameLODManager;
int GetGameClientRandomValue(int,int,char*,int);
struct BfmeNarrowRecord000BFDC7 {
 unsigned m_word0;_STL::basic_string<char> m_text;float x,y,z;unsigned flags;
};
namespace _STL {template<>void vector<BfmeNarrowRecord000BFDC7,allocator<BfmeNarrowRecord000BFDC7> >::push_back(const BfmeNarrowRecord000BFDC7&);}
class Rva000C433A {public:
 void rva000C433A(RenderObjClass*,const char*,bool,unsigned);
 char opaque00[0x50];RenderObjClass*render;char opaque54[0x164-0x54];_STL::vector<BfmeNarrowRecord000BFDC7> attachments;
};
void Rva000C433A::rva000C433A(RenderObjClass*obj,const char*bone,bool random,unsigned flags){
 if(TheGameLODManager&&TheGameLODManager->level1774<=1)return;
 if(!obj||!bone||!render||!render->Get_Bone_Index(bone))return;
 BfmeNarrowRecord000BFDC7 record;record.m_word0=(unsigned)obj;((RenderObjClass*)record.m_word0)->Add_Ref();record.m_text=bone;
 if(random){
  record.x=(float)GetGameClientRandomValue(-3,3,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DScriptedModelDraw.cpp",0x26D8);
  record.y=(float)GetGameClientRandomValue(-3,3,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DScriptedModelDraw.cpp",0x26D9);
  record.z=(float)GetGameClientRandomValue(-3,3,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DScriptedModelDraw.cpp",0x26DA);
 }else{record.x=0;record.y=0;record.z=0;}
 record.flags=flags;W3DDisplay::m_3DScene->Add_Render_Object((RenderObjClass*)record.m_word0);attachments.push_back(record);
}
