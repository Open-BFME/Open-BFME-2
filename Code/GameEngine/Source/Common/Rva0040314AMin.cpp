// cl: /DNDEBUG /MD
// ?rva0040314A@Rva0040314A@@QAEIXZ @0x0040314A 20B, call sites 0x00403DAC,
// 0x00403DB9 and 0x004040C7. Unsigned min with a zero guard: when the cap at
// +0x0C is set, the smaller of +0x08 and +0x0C, else +0x08.
// Target evidence: mov/test/jbe, then cmp plus cmovb; cmov needs the P6
// instruction set, which /arch:SSE enables (the banked attempt lacked it and
// got jae plus mov).
class Rva0040314A
{
public:
	unsigned int rva0040314A();
private:
	char _pad[8];
	unsigned int m_08;
	unsigned int m_0c;
};

unsigned int Rva0040314A::rva0040314A()
{
	if (m_0c > 0)
		return m_08 < m_0c ? m_08 : m_0c;
	return m_08;
}
