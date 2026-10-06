// cl: /MD /EHsc
// ?rva005F7512@Rva005F6A58@@QAEXHH@Z @0x005F7512 44B: vslot 12 of Rva005F6A58 vtable 0x008797F4 forwards to rowed Rva005F6CA8 rva005F6E85 0x005F6E85 when args differ from +0x20 +0x24.
class Rva005F6CA8
{
public:
	void rva005F6E85(int unused, int turns);
};
class Rva005F6A58
{
public:
	void rva005F7512(int a, int b);
private:
	char m_pad00[0x20];
	int m_20;
	int m_24;
};
void Rva005F6A58::rva005F7512(int a, int b)
{
	if (a == m_20 && b == m_24)
		return;
	((Rva005F6CA8 *)this)->rva005F6E85(a, b);
	m_20 = a;
	m_24 = b;
}
