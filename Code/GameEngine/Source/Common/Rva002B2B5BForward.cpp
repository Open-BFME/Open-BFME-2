// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002B2B5B@Rva002B2B5B@@QAEHH@Z, retail 0x002B2B5B, 11 bytes.
// Tail-forwarding method: this+0xB0 holds Rva0020E3AD object, jmp to rowed
// 0x0020E3AD level via three thresholds. Caller at 0x0031910E.
class Rva0020E3AD
{
public:
	int rva0020E3AD(int v);
};

class Rva002B2B5B
{
public:
	int rva002B2B5B(int v);

private:
	char m_pad[0xB0];
	Rva0020E3AD *m_ptr;
};

int Rva002B2B5B::rva002B2B5B(int v)
{
	return m_ptr->rva0020E3AD(v);
}
