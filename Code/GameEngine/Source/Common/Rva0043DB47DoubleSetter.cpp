// cl: /DNDEBUG /MD
// ?enable@Rva0043DB47DoubleSetter@@QAEXXZ @ 0x0043DB47, 15 bytes.
// Double byte setter at +0x2B9 +0x2BA to 1.
// Evidence: retail mov byte [ecx+0x2B9] 1 mov byte [ecx+0x2BA] 1 ret; neighbours Rva0043DA65Getter and DispByteOneSetters; 13 callers.
class Rva0043DB47DoubleSetter
{
public:
	void enable();

	char m_lead[0x2B9];
	unsigned char m_a;
	unsigned char m_b;
};

void Rva0043DB47DoubleSetter::enable()
{
	m_a = 1;
	m_b = 1;
}
