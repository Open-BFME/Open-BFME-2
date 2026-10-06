// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0029AA27@Rva0029AA27@@QAEXPBUS12_0029AA27@@@Z @0x0029AA27 24B
// Guarded 12-byte copy via movsd string; caller at 0x00432145; unlock.
struct S12_0029AA27
{
	int a;
	int b;
	int c;
};
class Rva0029AA27
{
public:
	void rva0029AA27(const S12_0029AA27 *src);
private:
	char m_pad[0x9B8];
	S12_0029AA27 m_9B8;
};
void Rva0029AA27::rva0029AA27(const S12_0029AA27 *src)
{
	if (src != 0)
		m_9B8 = *src;
}
