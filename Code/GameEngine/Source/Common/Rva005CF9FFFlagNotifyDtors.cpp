// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ??1Rva005CF9FF@@UAE@XZ @0x005CF9FF 68B, ??1Rva005CFA43@@UAE@XZ @0x005CFA43
// 68B and ??1Rva005CFA87@@UAE@XZ @0x005CFA87 68B: three sibling dtors,
// identical but for their own vtables 0x00C752CC, 0x00C752D4 and 0x00C752DC
// (callers: the rowed ??_G wrappers 0x005CFDDC, 0x005CFDF8, 0x005CFE14).
// Each stores its vtable; when its flag byte (+0x10, +0x08 and +0x0C respectively) is set and the global
// at VA 0x00E05FAC is non-null, calls the pinned Rva0054CBEFTarget::method
// 0x0054CBEF on it with 0 (the same gated call, with 1, as the rowed
// ??1Rva004FBCBE, whose (int)AptStrategicMessageBox::s_instance spelling is reused); then the inline
// base dtor resets to 0x00C75290 (Rva005CF872, as in Rva005CFDA6Dtor.cpp).
// Identities unproven; address-derived names.

#include "ascii_string.h"
#include "unicode_string.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class GameTextInterface {public:
 virtual ~GameTextInterface(){};
 virtual void s00()=0;virtual void s04()=0;virtual void s08()=0;virtual void s0c()=0;virtual void s10()=0;virtual void s14()=0;virtual void s18()=0;virtual void s1c()=0;virtual void s20()=0;virtual void s24()=0;virtual void s28()=0;virtual void s2c()=0;virtual void s30()=0;
 virtual UnicodeString fetch(const char*,bool * =0)=0;
 virtual UnicodeString fetch(const AsciiString&,bool * =0)=0;
};
extern GameTextInterface *TheGameText;
class Rva0054D3E1Prompt {public:bool configure(int,const UnicodeString&,const UnicodeString&);};
class Rva0054D2DDTarget {public:void method(int,const UnicodeString&,const UnicodeString&);};
class Rva0054CBEFTarget
{
public:
	void method(int arg);
};

class AptStrategicMessageBox {private: static AptStrategicMessageBox *s_instance; friend class Rva005CF9FF; friend class Rva005CFA43; friend class Rva005CFA87;};

class Rva005CF872
{
public:
	Rva005CF872(void *owner):m_04((int)owner) {}
	virtual ~Rva005CF872() {}
	virtual void slot1();
	virtual void slot2();

private:
	int m_04;
};

class Rva005CF9FF : public Rva005CF872
{
public:
	virtual ~Rva005CF9FF();
	virtual void slot1();

private:
	int m_08;
	int m_0C;
	bool m_flag;
};

Rva005CF9FF::~Rva005CF9FF()
{
	if (m_flag && (int)AptStrategicMessageBox::s_instance != 0)
		((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(0);
}

class Rva005CFA43 : public Rva005CF872
{
public:
	virtual ~Rva005CFA43();
	virtual void slot1();

private:
	bool m_flag;
};

Rva005CFA43::~Rva005CFA43()
{
	if (m_flag && (int)AptStrategicMessageBox::s_instance != 0)
		((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(0);
}

class Rva005CFA87 : public Rva005CF872
{
public:
	Rva005CFA87(void *owner, bool change);
	virtual ~Rva005CFA87();
	virtual void slot1();

private:
	int m_08;
	bool m_flag;
};

Rva005CFA87::~Rva005CFA87()
{
	if (m_flag && (int)AptStrategicMessageBox::s_instance != 0)
		((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(0);
}


// Native187B5D044C..5D0507; WB15B9220 names the ShowAllEnemiesRetreated
// state constructor with the two identical strategic text labels. Existing
// dtor-owned Rva005CFA87 spelling preserved; boolC and timestamp8 target-read.
Rva005CFA87::Rva005CFA87(void*o,bool change):Rva005CF872(o),m_08(timeGetTime()),m_flag(change) {
 AptStrategicMessageBox *prompt=AptStrategicMessageBox::s_instance;
 if(prompt){
  UnicodeString title=TheGameText->fetch("STRATEGICHUD:AllEnemiesRetreatedTitle",0);
  UnicodeString text=TheGameText->fetch("STRATEGICHUD:AllEnemiesRetreatedMessage",0);
  if(change) ((Rva0054D3E1Prompt*)prompt)->configure(4,title,text);
  else ((Rva0054D2DDTarget*)prompt)->method(4,title,text);
  m_flag=true;
 }
}
