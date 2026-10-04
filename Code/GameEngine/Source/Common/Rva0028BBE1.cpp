// cl: /O1
// ?rva0028BBE1@Rva0028BBE1@@QAEXPAX@Z @0x0028BBE1 18B: holder at +0x23c forwards to rowed Rva004DF2E2::rva004DF3B0 tail-jmp; caller 0x003512D2 in 0x003511E3 unblocks it; neighbours share /O1
class Rva004DF2E2
{
public:
	void rva004DF3B0(void *p);
};

class Rva0028BBE1
{
public:
	void rva0028BBE1(void *p);
private:
	char m_pad00[0x23c];
	Rva004DF2E2 *m_23c;
};

void Rva0028BBE1::rva0028BBE1(void *p)
{
	Rva004DF2E2 *holder = m_23c;
	if (holder != 0)
		holder->rva004DF3B0(p);
}
