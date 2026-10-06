// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D9AD4@Rva002D9AD4@@QAEAAVBfmePoolRef10@@ABV2@@Z @ 0x002D9AD4 8B
// Tail-jmp assign forwarder: return m_pool = other where m_pool is BfmePoolRef10 at +0x10.
// Evidence: honest address name; add ecx 0x10 jmp to rowed ??4BfmePoolRef10@@QAEAAV0@ABV0@@Z; callers in FUN_0045a451 and FUN_0045dd40; neighbours BfmeStringTailRecord144 dtor and CDManager getPath.
class BfmePoolRef10
{
public:
	BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
};
class Rva002D9AD4
{
public:
	BfmePoolRef10 &rva002D9AD4(const BfmePoolRef10 &other);
	char m_pad[0x10];
	BfmePoolRef10 m_pool;
};
BfmePoolRef10 &Rva002D9AD4::rva002D9AD4(const BfmePoolRef10 &other)
{
	return m_pool = other;
}
