// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0039D5A9@Rva0039D5A9@@QAEHXZ @0x0039D5A9 (24B).
// Strided sum: adds count dwords at stride 0x18 starting at this+0x04 where
// count lives at +0xAC. Retail shape is count load plus xor plus jle plus
// add-ecx-4 plus add-eax plus add-ecx-0x18 plus dec plus jne plus ret.
// Callers at 0x003A0DB1 0x0059A328 0x0059A60F 0x0059AC27 0x0059ACEC read the
// total; owner unproven so the name keeps the address token.

class Rva0039D5A9
{
public:
	int rva0039D5A9();

private:
	int m_00; // +0x00
	int m_04; // +0x04 first summed slot
	char m_pad08[0xAC - 0x08];
	int m_countAC; // +0xAC
};

int Rva0039D5A9::rva0039D5A9()
{
	int count = m_countAC;
	int sum = 0;
	if (count > 0) {
		int *p = &m_04;
		do {
			sum += *p;
			p = (int *)((char *)p + 0x18);
			--count;
		} while (count != 0);
	}
	return sum;
}
