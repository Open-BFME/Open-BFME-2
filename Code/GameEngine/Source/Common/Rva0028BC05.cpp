// cl: /O1
// ?rva0028BC05@Rva0028BC05@@QAEXPAX@Z @0x0028BC05 18B: holder at +0x23c forwards to rowed Rva004DF4B5::rva004DF4B5 tail-jmp; caller 0x004DF3E8 in 0x004DF3B0 unblocks 0x004DF3B0; neighbours share /O1
class Rva004DF4B5
{
public:
	void rva004DF4B5(void *p);
};

class Rva0028BC05
{
public:
	void rva0028BC05(void *p);
private:
	char m_pad00[0x23c];
	Rva004DF4B5 *m_23c;
};

void Rva0028BC05::rva0028BC05(void *p)
{
	Rva004DF4B5 *holder = m_23c;
	if (holder != 0)
		holder->rva004DF4B5(p);
}
