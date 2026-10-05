// cl: /O1 /DNDEBUG /MD
// ?rva0039ACA4@Rva0039ACA4@@QAEXPBV1@@Z 0x0039ACA4 25B copy of +0x10/+0x1C via +0x264 pointer
// Evidence: callers at 0x0047E7A0 and 0x0047E8C7 pass outer object; this is its +0x264 inner; retail copies inner+0x1C then inner+0x10.

class Rva0039ACA4
{
public:
	void rva0039ACA4(Rva0039ACA4 const *src);
private:
	char m_pad00[0x10];
	int m_10;
	char m_pad14[0x1C - 0x14];
	int m_1C;
	char m_pad20[0x264 - 0x20];
	Rva0039ACA4 const *m_264;
};

void Rva0039ACA4::rva0039ACA4(Rva0039ACA4 const *src)
{
	Rva0039ACA4 const *inner = src->m_264;
	m_1C = inner->m_1C;
	m_10 = inner->m_10;
}
