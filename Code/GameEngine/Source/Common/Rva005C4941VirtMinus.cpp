// cl: /O1
// ?rva005C4941@Rva005C4941@@QAEHXZ 0x005C4941 12B evidence: gap between ptr-chase getter 0x005C493A and dword clearer 0x005C494D; thiscall int() via virtual slot 0 minus dword at +0x14; honest Rva name
class Rva005C4941
{
public:
	virtual int v0();
	int rva005C4941();

private:
	char m_04[0x10];
	int m_14;
};

int Rva005C4941::rva005C4941()
{
	return v0() - m_14;
}
