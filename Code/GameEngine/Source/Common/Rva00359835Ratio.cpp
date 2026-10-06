// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00359835@Rva00359835@@QBEMXZ, retail 0x00359835, 30 bytes.
// Float ratio with zero guard: if ([ecx+0x10]==0) return pooled 0.0f at
// 0x007BAEAC else (float)[ecx+0x14] / (float)[ecx+0x10] via x87
// (mov eax,[ecx+0x10]; test; mov [ebp-4],eax; jne; fld [pool]; leave; ret;
// fild [ecx+0x14]; fidiv [ebp-4]; leave; ret). Callers at 0x00359AD8/
// 0x00359FB7 pass this as lea [ebp-0x30]/[ebp-0x38] (thiscall, no args,
// ST(0) return). Identity stays honest rva (owner unproven local struct).
class Rva00359835
{
public:
	float rva00359835() const;
private:
	char m_pad[0x10];
	int m_10;
	int m_14;
};
float Rva00359835::rva00359835() const
{
	if (m_10 == 0)
		return 0.0f;
	return (float)m_14 / (float)m_10;
}
