// cl: /DNDEBUG /MD
// ?rva0031AEAE@ControlBar@@QAEXPAH0@Z @ 0x0031AEAE 27B: ControlBar copy
// +0x288/+0x28C to out params. Evidence: gap between 0x0031AE13 and
// 0x0031AEC9 plus caller 0x0009FA82 plus ret 8 two-pointer shape.
class ControlBar
{
public:
	void rva0031AEAE(int *a, int *b);

private:
	char m_pad00[0x288];
	int m_0288;
	int m_028C;
};

void ControlBar::rva0031AEAE(int *a, int *b)
{
	*a = m_0288;
	*b = m_028C;
}
