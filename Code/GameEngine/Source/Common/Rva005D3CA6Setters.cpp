// cl: /MD
struct TreeHintRef00217D4C
{
	void *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};
class Rva005D3AF2
{
public:
	void rva005D3AF2();
};
class Rva005D3B26
{
public:
	void rva005D3A91();
};
class Rva005D3CA6
{
public:
	void rva005D3CA6(void *v);
	void rva005D3DD5(const TreeHintRef00217D4C &v);
private:
	char m_00[0x18];
	void *m_18;
	char m_1C[0x24 - 0x1C];
	TreeHintRef00217D4C m_24;
	char m_28[0x30 - 0x28];
	bool m_30;
	char m_31;
	bool m_32;
};
void Rva005D3CA6::rva005D3CA6(void *v)
{
	if (v == m_18)
		return;
	((Rva005D3AF2 *)this)->rva005D3AF2();
	m_18 = v;
	if (m_32)
		((Rva005D3B26 *)this)->rva005D3A91();
}
void Rva005D3CA6::rva005D3DD5(const TreeHintRef00217D4C &v)
{
	if (m_30)
		((Rva005D3AF2 *)this)->rva005D3AF2();
	m_24 = v;
	if (m_30 && m_32)
		((Rva005D3B26 *)this)->rva005D3A91();
}
