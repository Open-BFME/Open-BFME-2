// ?WinCreate@AptPlayer@@QAEPAVGameWindow@@PBVAsciiString@@PAUAptLayoutInfoView@@@Z
// partial score=0.95 date=2026-10-08
// Bank only: 323-byte complete reconstruction, not byte exact.
// Receiver/key call order agrees; four local slots are assigned differently.
// The retail fallback factory2223FE is unrowed. Its constructor40FDD1 has
// an old Locomotor pin refuted by WB109CD40 AptWindowLayout::AptWindowLayout.
// Resolve that dependency before claiming a recovery; this bank adds no pin.
// cl: /O1 /G7 /ICode/GameEngine/Source/GameClient/GUI /GX /MD /arch:SSE /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include <utility>
#include "ascii_string.h"
struct TargetRef00217D4C { virtual void *destroy(unsigned); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00222C5A {
	TargetRef00217D4C *m_ptr;
	TreeHintRef00222C5A() : m_ptr(0) {}
	TreeHintRef00222C5A(const TreeHintRef00222C5A &other) : m_ptr(other.m_ptr) { if(m_ptr) ++m_ptr->references; }
	__forceinline ~TreeHintRef00222C5A() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
typedef _STL::pair<const AsciiString, TreeHintRef00222C5A> Rva00223F4BPair;
class Rva00056F61;
struct Rva0041534BIter {
	void *m_node; Rva00056F61 *m_table;
	Rva0041534BIter(void *n,Rva00056F61*t) : m_node(n), m_table(t) {}
};
class Rva00056F61 { public: Rva0041534BIter rva0041534B(const AsciiString *); };
struct Rva002236F2Value;
class Rva002236F2 { public: Rva002236F2Value &rva002236F2(const Rva002236F2Value &); };
struct Rva00223F4BNode { Rva00223F4BNode *next; Rva00223F4BPair value; };
class Rva00223F4B { public: TreeHintRef00222C5A &rva00223F4B(const AsciiString &key); };
// STLport _hash_map.h operator[] supplies the find-or-insert expression.
// The native iterator is {node, table}; insertion returns the eight-byte
// key/handle pair at node+4. The existing helper views describe that ABI.
// End the trivial iterator lifetime before constructing either temporary:
// retail reuses its owner slot for the default handle at EBP-14.
TreeHintRef00222C5A &Rva00223F4B::rva00223F4B(const AsciiString &key)
{
	Rva00223F4BNode *node;
	{
	 Rva0041534BIter it = reinterpret_cast<Rva00056F61 *>(this)->rva0041534B(&key);
	 node = static_cast<Rva00223F4BNode *>(it.m_node);
	}
	return !node ? reinterpret_cast<Rva00223F4BPair &>(reinterpret_cast<Rva002236F2 *>(this)->rva002236F2(
	  reinterpret_cast<const Rva002236F2Value &>(Rva00223F4BPair(key, TreeHintRef00222C5A())))).second : node->value.second;
}

// Native 0x002BFC59 uses the same STLport hash_map subscript expression,
// but inserts through 0x002BFAD6 and destroys its pair at 0x002BF0D6.
// The iterator, node+8 mapped value, and null-handle temporary are target
// facts. The mapped application type is unknown; its address name describes
// only the observed four-byte reference-counted handle, not an Apt type.
struct TreeHintRef002BF0D6 {
 TargetRef00217D4C *m_ptr;
 TreeHintRef002BF0D6() : m_ptr(0) {}
 TreeHintRef002BF0D6(const TreeHintRef002BF0D6 &other) : m_ptr(other.m_ptr) { if(m_ptr) ++m_ptr->references; }
 __forceinline ~TreeHintRef002BF0D6() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
typedef _STL::pair<const AsciiString, TreeHintRef002BF0D6> Rva002BFC59Pair;
class Rva002BFAD6 { public: void *rva002BFAD6(const void *); };
struct Rva002BFC59Node { Rva002BFC59Node *next; Rva002BFC59Pair value; };
class Rva002BFC59 { public: TreeHintRef002BF0D6 &rva002BFC59(const AsciiString &key); };
TreeHintRef002BF0D6 &Rva002BFC59::rva002BFC59(const AsciiString &key)
{
 Rva002BFC59Node *node;
 {
  Rva0041534BIter it = reinterpret_cast<Rva00056F61 *>(this)->rva0041534B(&key);
  node = static_cast<Rva002BFC59Node *>(it.m_node);
 }
 return !node ? static_cast<Rva002BFC59Pair *>(reinterpret_cast<Rva002BFAD6 *>(this)->rva002BFAD6(
   &Rva002BFC59Pair(key, TreeHintRef002BF0D6())))->second : node->value.second;
}

// AptPlayer.cpp -- AptPlayer members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. The focus stack is a vector of pointers whose finish
// pointer is at +0x300; popping the top focus marks the player dirty at
// +0x308.

typedef bool Bool;

class AptFocusTarget;

// STLport vector<AptFocusTarget *> view.
class AptFocusStack
{
public:
	AptFocusTarget *&back() { return *(m_finish - 1); }
	void pop_back() { --m_finish; }

private:
	AptFocusTarget **m_start;
	AptFocusTarget **m_finish;
	AptFocusTarget **m_endOfStorage;
};

class AptRefCounted { public: void *m_vtbl; int m_refCount; };
class AptCommandMap : public AptRefCounted {};
class AptCustomRender : public AptRefCounted {};
class AptTimer : public AptRefCounted {};
class AptOverButtonHandler : public AptRefCounted {};
template <class T> class AptRef {
public:
 T *m_ptr;
 AptRef(const AptRef &other) : m_ptr(other.m_ptr) { if(m_ptr) ++m_ptr->m_refCount; }
 ~AptRef()
 {
  if (m_ptr)
   ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
 }
 __declspec(noinline) AptRef &operator=(const AptRef &other);
};
template<class T> AptRef<T> &AptRef<T>::operator=(const AptRef &other) {
 if(this != &other) {
  if(other.m_ptr) ++other.m_ptr->m_refCount;
  if(m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
  m_ptr=other.m_ptr;
 }
 return *this;
}

class GameWindow;
struct AptLayoutInfoView;
class AptPlayer
{
public:
	void PopFocus(AptFocusTarget *target);
 GameWindow *WinCreate(const AsciiString *name,AptLayoutInfoView *layout);
 void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
 void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);
 void AddTimer(const AsciiString &name, AptRef<AptTimer> timer);
 void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);

private:
	unsigned char m_pad000[0xc];
 unsigned char m_commandMap[0x28]; // observed member start +0x0C
 unsigned char m_customRenderMap[0x28]; // observed member start +0x34
 unsigned char m_pad05c[0xa4-0x5c];
 unsigned char m_overButtonMap[0x14]; // +0xA4
 unsigned char m_timerMap[0x14]; // +0xB8
 unsigned char m_pad0cc[0x2fc-0xcc];
	AptFocusStack m_focusStack;		// +0x2FC
	Bool m_focusChanged;			// +0x308
};

// AptPlayer::PopFocus, retail 0x00222A33.
void AptPlayer::PopFocus(AptFocusTarget *target)
{
	if (m_focusStack.back() == target)
	{
		m_focusStack.pop_back();
		m_focusChanged = true;
	}
}


// WorldBuilder names AddCommandMap; native retail uses the map at +0x0C.
// Copying the existing handle retains it until the duplicate check finishes.
void AptPlayer::AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map) {
 if(!map.m_ptr) return;
 Rva00223F4B *table = reinterpret_cast<Rva00223F4B *>(m_commandMap);
 AptRef<AptCommandMap> oldMap = reinterpret_cast<AptRef<AptCommandMap> &>(table->rva00223F4B(name));
 if(oldMap.m_ptr) return;
 AptRef<AptCommandMap> &entry = reinterpret_cast<AptRef<AptCommandMap> &>(table->rva00223F4B(name));
 entry = map;
}
// WorldBuilder names AddCustomRender; native retail finds in the map at +0x34.
// Only a missing node or empty mapped handle may receive the new renderer.
void AptPlayer::AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render) {
 if(!render.m_ptr) return;
 Rva0041534BIter it = reinterpret_cast<Rva00056F61 *>(m_customRenderMap)->rva0041534B(&name);
 Rva00223F4BNode *node = static_cast<Rva00223F4BNode *>(it.m_node);
 if(node && node->value.second.m_ptr) return;
 AptRef<AptCustomRender> &entry = reinterpret_cast<AptRef<AptCustomRender> &>(reinterpret_cast<Rva00223F4B *>(m_customRenderMap)->rva00223F4B(name));
 entry = render;
}

// WB AptPlayer::AddTimer; retail map starts at +0xB8.
void AptPlayer::AddTimer(const AsciiString &name, AptRef<AptTimer> timer) {
 if(!timer.m_ptr) return;
 AptRef<AptTimer> &entry = reinterpret_cast<AptRef<AptTimer> &>(reinterpret_cast<Rva00223F4B *>(m_timerMap)->rva00223F4B(name));
 if(entry.m_ptr) return;
 entry = timer;
}
// WB AptPlayer::AddOverButtonHandler; retail +0xA4 map takes a local key copy.
// That copy outlives the duplicate check and assignment.
void AptPlayer::AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler) {
 if(!handler.m_ptr) return;
 AsciiString key(name);
 AptRef<AptOverButtonHandler> &entry = reinterpret_cast<AptRef<AptOverButtonHandler> &>(reinterpret_cast<Rva00223F4B *>(m_overButtonMap)->rva00223F4B(key));
 if(entry.m_ptr) return;
 entry = handler;
}

#include "unicode_string.h"
#include "GameWindowManagerRecordView.h"
#include <list>
enum NameKeyType {NAMEKEY_INVALID=0};
class NameKeyGenerator {public: NameKeyType nameToKey(const AsciiString &);};
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva00DFF024Registry {public: void *lookup56(int,int);};
class FunctionLexicon {
public: enum TableIndex {TABLE_ANY=-1,TABLE_MAIN_WINDOW=11};
protected: void *findFunction(NameKeyType,TableIndex);
friend class AptPlayer;
};
extern FunctionLexicon *TheFunctionLexicon;
class GameWindow {
public:
 virtual int winSetText(UnicodeString);
 unsigned char m_pad04[0x1f4-4];
 void *m_field1f4;
 unsigned char m_pad1f8[0x270-0x1f8];
 AsciiString m_name;
};
class AptWindowSendView {
public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
 V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
 V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
 V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
 V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57)
#undef V
 virtual void findWindow(GameWindow *,int,int,GameWindow **);
};
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
struct AptLayoutInfoView {
 unsigned int version;
 void *init,*update,*shutdown,*callback;
 AsciiString initName,updateName,shutdownName,unknown20,unknown24;
 _STL::list<GameWindow *> windows;
};
// This native callback is unrowed. WB B93C20 allocates an AptWindowLayout;
// native 2223FE..222435 calls 40FDD1, whose old Locomotor pin conflicts with
// the WB identity. This declaration is a bank dependency, not a new pin.
void * __stdcall Rva002223FECreateLayout(GameWindow *);
class ObjectSellInfo;
typedef _STL::list<ObjectSellInfo *> NativePointerList;

// Primary semantic guide: BFME1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/.../GUI/Rva0046A870CreateMainWindow.cpp. WB B93760 names WinCreate.
// Native 223263..2233A6 proves name-by-reference, descriptor size0x34,
// slots88/E8, GameWindow name270 and layout callback10/list28.
GameWindow *AptPlayer::WinCreate(const AsciiString *name,AptLayoutInfoView *layout)
{
 GadgetCreateView view;
 view.status=0x08000001;
 view.unknown24=reinterpret_cast<Rva00DFF024Registry *>(TheFunctionLexicon)->lookup56(TheNameKeyGenerator->nameToKey(*name),-1);
 if(!view.unknown24) return 0;
 GameWindow *window=reinterpret_cast<TabWindowManagerView *>(TheWindowManager)->createFromView(&view);
 window->m_field1f4=0;
 GameWindow *found=0;
 reinterpret_cast<AptWindowSendView *>(TheWindowManager)->findWindow(window,29,2000,&found);
 if(found!=window) return 0;
 found->m_name.setCopyInline(*name);
 AsciiString mainName(*name);
 mainName.concat(":MainWindow");
 UnicodeString title;
 title.translate(mainName);
 window->GameWindow::winSetText(title);
 if(layout) {
  // Existing rowed pointer-list provider: node payload and argument are
  // the same four-byte pointer word. No application type is reclassified.
  reinterpret_cast<NativePointerList *>(&layout->windows)->push_back(reinterpret_cast<ObjectSellInfo *const &>(window));
  NameKeyType key=TheNameKeyGenerator->nameToKey(*name);
  layout->callback=TheFunctionLexicon->findFunction(key,FunctionLexicon::TABLE_MAIN_WINDOW);
  if(!layout->callback) layout->callback=reinterpret_cast<void *>(&Rva002223FECreateLayout);
 }
 return found;
}
