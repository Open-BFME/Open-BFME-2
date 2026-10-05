// cl: /O1 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva0009DA28@Rva0009D9BD@@QAEXXZ, retail 0x0009DA28, 19 bytes.
// Evidence: reads this+0x19C null-guarded byte clear at +4 then tail-jmp to rowed rva0009D9BD 0x0009D9BD (same class, vector at +0x1C0); callers in FUN_0049db5a.
#include <vector>

struct Rva0009DA28Node
{
	char m_pad[4];
	unsigned char m_flag;
};

class Rva0009D9BD
{
public:
	void rva0009D9BD();
	void rva0009DA28();

private:
	char m_pad00[0x19C];
	Rva0009DA28Node *m_19C;
	unsigned char m_pad1A0[0x1C0 - 0x19C - 4];
	_STL::vector<void *> m_vec;
};

void Rva0009D9BD::rva0009DA28()
{
	if (m_19C)
		m_19C->m_flag = 0;
	rva0009D9BD();
}
