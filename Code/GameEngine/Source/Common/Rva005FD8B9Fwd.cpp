// cl: /MD /EHsc
// ?rva005FD8B9@Rva005FD8B9@@QAEX_N@Z retail 0x005FD8B9 8B
// Evidence: chain via 0x005FD72D row; mov ecx [ecx+4] jmp tail; caller 0x005F55C0; neighbour 0x005FD8B1
struct Rva005FD72D
{
	void rva005FD72D(bool enabled);
};

struct Rva005FD8B9
{
	char m_pad0[4];
	Rva005FD72D *m_ptr4;
	void rva005FD8B9(bool enabled);
};

void Rva005FD8B9::rva005FD8B9(bool enabled)
{
	return m_ptr4->rva005FD72D(enabled);
}
