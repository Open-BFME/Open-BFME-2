// ?rva004FBD3A@Rva004FBC02@@QAEXXZ
// partial score=0.8900527368612475 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /ICode/Libraries/Include/Lib
#include "unicode_string.h"
#include "Coord3D.h"
// ?rva004FBC02@Rva004FBC02@@QAEXPBURva004FBC02Src@@@Z 0x004FBC02 21: copies 12 bytes
// from arg to +0x18 and sets byte at +0x24 to 1. Evidence: callers 0x002BA331 and
// 0x002BA7E1 pass a pointer; no other callees.

struct Rva004FBC02Src
{
	int m_0;
	int m_4;
	int m_8;
};

class __single_inheritance Rva004FBC02;
typedef void(Rva004FBC02::*DelegateMethod)(int);
struct DelegateDesc {void*object;DelegateMethod method;DelegateDesc(DelegateMethod m,void*o):object(o),method(m){}};
class Rva00579E47 {public:Rva00579E47(){}Rva00579E47(const DelegateDesc&);void*ptr;};
struct TreeHintRef00217D4C:public Rva00579E47 {
 TreeHintRef00217D4C(){ptr=0;}
 TreeHintRef00217D4C(const DelegateDesc&d):Rva00579E47(d){}
 TreeHintRef00217D4C(const TreeHintRef00217D4C&o):Rva00579E47(o){if(ptr)++((int*)ptr)[1];}
 ~TreeHintRef00217D4C();
};
class Rva0054D2DDTarget {public:void method(int,const UnicodeString&,const UnicodeString&,TreeHintRef00217D4C,TreeHintRef00217D4C);};
class AptStrategicMessageBox {private:static AptStrategicMessageBox*s_instance;public:static __forceinline AptStrategicMessageBox*get(){return s_instance;}};
class Eva {public:void reportEvaEvent(int,const Coord3D*,int);};extern Eva*TheEva;
class Rva004FBC02
{
public:
 virtual void slot0();virtual void slot1();virtual void slot2();
 void rva004FBC02(const Rva004FBC02Src*src);
 void rva004FBBEB(int response);
 void rva004FBD3A();
private:
 char pad04[4];UnicodeString text,title;int mode,event;
 Rva004FBC02Src m_18;unsigned char m_24;bool shown,accepted;
};
void Rva004FBC02::rva004FBBEB(int response){if(response==3){shown=false;accepted=true;slot2();}}
void Rva004FBC02::rva004FBD3A(){
 Rva0054D2DDTarget*box=(Rva0054D2DDTarget*)AptStrategicMessageBox::get();
 if(box){
 DelegateMethod method=&Rva004FBC02::rva004FBBEB;
 DelegateDesc d(method,this);
 box->method(mode,text,title,TreeHintRef00217D4C(),TreeHintRef00217D4C(d));
 shown=true;TheEva->reportEvaEvent(event,m_24?(const Coord3D*)&m_18:0,0);slot1();
 }
}

void Rva004FBC02::rva004FBC02(const Rva004FBC02Src *src)
{
	m_18 = *src;
	m_24 = 1;
}

// ?rva004FBDB0@Rva004FBDB0@@QAEX_N@Z 0x004FBDB0 28: forwards its flag to slot-12
// virtual on the object looked up by this+0x18 key in the global map at 0x009FE1C8
// via rowed Rva002120A4::rva002120A4; returns on miss. Evidence: callers 0x004FBFF4
// and 0x004FC0E2 (in 0x004FC0AD) pass 0/1; the latter pushes a sete result
// without widening it, so the argument is a bool; callees rowed.

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Rva002120A4
{
public:
	int rva002120A4(NameKeyType key);
};

class Rva0021294A;
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

// Slot-12 target is unidentified; dummies pad the vtable so slot12 lands at +0x30.
class Rva004FBDB0Target
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void slot12(bool arg);
};

class Rva004FBDB0
{
private:
	char m_pad[0x18];
	NameKeyType m_key;
public:
	void rva004FBDB0(bool arg);
};

void Rva004FBDB0::rva004FBDB0(bool arg)
{
	int found = ((Rva002120A4 *)TheLivingWorldManager)->rva002120A4(m_key);
	if (found == 0)
		return;
	((Rva004FBDB0Target *)found)->slot12(arg);
}

// ?rva004FBDCC@Rva004FBDCC@@QAEXXZ 0x004FBDCC 19: pushes this+0x18 then sets
// byte at +0x1c to 1 and forwards the int to Rva00DFE1C8Host::rva00212655
// through global TheLivingWorldManager. Evidence: pin 0x00212655 plus caller 0x002BAF01.
class Rva00DFE1C8Host
{
public:
	void rva00212655(int val);
};

class Rva004FBDCC
{
private:
	char m_pad[0x18];
	int m_18;
	bool m_1c;
public:
	void rva004FBDCC();
};

void Rva004FBDCC::rva004FBDCC()
{
	m_1c = true;
	((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(m_18);
}
