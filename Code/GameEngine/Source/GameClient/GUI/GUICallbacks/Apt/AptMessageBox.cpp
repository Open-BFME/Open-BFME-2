// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// AptMessageBox (WorldBuilder GameClient/Gui/GUICallbacks/Apt/AptMessageBox.cpp).
// Target facts: the static Show 0x00437E84 and Change 0x00437EAC (cdecl,
// three arguments) forward to the singleton instance (WorldBuilder
// Instance(), the dword at 0x00A032FC, rowed as the address-named
// g_Va00E032FC) through 0x0054D2DD / 0x0054D3D9 (unnamed there, pinned
// address-named). Argument types are not recovered.
extern int g_Va00E032FC;

#include "unicode_string.h"

// Counted callback ABI established by the rowed 54D362 forwarder and
// ReleaseTreeHintRef00217D4C: pointer at +0; target reference count at +4.
struct TargetRef00217D4C { virtual void *destroy(unsigned int); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 TargetRef00217D4C *m_ptr;
 TreeHintRef00217D4C(const TreeHintRef00217D4C &v):m_ptr(v.m_ptr) {
  if(m_ptr) ++m_ptr->references;
 }
 ~TreeHintRef00217D4C() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
class Rva0054D2DDTarget { public:
 void method(int,const UnicodeString &,const UnicodeString &,
  TreeHintRef00217D4C,TreeHintRef00217D4C);
};

class AptMessageBox
{
public:
	static void Show(void *a, void *b, void *c);
 static void Show(int,const UnicodeString &,const UnicodeString &,TreeHintRef00217D4C,TreeHintRef00217D4C);
	static void Change(void *a, void *b, void *c);

	void rva0054D2DD(void *a, void *b, void *c);
	void rva0054D3D9(void *a, void *b, void *c);

private:
	static AptMessageBox *Instance() { return (AptMessageBox *)g_Va00E032FC; }
};

void AptMessageBox::Show(void *a, void *b, void *c)
{
	Instance()->rva0054D2DD(a, b, c);
}

void AptMessageBox::Change(void *a, void *b, void *c)
{
	Instance()->rva0054D3D9(a, b, c);
}

// WB12B4240 names this five-argument static Show overload. Retail
// [437FB3,43802B) copies both incoming counted handles into 54D362 and
// releases the incoming copies. Text/title are const references, as proved
// by the independently verified callee. Callback payload identity is unknown.
void AptMessageBox::Show(int type,const UnicodeString &text,
 const UnicodeString &title,TreeHintRef00217D4C callback,
 TreeHintRef00217D4C callback2)
{
 reinterpret_cast<Rva0054D2DDTarget *>(Instance())->method(type,text,title,callback,callback2);
}
