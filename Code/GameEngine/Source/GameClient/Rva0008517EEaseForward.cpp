// cl: /MD /EHsc /DNDEBUG
// Target8517E+40 forwards three floats to the real178B normalization body
// and returns this, RET12. Separate compilation keeps the callee opaque;
// the same-TU trial retains ECX and emits36B instead of the target ESI save.
// The existing donor-named easing view is identical in both source units.
// Reference constructor forwarding is a semantic lead only: the target's
// constructor-versus-initializer identity and original name remain unknown.
typedef float Real;
class ParabolicEase
{
public:
	void rva0030E51F(Real easeInTime, Real easeOutTime, Real duration);
	ParabolicEase *rva0008517E(Real easeInTime, Real easeOutTime, Real duration);
	Real operator()(Real param) const;
private:
	Real m_in;
	Real m_out;
};

// Target Ghidra8517E+40 / RET12: same this pointer forwards three float
// values to30E51F and returns this inEAX. Reference header has a constructor
// forwarding to its setter, but target has three inputs and the original
// constructor-versus-initializer identity is unknown. Keep an address name.
ParabolicEase *ParabolicEase::rva0008517E(Real easeInTime, Real easeOutTime, Real duration)
{
	rva0030E51F(easeInTime, easeOutTime, duration);
	return this;
}
