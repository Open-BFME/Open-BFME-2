// cl: /MD
// ?rva0010E482@Rva0010E482@@QAEHH@Z at 0x0010E482 (34B).
// Dual-table non-zero predicate: true if dword at +0xB8 or +0x108 indexed by arg is non-zero.
// Evidence: retail mov eax [esp+4]; cmp [ecx+eax*4+0xB8] 0; jne; cmp [ecx+eax*4+0x108] 0;
// xor/inc bool shape; callers at 0x0010E6DA 0x0010E8DE 0x0010EAAD 0x00136C50.
class Rva0010E482
{
public:
	int rva0010E482(int idx);
private:
	char m_padB8[0xB8];
	int m_tableB8[20];
	int m_table108[1];
};

int Rva0010E482::rva0010E482(int idx)
{
	if (m_tableB8[idx] == 0 && m_table108[idx] == 0)
		return 0;
	return 1;
}
