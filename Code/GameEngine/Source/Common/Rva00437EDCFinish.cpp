// cl: /O1 /GX /MD /D_CRTIMP= /Ireference/shims/bfme2_ascii
// ?Rva00437EDCGet@@YA_NXZ @0x00437EDC 18B null-checks g_Va00E032FC then tail-calls Rva0054C88A::rva0054C88A.
// Evidence: packet disassembly; global g_Va00E032FC ?g_Va00E032FC@@3HA; callee row ?rva0054C88A@Rva0054C88A@@QAE_NXZ; callers test al as bool with no pushes.
extern int g_Va00E032FC;

class Rva0054C88A
{
public:
	void rva0054C877(float);
	bool rva0054C88A();
};

void Rva00437EC4Set(float val)
{
	Rva0054C88A *p = (Rva0054C88A *)g_Va00E032FC;
	if (p != 0)
		p->rva0054C877(val);
}

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
 friend class Rva0054D3E1Prompt;
 friend class Rva0054D438Prompt;
 unsigned m_level00; AsciiString m_movie04; char m_pad08[0xc]; int m_previous14; int m_state18; TreeHintRef00217D4C m_callback;
 TreeHintRef00217D4C m_callback20;
};
// The two-callback prompt the child04 forwarder 0x0054D4CD calls (pinned
// name); retail runs it on the same object as Rva0054D222Prompt.
class Rva0054D438Prompt : public Rva0054D222Prompt {
public: bool prompt(int,const UnicodeString &,const UnicodeString &,TreeHintRef00217D4C,TreeHintRef00217D4C);
};
class Rva0054D3E1Prompt {
public: bool prompt(int,const UnicodeString &,const UnicodeString &,TreeHintRef00217D4C);
 bool configure(int,const UnicodeString &,const UnicodeString &);
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

// ?configure@Rva0054D3E1Prompt@@QAE_NHABVUnicodeString@@0@Z @0x0054D3D9 8B.
// Target moves this+4 into ecx and tail-jumps to the rowed private
// Rva0054D222Prompt::configure; adjacent prompt body and its child04 layout
// identify this forwarding method and wrapper class.
bool Rva0054D3E1Prompt::configure(int kind, const UnicodeString &title,
 const UnicodeString &message)
{
 return m_child04->configure(kind, title, message);
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

// Native [54D438,54D4B1)121B thiscall RET20, ending at the deleting dtor
// 54D4B1: the one-callback prompt 54D222 gets a copy of the first callback;
// when it accepts, the second goes to callback20. Retail returns false on
// both paths.
bool Rva0054D438Prompt::prompt(int kind, const UnicodeString &title,
 const UnicodeString &message, TreeHintRef00217D4C callback,
 TreeHintRef00217D4C callback2)
{
 if (Rva0054D222Prompt::prompt(kind, title, message, callback))
  {
  TreeHintRef00217D4C &destination = m_callback20;
  destination = callback2;
 }
 return false;
}

// Native [54D3E1,54D438)87B thiscall RET16: entered by43802B;
// next EH prologue establishes its end. Native child pointer is at4.
bool Rva0054D3E1Prompt::prompt(int kind, const UnicodeString &title,
 const UnicodeString &message, TreeHintRef00217D4C callback)
{
 return m_child04->prompt(kind, title, message, callback);
}

// Native Ghidra [43802B,438083)88B cdecl; AptSaveLoad caller4355E2
// passes kind2, a fetched title, message reference and counted callback.
extern "C" bool Rva0043802B(int kind, const UnicodeString &title,
 const UnicodeString &message, TreeHintRef00217D4C callback)
{
 return ((Rva0054D3E1Prompt *)g_Va00E032FC)->prompt(kind, title, message, callback);
}


// Target Ghidra FUN_00838083 [438083,43812F) is a 172B cdecl prompt
// wrapper. The exact body ends in ret at +0xAB. Retail reads the prompt from
// g_Va00E032FC, passes kind/title/message to 54D4CD, and keeps the two
// counted callback values alive across that call. The owner and behavior
// remain address-derived; 54D4CD is a five-argument thiscall child forwarder.
class Rva0054D4CDPrompt
{
public:
 bool prompt(int, const UnicodeString &, const UnicodeString &,
  TreeHintRef00217D4C, TreeHintRef00217D4C);
};

extern "C" bool Rva00438083(int kind, const UnicodeString &title,
 const UnicodeString &message, TreeHintRef00217D4C callback1,
 TreeHintRef00217D4C callback2)
{
 if (g_Va00E032FC == 0)
  return false;
 return ((Rva0054D4CDPrompt *)g_Va00E032FC)->prompt(
  kind, title, message, callback1, callback2);
}
