// cl: /MD /EHsc /DNDEBUG
// ?rva0030E8DF@Rva0030E8DF@@QAEXXZ, retail 0x0030E8DF, 44 bytes.
// Clear helper: vector erase via rowed voidptr erase plus zeroing and 1.0f default.
// Evidence: callers at 0x00085947/0x0008D807 operate on subobject at +0x2458;
//   vector at +0x00 clears through rowed erase 0x0031BD55 (ICF pin for RvaVector erase);
//   float at +0x14 defaults to shared 1.0f at 0x00BBB8D8; ints at +0x0C/+0x10/+0x18 and byte at +0x1C zeroed.
struct RvaVector {
	void **m_begin;
	void **m_end;
	void **m_cap;
	void **erase(void **first, void **last);
};
class Rva0030E8DF {
public:
	void rva0030E8DF();
private:
	RvaVector m_vec; // +0x00
	int m_0c; // +0x0C
	int m_10; // +0x10
	float m_14; // +0x14
	int m_18; // +0x18
	unsigned char m_1c; // +0x1C
};
void Rva0030E8DF::rva0030E8DF()
{
	m_0c = 0;
	m_10 = 0;
	m_18 = 0;
	m_14 = 1.0f;
	m_vec.erase(m_vec.m_begin, m_vec.m_end);
	m_1c = 0;
}
