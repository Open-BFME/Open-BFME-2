// cl: /O1 /GX /MD /arch:SSE /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_CRTIMP=
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

class AptPlayer
{
public:
	void PopFocus(AptFocusTarget *target);
 void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
 void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);

private:
	unsigned char m_pad000[0xc];
 unsigned char m_commandMap[0x28]; // observed member start +0x0C
 unsigned char m_customRenderMap[0x28]; // observed member start +0x34
 unsigned char m_pad05c[0x2fc-0x5c];
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
