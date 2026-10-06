// cl: /MD /EHsc /DNDEBUG
// ?rva000858C1@Rva000858C1@@QAEPAV1@XZ, retail 0x000858C1, 35 bytes.
// __thiscall initializer forwarding (0 0 1) to rowed ParabolicEase
// 0x0008517E at +0x1C then returning this. Evidence: same callee and args
// as neighbouring rows 0x00085858-0x0008589E; caller 0x0008B7CF.
typedef float Real;

class ParabolicEase
{
public:
	ParabolicEase *rva0008517E(Real easeInTime, Real easeOutTime, Real duration);
private:
	Real m_in;
	Real m_out;
};

class Rva000858C1
{
public:
	Rva000858C1 *rva000858C1();
private:
	unsigned char m_pad[0x1C];
	ParabolicEase m_1C;
};

Rva000858C1 *Rva000858C1::rva000858C1()
{
	m_1C.rva0008517E(0.0f, 0.0f, 1.0f);
	return this;
}
