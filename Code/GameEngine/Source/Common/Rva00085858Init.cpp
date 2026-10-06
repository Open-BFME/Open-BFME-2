// cl: /MD /EHsc /DNDEBUG
// ?rva00085858@Rva00085858@@QAEPAV1@XZ, retail 0x00085858, 35 bytes.
// __thiscall initializer forwarding (0 0 1) to rowed ParabolicEase
// 0x0008517E at +0x14 then returning this. Evidence: same callee and args
// as neighbouring ctor 0x00085815; caller 0x0008B7CF.
typedef float Real;

class ParabolicEase
{
public:
	ParabolicEase *rva0008517E(Real easeInTime, Real easeOutTime, Real duration);
private:
	Real m_in;
	Real m_out;
};

class Rva00085858
{
public:
	Rva00085858 *rva00085858();
private:
	unsigned char m_pad[0x14];
	ParabolicEase m_14;
};

Rva00085858 *Rva00085858::rva00085858()
{
	m_14.rva0008517E(0.0f, 0.0f, 1.0f);
	return this;
}
