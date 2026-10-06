// cl: /MD
// ?rva005EE9CE@Rva005EE9CE@@QAEPAV1@XZ, retail 0x005EE9CE, 23 bytes.
// Zeroes 16-byte struct at +0 +4 +8 +0xC and returns this. Called on stack
// temp from 0x005D81CF 0x005D8483 0x005D8648. No callees.

class Rva005EE9CE
{
public:
	Rva005EE9CE *rva005EE9CE();

private:
	int m_00;
	float m_04;
	int m_08;
	float m_0C;
};

Rva005EE9CE *Rva005EE9CE::rva005EE9CE()
{
	m_00 = 0;
	m_04 = 0.0f;
	m_08 = 0;
	m_0C = 0.0f;
	return this;
}
