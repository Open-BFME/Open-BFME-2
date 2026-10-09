// ?rva003FA878@Rva003FA835@@QAEXXZ
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// NEAR (328 of 359 bytes; the same blocks and order, short of two SSE->x87 copy pairs)
// ?rva003FA878@Rva003FA835@@QAEXXZ retail 0x003FA878..0x003FA9DF (359 bytes).
// It is called from 0x002BFFBF (the 0x002BFF5A lookup family). It is the
// per-frame tick of the Rva003FA835 glow helper (view as in Rva003FA781.cpp).
// - With no render object at the target's +0x08 it returns.
// - When m_20 is set (rva003FA7D3 mode): if TheLivingWorldLogic->rva002B59FF()
//   then elapsed += 0.15 and value = base + |cos(elapsed)| * amplitude (the
//   template's +0x14 / +0x18 floats through the rowed OVERRIDE getter);
//   otherwise elapsed = 0 and value = base.
// - Otherwise, when enabled: elapsed = min(PI/2 / elapsed + 0.2) with the
//   same pulse.
// - Otherwise elapsed = 0 and value = base.
// - Every path ends in the rowed rva003FA705(m_target / value).
// cos and fabs go through the CRT import thunks (/D_CRTIMP=).
// Remaining wall: in both pulse paths retail reloads the elapsed copy into
// xmm0 and stores it back to the same slot (movss xmm0,[x] / movss [x],xmm0)
// before `fld [x]`. cl loads it straight with fld. That costs 20 bytes plus
// the near/short jump growth. Tried: math.h cos/cosf/fabsf forms, WWMath-style
// Cos/Fabs inline wrappers (plain and forceinline), a +0.0f / cast copy, the
// register keyword, function-scope locals and a single-expression call.
#include <math.h>
#include <algorithm>

typedef float Real;

class LocomotorTemplate;

template<class T> class OVERRIDE
{
public:
	const T *operator->() const;
private:
	const T *head;
};

struct Rva003FA878Template
{
	char pad[0x14];
	Real value;										// +0x14
	Real amplitude;									// +0x18
};

struct Rva003FA878Target
{
	char pad[0x08];
	void *m_renderObject;							// +0x08
};

class Rva002B59FF
{
public:
	bool rva002B59FF();
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva003FA835
{
public:
	void rva003FA878();
	void rva003FA705(void *target, Real value);
private:
	const Rva003FA878Template *getTemplate() const { return (const Rva003FA878Template *)m_template.operator->(); }
	char m_pad[8];
	OVERRIDE<LocomotorTemplate> m_template;			// +0x08
	unsigned m_unknown0C;
	void *m_target;									// +0x10
	bool m_enabled;									// +0x14
	char m_pad15[3];
	Real m_elapsed;									// +0x18
	Real m_unknown1C;
	Real m_20;										// +0x20
};

void Rva003FA835::rva003FA878()
{
	void *target = m_target;
	if (((Rva003FA878Target *)target)->m_renderObject == 0)
		return;

	if (m_20 != 0.0f)
	{
		if (((Rva002B59FF *)TheLivingWorldLogic)->rva002B59FF())
		{
			Real elapsed = m_elapsed + 0.15f;
			m_elapsed = elapsed;
			Real base = getTemplate()->value;
			Real amplitude = getTemplate()->amplitude;
			elapsed = *reinterpret_cast<volatile Real *>(&elapsed);
		Real value = base + fabs(cos(elapsed)) * amplitude;
			rva003FA705(m_target, value);
		}
		else
		{
			m_elapsed = 0.0f;
			rva003FA705(m_target, getTemplate()->value);
		}
	}
	else if (m_enabled)
	{
		m_elapsed += 0.2f;
		Real base, amplitude, elapsed;
		elapsed = _STL::min(1.5707964f, m_elapsed);
		m_elapsed = elapsed;
		base = getTemplate()->value;
		amplitude = getTemplate()->amplitude;
		elapsed = *reinterpret_cast<volatile Real *>(&elapsed);
		Real value = base + fabs(cos(elapsed)) * amplitude;
		rva003FA705(m_target, value);
	}
	else
	{
		m_elapsed = 0.0f;
		rva003FA705(target, getTemplate()->value);
	}
}
