// cl: /O1 /GX /MD /D_CRTIMP= /Ireference/shims/bfme2_ascii
// ?Rva00437EDCGet@@YA_NXZ @0x00437EDC 18B null-checks g_Va00E032FC then tail-calls Rva0054C88A::rva0054C88A.
// Evidence: packet disassembly; global g_Va00E032FC ?g_Va00E032FC@@3HA; callee row ?rva0054C88A@Rva0054C88A@@QAE_NXZ; callers test al as bool with no pushes.
extern int g_Va00E032FC;

class Rva0054C88A
{
public:
	bool rva0054C88A();
};

bool Rva00437EDCGet()
{
	Rva0054C88A *p = (Rva0054C88A *)g_Va00E032FC;
	if (p == 0)
		return false;
	return p->rva0054C88A();
}
// Native APT prompt state and forwarding family. Original class and method
// names are unknown; address names preserve that uncertainty.
// Retail Ghidra [54D12A,54D222)248B configures a prompt unless state18==5,
// writes previous14=4 and state18=kind, and binds Title/Text using
// APT:_level%u.%s_ with unsigned level00 and AsciiString movie04.
// Target accesses establish these prefix offsets; the untouched bytes08..13
// remain opaque. No donor class layout or inheritance is asserted.
// Full byte proofs use the existing format38150/20, operator+B49C5/52,
// concat conversionBC4F7/98, release36410/133 and bfmeSetText225301/116.
// The refcounted callback prefix agrees with rowed TreeHintRef00217D4C:
// one pointer, signed count at referent+4, fastcall release7DEEF/24.
// 43802B is called cdecl from AptSaveLoad4355E2 with kind2, title fetched
// through GameText, message by reference, and a23E8D8 callback holder.
// 54D3E1's native call entry, EH prologue and ret16 prove its87B body ending
// at the next EH-prologue54D438; Ghidra omits that entry. It forwards via
// child04 to confirmed100B54D222, which assigns callback1C only on success.
// A local callback-member reference preserves retail's address evaluation.

struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
 TargetRef00217D4C *m_ptr;
 // ?TreeHintRef00217D4C::TreeHintRef00217D4C present-unmatched
 TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr)
 {
  if (m_ptr)
   ++m_ptr->references;
 }
 // ?TreeHintRef00217D4C::~TreeHintRef00217D4C present-unmatched
 __forceinline ~TreeHintRef00217D4C()
 {
  if (m_ptr)
   ReleaseTreeHintRef00217D4C(m_ptr);
 }
};
#include "ascii_string.h"
class UnicodeString;
class Rva000B3F84Pair { public: const char *m_ptr; int m_len; };
struct AsciiStringRef { const AsciiString *m_string; };
struct AsciiStringPlusText : AsciiStringRef { operator AsciiString(); Rva000B3F84Pair m_right; };
AsciiStringPlusText operator+(const AsciiString &,const char *);
class BfmeAptWindowManager {public: void bfmeSetText(const AsciiString &,const UnicodeString &,bool);};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva0054D222Prompt {
public: bool prompt(int,const UnicodeString &,const UnicodeString &,TreeHintRef00217D4C);
private: bool configure(int,const UnicodeString &,const UnicodeString &);
 unsigned m_level00; AsciiString m_movie04; char m_pad08[0xc]; int m_previous14; int m_state18; TreeHintRef00217D4C m_callback;
};
class Rva0054D3E1Prompt {
public: bool prompt(int,const UnicodeString &,const UnicodeString &,TreeHintRef00217D4C);
private: unsigned char m_pad00[4]; Rva0054D222Prompt *m_child04;
};
bool Rva0054D222Prompt::configure(int kind, const UnicodeString &title,
 const UnicodeString &message)
{
 if (m_state18 == 5)
  return false;
 m_previous14 = 4;
 m_state18 = kind;
 AsciiString prefix;
 prefix.format("APT:_level%u.%s_", m_level00, m_movie04.str());
 g_bfmeAptWindowManager->bfmeSetText(prefix + "Title", title, true);
 g_bfmeAptWindowManager->bfmeSetText(prefix + "Text", message, true);
 return true;
}


// Native Ghidra [54D222,54D286)100B; successful configuration retains
// the passed callback at1C. Both returns release the owned by-value input.
bool Rva0054D222Prompt::prompt(int kind, const UnicodeString &title,
 const UnicodeString &message, TreeHintRef00217D4C callback)
{
 if (configure(kind, title, message))
 {
  TreeHintRef00217D4C &destination = m_callback;
  destination = callback;
  return true;
 }
 return false;
}
