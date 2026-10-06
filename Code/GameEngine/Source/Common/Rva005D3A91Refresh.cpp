// cl: /MD /EHsc
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	void *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
};
class Rva005D388B
{
public:
	TreeHintRef00217D4C rva005D388B();
	void *m_ptr;
};
class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &v);
};
class Rva005D3A91
{
public:
	void rva005D3A91();
private:
	char m_00[0x18];
	void *m_18;
	TreeHintRef00217D4C m_1C;
	char m_pad20[0x24 - 0x20];
	Rva005D388B m_24;
};
void Rva005D3A91::rva005D3A91()
{
	if (m_18 == 0)
		return;
	if (m_24.m_ptr == 0)
		return;
	m_1C = m_24.rva005D388B();
	if (m_1C.m_ptr == 0)
		return;
	((Rva001FF3A9 *)m_18)->rva001FF3A9(m_1C);
}
