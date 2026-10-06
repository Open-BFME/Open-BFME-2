// cl: /DNDEBUG /MD /EHsc
// ?rva005E73E4@Rva005E73E4@@QAEPAXH@Z, retail 0x005E73E4, 23 bytes.
// Indexed accessor: index 0 returns inline slot at +0x20, else array at +0x24.
// Evidence: 3 calls from 0x005E7CAA passing +0x30/arg as index; return used as this.

class Rva005E73E4
{
public:
	void *rva005E73E4(int index);

private:
	char m_pad[0x20];
	void *m_first;
	void **m_rest;
};

void *Rva005E73E4::rva005E73E4(int index)
{
	if (index == 0)
		return m_first;
	return m_rest[index - 1];
}
