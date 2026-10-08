// cl: /O1 /G7 /arch:SSE /Oy- /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP=
// stlport
// Native41F56F..41F71A constructs the224B object allocated by the named WB
// ArmyDefinitionManager::parseArmyDefinition (WB1333640 in
// GameLogic/SkirmishAI/ArmyDefinitionManager.cpp). Its matching destructor
// 41F760 independently names ArmyDefinition and confirms strings0/24/28
// and owned storage headers4/54/60/8C/98. WB13329C0's constructor twin
// confirms each default and initialization order. No compatible clean BF1
// or ZH ArmyDefinition source is present at verified donor ba7ddda.
// Header fields below are initialization ABI views only. Their actual vector
// element types are not asserted. All five calls target the same existing
//29B empty-header owner at211E58, whose body/proxy only zero three words.
// The nonthrowing call view follows Keyboard.cpp and CrateSystemLifetime.cpp;
// it preserves the allocator temporary address without inventing EH states.
// BfmeE16 is the existing provider's address-derived storage spelling, not
// a claim that ArmyDefinition stores16B elements. No new aliases or pins.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include "ascii_string.h"
struct BfmeE16 {float x,y,z,w;};
namespace _STL {
template<class T> class allocator {public:allocator(){}};
template<class T,class A> class _Vector_base {public:_Vector_base(const A &)throw();T *begin,*end,*capacity;};
}
typedef _STL::allocator<BfmeE16> HeaderAllocator;
typedef _STL::_Vector_base<BfmeE16,HeaderAllocator> EmptyHeader;
class ArmyDefinition
{
public:
 ArmyDefinition();
 AsciiString name;
 EmptyHeader header04;
 float array10[3],value1C,value20;
 AsciiString string24,string28;
 float value2C;int field30;float array34[3];
 int field40,field44,field48;float value4C,value50;
 EmptyHeader header54,header60;
 float value6C,value70;int field74,field78;float array7C[3],value88;
 EmptyHeader header8C,header98;
 float valueA4,valueA8,arrayAC[3],arrayB8[3];
 float valueC4,valueC8,valueCC,valueD0,valueD4,valueD8,valueDC;
};
ArmyDefinition::ArmyDefinition():header04(HeaderAllocator()),value1C(100.0f),value20(1950.0f),value2C(0.0f),field30(0),field40(2),field44(300),field48(70),value4C(3.0f),value50(20.0f),header54(HeaderAllocator()),header60(HeaderAllocator()),value6C(90.0f),value70(0.5f),field74(1),field78(4),value88(0.5f),header8C(HeaderAllocator()),header98(HeaderAllocator()),valueA4(120.0f),valueA8(420.0f),valueC4(30.0f),valueC8(85.0f),valueCC(150.0f),valueD0(200.0f),valueD4(250.0f),valueD8(100.0f),valueDC(200.0f) {
 memset(array34,0,sizeof(array34));
 memset(array7C,0,sizeof(array7C));
 memset(array10,0,sizeof(array10));
 memset(arrayAC,0,sizeof(arrayAC));
 memset(arrayB8,0,sizeof(arrayB8));
}
