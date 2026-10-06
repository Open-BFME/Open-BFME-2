// cl: /EHsc
// ?rva000B49F9@Rva000B49F9@@QAEEXZ, RVA 0x000B49F9, 35 bytes.
// Flag check: if ModelConditionFlags at +4 fails return true, if byte at
// +0x64 set return true, else return bit5 of dword at +0x5C. Evidence: rowed
// pin callee ModelConditionFlags 0x000B3EB3, callers 0x00078C33 0x000BF27B,
// LINK BONUS via 0x00078C10 (1175B file). Layout from immediates.
class ModelConditionFlags
{
public:
	bool rva000B3EB3() const;
};
class Rva000B49F9
{
public:
	unsigned char rva000B49F9();
private:
	char m_pad00[0x5C];
	unsigned int m_5C;
	char m_pad60[0x64 - 0x60];
	unsigned char m_64;
};
unsigned char Rva000B49F9::rva000B49F9()
{
	if (!((ModelConditionFlags *)((char *)this + 4))->rva000B3EB3())
		return 1;
	else if (*(unsigned char *)((char *)this + 0x64))
		return 1;
	else
	{
		unsigned char r = (unsigned char)((*(unsigned int *)((char *)this + 0x5C) >> 5) & 1);
		return r;
	}
}
