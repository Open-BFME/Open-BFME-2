// cl: /DNDEBUG /MD
// ?rva0031AE93@ControlBar@@QAEXPAH0@Z @ 0x0031AE93 27B: ControlBar copy
// +0x280/+0x284 to out params. Evidence: sibling 0x0031AEAE shares
// two-out shape plus caller 0x0009FB63 plus ret 8.
class ControlBar
{
public:
	void rva0031AE93(int *a, int *b);

private:
	char m_pad00[0x280];
	int m_0280;
	int m_0284;
};

void ControlBar::rva0031AE93(int *a, int *b)
{
	*a = m_0280;
	*b = m_0284;
}
