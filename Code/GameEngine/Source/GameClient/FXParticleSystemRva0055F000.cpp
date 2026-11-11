// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /ICode/Libraries/Include/Lib
// ?rva0055F000@Rva0055F218@@QAEXXZ @0x0055F000 (407B). Particle-system spawn step
// (see the bank notes in the body). The equal-arm receiver on the m_b15 gate
// keeps retail's scheduling of the flag load (W7-S2 r4 sweepthis).
// ??0Rva0055F218@@QAE@IAAUSrc0055F218@@@Z, retail 0x0055F218, 120 bytes.
// UInt-plus-template ctor: forwards the dword to the rowed base
// ??0Rva0055EFE1@@QAE@I@Z at 0x0055EFE1, subobject defaults at +0xC/+0x10/+0x14/+0x15,
// final vtables +0 0x00C1D1D4 plus +8 0x00C1C780 plus +0xC 0x00C1D1E4,
// float via rowed GameClientRandomVariable::getValue 0x002341A1, flag bytes
// from +0x3C/+0x3D. Same shape as sibling 0x005646BC. Caller at 0x003ACF96.
//
// that vtable 0x00C1D1D4 (after ??_G 0x003AE270; also slot 1 of 0x00C1CE20)
// - the particle physics step. Holding a copy of the particle's system handle
// (+0x3C, BfmeParticleSystemHandle idiom of ParticleSystemManagerFindByID.cpp),
// a +0x15 particle hands its position (+0x1C) to the system (0x001F385A);
// otherwise the force (+4) takes the system's gravity (0x001F510D, the
// "Gravity" binder callback) as z and is added to the velocity (+0x10), which
// is damped by the +0x10 float, then the system's drift (0x001F512F, the
// "DriftVelocity" callback) plus velocity moves the position; with +0x14 a
// hit reported by 0x001F3828 pushes the position along its 3-float result by
// four times the velocity's GetLengthEstimate (literal 4.0f at 0x00BC2918).
// The force is cleared after a non-+0x15 step. Address-derived names; field
// meanings are structural inferences from the arithmetic and binder names.

#include "../../Include/GameClient/GameClientRandomVariable.h"

#include "Code/Libraries/Include/Lib/Coord3D.h"
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}

class Rva0055EFE1
{
public:
	Rva0055EFE1(unsigned int a);
	~Rva0055EFE1();
protected:
	void *m_v0;
	unsigned int m_arg4;
	void *m_v8;
};

#include "RGBColor.h"

// Rowed ParticleSystem methods under address-derived classes.
#include "../../Include/GameClient/Rva001F385A.h"
#include "../../Include/Common/Rva001F510D.h"
class Rva001F512FSlot { public: const RGBColor *get() const; };
class Rva001F3828 { public: bool rva001F3828(int a, int b); };

class ParticleSystem
{
public:
	void rva001F385A(Coord3D *position) { ((Rva001F385A *)this)->rva001F385A(position); }
	float gravity() { return ((Rva001F510D *)this)->rva001F510D(); }
	const RGBColor *drift() const { return ((const Rva001F512FSlot *)this)->get(); }
	bool rva001F3828(Coord3D *position, Coord3D *out) { return ((Rva001F3828 *)this)->rva001F3828((int)position, (int)out); }
};

ParticleSystem *Make001FCBD7();

#include "../../Include/Common/RvaSmartPtr12.h"

class BfmeParticleSystemHandle
{
public:
	__forceinline BfmeParticleSystemHandle(const BfmeParticleSystemHandle &that)
	{
		((RvaSmartPtr12 *)this)->RvaSmartPtr12::RvaSmartPtr12(*(const RvaSmartPtr12 *)&that);
	}
	~BfmeParticleSystemHandle() throw()
	{
		if (m_system)
			((RvaSmartPtr12 *)this)->rva0004CBC0();
	}
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make001FCBD7();
	}

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

struct Rva0055F000Particle
{
	unsigned char m_pad00[4];
	Coord3D m_force;			// +0x04
	Coord3D m_velocity;			// +0x10
	Coord3D m_position;			// +0x1C
	unsigned char m_pad28[0x3C - 0x28];
	BfmeParticleSystemHandle m_system;	// +0x3C
};

extern const void *const g_00C1D1D4[];
extern const void *const g_00C1D1E4[];
extern "C" const void *const __identifier("??_7Rva003ADE98@@6B@")[];

struct Src0055F218
{
	char m_pad0[0x30];
	GameClientRandomVariable m_var30;
	unsigned char m_3C;
	unsigned char m_3D;
};

struct Rva0055F218Sub
{
	Rva0055F218Sub() : m_v((void *)__identifier("??_7Rva003ADE98@@6B@")), m_f(0.0f), m_b14(0), m_b15(0) {}
	~Rva0055F218Sub();
	void *m_v;
	float m_f;
	unsigned char m_b14;
	unsigned char m_b15;
};

class Rva0055F218 : public Rva0055EFE1, public Rva0055F218Sub
{
public:
	Rva0055F218(unsigned int a, struct Src0055F218 &src);
	~Rva0055F218();
	void rva0055F000();
};

// Rva0055F218::Rva0055F218 is rowed in its home unit; this copy was a duplicate definition.

void Rva0055F218::rva0055F000()
{
	BfmeParticleSystemHandle system(((Rva0055F000Particle *)m_arg4)->m_system);
	if ((this ? this : this)->m_b15)
	{
		system->rva001F385A(&((Rva0055F000Particle *)m_arg4)->m_position);
		return;
	}
	Coord3D *position = &((Rva0055F000Particle *)m_arg4)->m_position;
	Coord3D *velocity = &((Rva0055F000Particle *)m_arg4)->m_velocity;
	Coord3D *force = &((Rva0055F000Particle *)m_arg4)->m_force;
	force->z = system->gravity();
	__vref(velocity->x) += force->x;
	velocity->y += force->y;
	velocity->z += force->z;
	velocity->x *= __vref(m_f);
	velocity->y *= m_f;
	velocity->z *= m_f;
	const RGBColor *drift = system->drift();
	if (drift)
	{
		position->x += velocity->x + drift->red;
		position->y += velocity->y + drift->green;
		position->z += velocity->z + drift->blue;
		if (m_b14)
		{
			Coord3D normal;
			if (system->rva001F3828(position, &normal))
			{
				float scale = velocity->GetLengthEstimate() * 4.0f;
				position->x += normal.x * scale;
				position->y += normal.y * scale;
				position->z += normal.z * scale;
			}
		}
	}
	force->x = 0.0f;
	force->y = 0.0f;
	force->z = 0.0f;
}

// The vtable-tag externs above are the data ledger's accepted g_00C1D1xx spellings;
// binding g_00C1D1F4 to its class vtable name is left to the link pass (no /alternatename).
