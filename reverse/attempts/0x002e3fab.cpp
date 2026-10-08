// ??0PolygonTrigger@@QAE@HH@Z
// partial score=0.949367 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Banked near miss: native2E3FAB..2E4049 is158B ending ret12;
// Ghidra297B conflates the following destructor. WBAB9C60 and parser
// new(0x64) establish PolygonTrigger identity and the two explicit int args.
// Provisional measured MI view; next-pointer base remains an inference.
// Native stores next+3C before the base call; this C++ stores it afterwards.
// 150/158 patched bytes match. Do not admit or fake a constructor pin.
// Native 330C50..330CC2: primary vptr +0, vbptr +4, container +8,
// flag +34, vtordisp +38, seven-slot virtual interface +3C.
// The vbtable contains {-4, 0x38}; interface thunks 2E3E80..2E3EB0
// each subtract the vtordisp before dispatching the corresponding member.
class Rva00330C50Interface
{
public:
	~Rva00330C50Interface() {}
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
};

class Rva0030B9DD
{
public:
	Rva0030B9DD(int);
	~Rva0030B9DD();
private:
	char unknown00[0x2C];
};

class Rva00330C50 : public virtual Rva00330C50Interface
{
public:
	Rva00330C50();
	void rva00330AA6(int);
	virtual ~Rva00330C50();
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
private:
	Rva0030B9DD container;
	bool changed;
};

Rva00330C50::Rva00330C50() : container(0)
{
	changed = true;
}

class AreaPolygonBase { public: void reserve(int); };
// Native330AA6 is an8-byte terminal jump to rowed AreaPolygonBase::reserve
// at30B96B with the measured container adjustment8. The following16 bytes
// form a separate float virtual dispatch, not part of this reserve wrapper.
__declspec(noinline) void Rva00330C50::rva00330AA6(int count)
{
 reinterpret_cast<AreaPolygonBase*>(&container)->reserve(count);
}

#include "ascii_string.h"
class PolygonTrigger;
class PolygonNext { public: PolygonNext():next(0){} PolygonTrigger *next; };
class PolygonSecondary : public PolygonNext {
public:
 PolygonSecondary(){}

 virtual PolygonTrigger* secondarySlot()=0;

};
class PolygonTrigger : public Rva00330C50, public PolygonSecondary {
public:
 PolygonTrigger(int,int);
 virtual ~PolygonTrigger();
 virtual PolygonTrigger* secondarySlot();
 void rva002E36B7(int);
 AsciiString name;
 int id;
 bool flag48;
 AsciiString layer;
 bool flag50;
 int field54,field58;
};
PolygonTrigger::PolygonTrigger(int identifier,int count):id(identifier)
{ rva002E36B7(count); }
__declspec(noinline) void PolygonTrigger::rva002E36B7(int count)
{
 rva00330AA6(count);
 flag48=false;flag50=false;field54=0;field58=0;
}





