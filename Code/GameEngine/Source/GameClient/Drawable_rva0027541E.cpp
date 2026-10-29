// cl: /DNDEBUG /MD /EHs-c- /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Link view first: Vector3::Length stays inline without emitting a copy that competes with retail's owner (0x000692B3).
#include "../../../../reference/shims/bfme_vector3_lenfull_link/vector3_lenfull_link.h"
// ?colorFlash@Drawable@@QAEXPBURGBColor@@III@Z @0x0027541E 114B evidence: lazy TintEnvelope at +0x68 via rowed new 0x2FDA0 and ctor 0x271826, TintEnvelope::play 0x2744F2 row, float 1.0f via g_Va00BBB8D8, clears bit 2 at +0x114; neighbours Rva00275376/Drawable_rva00275545 same flags.
// BFME1 34f59164 Rva00415790EnvelopeUpdate.cpp and Drawable.cpp provide the
// envelope algorithm. Target play2744F2, attack27192B, decay2719C0 and
// update274591 establish one vptr, vectors04/10/1c/28, counter34, signed
// state38 and affect39. update has no calls; WB cb5ed0 carries the same
// state machine and Vector3 Add/Subtract/Length assertions.
#include "vector3.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"

class Rva00271826
{
public:
	Rva00271826() throw();
	char m_pad00[0x38];
	unsigned char m_38;
	char m_pad39[0x50 - 0x39];
};

class TintEnvelope
{
public:
 void play(const RGBColor *peak, unsigned int attackFrames, unsigned int decayFrames, unsigned int sustainAtPeak);
 void rva002719A7(float first, float second);
 void update();
private:
 void setDecayFrames(unsigned int frames);
 void setAttackFrames(unsigned int frames);
 enum EnvelopeStates { ENVELOPE_STATE_REST, ENVELOPE_STATE_ATTACK, ENVELOPE_STATE_DECAY, ENVELOPE_STATE_SUSTAIN };
 void *m_vtable;
 Vector3 m_attackRate;
 Vector3 m_decayRate;
 Vector3 m_peakColor;
 Vector3 m_currentColor;
 unsigned int m_sustainCounter;
 signed char m_envState;
 bool m_affect;
 char m_pad3A[2];
 float m_3C;
 float m_40;
};


void *operator new(unsigned int s) throw();

class Drawable
{
public:
	void colorFlash(const RGBColor *peak, unsigned int decayFrames, unsigned int attackFrames, unsigned int sustainAtPeak);
	void colorTint(const RGBColor *peak);
private:
	unsigned char m_pad00[0x68];
	Rva00271826 *m_68;
	unsigned char m_pad6C[0x114 - 0x6C];
	int m_114;
};

void Drawable::colorFlash(const RGBColor *peak, unsigned int decayFrames, unsigned int attackFrames, unsigned int sustainAtPeak)
{
	if (m_68 == 0)
		m_68 = new Rva00271826;
	if (peak != 0) {
		((TintEnvelope *)m_68)->play(peak, attackFrames, decayFrames, sustainAtPeak);
	} else {
		float white = 1.0f;
		RGBColor whiteColor;
		whiteColor.red = white;
		whiteColor.green = white;
		whiteColor.blue = white;
		((TintEnvelope *)m_68)->play(&whiteColor, 1, 4, 1);
	}
	m_114 &= ~4;
}

void Drawable::colorTint(const RGBColor *peak)
{
	if (peak != 0) {
		colorFlash(peak, 0, 0, (unsigned int)-2);
		m_114 |= 4;
	} else {
		if (m_68 == 0)
			m_68 = new Rva00271826;
		m_68->m_38 = 0;
		m_114 &= ~4;
	}
}

// BFME1 1399ad37 DrawableUpdateDrawable.cpp donor calls this setPulse.
// Native +0x3C/+0x40 are established by the 25-byte two-float stores.
// TintEnvelope owner follows the constructor/play family; the original
// target method name remains unproven, so retain its native address.
// ?rva002719A7@TintEnvelope@@QAEXMM@Z
void TintEnvelope::rva002719A7(float first, float second)
{
	m_3C = first;
	m_40 = second;
}

const float FADE_RATE_EPSILON=0.001f;
void TintEnvelope::update()
{
	switch (m_envState)
	{
	case 0:
		m_currentColor.Set(0, 0, 0);
		m_affect = false;
		break;

	case 2:
		if (m_decayRate.Length() > m_currentColor.Length() ||
			m_currentColor.Length() <= FADE_RATE_EPSILON)
		{
			m_envState = 0;
			m_affect = false;
		}
		else
		{
			Vector3::Add(m_decayRate, m_currentColor, &m_currentColor);
			m_affect = true;
		}
		break;

	case 1:
		{
			Vector3 delta;
			Vector3::Subtract(m_currentColor, m_peakColor, &delta);

			if (m_attackRate.Length() > delta.Length() ||
				delta.Length() <= FADE_RATE_EPSILON)
			{
				if (m_sustainCounter)
					m_envState = 3;
				else
					m_envState = 2;
			}
			else
			{
				Vector3::Add(m_attackRate, m_currentColor, &m_currentColor);
				m_affect = true;
			}
			break;
		}

	case 3:
		if (m_sustainCounter > 0)
			--m_sustainCounter;
		else
			m_envState = 2;
		break;
	}
}
