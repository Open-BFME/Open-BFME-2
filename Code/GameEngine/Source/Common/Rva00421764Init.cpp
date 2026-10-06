// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva00421764@@QAE@PBXH0@Z @0x00421764 49B
// Init 3-arg thiscall: +0=arg2 +4=*(arg1+0x74) +0x10/+0x14=arg3[0/1] +0x18/+0x1c=0.0f.
// Evidence: unlock lane; ret 0xc; caller 0x0042513A; neighbours Disp8ByteSetters and ClientRandomValue.
class Rva00421764
{
public:
	Rva00421764(const void *a, int b, const void *c);
private:
	int m_a;
	int m_b;
	char m_pad[8];
	int m_c;
	int m_d;
	float m_e;
	float m_f;
};

Rva00421764::Rva00421764(const void *a, int b, const void *c)
	: m_e(0.0f), m_f(0.0f), m_a(b), m_b(*(const int *)((const char *)a + 0x74)),
	  m_c(((const int *)c)[0]), m_d(((const int *)c)[1])
{
}
