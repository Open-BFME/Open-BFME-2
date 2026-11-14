// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// ??RParabolicEase@@QBEMM@Z, retail 0x0030E5D1, 171 bytes.
// ParabolicEase::operator() -- ease in/out based on parabolic function.
// Donor: BFME1 Code/GameEngine/Source/GameClient/ParabolicEase.cpp (return-style clamp)
//   and ZH reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/ParabolicEase.cpp
//   (ParabolicEase.h: m_in/m_out, Real operator()(Real) const).
// Evidence: clamp-then-piecewise shape matches donor verbatim (denominator 1+m_out-m_in,
//   t<t branch t*t/(den*m_in), t<=b branch (m_in+2*(t-m_in))/den,
//   else (m_in+2*(m_out-m_in)+(2*(t-m_out)+m_out*m_out-t*t)/(1-m_out))/den);
//   landing unblocks 7 callers (0x00086C4A/0x00086CDA/0x00086D73/0x00086E24/0x00086EBD/0x00086F56/0x00089ED4)
//   that lerp with its result; 1.0f global at 0x00BBB8D8.
typedef float Real;
#include "../../Include/Common/ParabolicEase.h"
Real ParabolicEase::operator()(Real param) const
{
	if (param < 0.0f || param > 1.0f) {
		if (param < 0.0f) {
			param = 0.0f;
		} else if (param > 1.0f) {
			param = 1.0f;
		}
	}
	const Real denominator = 1.0f + m_out - m_in;
	if (param < m_in) {
		return param * param / (denominator * m_in);
	} else if (param <= m_out) {
		return (m_in + 2.0f * (param - m_in)) / denominator;
	} else {
		return (m_in + 2.0f * (m_out - m_in) + (2.0f * (param - m_out) + m_out * m_out - param * param) / (1.0f - m_out)) / denominator;
	}
}

// Clean BFME1 6d9434269164392c5ba62aaa7c15a86b5b020d76,
// game/GameEngine/Source/Common/ParabolicEaseSetEaseTimesBFME.cpp,
// /O1 /G7 /arch:SSE /MD /EHsc. Ghidra178B/RET12 at30E51F ends exactly
// at the existing171B operator30E5D1. Three float inputs and two float
// stores at+0/+4 are independently visible in target. Init caller8647C
// passes this+1C0; evaluator8AAD4 uses that same offset. Donor carries
// ease/duration semantics and class name; original target setter name,
// full class identity and object size remain unknown. Preserve NaN branches.
namespace
{
	template <typename T>
	// ?clamp present-unmatched
	inline T clamp(T value, T minimum = T(0), T maximum = T(1))
	{
		if (value < minimum)
			return minimum;
		else if (value > maximum)
			return maximum;
		return value;
	}
}

void ParabolicEase::rva0030E51F(Real easeInTime, Real easeOutTime, Real duration)
{
	if (duration > 0.0f)
	{
		if (easeInTime > 0.0f)
			easeInTime /= duration;
		else
			easeInTime = 0.0f;

		if (easeOutTime > 0.0f)
			easeOutTime /= duration;
		else
			easeOutTime = 0.0f;
	}

	m_in = easeInTime;
	if (m_in < 0.0f || m_in > 1.0f)
		m_in = clamp(m_in);

	m_out = 1.0f - easeOutTime;
	if (m_out < 0.0f || m_out > 1.0f)
		m_out = clamp(m_out);

	if (m_in > m_out)
		m_in = m_out;
}
