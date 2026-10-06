// cl: /EHs-c-
// ??0Rva003ADC4F@@QAE@ABV0@@Z @0x003ADC4F 38B copy ctor via rowed base 0x003ADC75 with three derived stores. Evidence: callee rowed; caller 0x003ADC44; chain from just-landed 0x003ADC75.
class Rva003ADC75
{
public:
	Rva003ADC75(const Rva003ADC75 &other);
private:
	char m_pad[176];
};
extern const void *const g_00C1C904[];
extern const void *const g_00C1C900[];
class Rva003ADC4F : public Rva003ADC75
{
public:
	Rva003ADC4F(const Rva003ADC4F &other);
};
Rva003ADC4F::Rva003ADC4F(const Rva003ADC4F &other)
	: Rva003ADC75(other)
{
	*(const void **)this = g_00C1C904;
	*(const void **)((char *)this + 8) = g_00C1C900;
	*(const char **)((char *)this + 12) = "HZz";
}
