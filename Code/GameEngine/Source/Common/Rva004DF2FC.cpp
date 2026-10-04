// cl: /O1 /GX- /MD /DNDEBUG
// ?rva004DF2FC@Rva004DF2E2@@QAEXPAVBfmeSubBEC@@@Z @0x004DF2FC 40B: guard on arg null and m_20 flag then forward m_08 via rowed BfmeSubBEC::rva0028BC17 and clear status via rowed rva004DF2EF; callers 0x004DF3D2 and 0x0028BBFD unblocks 0x0028BBF3 and 0x004DF3B0; neighbours share flags
class BfmeSubBEC
{
public:
	void rva0028BC17(void *p);
};

class Rva004DF2E2
{
public:
	void rva004DF2FC(BfmeSubBEC *bec);
	void rva004DF2EF();
private:
	char m_pad00[8];
	void *m_08;
	char m_pad0C[0x20 - 0x0C];
	int m_20;
};

void Rva004DF2E2::rva004DF2FC(BfmeSubBEC *bec)
{
	if (bec == 0)
		return;
	if (m_20 == 0)
		return;
	void *slot = m_08;
	m_20 = 0;
	bec->rva0028BC17(slot);
	rva004DF2EF();
}
