// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /O1 /G7 /arch:SSE
// stlport
//
// ??1Rva0054C941@@QAE@XZ @0x0054C941 (89B).
// Dtor with EH scope 0x0079824F: releases TreeHint refs at +0x20/+0x1c,
// destroys Rva0052413E at +8, releases AsciiString at +4. LINK BONUS 46B,
// callers 0x0054CC02/0x0054CC27, unblocks 0x0054CC1B.
#include "ascii_string.h"
#include <vector>

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_vec;	// +0x00, size 12
};
struct TargetRef00217D4C {void*vt;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
 TreeHintRef00217D4C(TargetRef00217D4C*p=0):m_ptr(p){if(m_ptr)++m_ptr->references;}
 __declspec(noinline) TreeHintRef00217D4C&operator=(const TreeHintRef00217D4C&other) {
 if(this!=&other) {
  if(other.m_ptr)++other.m_ptr->references;
  if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);
  m_ptr=other.m_ptr;
 }
 return *this;
}


	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
class Rva0054C941
{
public:
	~Rva0054C941();
 void rva0054C99A(int);void rva0054CA4A();void rva0054CBB0(int);
private:
	void*m_level;			// +0x00
	AsciiString m_str;			// +0x04
	Rva0052413E m_rva08;			// +0x08
	int m_word14;int m_word18;		// +0x14
	TreeHintRef00217D4C m_holder1C;	// +0x1c
	TreeHintRef00217D4C m_holder20;	// +0x20
 unsigned m_word24;bool m_flag28,m_flag29;
};
Rva0054C941::~Rva0054C941()
{
}

class Rva0057CC15Ref {public:void invoke(int);};
class BfmeAptWindowManager {public:unsigned char pad[0x312];bool flag312;};
extern BfmeAptWindowManager*g_bfmeAptWindowManager;
// Native54CBB0..54CBEF complete63B EH+RET4; callback holder+20 is
// independently established by89B dtor and native176B sibling. The exact
// existing43B noinline assignment is visible so VC7.1 proves the empty
// temporary is not modified and removes spurious hot releases. The holder
// callback is invoked with3 before clearing; argument is unused.
void Rva0054C941::rva0054CBB0(int unused) {
 if(m_holder20.m_ptr) {
  ((Rva0057CC15Ref*)&m_holder20)->invoke(3);
  m_holder20=TreeHintRef00217D4C();
 }
}

