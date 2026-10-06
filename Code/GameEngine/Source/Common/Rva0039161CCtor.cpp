// cl: /O1 /MD /arch:SSE /G7
// ??0Rva0039161C@@QAE@PBX0M_N@Z @0x0039161C 65B ctor stores vtable 0x00C1A05C copies 3 dwords from param clears +4 caller 0x003948EB
struct Rva0039161CBase
{
	int m_04;
	Rva0039161CBase() : m_04(0) {}
};
class Rva0039161C : public Rva0039161CBase
{
public:
	Rva0039161C(void const *p1, void const *p2, float f, bool b);
	virtual ~Rva0039161C();
private:
	int m_08;
	int m_0c;
	int m_10;
	void const *m_14;
	float m_18;
	bool m_1c;
	bool m_1d;
};
Rva0039161C::Rva0039161C(void const *p1, void const *p2, float f, bool b)
{
	int const *q = (int const *)p1;
	m_08 = q[0];
	m_0c = q[1];
	m_10 = q[2];
	m_14 = p2;
	m_18 = f;
	m_1c = b;
	m_1d = true;
}
