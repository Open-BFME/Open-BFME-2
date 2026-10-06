// cl: /DNDEBUG /MD /EHsc /Ob2
// ?bfmeTotalVNQ@BfmeThingVNQ@@QAEHXZ 0x0016EEE0 63B evidence: BFME1 donor BfmeConv1517.cpp bfmeTotalVNQ same layout same total; BFME2 callee rowed VertexMaterial rva0013D250 const; caller 0x00188117 unblocks link bonus
class VertexMaterialClass
{
public:
	int rva0013D250() const;
};
class BfmeThingVNQ
{
public:
	int bfmeTotalVNQ();
	char m_bfmePad00[0xc];
	VertexMaterialClass **m_bfme0c;
	char m_bfmePad10[8];
	int m_bfme18;
	char m_bfmePad1c[0x14];
	int m_bfme30;
};
int BfmeThingVNQ::bfmeTotalVNQ()
{
	int n = m_bfme18;
	int total = (m_bfme30 + n) * 4 + 0x38;
	int i = 0;
	if (n > 0) {
		do {
			VertexMaterialClass *p = m_bfme0c[i];
			if (p != 0)
				total += p->rva0013D250();
			++i;
		} while (i < m_bfme18);
	}
	return total;
}
