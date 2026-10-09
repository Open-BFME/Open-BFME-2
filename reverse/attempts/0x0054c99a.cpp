// ?rva0054C99A@Rva0054C941@@QAEXH@Z
// partial score=0.97 date=2026-10-09
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
 __declspec(noinline) TreeHintRef00217D4C&operator=(const TreeHintRef00217D4C&);
	__forceinline void clear(){*this=TreeHintRef00217D4C();}
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
 TreeHintRef00217D4C&pendingRef(){return m_holder1C;}
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
void Rva0054C941::rva0054C99A(int arg) {
 if(m_word18!=5) {
  m_word18=5;
  ((TreeHintRef00217D4C*)&m_holder1C)->operator=(TreeHintRef00217D4C(0));
  m_word24=~0u;
  if(m_word14!=0 && m_word14!=3)m_word14=3;
  if((unsigned char)arg) {
   m_flag29=true;
   if(m_holder20.m_ptr) {
    ((Rva0057CC15Ref*)&m_holder20)->invoke(2);
    ((Rva0057CC15Ref*)&m_holder20)->invoke(3);
    m_holder20=TreeHintRef00217D4C();
   }
  }
  if(g_bfmeAptWindowManager && !g_bfmeAptWindowManager->flag312)rva0054CA4A();
 }
}
void Rva0054C941::rva0054CBB0(int unused) {
 if(m_holder20.m_ptr) {
  ((Rva0057CC15Ref*)&m_holder20)->invoke(3);
  m_holder20=TreeHintRef00217D4C();
 }
}

TreeHintRef00217D4C&TreeHintRef00217D4C::operator=(const TreeHintRef00217D4C&other) {
 if(this!=&other) {
  if(other.m_ptr)++other.m_ptr->references;
  if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);
  m_ptr=other.m_ptr;
 }
 return *this;
}

class Rva00222A8BTarget;
int Rva0054C83FAptCall(Rva00222A8BTarget*,void*,const char*,const char*,const char**,bool*);
void Rva005277D9Fire(Rva00222A8BTarget*,void*,const char*,const char*,bool*);
int Rva0050E9FEAptCall(Rva00222A8BTarget*,void*,const char*,const char*,const char**);
extern int g_Va00E032C8;
class Rva00432AEB {public:int rva00432AEB(int);};
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
void Rva0054C941::rva0054CA4A() {
 const char*caption;
 if(m_word14==2) {
  Rva00432AEB*mouse=(Rva00432AEB*)g_Va00E032C8;
  if(mouse)mouse->rva00432AEB(2);
  if(m_word18==2)caption="YesNo";
  else if(m_word18==1)caption="OkCancel";
  else if(m_word18==3)caption="Cancel";
  else if(m_word18==4)caption="NonInteractive";
  else caption="Ok";
  Rva0054C83FAptCall((Rva00222A8BTarget*)g_bfmeAptWindowManager,m_level,m_str.str(),"Show",&caption,&m_flag28);
  m_word14=1;
 } else if(m_word14==3) {
  Rva005277D9Fire((Rva00222A8BTarget*)g_bfmeAptWindowManager,m_level,m_str.str(),"Hide",&m_flag29);
  m_word14=0;m_flag29=false;
 } else if(m_word14==4) {
  if(m_word18==2)caption="YesNo";
  else if(m_word18==1)caption="OkCancel";
  else if(m_word18==4)caption="NonInteractive";
  else if(m_word18==3)caption="Cancel";
  else caption="Ok";
  Rva0050E9FEAptCall((Rva00222A8BTarget*)g_bfmeAptWindowManager,m_level,m_str.str(),"Change",&caption);
  m_word14=1;
 }
 if(m_word14 && timeGetTime()>m_word24)rva0054C99A(0);
}
