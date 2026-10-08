// ??0PolygonTrigger@@QAE@H@Z
// partial score=0.9 date=2026-10-08
// PARTIAL: native002E3EB8..002E3F5E, WB00AB9AE0. 166-byte instruction shape matches
// apart from unresolved REL32 rva002E36B7; DIR32s remain unproven.
// Native secondary interface has one pure virtual at C1C780 and trivial destruction;
// native derived entry C04C78 points to this-38 thunk002E37C3 ->002E37B1.
// Primary vtable C04C7C has13 entries; this provisional base declaration is incomplete.
// Do not ledger this constructor until all emitted tables and EH dependencies are verified.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
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


#include <ascii_string.h>
class Rva002E3EB8Base { public: virtual void slot()=0; };
class PolygonTrigger;
class PolygonLink { public: PolygonLink():next(0){} PolygonTrigger* next; };
class PolygonTrigger:public PolygonLink,public Rva00330C50,public Rva002E3EB8Base {
public:
 PolygonTrigger(int);
 virtual ~PolygonTrigger();
 virtual void slot();
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6();
 void rva002E36B7(int);
private:
 AsciiString name;
 int id;
 void* unknown48;
 AsciiString layer;
 char unknown50[12];
 static int s_currentID;
};
typedef char PolygonExtent[sizeof(PolygonTrigger)==100?1:-1];
PolygonTrigger::PolygonTrigger(int n):id(s_currentID++) { rva002E36B7(n); }
