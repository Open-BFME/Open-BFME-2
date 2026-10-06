// cl: /MD
// ?rva0037F51A@Rva0037F51A@@QAEAAV1@ABV1@@Z retail 0x0037F51A 55B
// Evidence: same 0x20 layout as 0x0037F4EA (int plus six floats plus bool); callers 0x0037F551 0x0037F950 copy twice each
class Rva0037F51A
{
public:
	Rva0037F51A &rva0037F51A(const Rva0037F51A &src);
private:
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	bool m_1c;
};

Rva0037F51A &Rva0037F51A::rva0037F51A(const Rva0037F51A &src)
{
	m_00 = src.m_00;
	m_04 = src.m_04;
	m_08 = src.m_08;
	m_0c = src.m_0c;
	m_10 = src.m_10;
	m_14 = src.m_14;
	m_18 = src.m_18;
	m_1c = src.m_1c;
	return *this;
}
