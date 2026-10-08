// ?rva0022402A@Rva0022402A@@QAEAAVRva00468520@@ABVAsciiString@@@Z
// partial score=0.96 date=2026-10-08
// cl: /O1 /GX /MD /arch:SSE /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include <utility>
#include "ascii_string.h"
struct TargetRef00217D4C { virtual void *destroy(unsigned); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva00056F61;
struct Rva0041534BIter {
	void *m_node; Rva00056F61 *m_table;
	Rva0041534BIter(void *n,Rva00056F61*t) : m_node(n), m_table(t) {}
};
class Rva00056F61 { public: Rva0041534BIter rva0041534B(const AsciiString *); };
// STLport hash_map operator[] for the native eight-byte callback/index value.
class Rva00468520 {
public:
 TargetRef00217D4C *m_ptr; int m_index;
 Rva00468520() : m_ptr(0), m_index(0) {}
 Rva00468520(const Rva00468520 &other) { set(&other); }
 Rva00468520 *set(const Rva00468520 *src) throw();
 ~Rva00468520() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
typedef _STL::pair<const AsciiString,Rva00468520> Rva0022402APair;
struct Rva0022402ANode { Rva0022402ANode *next; Rva0022402APair value; };
class Rva00223591 { public: void *rva002237C7(const void *value); };
class Rva0022402A { public: Rva00468520 &rva0022402A(const AsciiString &key); };
Rva00468520 &Rva0022402A::rva0022402A(const AsciiString &key) {
 Rva0022402ANode *node;
 {
  Rva0041534BIter it = reinterpret_cast<Rva00056F61 *>(this)->rva0041534B(&key);
  node = static_cast<Rva0022402ANode *>(it.m_node);
 }
 return !node ? reinterpret_cast<Rva0022402APair *>(reinterpret_cast<Rva00223591 *>(this)->rva002237C7(&Rva0022402APair(key,Rva00468520())))->second : node->value.second;
}
