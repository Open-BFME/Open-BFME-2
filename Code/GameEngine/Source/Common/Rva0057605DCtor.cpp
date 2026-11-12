// cl: /EHsc /MD
// ??0Rva0057605D@@QAE@HPAUParent0057605D@@@Z @0x0057605D 84B.
// Constructor of a listener-registering object: a first polymorphic base
// holding the int argument at +4, the Rva0057605DSecond interface as a
// second base at +8, and the parent pointer at +0xC; the body appends the
// listener base to the parent's list through the rowed append 0x005A0B4C.
// Evidence from retail: the unwind map destroys the first base through the
// 7-byte vptr setter 0x0057571C (state 0) and the +8 subobject through
// 0x002B2294 (state 1); the +8 vptr is written first with the listener's own
// vtable and then, together with the +0 vptr, with this class's second
// vtable, which is how cl builds a second base, not a member. Replaces the
// banked 0.9 attempt, which modelled the +8 object as volatile integer
// vtable stores behind two empty bases.
// The native C77F44 secondary base is the same view used by the rowed
// destructor in Rva0057605DDtor.cpp. It is distinct from the two-slot
// Rva002BA8F1Listener interface whose native table is C3702C.
struct Rva002BA8F1Listener; // Existing list-provider argument spelling.
struct Parent0057605D;
#include "../../Include/Common/Rva0057605DSecond.h"
// Preserve the existing inlined native constructor path.
__forceinline Rva0057605DSecond::Rva0057605DSecond() {}
#include "../../Include/Common/Rva005A0B4CList.h"
struct Parent0057605D
{
	char pad[8];
	Rva005A0B4CList list;
};
class Rva0057605DBase
{
public:
	Rva0057605DBase(int a) : m_a4(a) {}
	virtual ~Rva0057605DBase() {}
	// Retail table 0x00C6E60C holds __purecall at slot 1; the derived table
	// 0x00C6E6A0 holds 0x00575DE6 there.
	virtual void rva00575DE6() = 0;
private:
	int m_a4;
};
class Rva0057605D : public Rva0057605DBase, public Rva0057605DSecond
{
public:
	Rva0057605D(int a, Parent0057605D *b);
	virtual ~Rva0057605D();
private:
	Parent0057605D *m_parentC;
};
Rva0057605D::Rva0057605D(int a, Parent0057605D *b)
	: Rva0057605DBase(a)
{
	m_parentC = b;
	b->list.append(reinterpret_cast<Rva002BA8F1Listener *>(static_cast<Rva0057605DSecond *>(this)));
}
