// cl: /MD
// ?rva0037F4EA@Rva0037F4EA@@QAEPAV1@H@Z retail 0x0037F4EA 48B
// Evidence: callers 0x0037F90F 0x0037F985 pass dword from +0x12c; zeroes six floats plus bool; second instance at +0x20
class Rva0037F4EA
{
public:
	Rva0037F4EA *rva0037F4EA(int v);
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

Rva0037F4EA *Rva0037F4EA::rva0037F4EA(int v)
{
	m_00 = v;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0c = 0.0f;
	m_10 = 0.0f;
	m_14 = 0.0f;
	m_18 = 0.0f;
	m_1c = false;
	return this;
}
