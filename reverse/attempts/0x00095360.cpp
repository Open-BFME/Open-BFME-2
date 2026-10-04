// ??1Rva00095360View@@UAE@XZ
// partial score=0.99 date=2026-10-04
// cl: /O1 /MD /EHsc /DNDEBUG
// BFME1 BfmeDtor006e2480.cpp at 1281192: reference-counted global cleanup.
// Native 95360/83 has rowed deleting caller 982DD/28 and base 9519B/113;
// ctor 9525E independently installs the same BC8208 table.
// Original class/global/member names are unproven. These are prefix views,
// never used for sizeof or creation. The complete derived table has 24 slots;
// slot declarations are address placeholders, not recovered prototypes.
// BLOCKED: native slots94C58,94C70,94CA9,94CEA,94D44,94E2C,982F9,
// 1B5384 and2150BE have no matched body/provider. No 1-slot substitute.
// Global DE4880's native initial value is loader-zero BSS; proper provider also needed.
// Native table slot RVAs, in order (address facts, prototypes unresolved):
// 0x000982DD, 0x000B3FD0, 0x001B5384, 0x000B3FD0, 0x005CB9FF, 0x0047A699
// 0x000D43D0, 0x0047A69C, 0x000B3FD0, 0x002150BE, 0x000982F9, 0x005CB9FF
// 0x000B3FD0, 0x0047A69C, 0x00214F14, 0x00094DA8, 0x00094C70, 0x00094CA9
// 0x00095343, 0x0009533C, 0x00094CEA, 0x00094D44, 0x00094E2C, 0x00094C58
struct Rva00095360Ref {
 virtual void releaseAtSlot0();
 int references04;
 void decrement() { if (--references04==0) releaseAtSlot0(); }
};
extern Rva00095360Ref *g_Rva009E4880;
class Rva009519B {
public:
 virtual ~Rva009519B();
};
class Rva00095360View: public Rva009519B {
public:
 virtual ~Rva00095360View();
 virtual void unresolvedAddressSlot01();
 virtual void unresolvedAddressSlot02();
 virtual void unresolvedAddressSlot03();
 virtual void unresolvedAddressSlot04();
 virtual void unresolvedAddressSlot05();
 virtual void unresolvedAddressSlot06();
 virtual void unresolvedAddressSlot07();
 virtual void unresolvedAddressSlot08();
 virtual void unresolvedAddressSlot09();
 virtual void unresolvedAddressSlot10();
 virtual void unresolvedAddressSlot11();
 virtual void unresolvedAddressSlot12();
 virtual void unresolvedAddressSlot13();
 virtual void unresolvedAddressSlot14();
 virtual void unresolvedAddressSlot15();
 virtual void unresolvedAddressSlot16();
 virtual void unresolvedAddressSlot17();
 virtual void unresolvedAddressSlot18();
 virtual void unresolvedAddressSlot19();
 virtual void unresolvedAddressSlot20();
 virtual void unresolvedAddressSlot21();
 virtual void unresolvedAddressSlot22();
 virtual void unresolvedAddressSlot23();
};
Rva00095360View::~Rva00095360View() {
 if (g_Rva009E4880) {
  g_Rva009E4880->decrement();
  g_Rva009E4880=0;
 }
}
