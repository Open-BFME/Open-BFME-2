// cl: /MD
// ??0Rva00584C42@@QAE@XZ @0x00584C42 39B
// Ctor with vtable 0x0086FCDC plus bool at +4 plus floats at +8 +0xc from globals 0x7C736C 0x7C672C.
// Evidence: frameless movss plus vtable store plus bool clear; caller @0x00469233.
class Rva00584C42
{
public:
	Rva00584C42();
	virtual ~Rva00584C42();
private:
	bool m_flag; // +4
	float m_a; // +8
	float m_b; // +0xc
};

Rva00584C42::Rva00584C42()
{
	m_flag = false;
	m_a = 40.0f;
	m_b = 15.0f;
}
