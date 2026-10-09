// ?rva0054C99A@Rva0054C99AImpl@@QAEXH@Z
// partial score=0.86 date=2026-10-10
// cl: /O1 /GX /MD /D_CRTIMP= /Ireference/shims/bfme2_ascii
//
// Message-box movie clip state machine at its WorldBuilder home. WB's
// AptMessageBoxMovieClip.cpp names 0x0054CFB8 AptMessageBoxMovieClip::Impl::
// Show (callgraph lead, asserts "Multiple message boxes at the same time are
// not allowed."); the address-derived class and method names already pinned
// for its callers are kept, since retail proves the bodies, not the names.
//
// Target facts (read from retail): the object is the child at +4 of the
// g_Va00E032FC holder, the same one the adjacent configure 0x0054D12A
// (Rva00437EDCFinish.cpp) drives: level00, movie04, previous14 (pending
// transition), state18 (box type, 5 = none), callbacks 1C/20, a timeGetTime
// deadline at 24, the long-text byte 28 and the hide byte 29.
// 0x00DFE4CC is the window manager; its byte 312 suppresses the immediate
// transition flush. The box-type names are retail's literals.

struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
 TargetRef00217D4C *m_ptr;
 TreeHintRef00217D4C() : m_ptr(0) {}
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
#include "unicode_string.h"
class Rva000B3F84Pair { public: const char *m_ptr; int m_len; };
struct AsciiStringRef { const AsciiString *m_string; };
struct AsciiStringPlusText : AsciiStringRef { operator AsciiString(); Rva000B3F84Pair m_right; };
AsciiStringPlusText operator+(const AsciiString &,const char *);
class BfmeAptWindowManager {public: void bfmeSetText(const AsciiString &,const UnicodeString &,bool);
 char m_pad000[0x312]; bool m_flag312;};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva0054CFB8Target {
public: void method(int,const UnicodeString &,const UnicodeString &,TreeHintRef00217D4C,TreeHintRef00217D4C);
 void rva0054CA4A();
protected:
 unsigned m_level00; AsciiString m_movie04; char m_pad08[0xc]; int m_previous14; int m_state18;
 TreeHintRef00217D4C m_callback1C; TreeHintRef00217D4C m_callback20; unsigned m_deadline24; bool m_long28; bool m_29;
};
// Pinned 0x0054C99A (unrowed; closes the box) names this view of the same
// object; Show passes its own this.
class Rva0054C99AImpl : public Rva0054CFB8Target { public: void rva0054C99A(int); };
class Rva00432AEB { public: int rva00432AEB(int); };
class Rva0057CC15Ref { public: void invoke(int); };
extern int g_Va00E032C8;
class Rva00222A8BTarget;
int __cdecl Rva0054C83FAptCall(Rva00222A8BTarget *, void *, const char *, const char *, const char **, bool *);
void __cdecl Rva005277D9Fire(Rva00222A8BTarget *, void *, const char *, const char *, bool *);
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *, void *, const char *, const char *, const char **);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// Native [54CA4A,54CBB0)358B thiscall plain RET. Pending transition
// previous14: 2 releases g_Va00E032C8's 432AEB(2) and calls the movie's
// "Show" with the box-type name and the long-text byte28; 3 calls "Hide"
// with byte29 and resets both; 4 calls "Change" with the type name. Show and
// Change leave previous14 at 1. A pending box past its deadline24 closes.
void Rva0054CFB8Target::rva0054CA4A()
{
 const char *type;
 if (m_previous14 == 2)
 {
  if (g_Va00E032C8)
   ((Rva00432AEB *)g_Va00E032C8)->rva00432AEB(2);
  if (m_state18 == 2)
   type = "YesNo";
  else if (m_state18 == 1)
   type = "OkCancel";
  else if (m_state18 == 3)
   type = "Cancel";
  else if (m_state18 == 4)
   type = "NonInteractive";
  else
   type = "Ok";
  Rva0054C83FAptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,
   (void *)m_level00, m_movie04.str(), "Show", &type, &m_long28);
 }
 else if (m_previous14 == 3)
 {
  Rva005277D9Fire((Rva00222A8BTarget *)g_bfmeAptWindowManager,
   (void *)m_level00, m_movie04.str(), "Hide", &m_29);
  m_previous14 = 0;
  m_29 = false;
  goto check;
 }
 else if (m_previous14 == 4)
 {
  if (m_state18 == 2)
   type = "YesNo";
  else if (m_state18 == 1)
   type = "OkCancel";
  else if (m_state18 == 4)
   type = "NonInteractive";
  else if (m_state18 == 3)
   type = "Cancel";
  else
   type = "Ok";
  Rva0050E9FEAptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,
   (void *)m_level00, m_movie04.str(), "Change", &type);
 }
 else
  goto check;
 m_previous14 = 1;
check:
 if (m_previous14 != 0 && timeGetTime() > m_deadline24)
  ((Rva0054C99AImpl *)this)->rva0054C99A(0);
}

// Native [54CFB8,54D12A)370B thiscall RET20, ending at the adjacent
// configure 54D12A. It closes a live box via pinned 54C99A(0), binds both
// handles, writes Title/Text, flags text over 0x100 chars and flushes through
// 54CA4A while the window manager's byte 312 is clear. Local member
// references keep retail's address-before-argument evaluation order.
void Rva0054CFB8Target::method(int kind, const UnicodeString &title,
 const UnicodeString &message, TreeHintRef00217D4C callback,
 TreeHintRef00217D4C callback2)
{
 if (m_state18 != 5)
  ((Rva0054C99AImpl *)this)->rva0054C99A(0);
 m_state18 = kind;
 TreeHintRef00217D4C &first = m_callback1C;
 first = callback;
 TreeHintRef00217D4C &second = m_callback20;
 second = callback2;
 m_deadline24 = (unsigned)-1;
 AsciiString prefix;
 prefix.format("APT:_level%u.%s_", m_level00, m_movie04.str());
 g_bfmeAptWindowManager->bfmeSetText(prefix + "Title", title, true);
 g_bfmeAptWindowManager->bfmeSetText(prefix + "Text", message, true);
 m_previous14 = 2;
 m_29 = false;
 m_long28 = message.getLength() > 0x100;
 if (g_bfmeAptWindowManager && !g_bfmeAptWindowManager->m_flag312)
  rva0054CA4A();
}

// Native [54C99A,54CA4A)176B thiscall RET4. Unless state18 is already 5 it
// sets 5, clears callback1C and the deadline, moves a nonzero previous14 to 3,
// and when its byte argument is set marks byte29 and fires callback20
// through rowed 57CC15 with 2 then 3 before clearing it. Same 54CA4A tail
// as Show. Show calls it with 0 when replacing a live box.
void Rva0054C99AImpl::rva0054C99A(int notify)
{
 if (m_state18 == 5)
  return;
 m_state18 = 5;
 TreeHintRef00217D4C &first = m_callback1C;
 first = TreeHintRef00217D4C();
 m_deadline24 = (unsigned)-1;
 if (m_previous14 != 0 && m_previous14 != 3)
  m_previous14 = 3;
 if ((char)notify)
 {
  m_29 = true;
  if (m_callback20.m_ptr)
  {
   ((Rva0057CC15Ref *)&m_callback20)->invoke(2);
   ((Rva0057CC15Ref *)&m_callback20)->invoke(3);
   TreeHintRef00217D4C &second = m_callback20;
   second = TreeHintRef00217D4C();
  }
 }
 if (g_bfmeAptWindowManager && !g_bfmeAptWindowManager->m_flag312)
  rva0054CA4A();
}
