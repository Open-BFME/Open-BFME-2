// cl: /O1 /DNDEBUG /MD /EHsc
// Retail 0x002BF6A7, 16B: pass the argument's +0x44 sub-object to member
// 0x002BF61B on the same object. The existing pin types the argument int.

class Rva002BF6A7
{
public:
	void rva002BF61B(int sub);
	void rva002BF687(int owner);
	void rva002BF697(int owner);
	void rva002BF6A7(int owner);
};

// Retail 0x005F83A9, 16B: pass the 8-byte element count of the range at
// +0x20/+0x24 to member 0x00578513 on the same object.
struct Rva005F83A9Element
{
	int m_a;
	int m_b;
};

// LINK: 0x00578513 is rowed as Rva00578513::rva00578513; bind it through a view of this object.
class Rva00578513
{
public:
	void rva00578513(int count);
};

class Rva005F83A9
{
public:
	void rva005F83A9();

private:
	char m_pad00[0x20];
	Rva005F83A9Element *m_begin;
	Rva005F83A9Element *m_end;
};

void Rva005F83A9::rva005F83A9()
{
	((Rva00578513 *)this)->rva00578513(m_end - m_begin);
}

// Native2BF652..2BF687 RET4: output pair on the stack; value+12C region ID.
// WB D27970 supports region-center fetch and then owned55B ground placement.
// Both physical results are unused here; no pointer-result fact is established.
#include "RegionCenterPointDispatchView.h"
class LivingWorldLogic;extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva002BF652LogicView{char pad[0xB0];Rva0020F27EHost*regions;};
struct RegionView{char pad[0x12C];int id;};
class Rva002BF652{public:void rva002BF652(void*);};

// Native5CD284..5CD2A3 RET0, WB15C5010: empty folded hook, owned
// 8B child-forwarder then region placement(value20->18, receiver10).
// Existing neutral noop owner names only the proven shared empty RET.
class PathfindLayer {public:void rva000B3FD0();};
class Rva005CCB5B {public:void rva005CCB5B();};
struct Rva005CD284Value {char pad[0x18];void*value;};
class Rva005CD284 {public:void rva005CD284();private:char pad[0x10];Rva002BF652*placer;char pad14[0xC];Rva005CD284Value*holder;};
void Rva005CD284::rva005CD284(){
 ((PathfindLayer*)this)->rva000B3FD0();
 ((Rva005CCB5B*)this)->rva005CCB5B();
 placer->rva002BF652(holder->value);
}
