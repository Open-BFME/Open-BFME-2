// cl: /MD /EHsc /DNDEBUG
// ?rva0008587B@Rva0008587B@@QAEPAV1@XZ, retail 0x0008587B, 35 bytes.
// __thiscall initializer forwarding (0 0 1) to rowed ParabolicEase
// 0x0008517E at +0x18 then returning this. Evidence: same callee and args
// as neighbouring row 0x00085858; caller 0x0008B7CF.
typedef float Real;

class ParabolicEase
{
public:
	ParabolicEase *rva0008517E(Real easeInTime, Real easeOutTime, Real duration);
private:
	Real m_in;
	Real m_out;
};

class Rva0008587B
{
public:
	Rva0008587B *rva0008587B();
private:
	unsigned char m_pad[0x18];
	ParabolicEase m_18;
};

Rva0008587B *Rva0008587B::rva0008587B()
{
	m_18.rva0008517E(0.0f, 0.0f, 1.0f);
	return this;
}
