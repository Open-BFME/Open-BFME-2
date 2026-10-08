// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva005CF27A@@QAE@PAVRva005CF7BF@@HHHHHHHH@Z, retail 0x005CF27A..
// 0x005CF363 (233 bytes, EH, RET 36): the 0x20-byte implementation the
// rowed Rva005CF7BF constructor allocates (the spelling its caller pinned).
// Its vtable 0x00C75244 carries the rowed
// StrategicInGameUI::PlanningPhaseRegionSelection::Impl::OnRegionChangingOwnership
// in slot 1, so this is that Impl's constructor; the name stays the pinned
// one its caller uses. The owner and five arguments are kept at
// +0x04..+0x18 and the +0x1C holder is cleared; the impl joins the +0x18
// object's listener list at +0x04 (rowed append 0x005A0B4C). When the +0x10
// field yields both a value and a listener (rowed getters 0x0042D6B4 and
// 0x0042D6FD), the listener's slot 3 receives a counted record built from a
// six-word payload (rowed 0x005CE912 and factory 0x005CECC1). The +0x14
// object is then told the +0x18 value (rowed 0x005CB84A), as is
// TheLivingWorldManager's +0x268 object when present (rowed 0x003EE91A).

#include "../../../Common/BattlePromptCallbackPayloadView.h"

struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

class Rva0042D6B4PtrChaseField
{
public:
	int get() const;
};

class Rva0042D6FDPtrChaseField
{
public:
	int get() const;
};

class Rva005CE912
{
public:
	Rva005CE912(int a1, int a2, int a3, int a4, int a5, int a6);
private:
	int m_words[6];
};

class Rva005CEB57
{
public:
	struct Payload { int v[6]; };
	Rva005CEB57(const Payload *src) throw();
	virtual ~Rva005CEB57();
	int m_ref;
	Payload m_data;
};

RvaCloneResult<Rva005CEB57> Rva005CECC1Create(const Rva005CEB57::Payload *src);

class Rva005CB84A
{
public:
	void rva005CB84A(int value);
};

class Rva003EE91A
{
public:
	void rva003EE91A(int value);
};

class LivingWorldManager
{
public:
	unsigned char m_pad000[0x268];
	Rva003EE91A *m_268;						// +0x268
};

extern LivingWorldManager *TheLivingWorldManager;

class Rva005CF27AListener
{
public:
	virtual void l0();
	virtual void l1();
	virtual void l2();
	virtual void l3(const TreeHintRef00217D4C &record);
};

// The +0x1C holder needs unwinding (EH state 1); its destructor running the
// rowed Rva000AD6F4::clear is inferred from the sibling holders, as only the
// unwind funclet calls it.
class Rva000AD6F4
{
public:
	void clear();
};

class Rva005CF27AHolder
{
public:
	Rva005CF27AHolder() : m_ptr(0) {}
	~Rva005CF27AHolder() { reinterpret_cast<Rva000AD6F4 *>(this)->clear(); }
private:
	void *m_ptr;
};

// The listener interface the impl registers as (four slots, no destructor
// slot).
class Rva005CF27ABase
{
public:
	~Rva005CF27ABase() {}
	virtual void b0();
	virtual void b1();
	virtual void b2();
	virtual void b3();
};

class Rva005CF7BF;

class Rva005CF27A : public Rva005CF27ABase
{
public:
	Rva005CF27A(Rva005CF7BF *owner, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9);
	virtual void b0();
	virtual void b1();

private:
	Rva005CF7BF *m_owner04;					// +0x04
	int m_08;								// +0x08
	int m_0C;								// +0x0C
	int m_field10;							// +0x10
	Rva005CB84A *m_14;						// +0x14
	int m_18;								// +0x18
	Rva005CF27AHolder m_holder1C;			// +0x1C
};

Rva005CF27A::Rva005CF27A(Rva005CF7BF *owner, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
	: m_owner04(owner), m_08(a2), m_0C(a3), m_field10(a4), m_14((Rva005CB84A *)a5), m_18(a6)
{
	reinterpret_cast<Rva005A0B4CList *>(m_18 + 4)->append((Rva002BA8F1Listener *)this);
	if (int value = ((const Rva0042D6B4PtrChaseField *)m_field10)->get())
	{
		if (Rva005CF27AListener *listener = (Rva005CF27AListener *)((const Rva0042D6FDPtrChaseField *)m_field10)->get())
		{
			Rva005CE912 payload((int)this, a7, m_18, a8, a9, value);
			listener->l3(Rva005CECC1Create((const Rva005CEB57::Payload *)&payload));
		}
	}
	m_14->rva005CB84A(m_18);
	if (TheLivingWorldManager->m_268)
		TheLivingWorldManager->m_268->rva003EE91A(m_18);
}
