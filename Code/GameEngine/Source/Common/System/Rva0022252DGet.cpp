// flags: region default (reverse/retail_inventory/flag_regions.csv)

// ?rva0022252D@Rva0022252D@@QAEPAXH@Z, retail 0x0022252D, 26 bytes.
// Bounds-checked slot lookup: 14 entries at this+0xD4 stride 0x28 return
// element pointer else null. Callers 0x004115CF 0x00412017 pass level from
// Rva004128BBGetLevel through global 0x009FE4CC. Honest address class.
struct Rva0022252DElem
{
	void *ptr;
	char pad[0x24];
};

class Rva0022252D
{
public:
	void *rva0022252D(int index);
private:
	char m_pad[0xD4];
	Rva0022252DElem m_elems[14];
};

void *Rva0022252D::rva0022252D(int index)
{
	if ((unsigned int)index >= 14)
		return 0;
	return m_elems[index].ptr;
}
