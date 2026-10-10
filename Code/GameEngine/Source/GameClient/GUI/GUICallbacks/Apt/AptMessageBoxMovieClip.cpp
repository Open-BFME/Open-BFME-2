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
 __declspec(noinline) TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other) {if(this!=&other){if(other.m_ptr)++other.m_ptr->references;if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);m_ptr=other.m_ptr;}return *this;}
 TargetRef00217D4C *m_ptr;
 // ?TreeHintRef00217D4C::TreeHintRef00217D4C present-unmatched
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
class Rva000B3F84Pair { public: Rva000B3F84Pair() {} Rva000B3F84Pair *init(const char *src); const char *m_ptr; int m_len; };
struct AsciiStringRef { const AsciiString *m_string; };
struct AsciiStringPlusText : AsciiStringRef { operator AsciiString(); Rva000B3F84Pair m_right; };
AsciiStringPlusText operator+(const AsciiString &,const char *);
// (prefix + movie) + "_OnX" nodes, as in Rva005794EDDtor.cpp: concat
// 0x00109CFD (pinned ICF fold) and conversion 0x0050F74B.
struct AsciiStringPlusString : AsciiStringRef { AsciiStringRef m_second; };
struct AsciiStringPlusStringText : AsciiStringPlusString { operator AsciiString(); Rva000B3F84Pair m_right; };
static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
 AsciiStringPlusString result;
 result.m_string = &left;
 result.m_second.m_string = &right;
 return result;
}
// ?operator+(AsciiStringPlusString, text) present-unmatched (inline, emitted out of line; ICF-folded at 0x00109CFD; pinned)
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
 Rva000B3F84Pair text;
 text.init(right);
 AsciiStringPlusStringText result;
 static_cast<AsciiStringPlusString &>(result) = left;
 result.m_right = text;
 return result;
}

// Apt delegate (object, member) and the command-map name list that binds
// it: ctor 0x001F81BF (ICF fold, pinned), AddCommandMap 0x0052458E, dtor
// 0x0052413E (pinned), delegate ref 0x00579E47 (pinned).
class AptCommandTarget {};
struct DelegateDesc {
 template <class T> DelegateDesc(T *object, void (T::*method)(const char *))
  : m_object(reinterpret_cast<AptCommandTarget *>(object)),
    m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *)>(method)) {}
 AptCommandTarget *m_object;
 void (AptCommandTarget::*m_method)(const char *);
};
class AptCommandMap { public: void *m_vtbl; int m_refCount; };
// 0x00579E47 is rowed as the delegate-wrapper constructor ??0Rva00579E47@@QAE@ABUDelegateDesc@@@Z
// (built in place as the by-value AddCommandMap argument); AptRef<T> builds through it.
class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc); // 0x00579E47
protected:
	Rva00579E47() {}
};

template <class T> class AptRef : public Rva00579E47 {
public:
 AptRef(const DelegateDesc *desc) : Rva00579E47(*desc) {}
 AptRef(const AptRef &that) : m_ptr(that.m_ptr) { if (m_ptr) m_ptr->m_refCount++; }
 ~AptRef() { if (m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
private:
 T *m_ptr;
};
class AptCommandMapAdder {
public:
 AptCommandMapAdder();
 ~AptCommandMapAdder();
 void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
 __forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
 {
  AddCommandMap(name, &desc);
 }
private:
 char m_pad[0xC];
};
class BfmeAptWindowManager {public: void bfmeSetText(const AsciiString &,const UnicodeString &,bool);
 char m_pad000[0x312]; bool m_flag312;};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva0054CFB8Target {
public: Rva0054CFB8Target(int level, const AsciiString &movie);
 void method(int,const UnicodeString &,const UnicodeString &,TreeHintRef00217D4C,TreeHintRef00217D4C);
 void rva0054CA4A();
protected:
 unsigned m_level00; AsciiString m_movie04; AptCommandMapAdder m_commands08; int m_previous14; int m_state18;
 TreeHintRef00217D4C m_callback1C; TreeHintRef00217D4C m_callback20; unsigned m_deadline24; bool m_long28; bool m_29;
};
// Pinned 0x0054C99A (unrowed; closes the box) names this view of the same
// object; Show passes its own this.
class Rva0054C99AImpl : public Rva0054CFB8Target { public: void rva0054C99A(int); };
class Rva00432AEB { public: int rva00432AEB(int); };
class Rva0057CC15Ref { public: void invoke(int); };
// The Apt delegates the box ctor 0x0054CC35 binds by name (retail literals
// "_OnButtonOk".."_OnHidden", in this address order); WB names the four
// button handlers AptMessageBoxMovieClip::Impl::OnButton*.
class AptMessageBoxMovieClip { public: class Impl; };
class AptMessageBoxMovieClip::Impl : public Rva0054CFB8Target {
public:
 void OnButtonOk(const char *);
 void OnButtonCancel(const char *);
 void OnButtonYes(const char *);
 void OnButtonNo(const char *);
 void OnShowing(const char *);
 void OnShown(const char *);
 void OnHiding(const char *);
 void OnHidden(const char *);
};
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

// Native [54C898,54C941) seven thiscall RET4 delegates. A button press ends
// the box (previous14 0, state18 5 = none) and passes its button index to
// the callback1C functor; the window events pass theirs to callback20.
void AptMessageBoxMovieClip::Impl::OnButtonOk(const char *)
{
 m_state18 = 5;
 m_previous14 = 0;
 if (m_callback1C.m_ptr)
  ((Rva0057CC15Ref *)&m_callback1C)->invoke(0);
}

void AptMessageBoxMovieClip::Impl::OnButtonCancel(const char *)
{
 m_previous14 = 0;
 m_state18 = 5;
 if (m_callback1C.m_ptr)
  ((Rva0057CC15Ref *)&m_callback1C)->invoke(1);
}

void AptMessageBoxMovieClip::Impl::OnButtonYes(const char *)
{
 m_previous14 = 0;
 m_state18 = 5;
 if (m_callback1C.m_ptr)
  ((Rva0057CC15Ref *)&m_callback1C)->invoke(2);
}

void AptMessageBoxMovieClip::Impl::OnButtonNo(const char *)
{
 m_previous14 = 0;
 m_state18 = 5;
 if (m_callback1C.m_ptr)
  ((Rva0057CC15Ref *)&m_callback1C)->invoke(3);
}

void AptMessageBoxMovieClip::Impl::OnShowing(const char *)
{
 if (m_callback20.m_ptr)
  ((Rva0057CC15Ref *)&m_callback20)->invoke(0);
}

void AptMessageBoxMovieClip::Impl::OnShown(const char *)
{
 if (m_callback20.m_ptr)
  ((Rva0057CC15Ref *)&m_callback20)->invoke(1);
}

void AptMessageBoxMovieClip::Impl::OnHiding(const char *)
{
 if (m_callback20.m_ptr)
  ((Rva0057CC15Ref *)&m_callback20)->invoke(2);
}

// Native [54CC35,54CFB8)899B thiscall RET8 ending at Show 54CFB8, the
// box ctor called from 0x0054D286: level00, movie04, the command-map list at
// 08, no pending transition, state18 5 (no box), empty callbacks, no
// deadline; then binds the eight delegates as "_level%u." + movie + "_OnX".
// OnHidden0x0054CBB0 is recovered below under its constructor-bound name.
Rva0054CFB8Target::Rva0054CFB8Target(int level, const AsciiString &movie)
 : m_level00(level), m_movie04(movie), m_previous14(0), m_state18(5),
   m_deadline24((unsigned)-1), m_long28(false), m_29(false)
{
 typedef AptMessageBoxMovieClip::Impl Impl;
 Impl *impl = static_cast<Impl *>(this);
 AsciiString prefix;
 prefix.format("_level%u.", m_level00);
 m_commands08.AddCommandMapDelegate(prefix + m_movie04 + "_OnButtonOk", DelegateDesc(impl, &Impl::OnButtonOk));
 m_commands08.AddCommandMapDelegate(prefix + m_movie04 + "_OnButtonCancel", DelegateDesc(impl, &Impl::OnButtonCancel));
 m_commands08.AddCommandMapDelegate(prefix + m_movie04 + "_OnButtonYes", DelegateDesc(impl, &Impl::OnButtonYes));
 m_commands08.AddCommandMapDelegate(prefix + m_movie04 + "_OnButtonNo", DelegateDesc(impl, &Impl::OnButtonNo));
 m_commands08.AddCommandMapDelegate(prefix + m_movie04 + "_OnShowing", DelegateDesc(impl, &Impl::OnShowing));
 m_commands08.AddCommandMapDelegate(prefix + m_movie04 + "_OnShown", DelegateDesc(impl, &Impl::OnShown));
 m_commands08.AddCommandMapDelegate(prefix + m_movie04 + "_OnHiding", DelegateDesc(impl, &Impl::OnHiding));
 m_commands08.AddCommandMapDelegate(prefix + m_movie04 + "_OnHidden", DelegateDesc(impl, &Impl::OnHidden));
}

// Native176B [54C99A,54CA4A), EH+RET4. Existing level/movie/state
// view is independently proven by899B constructor and370B Show. Visible
// exact43B noinline handle assignment preserves source ownership knowledge;
// construct empty BEFORE binding its destination reference to reproduce
// native LEA/PUSH scheduling. Input uses only its low byte, retained from
// existing int ABI view. All named callers continue to use this sole owner.
void Rva0054C99AImpl::rva0054C99A(int arg) {
 if(m_state18!=5) {
  m_state18=5;
  {const TreeHintRef00217D4C empty;
   TreeHintRef00217D4C&pending=m_callback1C;
   pending=empty;}
  m_deadline24=~0u;
  if(m_previous14!=0 && m_previous14!=3)m_previous14=3;
  if((unsigned char)arg) {
   m_29=true;
   if(m_callback20.m_ptr) {
    ((Rva0057CC15Ref*)&m_callback20)->invoke(2);
    ((Rva0057CC15Ref*)&m_callback20)->invoke(3);
    m_callback20=TreeHintRef00217D4C();
   }
  }
  if(g_bfmeAptWindowManager && !g_bfmeAptWindowManager->m_flag312)rva0054CA4A();
 }
}

// Constructor binds63B native callback54CBB0 by _OnHidden; its complete
// unused word argument is the same const-char-pointer ABI as the other seven
// registered callbacks. Rehome the existing63B row; no new byte credit.
void AptMessageBoxMovieClip::Impl::OnHidden(const char*unused) {
 if(m_callback20.m_ptr) {
  ((Rva0057CC15Ref*)&m_callback20)->invoke(3);
  m_callback20=TreeHintRef00217D4C();
 }
}
