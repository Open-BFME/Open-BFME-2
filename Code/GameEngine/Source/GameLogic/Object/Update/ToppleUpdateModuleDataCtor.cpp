// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0ToppleUpdateModuleData@@QAE@XZ, retail 0x004A8173, 125 bytes.
//
// The module-data half of ToppleUpdate: vtable immediate 0x00C538A0 modelled
// as an explicit first member (DemoTrapUpdateModuleDataCtor precedent, so no
// vtable is emitted and no dtor row is owed), an uninitialised word at +0x04
// retail never stores, the ToppleFX/BounceFX slots at +0x08/+0x0C, the
// StumpName string at +0x10, the four percent/speed reals at
// +0x14/+0x18/+0x1C/+0x20 and the five kill/reorient flags at
// +0x24/+0x25/+0x26/+0x27/+0x28. Field identity is retail's own INI table at
// RVA 0x853980 (VA 0xC53980, landed buildFieldParse row) joined to the Zero
// Hour ToppleUpdate donor (ToppleFX, BounceFX, StumpName,
// KillWhenStartToppling/KillWhenFinishedToppling, KillStumpWhenToppled,
// ToppleLeftOrRightOnly, ReorientToppledRubble, InitialVelocityPercent,
// InitialAccelPercent, BounceVelocityPercent). BFME2 deltas: the new
// MinimumToppleSpeed real at +0x20 defaulting to 0.5f, and
// BounceVelocityPercent defaulting to 0.2f (retail loads the same literal as
// InitialVelocityPercent). The string clears through the rowed 0x36410 clear
// fold (ImageCtor precedent: inline default ctor plus declared-only clear
// and dtor). The empty UpdateModuleData base (inline-empty ctor plus
// declared-only dtor) is load-bearing for the EH state machine: it advances
// the state to 0 with no emitted code, so the member init is bracketed by
// state 0/1 exactly as retail; a standalone class emits only state 0.
// Body order follows the donor.

typedef int Int;

#define NULL 0

#include "ascii_string.h"

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class ToppleUpdateModuleData : public UpdateModuleData
{
public:
	ToppleUpdateModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	void *m_toppleFX;				// +0x08
	void *m_bounceFX;				// +0x0C
	AsciiString m_stumpName;			// +0x10
	float m_initialVelocityPercent;		// +0x14
	float m_initialAccelPercent;		// +0x18
	float m_bounceVelocityPercent;		// +0x1C
	float m_minimumToppleSpeed;		// +0x20
	bool m_killWhenToppled;			// +0x24
	bool m_killWhenStartToppled;		// +0x25
	bool m_killStumpWhenToppled;		// +0x26
	bool m_toppleLeftOrRightOnly;		// +0x27
	bool m_reorientToppledRubble;		// +0x28
};

ToppleUpdateModuleData::ToppleUpdateModuleData()
	: m_vtable( reinterpret_cast<const void *>(0x00C538A0) )
	, m_stumpName()
{
	m_toppleFX = NULL;
	m_bounceFX = NULL;
	m_stumpName.clear();
	m_killWhenToppled = true;
	m_killWhenStartToppled = false;
	m_killStumpWhenToppled = false;
	m_toppleLeftOrRightOnly = false;
	m_reorientToppledRubble = false;
	m_initialVelocityPercent = 0.2f;
	m_initialAccelPercent = 0.01f;
	m_bounceVelocityPercent = 0.2f;
	m_minimumToppleSpeed = 0.5f;
}
