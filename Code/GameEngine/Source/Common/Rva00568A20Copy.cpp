// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva00568A20@@QAE@ABV0@@Z @0x00568A20 33B: copy ctor over BfmePoolRef10 base plus int at +4 and byte at +8. Base copy is rowed at 0x00051950. Caller at 0x00568C8F passes dest in ecx with null check.
struct BfmePoolHolder88;
class BfmePoolRef10
{
	BfmePoolHolder88 *m_target;
public:
	BfmePoolRef10(const BfmePoolRef10 &other);
};
class Rva00568A20
{
public:
	Rva00568A20(const Rva00568A20 &o);
private:
	BfmePoolRef10 m_pool;
	int m_word;
	unsigned char m_flag;
};
Rva00568A20::Rva00568A20(const Rva00568A20 &o) : m_pool(o.m_pool), m_word(o.m_word), m_flag(o.m_flag)
{
}
