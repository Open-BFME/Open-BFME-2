// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005F93D3@Rva005F93D3@@QAEX_N@Z @0x005F93D3 8B forwarder to 0x005F927A.
// Evidence: jmp to rowed 0x005F927A; callers 0x005E96B3 0x005E9E02; neighbour Rva005F93CBForward.
class Rva005F927A
{
public:
	void rva005F927A(bool flag);
};

class Rva005F93D3
{
public:
	void rva005F93D3(bool flag);
private:
	char m_pad[4];
	Rva005F927A *m_member04;
};

void Rva005F93D3::rva005F93D3(bool flag)
{
	m_member04->rva005F927A(flag);
}
