// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D9531@Rva002D9531@@QAEXH@Z @ 0x002D9531 28B
// Conditional dword setter: if state at +0x38 is 2 or 6 store arg at +0x34 and set state to 2.
// Evidence: honest address name; __thiscall via ecx use and ret 4; callers in FUN_005f1634 and others; neighbours Disp8DwordFieldSetters.cpp and ConstZeroGetters.cpp.
class Rva002D9531
{
public:
	void rva002D9531(int value);
	char m_pad[0x34];
	int m_value;
	int m_state;
};
void Rva002D9531::rva002D9531(int value)
{
	if (m_state == 2 || m_state == 6) {
		m_value = value;
		m_state = 2;
	}
}

struct Rva002D9508Twelve
{
	int v0, v1, v2;
};

class Rva002D9508
{
public:
	void rva002D9508(const void *src);
	char m_pad[0x38];
	int m_state;
	Rva002D9508Twelve m_data;
	unsigned char m_flag;
};

void Rva002D9508::rva002D9508(const void *src)
{
	if (src != 0 && (m_state == 0 || m_state == 6))
	{
		m_data = *(const Rva002D9508Twelve *)src;
		m_state = 0;
		m_flag = 1;
	}
}
