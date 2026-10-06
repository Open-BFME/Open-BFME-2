// cl: /MD /EHsc /DNDEBUG
// ?rva0008589E@Rva0008589E@@QAEPAV1@XZ, retail 0x0008589E, 35 bytes.
// __thiscall initializer forwarding (0 0 1) to rowed ParabolicEase
// 0x0008517E at +0x20 then returning this. Evidence: same callee and args
// as neighbouring rows 0x00085858 0x0008587B; caller 0x0008B7CF.
typedef float Real;

class ParabolicEase
{
public:
	ParabolicEase *rva0008517E(Real easeInTime, Real easeOutTime, Real duration);
private:
	Real m_in;
	Real m_out;
};

class Rva0008589E
{
public:
	Rva0008589E *rva0008589E();
private:
	unsigned char m_pad[0x20];
	ParabolicEase m_20;
};

Rva0008589E *Rva0008589E::rva0008589E()
{
	m_20.rva0008517E(0.0f, 0.0f, 1.0f);
	return this;
}
