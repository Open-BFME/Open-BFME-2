// cl: /Ireference/shims/bfmealloc /O1 /G7 /GX /MD /arch:SSE /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#define strchr _stlport_hides_strchr
#define sprintf _stlport_hides_sprintf
#include <utility>
#include <new>
#include <mbstring.h>
#include "ascii_string.h"
#undef strchr
#undef sprintf
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
	Rva0041534BIter() {}
	Rva0041534BIter(void *n,Rva00056F61*t) : m_node(n), m_table(t) {}
};
class Rva00056F61 {
public:
 __declspec(nothrow) void *rva00056F61(const AsciiString *);
 __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);
 __declspec(nothrow) __forceinline Rva0041534BIter findIter(const AsciiString &key) { return rva0041534B(&key); }
 __declspec(nothrow) __forceinline Rva0041534BIter find(const AsciiString &key) {
  return Rva0041534BIter(rva00056F61(&key),this);
 }
};
struct Rva002236F2Value;
class Rva002236F2 { public: Rva002236F2Value &insert(const Rva002236F2Value &); };
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
	return !node ? reinterpret_cast<Rva00223F4BPair &>(reinterpret_cast<Rva002236F2 *>(this)->insert(
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
class GameWindow;
class Image;
struct AptLayoutInfoView;

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
class AptExternHandler : public AptRefCounted {};
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
 void RemoveOverButtonHandler(int index, const AsciiString &key);
 void RemoveOverButtonHandler(const AsciiString &key);
 void OnCustomRender(const char *name, int a, int b, int c, int d);
 void HandleOverButtons();
 static int GetLevelIndex(GameWindow *window);
 GameWindow *WinCreate(const AsciiString *name,AptLayoutInfoView *layout);
 bool ShowLevel(int index);
 bool UnloadLevel(int index);
 bool HideLevel(int index);
 bool RemoveLevel(int index);
 void GetExtern(const char *name,char *out);
 const Image *FindRenderImage(const char *targetName,const char *parameters);
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
 void AddExternHandler(const AsciiString &name,int context,AptRef<AptExternHandler> handler);
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
 if(!directory.endsWith("\\") && !directory.endsWith("/")) reinterpret_cast<StringBase<char> *>(&directory)->concat("\\");
 m_levelData[level].rva00222647(level,directory,file,parameter);
 *static_cast<int *>(reinterpret_cast<Rva002235F3 *>(m_pad05c)->rva002235F3(&file))=level;
 if(show) {
  m_levelsDirty=true;
  m_levelData[level].m_flags|=1;
 }
 return level;
}

// WorldBuilder B958E0 names the static level-index query. Native
// 222547..222597 returns -1, 14, or the integer at reply+274.
typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

class UnicodeString;
class GameWindow {
public:
 GameWindow *winGetParent();
 virtual int winSetText(UnicodeString);
 unsigned char m_pad04[0x1f4-4];
 void *m_field1f4;
 unsigned char m_pad1f8[0x270-0x1f8];
 AsciiString m_name;
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	virtual void windowHiding(GameWindow *window) = 0;
	V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	virtual GameWindow *winGetFocus() = 0;
	virtual int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
};

extern GameWindowManager *TheWindowManager;

struct Rva00222547Out
{
	char m_pad[0x274];
	int m_result;
};

int AptPlayer::GetLevelIndex(GameWindow *gameWindow)
{
	if (gameWindow == 0)
		return -1;
	Rva00222547Out *out = 0;
	for (;;)
	{
		if (gameWindow == 0)
			return 14;
		TheWindowManager->winSendSystemMsg(gameWindow, 29, 2000, (WindowMsgData)&out);
		gameWindow = gameWindow->winGetParent();
		if (out == 0)
			continue;
		return out->m_result;
	}
}

bool Rva004128F0GetParam(const char *,const char *,AsciiString &);
extern "C" __declspec(dllimport) char *__cdecl strchr(const char *,int);
class ImageCollection { public: const Image *findImageByName(const AsciiString &); };
extern ImageCollection *TheMappedImageCollection;
struct AptImageNode { void *next; AsciiString key; const Image *image; };
// WB B92F00 names the resolver. Native223AC4..223BF6 proves image map90
// and the temporary truncation before ~ (or its preceding slash).
const Image *AptPlayer::FindRenderImage(const char *targetName,const char *parameters)
{
 AsciiString imageName;
 if(parameters) Rva004128F0GetParam(parameters,"_imageMap",imageName);
 else imageName=targetName;
 if(!imageName.isEmpty()) {
  AptImageNode *node=static_cast<AptImageNode *>(reinterpret_cast<Rva00056F61 *>(m_pad05c+0x34)->find(imageName).m_node);
  if(node) return node->image;
  if(TheMappedImageCollection) {
   const Image *image=TheMappedImageCollection->findImageByName(imageName);
   if(image) return image;
  }
 }
 targetName=AptUtils::SkipLevelN(targetName);
 if(!*targetName) return 0;
 Rva0041534BIter it=reinterpret_cast<Rva00056F61 *>(m_pad05c+0x34)->find(AsciiString(targetName));
 if(!it.m_node) {
  char *delimiter=strchr(targetName,'~');
  if(!delimiter) return 0;
  if(delimiter[-1]=='/') --delimiter;
  char saved=*delimiter;
  *delimiter=0;
  it=reinterpret_cast<Rva00056F61 *>(m_pad05c+0x34)->find(AsciiString(targetName));
  *delimiter=saved;
  if(!it.m_node) return 0;
 }
 return static_cast<AptImageNode *>(it.m_node)->image;
}

// Existing 22402A owns an eight-byte mapped {reference word,index} value.
// Only a call projection is needed here; its first word follows AptRef's
// proven intrusive retain/release ABI and the second is a plain context.
class Rva00468520;
class Rva0022402A { public: Rva00468520 &rva0022402A(const AsciiString &); };
struct AptExternMappedValue { AptRef<AptExternHandler> handler; int context; };
void AptPlayer::AddExternHandler(const AsciiString &name,int context,AptRef<AptExternHandler> handler)
{
 if(!handler.m_ptr) return;
 AptExternMappedValue &entry=reinterpret_cast<AptExternMappedValue &>(reinterpret_cast<Rva0022402A *>(m_commandMap+0x14)->rva0022402A(name));
 AptRef<AptExternHandler> oldHandler=entry.handler;
 if(oldHandler.m_ptr) return;
 entry.handler=handler;
 entry.context=context;
}

void AptPlayer::GetExtern(const char *name,char *out)
{
 if(!name || !out) return;
 *out=0;
 if(*name=='?') {
  ++name;
  Rva0041534BIter found=reinterpret_cast<AptExternTable *>(m_commandMap+0x14)->find(AsciiString(AptUtils::SkipLevelN(name)));
  if(found.m_node) _mbscpy((unsigned char *)out,(const unsigned char *)"extern");
  else {
   void *commandNode=reinterpret_cast<AptExternTable *>(m_commandMap)->find(AsciiString(name)).m_node;
   if(commandNode) _mbscpy((unsigned char *)out,(const unsigned char *)"fscommand");
   else _mbscpy((unsigned char *)out,(const unsigned char *)"0");
  }
  return;
 }
 Rva0041534BIter found=reinterpret_cast<AptExternTable *>(m_commandMap+0x14)->find(AsciiString(name));
 if(!found.m_node) {
  found=reinterpret_cast<AptExternTable *>(m_commandMap+0x14)->find(AsciiString(AptUtils::SkipLevelN(name)));
  if(!found.m_node) return;
 }
 AptExternNode *node=static_cast<AptExternNode *>(found.m_node);
 node->handle.invoke(node->context,reinterpret_cast<int>(out),0);
}

bool AptPlayer::ShowLevel(int index)
{
 if(static_cast<unsigned>(index)>=14) return false;
 Rva00062908Host::Slot &entry=m_levelData[index];
 if(entry.m_flags&2) return false;
 entry.m_flags|=1;
 m_levelsDirty=true;
 return true;
}

extern "C" __declspec(dllimport) int __cdecl sprintf(char *,const char *,...);
#pragma function(sprintf)
void Rva006CC600(const char *,char *);
void Rva00411E80(int);
// WB AptPlayer::UnloadLevel; native22481..224DE is the existing93-byte owner.
bool AptPlayer::UnloadLevel(int index)
{
 if(static_cast<unsigned>(index)>=14) return false;
 Rva00062908Host::Slot &entry=m_levelData[index];
 if(!(entry.m_flags&2)) return false;
 char key[32];
 sprintf(key,"_level%d",index);
 Rva006CC600("",key);
 entry.m_flags&=0xF5;
 Rva00411E80(index);
 return true;
}

#include "unicode_string.h"
struct RGBColor;
class Mouse { public: void rva001EEA6D(UnicodeString,int,const RGBColor *,float); };
extern Mouse *TheMouse;
// WB B94EA0 AptPlayer.cpp1240 names HideLevel. Native2277D..227DF is98 bytes.
bool AptPlayer::HideLevel(int index)
{
 if(static_cast<unsigned>(index)>=14) return false;
 Rva00062908Host::Slot *entry=&m_levelData[index];
 if(TheMouse) TheMouse->rva001EEA6D(UnicodeString::TheEmptyString,0,0,1.0f);
 if(!(entry->m_flags&2)) return false;
 return UnloadLevel(index);
}

class Rva000427195 { public: int rva00223429(const AsciiString *); };
class Rva0022494F { public: void rva0022494F(); };
// WB B94410 AptPlayer.cpp1118..1121 names RemoveLevel; native24B7D..24BC9.
bool AptPlayer::RemoveLevel(int index)
{
 if(static_cast<unsigned>(index)>=14) return false;
 Rva00062908Host::Slot *entry=&m_levelData[index];
 if(entry->m_c==-1) return false;
 if(entry->m_flags&2) UnloadLevel(index);
 reinterpret_cast<Rva000427195 *>(m_pad05c)->rva00223429(&entry->m_s0);
 reinterpret_cast<Rva0022494F *>(entry)->rva0022494F();
 return true;
}

// Native 2238E6..2239AD RET4; WB B8F570 (AptPlayer.cpp:158, unnamed) shows the
// same tooltip lookup. The owner is the lazy holder object returned by
// rva00224D80 (AptButtonTooltipMap per its constructor); its name map at +0x0C
// may redirect the key, then GameText slot 0x38 fetches "TOOLTIP:"+key and
// the mouse tooltip setter 0x001EEA6D receives the text when it was found.
// The early return on a missing string is a target fact: it gives retail's
// frame homes (key temporary at EBP-18, text at EBP-14).
struct Rva002226E5TextPlusString { Rva002226E5TextPlusString() {} const char *text; int length; const AsciiString *string; operator AsciiString(); };
Rva002226E5TextPlusString operator+(const char *, const AsciiString &);
class GameText {
public:
#define GAME_TEXT_SLOT(n) virtual void gameTextSlot##n();
 GAME_TEXT_SLOT(0) GAME_TEXT_SLOT(1) GAME_TEXT_SLOT(2) GAME_TEXT_SLOT(3) GAME_TEXT_SLOT(4)
 GAME_TEXT_SLOT(5) GAME_TEXT_SLOT(6) GAME_TEXT_SLOT(7) GAME_TEXT_SLOT(8) GAME_TEXT_SLOT(9)
 GAME_TEXT_SLOT(10) GAME_TEXT_SLOT(11) GAME_TEXT_SLOT(12) GAME_TEXT_SLOT(13)
#undef GAME_TEXT_SLOT
 virtual UnicodeString fetch(const AsciiString &label, bool *exists);
};
// The singleton at VA 0x00DFF0BC is owned by GameTextStringLookUpLess.cpp.
// Keep the local slot view while referring to that existing global's type.
class GameTextInterface;
extern GameTextInterface *TheGameText;
class Rva00224CDC {
public:
 void rva002238E6(AsciiString name);
private:
 char m_pad[0xc];
 Rva00056F61 m_tooltipNames; // +0x0C
};
void Rva00224CDC::rva002238E6(AsciiString name)
{
 Rva00056F61 *table = &m_tooltipNames;
 void *node = table->rva00056F61(&name);
 if (node)
  name = *(AsciiString *)((char *)node + 8);
 bool found = false;
 UnicodeString text = reinterpret_cast<GameText *>(TheGameText)->fetch("TOOLTIP:" + name, &found);
 if (!found)
  return;
 TheMouse->rva001EEA6D(text, -1, 0, 1.0f);
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
// Owned factory2223FE forwards the layout-info word to constructor40FDD1.
class AptWindowLayout;
AptWindowLayout * __stdcall Rva002223FECreateLayout(void *);
class ObjectSellInfo;
typedef _STL::list<ObjectSellInfo *> NativePointerList;

// Primary semantic guide: BFME1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/.../GUI/Rva0046A870CreateMainWindow.cpp. WB B93760 names WinCreate.
// Native 223263..2233A6 proves name-by-reference, descriptor size0x34,
// slots88/E8, GameWindow name270 and layout callback10/list28.
GameWindow *AptPlayer::WinCreate(const AsciiString *name,AptLayoutInfoView *layout)
{
 GadgetCreateView view;
 const AsciiString *originalName=name;
 view.status=0x08000001;
 view.unknown24=((Rva00DFF024Registry *)TheFunctionLexicon)->lookup56(TheNameKeyGenerator->nameToKey(*originalName),-1);
 if(!view.unknown24) return 0;
 GameWindow *window=reinterpret_cast<TabWindowManagerView *>(TheWindowManager)->createFromView(&view);
 window->m_field1f4=0;
 // Native reuses the dead incoming pointer word for the found-window slot.
 // Start a new pointer lifetime there after retaining the key in originalName.
 GameWindow *&found=*new (static_cast<void *>(&name)) GameWindow *(0);
 reinterpret_cast<AptWindowSendView *>(TheWindowManager)->findWindow(window,29,2000,&found);
 if(found!=window) return 0;
 found->m_name.setCopyInline(*originalName);
 AsciiString mainName(*originalName);
 reinterpret_cast<StringBase<char> *>(&mainName)->concat(":MainWindow");
 UnicodeString title;
 title.translate(mainName);
 window->GameWindow::winSetText(title);
 if(layout) {
  // Existing rowed pointer-list provider: node payload and argument are
  // the same four-byte pointer word. No application type is reclassified.
  reinterpret_cast<NativePointerList *>(&layout->windows)->push_back(reinterpret_cast<ObjectSellInfo *const &>(window));
  NameKeyType key=TheNameKeyGenerator->nameToKey(*originalName);
  layout->callback=TheFunctionLexicon->findFunction(key,FunctionLexicon::TABLE_MAIN_WINDOW);
  if(!layout->callback) layout->callback=reinterpret_cast<void *>(&Rva002223FECreateLayout);
 }
 return found;
}

// Retail 0x00223BF6, 199 bytes (RET 0xC, answers its first argument): the
// radial clock result for an Apt image path. The timer registered under the
// parameters' "_timerId" (map at +0xB8) or else under the path without its
// level prefix runs its functor into the result; no timer leaves {1.0, null}.
// WB B935C0 shape; the fraction/image pair is the consumer's
// (AptUtils.cpp) RadialClockResult.
struct RadialClockResult
{
	float fraction;
	Image *image;
};

class Rva002229B2Ref
{
public:
	void *invoke(void *result);
};

class Rva00223BF6
{
public:
	RadialClockResult *rva00223BF6(RadialClockResult *out, const char *path, const char *parameters);

private:
	unsigned char m_pad000[0xB8];
	unsigned char m_timerMap[0x14]; // +0xB8
};

RadialClockResult *Rva00223BF6::rva00223BF6(RadialClockResult *out, const char *path, const char *parameters)
{
	AsciiString timerId;
	if (parameters && Rva004128F0GetParam(parameters, "_timerId", timerId))
	{
		void *node = reinterpret_cast<Rva00056F61 *>(m_timerMap)->find(timerId).m_node;
		if (node)
		{
			reinterpret_cast<Rva002229B2Ref *>((char *)node + 8)->invoke(out);
			return out;
		}
	}
	path = AptUtils::SkipLevelN(path);
	void *node = reinterpret_cast<Rva00056F61 *>(m_timerMap)->find(AsciiString(path)).m_node;
	if (node)
	{
		reinterpret_cast<Rva002229B2Ref *>((char *)node + 8)->invoke(out);
		return out;
	}
	out->fraction = 1.0f;
	out->image = 0;
	return out;
}

// WorldBuilder identifies AptPlayer::OnCustomRender; retail 223D8D..223DD7
// proves the null-name guard, temporary key, +34 custom-render map, node+8
// callback handle and four forwarded machine words. Keep those argument
// types neutral: the native caller passes two coordinate pointers as words.
class Rva0022297BRef {
public:
 void invoke(int a, int b, int c, int d);
};
void AptPlayer::OnCustomRender(const char *name, int a, int b, int c, int d)
{
 if (!name)
  return;
 void *node;
 {
  AsciiString key(name);
  node = reinterpret_cast<Rva00056F61 *>(m_customRenderMap)->rva00056F61(&key);
 }
 if (!node)
  return;
 reinterpret_cast<Rva0022297BRef *>(static_cast<char *>(node) + 8)->invoke(a, b, c, d);
}

class Rva00223591 { public: int rva00223736(const AsciiString *key); };
// WB B92650 names the indexed overload and asserts 14 levels. Native
// 2245FF..22464C proves a copied key and the +DC table at stride 0x28.
void AptPlayer::RemoveOverButtonHandler(int index, const AsciiString &key)
{
 AsciiString copy(key);
 Rva00223591 *table = reinterpret_cast<Rva00223591 *>(m_levelData[index].m_pad10);
 table->rva00223736(&copy);
}

// WB B920E0 names the non-indexed overload at AptPlayer.cpp:699.
// Native 22453E..224584 proves the copied key and the +A4 handler map.
void AptPlayer::RemoveOverButtonHandler(const AsciiString &key)
{
 AsciiString copy(key);
 reinterpret_cast<Rva00223591 *>(m_overButtonMap)->rva00223736(&copy);
}

// WorldBuilder B905A0 names HandleOverButtons (AptPlayer.cpp:426..443); the
// tail jump at 0x00225294 reaches it. Native 224F6C..2251E5 proves the
// 512-byte rollover target buffer, the level-11 bit 2 in 0x00E02FC0, the
// mouse-string and window-manager slot 0xD4 guards, the level record's own
// map at +0x10 keyed by the SkipLevelN leaf, the "<movie>/<leaf>" key into
// the +0xA4 handler map (movie extension cut at '.'), the tooltip fallback
// for keys not ending in '/', and the movie-key retry. Callback and map
// providers keep their owned address names.
extern unsigned int g_rva00E02FC0Bits;
bool Rva006CD100Get();
void Rva006CD2A0(char *target);
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *path); }
class Rva001EDE45 { public: void *rva001EDE45(); };
class Rva00224F6CWindowManager {
public:
#define WM_SLOT(n) virtual void wmSlot##n();
 WM_SLOT(0) WM_SLOT(1) WM_SLOT(2) WM_SLOT(3) WM_SLOT(4) WM_SLOT(5) WM_SLOT(6) WM_SLOT(7) WM_SLOT(8) WM_SLOT(9)
 WM_SLOT(10) WM_SLOT(11) WM_SLOT(12) WM_SLOT(13) WM_SLOT(14) WM_SLOT(15) WM_SLOT(16) WM_SLOT(17) WM_SLOT(18) WM_SLOT(19)
 WM_SLOT(20) WM_SLOT(21) WM_SLOT(22) WM_SLOT(23) WM_SLOT(24) WM_SLOT(25) WM_SLOT(26) WM_SLOT(27) WM_SLOT(28) WM_SLOT(29)
 WM_SLOT(30) WM_SLOT(31) WM_SLOT(32) WM_SLOT(33) WM_SLOT(34) WM_SLOT(35) WM_SLOT(36) WM_SLOT(37) WM_SLOT(38) WM_SLOT(39)
 WM_SLOT(40) WM_SLOT(41) WM_SLOT(42) WM_SLOT(43) WM_SLOT(44) WM_SLOT(45) WM_SLOT(46) WM_SLOT(47) WM_SLOT(48) WM_SLOT(49)
 WM_SLOT(50) WM_SLOT(51) WM_SLOT(52)
#undef WM_SLOT
 virtual int slotD4();
};
class Rva0057CC15Ref { public: void invoke(int arg); void *m_ptr; };
struct AptOverButtonNode { AptOverButtonNode *next; AsciiString key; Rva0057CC15Ref handler; };
struct Rva002229E3S12 { Rva002229E3S12() {} char m_c; const char *m_ptr; int m_len; };
Rva002229E3S12 __cdecl Rva002229E3Build(const char &c, const char *s);
AsciiString &__cdecl Rva00222C93Append(AsciiString &str, const char *s);
Rva00224CDC *rva00224D80();
// Retail expands the character read in place here (buffer text at +8, zero
// for an empty string) instead of calling StringBase::getCharAt 0x00035720.
static __forceinline char Rva00224F6CCharAt(const AsciiString &asciiString, int i)
{
 const char *data = *reinterpret_cast<const char *const *>(&asciiString);
 return data ? data[8 + i] : 0;
}

void AptPlayer::HandleOverButtons()
{
 g_rva00E02FC0Bits &= ~2;
 if (!Rva006CD100Get())
  return;
 char target[512];
 Rva006CD2A0(target);
 if (target[0] == 0)
  return;
 int level = AptUtils::LevelIndexFromTarget(target);
 if (level == 11)
  g_rva00E02FC0Bits |= 2;
 if (static_cast<AsciiString *>(reinterpret_cast<Rva001EDE45 *>(TheMouse)->rva001EDE45())->getLength() > 0)
  return;
 if (TheWindowManager && reinterpret_cast<Rva00224F6CWindowManager *>(TheWindowManager)->slotD4())
  return;

 AsciiString name;
 AsciiString movie;
 if (level != -1 && m_levelData[level].m_c == level) {
  const char *leaf = AptUtils::SkipLevelN(target);
  {
   Rva00056F61 &levelMap = *reinterpret_cast<Rva00056F61 *>(m_levelData[level].m_pad10);
   Rva0041534BIter it = levelMap.findIter(AsciiString(leaf));
   if (it.m_node) {
    static_cast<AptOverButtonNode *>(it.m_node)->handler.invoke((int)leaf);
    return;
   }
  }
  movie.setCopyInline(m_levelData[level].m_s0);
  // Retail calls the rowed StringBase search directly.
  const char *dot = ((const StringBase<char> *)&movie)->find('.');
  if (dot)
   movie.setCopyInline(AsciiString(movie, 0, dot - movie.str()));
  name.setCopyInline(movie);
  Rva00222C93Append(name, (const char *)&(const Rva002229E3S12 &)Rva002229E3Build('/', leaf));
 } else {
  name.set(target);
 }

 Rva0041534BIter found;
 found = reinterpret_cast<AptExternTable *>(m_overButtonMap)->find(name);
 if (found.m_node) {
  AptOverButtonNode *node = static_cast<AptOverButtonNode *>(found.m_node);
  if (!node->handler.m_ptr)
   return;
  node->handler.invoke((int)name.str());
  return;
 }
 if (Rva00224F6CCharAt(name, name.getLength() - 1) != '/') {
  rva00224D80()->rva002238E6(name);
  return;
 }
 found = reinterpret_cast<AptExternTable *>(m_overButtonMap)->find(movie);
 if (!found.m_node)
  return;
 AptOverButtonNode *node = static_cast<AptOverButtonNode *>(found.m_node);
 if (node->handler.m_ptr)
  node->handler.invoke((int)name.str());
}
