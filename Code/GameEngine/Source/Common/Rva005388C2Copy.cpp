// cl: /MD
// ??0Rva005388C2@@QAE@ABV0@@Z @0x005388C2 53B
// Holder copy ctor via rowed Rva005386F5 vector copy then byte and conditional region float copy.
// Evidence: callee 0x005386F5 row Rva005386F5; caller none; prev reserve Float4 next slot4; layout matches Rva005386B7Swap.
class Rva005386F5
{
public:
	Rva005386F5(const Rva005386F5 &other);
private:
	void *m_p1;
	void *m_p2;
	void *m_p3;
};
struct Region2D
{
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};
class Rva005388C2
{
public:
	Rva005388C2(const Rva005388C2 &other);
private:
	Rva005386F5 m_vec;
	Region2D m_region;
	float m_1c;
	unsigned char m_20;
};
Rva005388C2::Rva005388C2(const Rva005388C2 &other)
	: m_vec(other.m_vec)
{
	m_20 = other.m_20;
	if (other.m_20 == 0) {
		m_region = other.m_region;
		m_1c = other.m_1c;
	}
}
