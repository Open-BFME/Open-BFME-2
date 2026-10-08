// cl: /O1 /G7 /Oy- /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// WB15E87D0 names StrategicConflictResults::Impl::ExternPlayerColor in
// GameClient/Gui/InGame/Strategic/StrategicConflictResults.cpp. Native
// 5EB955..5EB9D6 (ret12) proves the callback arguments and accessed prefix:
// battle at0C and the integer selector-to-packed-index map at38.
// Clean BF1 ba7ddda BfmeAptScreenObjectivesPlayerColor and
// ScoreScreenPlayerColor guide the getter/default/decimal-color purpose;
// BF2 adds the battle/map lookup and opaque-alpha bit, evidenced here.
// Native literals are complete "0" (7BFDDC) and "%d" (7BE164).
// Matched count3F459A, map find388F63, record lookup3F468D and RGBColor
// getAsInt4EA7 resolve every call. The lookup's existing integer-return
// declaration is preserved; native uses its bits as an address to color184.
// Prefix views assert only fields read here, not complete application layouts.
// The declaration-only int/int tree view follows Rva00422D1CFind.cpp and
// Rva005D62E8.cpp. Its private helper spelling preserves the rowed ABI.
// Native node+14 is the mapped value; the header pointer at map+0 is end.
// Only that accessed map prefix is modelled. No STL implementation copies,
// iterator comparison wrappers or application constructors are emitted.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdio.h>
#undef _CRTIMP
#define _CRTIMP
// Declaration-only STL call view, following Rva00422D1CFind.cpp.
class StrategicConflictResults {public:class Impl;};
namespace _STL {
template<class A,class B> struct pair {A first;B second;};
template<class T> struct _Select1st {};
template<class T> struct less {};
template<class T> class allocator {};
template<class V> struct _Rb_tree_node {char nodePrefix[16];V value;};
template<class K,class V,class S,class C,class A> class _Rb_tree {
friend class ::StrategicConflictResults::Impl;
private:template<class KT> _Rb_tree_node<V> *_M_find(const KT &)const;
};
}
typedef _STL::pair<const int,int> StrategicIntValue;
typedef _STL::_Rb_tree_node<StrategicIntValue> StrategicIntNode;
typedef _STL::_Rb_tree<int,StrategicIntValue,_STL::_Select1st<StrategicIntValue>,_STL::less<int>,_STL::allocator<StrategicIntValue> > StrategicIntTree;
struct StrategicIntIndexPrefix {StrategicIntNode *end;};
extern "C" unsigned char *__cdecl _mbscpy(unsigned char *,const unsigned char *);

struct RGBColor { int getAsInt()const;float red,green,blue;};
class LivingWorldBattle {public:int rva003F459A();};
class Rva003F468D {public:int rva003F468D(int,int);};
struct StrategicPlayerColorView {char unknown00[0x184];RGBColor color;};
class StrategicConflictResults::Impl {public:
 void ExternPlayerColor(int,char *,bool);
 char unknown00[0xC];LivingWorldBattle *battle;char unknown10[0x28];StrategicIntIndexPrefix players;
};
void StrategicConflictResults::Impl::ExternPlayerColor(int selector,char *out,bool setting) {
 _mbscpy(reinterpret_cast<unsigned char *>(out),reinterpret_cast<const unsigned char *>("0"));
 if(setting||!battle||selector>=battle->rva003F459A())return;
 StrategicIntNode *it=reinterpret_cast<const StrategicIntTree *>(&players)->_M_find(selector);
 if(it==players.end)return;
 int packed=it->value.second;
 int address=reinterpret_cast<Rva003F468D *>(battle)->rva003F468D(packed/10000,packed%10000);
 const StrategicPlayerColorView *player=reinterpret_cast<const StrategicPlayerColorView *>(address);
 _snprintf(out,255,"%d",player->color.getAsInt()|0xFF000000);
}
