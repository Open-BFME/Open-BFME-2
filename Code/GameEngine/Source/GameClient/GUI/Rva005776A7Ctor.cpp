// cl: /O1 /MD /EHsc /DNDEBUG
// ??0Rva005770F7@@QAE@PAVRva005772BF@@H@Z, retail 0x005776A7..0x00577747
// (160 bytes, EH): the constructor of the strategic UI phase object whose
// body ends in the rowed StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl::
// CreateChecklistItems (pinned name; constructed by ??0Rva005772BF). Over an
// interface base (table 0x00C6E430; unwind copy 0x00429191) and the rowed
// Rva005CD1A9 base at +4 it stores its owner and int argument, clears the
// +0x14 owner pointer (unwind 0x0057702E), builds the +0x18 record from the
// owner's +4 object (rowed getters 0x00328A83 and 0x00574A98) and its own
// +4 base, and the +0x28 member (rowed 0x005CD651) from that object again,
// then clears +0x38 and creates the checklist. Own tables 0x00C6E8F8 and
// 0x00C6E8EC (+4). Identities are not established.
// The 0x429191 cleanup is a shared teardown carrier. Its final table is
// 0xBDBA74, as independently verified in Rva004296EESlot.cpp. The phase
// interface has its own two-slot table at 0xC6E430; do not give both tables
// the carrier's COFF name. The implicit interface destructor keeps the
// existing carrier cleanup call and the complete retail exception data.
class Gen_uwm_00429191
{
public:
	virtual void s0() = 0;
	~Gen_uwm_00429191() {}
};

class Rva005776A7Interface : public Gen_uwm_00429191
{
public:
	virtual void r0() = 0;
};

class Rva005CD1A9
{
public:
	Rva005CD1A9();
	virtual ~Rva005CD1A9();
private:
	int m_04;
};

#include "../../../Include/Common/Rva00328A83PtrChaseField.h"

class Rva00574A98
{
public:
	void *rva00574A98();
};

struct Rva005772BFTarget;

class Rva005772BF
{
public:
	int m_00;
	Rva005772BFTarget *m_04;			// +0x04
};

class Rva0057702E
{
public:
	Rva0057702E() : m_ptr(0) {}
	~Rva0057702E();
private:
	void *m_ptr;
};

class Rva005CD7BD
{
public:
	Rva005CD7BD(void *source, int value, int owner);
	~Rva005CD7BD();
private:
	unsigned char m_data[0x10];
};

class Rva005CD651
{
public:
	Rva005CD651(int value);
	virtual ~Rva005CD651();
private:
	unsigned char m_pad04[0x10 - 4];
};

// The +0x18 record built from the owner's +4 object (read once).
class Wrap2000576C4B : public Rva005CD7BD
{
public:
	__forceinline Wrap2000576C4B(Rva005772BFTarget *source, Rva005CD1A9 *owner)
		: Rva005CD7BD(((Rva00574A98 *)source)->rva00574A98(), ((const Rva00328A83PtrChaseField *)source)->get(), (int)owner) {}
	~Wrap2000576C4B();
};

class StrategicInGameUI
{
public:
	class PlanRetreatsPhaseBehavior
	{
	public:
		class Impl
		{
		public:
			void CreateChecklistItems();
		};
	};
};

class Rva005770F7 : public Rva005776A7Interface, public Rva005CD1A9
{
public:
	Rva005770F7(Rva005772BF *owner, int value);
	virtual ~Rva005770F7();
private:
	Rva005772BF *m_owner;				// +0x0C
	int m_value;					// +0x10
	Rva0057702E m_14;				// +0x14
	Wrap2000576C4B m_18;				// +0x18
	Rva005CD651 m_28;				// +0x28
	bool m_38;					// +0x38
};

Rva005770F7::Rva005770F7(Rva005772BF *owner, int value)
	: m_owner(owner), m_value(value),
	  m_18(m_owner->m_04, this),
	  m_28(((const Rva00328A83PtrChaseField *)m_owner->m_04)->get())
{
	m_38 = false;
	((StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl *)this)->CreateChecklistItems();
}
