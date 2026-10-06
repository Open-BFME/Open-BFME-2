// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005F93CB@Rva005F93CB@@QAEX_N@Z @0x005F93CB 8B forwarder to 0x005F921F.
// Evidence: jmp to rowed 0x005F921F; callers 0x005E96A3 0x005E9DF3; neighbours Rva005F9364Region.
class Rva005F921F
{
public:
	void rva005F921F(bool flag);
};

class Rva005F93CB
{
public:
	void rva005F93CB(bool flag);
private:
	char m_pad[4];
	Rva005F921F *m_member04;
};

void Rva005F93CB::rva005F93CB(bool flag)
{
	m_member04->rva005F921F(flag);
}
