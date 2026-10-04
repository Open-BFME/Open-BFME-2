// cl: /O1 /DNDEBUG /MD
// ?rva00318FBE@Rva00318FBE@@QAEHXZ, retail 0x00318FBE, 8 bytes.
// Evidence: mov ecx [ecx+0x78] then jmp pinned ?bfmeVal1038@BfmeY1038@@QAEHXZ
// 0x0040CF91; 10 unclaimed callers; neighbours Rva00318E8CGet /O1 and
// Rva00319159Get; tail return m_ptr->method gives mov-plus-jmp at /O1.
class BfmeY1038
{
public:
	int bfmeVal1038();
};

class Rva00318FBE
{
public:
	int rva00318FBE();
private:
	char m_pad[0x78];
	BfmeY1038 *m_78;
};

int Rva00318FBE::rva00318FBE()
{
	return m_78->bfmeVal1038();
}
