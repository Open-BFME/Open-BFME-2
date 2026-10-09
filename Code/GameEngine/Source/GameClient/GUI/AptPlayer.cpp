// cl: /O1 /G7 /GX /MD /arch:SSE /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_CRTIMP=
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
class Rva00056F61 {
public:
 __declspec(nothrow) void *rva00056F61(const AsciiString *);
 Rva0041534BIter rva0041534B(const AsciiString *);
 __declspec(nothrow) __forceinline Rva0041534BIter find(const AsciiString &key) {
  return Rva0041534BIter(rva00056F61(&key),this);
 }
};
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

// Existing callee owners. The native records are 0x28 bytes, with two
// canonical strings, the parameter/index words and flag byte at +0x24.
class Rva00223CDB {public: int rva00223CDB(const AsciiString *);};
class Rva00222F0A {public: int rva00222F0A();};
class Rva002235F3 {public: void *rva002235F3(const void *);};
class Rva00062908Host {public:
 struct Slot {
  void rva00222647(int,const AsciiString &,const AsciiString &,int);
  AsciiString m_s0,m_s4;
  int m_8,m_c;
  unsigned char m_pad10[0x14],m_flags,m_tail[3];
 };
};
struct AptLevelOverrideNode {void *next; AsciiString key; int index;};
class AptPlayer
{
public:
	void PopFocus(AptFocusTarget *target);
 void SetExtern(const char *name,int value);
// Native vtable BE6E80 has AddLevel at +50 (entry 20). Earlier slots
 // are declaration-only positions; their original names and hierarchy remain unknown.
#define APT_PLAYER_SLOT(n) virtual void aptPlayerSlot##n();
 APT_PLAYER_SLOT(0) APT_PLAYER_SLOT(1) APT_PLAYER_SLOT(2) APT_PLAYER_SLOT(3) APT_PLAYER_SLOT(4)
 APT_PLAYER_SLOT(5) APT_PLAYER_SLOT(6) APT_PLAYER_SLOT(7) APT_PLAYER_SLOT(8) APT_PLAYER_SLOT(9)
 APT_PLAYER_SLOT(10) APT_PLAYER_SLOT(11) APT_PLAYER_SLOT(12) APT_PLAYER_SLOT(13) APT_PLAYER_SLOT(14)
 APT_PLAYER_SLOT(15) APT_PLAYER_SLOT(16) APT_PLAYER_SLOT(17) APT_PLAYER_SLOT(18) APT_PLAYER_SLOT(19)
#undef APT_PLAYER_SLOT
 virtual int AddLevel(AsciiString directory,AsciiString file,bool show,int parameter);
 void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
 void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);
 void AddTimer(const AsciiString &name, AptRef<AptTimer> timer);
 void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);

private:
	unsigned char m_pad004[8]; // two observed words after the virtual pointer
 unsigned char m_commandMap[0x28]; // observed member start +0x0C
 unsigned char m_customRenderMap[0x28]; // observed member start +0x34
 unsigned char m_pad05c[0xa4-0x5c];
 unsigned char m_overButtonMap[0x14]; // +0xA4
 unsigned char m_timerMap[0x14]; // +0xB8
 Rva00062908Host::Slot m_levelData[14]; // +0xCC
	AptFocusStack m_focusStack;		// +0x2FC
	Bool m_focusChanged;			// +0x308
 unsigned char m_pad309[8];
 bool m_levelsDirty; // +0x311
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

class Rva00222947Ref { public: void invoke(int,int,int); private: void *operation; };
struct AptExternNode { AptExternNode *next; AsciiString key; Rva00222947Ref handle; int context; };
namespace AptUtils { const char *SkipLevelN(const char *); }
class AptExternTable {
public:
 __declspec(nothrow) __forceinline Rva0041534BIter find(const AsciiString &key) {
  Rva00056F61 *table=reinterpret_cast<Rva00056F61 *>(this);
  return Rva0041534BIter(table->rva00056F61(&key),table);
 }
};
// WorldBuilder B97730 names SetExtern (AptPlayer.cpp:1927).
// Native 223DD7..223E4B proves map20, the key copy and prefix retry,
// four-byte callback handle at node8 and context word at nodeC.
// Existing find56F61, prefix412845 and invoke222947 providers retain
// their owned identities. Original application payload types are unasserted.
void AptPlayer::SetExtern(const char *name,int value)
{

 Rva0041534BIter found=reinterpret_cast<AptExternTable *>(m_commandMap+0x14)->find(AsciiString(name));
 if(!found.m_node) {
  found=reinterpret_cast<AptExternTable *>(m_commandMap+0x14)->find(AsciiString(AptUtils::SkipLevelN(name)));
  if(!found.m_node) return;
 }
 AptExternNode *node=static_cast<AptExternNode *>(found.m_node);
 node->handle.invoke(node->context,value,1);
}

// Semantic guide: BFME1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameClient/GUI/WindowManager_loadAptWindow.cpp.
// WB B93C90 names AddLevel; native 224710..224818 proves the 14 records,
// two name maps, existing helper owners and target-specific selection logic.
// The archive-loading tail in the BFME1 guide is absent from this target.
int AptPlayer::AddLevel(AsciiString directory,AsciiString file,bool show,int parameter)
{
 if(reinterpret_cast<Rva00223CDB *>(this)->rva00223CDB(&file)!=-1) return -1;
 AptLevelOverrideNode *overrideNode=static_cast<AptLevelOverrideNode *>(reinterpret_cast<Rva00056F61 *>(m_pad05c+0x14)->find(file).m_node);
 int level;
 if(overrideNode) level=overrideNode->index;
 else {
  level=reinterpret_cast<Rva00222F0A *>(this)->rva00222F0A();
  if(level==-1) return -1;
 }
 if(static_cast<unsigned>(level)>=14) return 0;
 if(m_levelData[level].m_c!=-1) return -1;
 if(!directory.endsWith("\\") && !directory.endsWith("/")) directory.concat("\\");
 m_levelData[level].rva00222647(level,directory,file,parameter);
 *static_cast<int *>(reinterpret_cast<Rva002235F3 *>(m_pad05c)->rva002235F3(&file))=level;
 if(show) {
  m_levelsDirty=true;
  m_levelData[level].m_flags|=1;
 }
 return level;
}
