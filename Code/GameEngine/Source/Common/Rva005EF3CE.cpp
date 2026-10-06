// cl: /MD /EHsc
// ?rva005EF3CE@Rva005EF3CE@@QAEHH@Z retail 0x005EF3CE 16B
// Evidence: array-index getter mov eax,[ecx+4]; mov eax,[eax+0x24]; mov eax,[eax+ecx*4] ret 4; caller 0x005E1B4E passes loop index and pushes result; neighbours Rva005EF283/Rva005EF3DE same TU flags.
struct Rva005EF3CEInner
{
	char m_pad[36];
	int *m_arr24;
};

class Rva005EF3CE
{
public:
	int rva005EF3CE(int index);
private:
	int m_pad00;
	Rva005EF3CEInner *m_ptr04;
};

int Rva005EF3CE::rva005EF3CE(int index)
{
	return m_ptr04->m_arr24[index];
}
