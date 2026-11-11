// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/stringinline
// stlport
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv1292.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: bfmeLoadSJA 0x00411B07 (75B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// The unresolved walker contracts live in BfmeConv1292DeferredWalkers.cpp.
// The independent Apt shutdown and teardown stubs stay here.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <map>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

#include <cstddef>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

#include "StringInline.h"
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Hashtable_node@U?$pair@$$CBVAsciiString@@URva004609B0Mapped@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString; struct Rva004609B0Mapped;
namespace _STL { template <> void allocator<_Hashtable_node<pair<AsciiString const ,Rva004609B0Mapped> > >::deallocate(_Hashtable_node<pair<AsciiString const ,Rva004609B0Mapped> > *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

class Rva00410C42 { public: ~Rva00410C42(); };
class Rva0041090E { public: ~Rva0041090E(); void rva00410A14(); };

class Rva004110B4Tree { public: ~Rva004110B4Tree(); };
Rva004110B4Tree::~Rva004110B4Tree() { ((Rva00410C42 *)this)->~Rva00410C42(); }

class Rva004110BETree { public: ~Rva004110BETree(); };
Rva004110BETree::~Rva004110BETree() { ((Rva0041090E *)this)->~Rva0041090E(); }

class GameWindow;
class GameWindowManager {
public:
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
 virtual void destroyWindow(GameWindow*);
};
extern GameWindowManager *TheWindowManager;
extern unsigned g_Va00E03020;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#include "../../Include/GameClient/Rva002246B1.h"
class Rva00224455 {public:int RemoveCommandMap(const AsciiString*);};
void _bfme_closeAptScreen(const AsciiString&);
// Structural RE label for the pointer released during Apt shutdown; original
// global/type names remain unknown. Native stores and initial data establish
// a single pointer at RVA00A02FC8, not a function pin or a fixed-address read.
class AptShutdownReceiverView {public:virtual void *slot00(int);};
AptShutdownReceiverView *AptShutdownReceiverInstance=0;

// Complete native00411B52..00411E80 and WB01092E70 establish this shutdown.
// The owned E03020 map header and clear provider's StringBase<char> key
// destruction establish a string-keyed map; node+14 and WindowManager
// slot35 establish window values. The folded empty constructor alone does
// not establish its key type.
// Twelve custom renders and two commands are removed in native literal order.
void Rva00411B52() {
 typedef _STL::map<AsciiString,GameWindow*> Windows;
 Windows *windows=(Windows*)&g_Va00E03020;
 for(Windows::iterator it=windows->begin();it!=windows->end();++it)
  TheWindowManager->destroyWindow(it->second);
 ((Rva0041090E*)windows)->rva00410A14();
 ::operator delete(AptShutdownReceiverInstance?AptShutdownReceiverInstance->slot00(0):0);
 AptShutdownReceiverInstance=0;
 if(g_bfmeAptWindowManager) {
  {AsciiString name("GameWindow");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("HorzSlider");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("ComboBox");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("ImageComboBox");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("CheckBox");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("TextEntry");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("ListBox");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("PushButton");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("BinkMovie");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("LivingWorldMap");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("View3D");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("ColorPicker");((Rva002246B1*)g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("DisableComponents");((Rva00224455*)g_bfmeAptWindowManager)->RemoveCommandMap(&name);}
  {AsciiString name("EnableComponents");((Rva00224455*)g_bfmeAptWindowManager)->RemoveCommandMap(&name);}
 }
 {AsciiString name("BinkMovieInit");_bfme_closeAptScreen(name);}
}
