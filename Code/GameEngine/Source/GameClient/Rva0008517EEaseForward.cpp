// cl: /MD /EHsc /DNDEBUG
// Target8517E+40 forwards three floats to the real178B normalization body
// and returns this, RET12. Separate compilation keeps the callee opaque;
// the same-TU trial retains ECX and emits36B instead of the target ESI save.
// The existing donor-named easing view is identical in both source units.
// Reference constructor forwarding is a semantic lead only: the target's
// constructor-versus-initializer identity and original name remain unknown.
#include "../../Include/Common/ScalarTypes.h"
class ParabolicEase
{
public:
	void rva0030E51F(Real easeInTime, Real easeOutTime, Real duration);
	ParabolicEase(Real easeInTime = 0.0f, Real easeOutTime = 0.0f, Real duration = 1.0f);
	Real operator()(Real param) const;
private:
	Real m_in;
	Real m_out;
};

// Target Ghidra8517E+40 / RET12: same this pointer forwards three float
// values to30E51F and returns this inEAX. Reference header has a constructor
// forwarding to its setter (ZH ParabolicEase(Real, Real) defaults 0/0). Target
// evidence for the constructor identity: the W3DView constructor 0x0008B7CF
// value-initializes its camera-move records (rep stosd zeroing, then a call
// to each record's implicit constructor 0x00085858..0x000858C1), and those
// implicit constructors reach this body with (0, 0, 1) as a member's default
// construction does.
ParabolicEase::ParabolicEase(Real easeInTime, Real easeOutTime, Real duration)
{
	rva0030E51F(easeInTime, easeOutTime, duration);
}
