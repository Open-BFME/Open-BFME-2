// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva0014F40C@@QAE@XZ retail 0x0014F40C 44B: default ctor storing vtable 0x007D38A0 plus member vtables 0x007D3874 0x007D3880 0x007D388C and zeroing +0x10..0x1C. Caller 0x00151137 member at +0xB8 in Sas ctor.

class M1
{
public:
	virtual void dummy();
};

class M2
{
public:
	virtual void dummy();
};

class M3
{
public:
	virtual void dummy();
};

class Rva0014F40C
{
public:
	Rva0014F40C();
	virtual void dummy();
private:
	M1 m_04;
	M2 m_08;
	M3 m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
};

Rva0014F40C::Rva0014F40C()
	: m_04()
	, m_08()
	, m_0c()
	, m_10(0)
	, m_14(0)
	, m_18(0)
	, m_1c(0)
{
}
