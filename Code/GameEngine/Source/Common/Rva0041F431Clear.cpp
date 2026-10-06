// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva0041F431@Rva0041F431@@QAEPAV1@XZ @0x0041F431 24B.
// Zeroes 16B record (int 0 plus three float 0.0) and returns this. Evidence:
// caller at 0x001DDB66 builds 16B stack record for BfmeFloat4Record use.
class Rva0041F431
{
public:
	Rva0041F431 *rva0041F431();
private:
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
};

Rva0041F431 *Rva0041F431::rva0041F431()
{
	m_00 = 0;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0c = 0.0f;
	return this;
}
