// cl: /MD
// ?rva0014F438@Rva0014DC76@@QAEPAXI@Z @0x0014F438, 28B.
// Conditional-delete wrapper: calls rowed ?rva0014DC76@Rva0014DC76@@QAEXXZ at 0x0014DC76 then rowed delete at 0x0002FD60 on flag bit 0, returning this.
// Evidence: retail calls 0x0014DC76 (rowed in Rva0014DC76Init.cpp) and 0x0002FD60 (rowed ??3@YAXPAX@Z); class layout copied from owner TU.
extern int g_00BC6F24;
class Rva0014DC76
{
public:
	void rva0014DC76();
	void *rva0014F438(unsigned int flag);
private:
	int m_0;
	int m_4;
	int m_8;
	int m_c;
};

void *Rva0014DC76::rva0014F438(unsigned int flag)
{
	rva0014DC76();
	if (flag & 1)
		delete this;
	return this;
}
