// cl: /O1 /DNDEBUG /MD
//
// ?rva0032ED61@Rva0032ED61@@QAEXXZ @0x0032ED61 20B.
// Clears two embedded rb-tree members at +0x24 and +0x30, second as tail-jmp.
// Evidence: callees 0x0032DCB7 ?rva0032DCB7@Rva0032D3D3@@QAEXXZ row and
// 0x0032EB5E ?rva0032EB5E@Rva0032EAA1@@QAEXXZ row, caller 0x0032F861.

class Rva0032D3D3
{
public:
	void rva0032DCB7();
private:
	void *m_head;
	int m_flag;
};

class Rva0032EAA1
{
public:
	void rva0032EB5E();
private:
	void *m_header;
	int m_count;
};

class Rva0032ED61
{
public:
	void rva0032ED61();
private:
	char m_pad00[0x24];
	Rva0032D3D3 m_24;
	char m_pad2C[0x30 - 0x24 - 8];
	Rva0032EAA1 m_30;
};

void Rva0032ED61::rva0032ED61()
{
	m_24.rva0032DCB7();
	return m_30.rva0032EB5E();
}
