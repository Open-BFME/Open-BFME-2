// ??0Rva0006AB90FunctionCurve@@QAE@PAVRva0006AB10Curve@@@Z
// cl: /O1 /arch:SSE /MD
// ??0Rva0006AB90FunctionCurve@@QAE@PAVRva0006AB10Curve@@@Z @ 0x00504682 (46B):
// Leaf thiscall constructor. Stores the Curve* argument at +0, 1 at +4, four
// zero floats at +8..+14 and zero bytes at +18/+19.
//
// Identity: reverse/symbols.csv pins this address as the FunctionCurve
// constructor, called by ?parse@Rva0006AF00FunctionCurve@@QAEXPAVINI@@@Z at
// retail 0x005051DA (donor-carried name, body unrowed). The body confirms it --
// `ret 4` and a single stack argument -- and the banked attempt filed it under
// the address-derived fallback ?rva00504682@Rva00504682@@QAEXH@Z, a void
// member function.
//
// That member-function spelling is what held the bank at 0.93: it pins the
// object pointer to ECX and emits 44B (`mov eax,[esp+4]` / stores through
// [ecx]). Retail opens `xorps xmm0,xmm0 / mov eax,ecx / mov ecx,[esp+4] /
// mov [eax],ecx`, the register pair VC7 allocates to a CONSTRUCTOR. Written as
// the constructor the pin names, the body's own statement order is byte-exact
// at 46B with no change to the bank's flags. The +0 field is the Curve* the
// caller passes, not an int; the storage instruction is the same either way.
class Rva0006AB10Curve;

class Rva0006AB90FunctionCurve
{
public:
	Rva0006AB90FunctionCurve(Rva0006AB10Curve *curve);
private:
	Rva0006AB10Curve *m_00;
	unsigned char m_04;
	char m_pad05[3];
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	unsigned char m_18;
	unsigned char m_19;
};

Rva0006AB90FunctionCurve::Rva0006AB90FunctionCurve(Rva0006AB10Curve *curve)
{
	m_00 = curve;
	m_04 = 1;
	m_08 = 0.0f;
	m_0C = 0.0f;
	m_10 = 0.0f;
	m_14 = 0.0f;
	m_18 = 0;
	m_19 = 0;
}
