// ??1Rva001F4C67@@UAE@XZ
// partial score=0.94 date=2026-09-30
// cl: /O1 /MD /EHsc
// ??1Rva001F4C67@@UAE@XZ @0x001F4C67 (159B)
// Virtual dtor unlinks node via rowed unlink then destroys handles.
// Sets own vtable then base vtable. Calls slot6 destroy manager.
// Ret 0. Evidence chain lane calls just-landed unlink plus destroy rows.
#include <stddef.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class ParticleSystem;
ParticleSystem *Make001FCBD7();
struct Rva001F45DFInner { char m_pad[0x7c]; int m_value; };
class Rva001F45DFSlot { public: int get() const; char m_lead[0x3c]; Rva001F45DFInner *m_ptr; };
struct Node001F4882;
class Rva001F4882 { public: void rva001F4882(Node001F4882 *n); };
struct Node001F4882 : public Rva001F45DFSlot { char m_p[0x6c-0x40]; Node001F4882 *m_prev; Node001F4882 *m_next; char m_g; unsigned char m_f; };
struct BfmeParticleSystemHandle { ~BfmeParticleSystemHandle() throw(); void *m_system; void *m_prev; void *m_next; };
class ParticleSystemManager;
extern ParticleSystemManager *TheParticleSystemManager;
struct Slot6Obj { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void slot6(void *arg); };
class ParticleSystem { public: void destroy(); char m_pad[0xa4]; Slot6Obj *m_slot2; char m_p2[0x19c-0xa8]; int m_19c; };
class BfmeParticleSystemPtr
{
public:
	operator ParticleSystem *(void) const { return m_target; }
	__forceinline ParticleSystem *operator->(void) const
	{
		ParticleSystem *target = m_target;
		if (!target)
			target = Make001FCBD7();
		return target;
	}
private:
	ParticleSystem *m_target;
};
struct RawHandle { BfmeParticleSystemPtr m_system; void *m_prev; void *m_next; };
struct Wrap3c {
	~Wrap3c() { if (m_h.m_system) ((BfmeParticleSystemHandle *)&m_h)->~BfmeParticleSystemHandle(); }
	RawHandle m_h;
};
struct Wrap78 {
	~Wrap78() { if (m_h.m_system) ((BfmeParticleSystemHandle *)&m_h)->~BfmeParticleSystemHandle(); }
	RawHandle m_h;
};
struct Base001F4C67 { virtual void bv0() = 0; virtual void bv1() = 0; virtual ~Base001F4C67(); };
class Rva001F4C67 : public Base001F4C67
{
public:
	virtual ~Rva001F4C67();
private:
	char m_04[0x38];
	Wrap3c m_w3c;
	char m_48[0x24];
	Node001F4882 *m_prev6c;
	Node001F4882 *m_next70;
	char m_g74;
	unsigned char m_f75;
	char m_76[2];
	Wrap78 m_w78;
};
Rva001F4C67::~Rva001F4C67()
{
	m_w3c.m_h.m_system->m_slot2->slot6(this);
	if (m_w78.m_h.m_system) {
		_ReadWriteBarrier();
		m_w78.m_h.m_system->m_19c = 0;
		m_w78.m_h.m_system->destroy();
	}
	((Rva001F4882 *)TheParticleSystemManager)->rva001F4882((Node001F4882 *)this);
}
// ?Base001F4C67::~Base001F4C67 present-unmatched
Base001F4C67::~Base001F4C67() {}
