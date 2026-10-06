// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005A6709@Rva005A6709@@QBEHXZ @0x005A6709 20B. Unlock lane: predicate
// returning (m_0C != 8 && m_0C == m_14); 9 callers including 0x005A6931 and
// 0x005BA3B0; unblocks 7. Prev/next are list append and cmp-bool getter.
typedef int Int;

class Rva005A6709
{
public:
	Int rva005A6709() const;
private:
	char m_pad[12];
	Int m_0C;
	Int m_10;
	Int m_14;
};
Int Rva005A6709::rva005A6709() const
{
	return (m_0C != 8) && (m_0C == m_14);
}

extern unsigned long g_00E063FC;
int Rva005A671DNext()
{
	if (!g_00E063FC)
		++g_00E063FC;
	return g_00E063FC++;
}

