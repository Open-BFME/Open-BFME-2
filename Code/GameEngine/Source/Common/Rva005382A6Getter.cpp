// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005382A6@Rva005382A6@@QAEPAXHH@Z, retail 0x005382A6, 16 bytes.
// Indexed address: base at +0 plus index*16 plus offset.
// Evidence: callers 0x0030BE00 plus jmp 0x0030BC0C; prev Disp8SarAvg no-flags next vector float4 /O1.
class Rva005382A6
{
public:
	void *rva005382A6(int i, int off);

private:
	void *m_base;
};

void *Rva005382A6::rva005382A6(int i, int off)
{
	return (char *)m_base + i * 16 + off;
}
