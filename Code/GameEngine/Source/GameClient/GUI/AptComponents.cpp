// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// AptComponents coordinate synchronization: complete native4102C8..4103A9
// RET0; WB10946D0's caller context and WB10935F0 establish the window,
// cached position14/18 and cached size1C/20. The existing GameWindow parent,
// position and size methods establish ABI and hierarchy independently.
// The banked implementation supplies the semantic skeleton. Replacing its
// folded RingRenderObj getter with the already pinned true winGetParent,
// then an ordinary two-float local constructor, closes all225 bytes. The
// constructor preserves a contiguous coordinate temporary so the parent
// output integers reuse dead argument slots, as retail does.
// No original helper or data-record type name is asserted.
// Native4115A9..4117E8 RET0 is the complete575B CreateGameWindowData:
// WB1093C40 names its role, and the target caller411EC3 passes two coordinate
// pointers, path, parameters and name. Native stores prove level+4/name+8,
// path+C/window10/cached geometry14..20/drawn24/initName28; prefix types stay opaque.
// Existing rowed map, layout ctor/dtor and window providers preserve their ABIs.
// The 13-word context uses the previously proved neutral22239C initializer.
// Native410223..41025D complete58B RET4 allocates270 bytes then forwards its
// one word to constructor56D671; BF1f989 AptScreenFactories.cpp is the clean
// factory-pattern guide. Target bytes establish size/ABI/address; original
// factory and constructor class identities remain unasserted. No member layout
// is inferred for the allocated object, and no callback body is lifted.
#include "../../../../Libraries/Include/Lib/Coord2D.h"
#include "ascii_string.h"
#include <string.h>
class GameWindow
{
public:
 GameWindow*winGetParent();
 int winEnable(bool);int winHide(bool);bool winIsHidden();unsigned int winGetStatus();int rva00314056(int);
	int winGetPosition(int *x, int *y);
	int winSetPosition(int x, int y);
	int winSetSize(int w, int h);
};

struct Rva004102C8Arg
{
	char m_00[0xC];AsciiString path;
	GameWindow *m_10;
	float m_14;
	float m_18;
	float m_1C;
	float m_20;bool drawn;AsciiString initName;
};

struct ComponentPosition{float x,y;ComponentPosition(float a,float b):x(a),y(b){}};
void Rva004102C8Update(Rva004102C8Arg *a1, float *a2, float *a3)
{
	int ix;
	int iy;
	GameWindow* f;
	ComponentPosition pos(a2[0],a2[1]);
	f = a1->m_10->winGetParent();
	if (f != 0) {
		((GameWindow *)f)->winGetPosition(&ix, &iy);
		pos.x -= (float)ix;
		pos.y -= (float)iy;
	}
	if (pos.x != a1->m_14 || pos.y != a1->m_18) {
		a1->m_14 = pos.x;
		a1->m_18 = pos.y;
		if (a1->m_10 != 0)
			((GameWindow *)a1->m_10)->winSetPosition((int)pos.x, (int)pos.y);
	}
	if (a3[0] != a1->m_1C || a3[1] != a1->m_20) {
		a1->m_1C = a3[0];
		a1->m_20 = a3[1];
		if (a1->m_10 != 0)
			((GameWindow *)a1->m_10)->winSetSize((int)a3[0], (int)a3[1]);
	}
}

bool Rva004128F0GetParam(const char*,const char*,AsciiString&);
const char*bfmePathLeafAfterMarker(const char*);
void*Rva004110C3Get(const AsciiString*);
Rva004102C8Arg*Rva004115A9Create(const Coord2D*,const Coord2D*,const char*,const char*,const AsciiString*);
namespace AptUtils {int LevelIndexFromTarget(const char*);}
class AptPlayer {public:void*PeekGameWindow(int);};
class BfmeAptWindowManager;extern BfmeAptWindowManager*g_bfmeAptWindowManager;
class Rva0031763A {public:Rva0031763A();~Rva0031763A();private:char data[0x2C];};
struct Rva004121D1Context {Rva004121D1Context();unsigned word[13];};
class GameWindowManager{public:
#define V(n) virtual void unusedSlot##n();
V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)V(16)V(17)V(18)V(19)V(20)V(21)V(22)V(23)V(24)V(25)V(26)V(27)V(28)V(29)V(30)
virtual GameWindow*loadWindow(AsciiString,Rva0031763A*,GameWindow*);
V(32)V(33)
virtual GameWindow*createFromContext(Rva004121D1Context*);
#undef V
GameWindow*duplicateGadget(GameWindow*,int);
protected:int drawWindow(GameWindow*);friend void Rva00411EC3(const Coord2D*,const Coord2D*,const char*,const char*);};extern GameWindowManager*TheWindowManager;
class Rva00056F61 {public:void*rva00056F61(const AsciiString*);};
class Rva00222947Ref {public:void invoke(int,int,int);};
struct BfmeAptScreenRefStorage;extern BfmeAptScreenRefStorage g_aptScreenReferences;

namespace _STL {
 template<class A,class B>struct pair;
 template<class T>class allocator;
 template<class T>struct less;
 template<class T>struct _Select1st;
 template<class T>struct _Rb_tree_node;
 template<class K,class V,class S,class C,class A>class _Rb_tree {template<class T>_Rb_tree_node<V>*_M_find(const T&)const;friend Rva004102C8Arg* ::Rva004115A9Create(const Coord2D*,const Coord2D*,const char*,const char*,const AsciiString*);};
 template<class K,class V,class H,class E,class A>class hash_map {public:V&operator[](const K&);};
}
namespace rts {template<class T>struct hash;template<class T>struct equal_to;}
class Rva0045EF90Object;
typedef _STL::hash_map<AsciiString,Rva0045EF90Object,rts::hash<AsciiString>,rts::equal_to<AsciiString>,_STL::allocator<_STL::pair<const AsciiString,Rva0045EF90Object> > > ComponentMap;
typedef _STL::pair<const AsciiString,AsciiString> WindowPathPair;
typedef _STL::_Rb_tree<AsciiString,WindowPathPair,_STL::_Select1st<WindowPathPair>,_STL::less<AsciiString>,_STL::allocator<WindowPathPair> > WindowPathTree;
extern unsigned int AptComponentWindowDataTableStorage[5];extern unsigned g_Va00E03020;
class AptShutdownReceiverView;extern AptShutdownReceiverView*AptShutdownReceiverInstance;
enum NameKeyType;
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};extern NameKeyGenerator*TheNameKeyGenerator;
class Rva0031404A{public:int rva0031404A(int);};
void*__stdcall Rva00410223(void*);void*__stdcall createAptScreenInGameChat(void*);
Rva004102C8Arg*Rva004115A9Create(const Coord2D*origin,const Coord2D*size,const char*path,const char*params,const AsciiString*name){
 int level=AptUtils::LevelIndexFromTarget(path);
 GameWindow*window=(GameWindow*)((AptPlayer*)g_bfmeAptWindowManager)->PeekGameWindow(level);
 if(!window)return 0;
 AsciiString load;
 if(!Rva004128F0GetParam(params,"_Load",load))return 0;
 if(strcmp(load.str(),"BinkGameWindow::Create")==0){
  Rva004121D1Context context;context.word[1]=0x8000001;context.word[6]=(unsigned int)Rva00410223;context.word[0]=(unsigned int)window;
  window=TheWindowManager->createFromContext(&context);
 }else if(strcmp(load.str(),"LivingWorldMap")==0){
  Rva004121D1Context context;context.word[1]=0x8000009;context.word[6]=(unsigned int)createAptScreenInGameChat;context.word[0]=(unsigned int)window;
  window=TheWindowManager->createFromContext(&context);
 }else{
  ((StringBase<char>*)&load)->toLower();
  const void*found=((WindowPathTree*)&g_Va00E03020)->_M_find(load);
  if(found==*(void**)&g_Va00E03020){Rva0031763A layout;window=TheWindowManager->loadWindow(load,&layout,window);}
  else{
   if(!*(GameWindow**)((char*)found+0x14)){Rva0031763A layout;*(GameWindow**)((char*)found+0x14)=TheWindowManager->loadWindow(load,&layout,(GameWindow*)AptShutdownReceiverInstance);}
   window=TheWindowManager->duplicateGadget(*(GameWindow**)((char*)found+0x14),(int)window);
  }
 }
 if(!window)return 0;
 Rva004102C8Arg*info=(Rva004102C8Arg*)&((ComponentMap*)AptComponentWindowDataTableStorage)->operator[](*name);
 info->m_10=window;*(int*)((char*)info+4)=level;
 ((StringBase<char>*)((char*)info+8))->set(path);
 window->winHide(false);*(int*)((char*)window+0x1F4)=0;
 ((Rva0031404A*)window)->rva0031404A((int)TheNameKeyGenerator->nameToKey(name->str()));
 Rva004102C8Update(info,(float*)origin,(float*)size);
 return info;
}

class Rva0056D671 {public:Rva0056D671(void*);private:char unmodelled[0x270];};
void*__stdcall Rva00410223(void*context){return new Rva0056D671(context);}
