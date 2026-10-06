// cl: /MD /EHsc
// ?rva005FD8B1@Rva005FD8B1@@QAEX_N@Z retail 0x005FD8B1 8B
// Evidence: chain via 0x005FD6D2 row; mov ecx [ecx+4] jmp tail; caller 0x005F55A2; neighbours 0x005FD8A9/0x005FD8E5
struct Rva005FD6D2
{
	void rva005FD6D2(bool enabled);
};

struct Rva005FD8B1
{
	char m_pad0[4];
	Rva005FD6D2 *m_ptr4;
	void rva005FD8B1(bool enabled);
};

void Rva005FD8B1::rva005FD8B1(bool enabled)
{
	return m_ptr4->rva005FD6D2(enabled);
}
