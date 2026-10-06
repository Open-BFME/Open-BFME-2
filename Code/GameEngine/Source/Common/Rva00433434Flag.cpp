// cl: /MD
// ?rva00433434@Rva00433434@@QAEX_N@Z, retail 0x00433434, 31 bytes. Sets bit 1 of +0xC4 then sets/clears bit 0 of +0x4C via rowed helpers 0x001D96FF/0x001D9709. Called from 0x00433999. Neighbours share +0xC4 flag pattern.
class Rva001D96FF
{
public:
	void rva001D96FF(int mask);
};
class Rva001D9709
{
public:
	void rva001D9709(int mask);
};
class Rva00433434
{
public:
	void rva00433434(bool flag);
private:
	char m_pad00[0x4C];
	int m_flags4C;
	char m_pad50[0x74];
	int m_flagsC4;
};
void Rva00433434::rva00433434(bool flag)
{
	m_flagsC4 |= 2;
	if (flag)
		((Rva001D96FF *)this)->rva001D96FF(1);
	else
		((Rva001D9709 *)this)->rva001D9709(1);
}
