// cl: /DNDEBUG /MD /EHsc
// ?rva0020E27B@Rva0020E449@@QAEXM@Z @0x0020E27B 105B
// Honest Rva0020E449 method scaling six ints at +4..+18 by float factor:
// cvtsi2ss/mulss/cvttss2si per field. Evidence: caller 0x0020F3AC calls it
// on a copy-constructed Rva0020E449 (rowed copy ctor 0x0020E449 in
// V3PolyCopyCtors.cpp, same six-int layout), float arrives via fstp [esp]
// from global 0x007BB8D8, ret 4 thiscall with SSE per /O1 /arch:SSE.
class Rva0020E449
{
public:
	Rva0020E449(const Rva0020E449 &other);
	virtual ~Rva0020E449();
	void rva0020E27B(float factor);
private:
	int m_field04;
	int m_field08;
	int m_field0C;
	int m_field10;
	int m_field14;
	int m_field18;
};

void Rva0020E449::rva0020E27B(float factor)
{
	m_field04 = (int)(m_field04 * factor);
	m_field08 = (int)(m_field08 * factor);
	m_field0C = (int)(m_field0C * factor);
	m_field10 = (int)(m_field10 * factor);
	m_field14 = (int)(m_field14 * factor);
	m_field18 = (int)(m_field18 * factor);
}
