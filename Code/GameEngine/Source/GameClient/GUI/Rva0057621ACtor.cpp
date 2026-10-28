// cl: /O1 /MD /EHsc /DNDEBUG
// ??0Rva0057621A@@QAE@PAVRva00575D45@@H@Z, retail 0x0057621A..0x00576323
// (265 bytes, EH): the 0x50-byte object Rva00575D45's constructor
// (0x005763ED) allocates with (this, int). The planning-phase sibling of
// Rva005776A7Ctor.cpp (PlanRetreatsPhaseBehavior), with the same tail
// members. Bases, in order (each table read from retail, each unwind target
// from the EH funclets at 0x0079B398..0x0079B3FE):
//   +0x00 the phase interface (table 0x00C6E430; unwind carrier 0x00429191),
//   +0x04 the seven-slot __purecall interface (0x00C6EE28; unwind 0x0057A243),
//   +0x08 Rva005D25F2Base (0x00C078DC; unwind 0x005D23FE),
//   +0x0C the rowed Rva005CD1A9 base (ctor 0x005CD167),
//   +0x14 the listener base (0x00C6E5C4; unwind 0x005753E2); the body appends
//         it to the +4 list of the object TheLivingWorldLogic's 0x002B256E
//         returns when 0x002B254F is set.
// Own tables 0x00C6E720/+4 0x00C6E700/+8 0x00C6E6EC/+C 0x00C6E6E4/+14 0x00C6E6B8.
// Members: +0x18 the owner, +0x1C the int argument, +0x20 TheLivingWorldLogic's 0x002B2B66,
// +0x24 the rowed Rva005CC61E, +0x28/+0x2C two owning pointers (unwind
// 0x000AD6F4), +0x30 the record built from the owner's +4 object (rowed
// getters 0x00574A98 and 0x00328A83) and the +0x0C base, +0x40 the rowed
// Rva005CD651 from that object again. Identities are not established.
class Gen_uwm_00429191
{
public:
	virtual void s0();
	~Gen_uwm_00429191() {}
};

class Rva005776A7Interface : public Gen_uwm_00429191
{
public:
	virtual void r0();
};

class Rva0057A243Interface
{
public:
	virtual void vslot0() = 0;
	~Rva0057A243Interface();
};

class Rva005D25F2Base
{
public:
	virtual int rva005D24E5(int) = 0;
	~Rva005D25F2Base();
};

class Rva005CD1A9
{
public:
	Rva005CD1A9();
	virtual ~Rva005CD1A9();
private:
	int m_04;
};

class Rva00575D45;

class Rva005753E2Listener
{
public:
	virtual void vslot0();
	~Rva005753E2Listener();
};

struct Rva005772BFTarget;

class Rva00575D45
{
public:
	virtual ~Rva00575D45();
	Rva005772BFTarget *m_04;			// +0x04
};

class Rva00328A83PtrChaseField
{
public:
	int get() const;
};

class Rva00574A98
{
public:
	void *rva00574A98();
};

class Rva005CC61E
{
public:
	Rva005CC61E();
	~Rva005CC61E();
private:
	void *m_ptr;
};

class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4();
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

// The +0x30 record built from the owner's +4 object (read once).
class Wrap2000576C4B : public Rva005CD7BD
{
public:
	__forceinline Wrap2000576C4B(Rva005772BFTarget *source, Rva005CD1A9 *owner)
		: Rva005CD7BD(((Rva00574A98 *)source)->rva00574A98(), ((const Rva00328A83PtrChaseField *)source)->get(), (int)owner) {}
	~Wrap2000576C4B();
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002B2B66
{
public:
	int rva002B2B66();
};

class Rva002B254F
{
public:
	int rva002B254F();
};

class Rva002B256E
{
public:
	void *rva002B256E();
};

struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

class Rva0057621A : public Rva005776A7Interface, public Rva0057A243Interface,
	public Rva005D25F2Base, public Rva005CD1A9, public Rva005753E2Listener
{
public:
	Rva0057621A(Rva00575D45 *owner, int value);
	virtual ~Rva0057621A();
	virtual void r0();
	virtual void vslot0();
	virtual int rva005D24E5(int);
private:
	Rva00575D45 *m_owner;				// +0x18
	int m_value;					// +0x1C
	int m_20;					// +0x20
	Rva005CC61E m_24;				// +0x24
	Rva000AD6F4 m_28;				// +0x28
	Rva000AD6F4 m_2C;				// +0x2C
	Wrap2000576C4B m_phaseEnder;				// +0x30
	Rva005CD651 m_statusDisplayer;				// +0x40
};

Rva0057621A::Rva0057621A(Rva00575D45 *owner, int value)
	: m_owner(owner), m_value(value),
	  m_20(((Rva002B2B66 *)TheLivingWorldLogic)->rva002B2B66()),
	  m_phaseEnder(m_owner->m_04, this),
	  m_statusDisplayer(((const Rva00328A83PtrChaseField *)m_owner->m_04)->get())
{
	if ((unsigned char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F())
		((Rva005A0B4CList *)((char *)((Rva002B256E *)TheLivingWorldLogic)->rva002B256E() + 4))
			->append((Rva002BA8F1Listener *)static_cast<Rva005753E2Listener *>(this));
}
