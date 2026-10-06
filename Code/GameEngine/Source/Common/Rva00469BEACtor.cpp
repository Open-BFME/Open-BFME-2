// cl: /MD
// ??0Rva00469BEA@@QAE@ABHABVRva00469155@@@Z 0x00469BEA 29B evidence: chain via operator= 0x46916D; caller 0x473FAF passes int and Rva stack record
class Rva00469155
{
public:
	Rva00469155 &operator=(const Rva00469155 &o);

private:
	struct Float3
	{
		float x;
		float y;
		float z;
	};
	Float3 m_pos;
	int m_0C;
};

class Rva00469BEA
{
public:
	Rva00469BEA(const int &a, const Rva00469155 &b);
	Rva00469BEA(const Rva00469BEA &o);

private:
	int m_00;
	Rva00469155 m_04;
};

Rva00469BEA::Rva00469BEA(const int &a, const Rva00469155 &b) : m_00(a)
{
	m_04 = b;
}

Rva00469BEA::Rva00469BEA(const Rva00469BEA &o) : m_00(o.m_00)
{
	m_04 = o.m_04;
}
