// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D94EB@Rva002D94EB@@QAEXM@Z @ 0x002D94EB 19B
// Float subtract setter: m_64 -= value via movss/subss/movss.
// Evidence: honest address name; __thiscall void float with SSE; caller in FUN_00453646; neighbours Rva002D94E4MulGetter.cpp and Disp8DwordFieldSetters.cpp.
class Rva002D94EB
{
public:
	void rva002D94EB(float value);
	char m_pad[0x64];
	float m_64;
};
void Rva002D94EB::rva002D94EB(float value)
{
	m_64 -= value;
}
