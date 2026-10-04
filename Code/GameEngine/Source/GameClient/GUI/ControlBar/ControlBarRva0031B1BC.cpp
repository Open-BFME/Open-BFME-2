// cl: /O1 /DNDEBUG /MD
// ?rva0031B1BC@ControlBar@@QAEXPBVImage@@0000000@Z @0x0031B1BC 84B ControlBar image slots set then refresh.
// Evidence: 8 dword stores +0x250 +0x254 +0x258 +0x25C +0x260 +0x264 +0x270 +0x274 then rowed rva0031AE13 0x0031AE13; ret 0x20; caller 0x0031EDD6; layout precedent Rva0031AE13 and Rva0031AA86.
class Image;

class ControlBar
{
public:
	void rva0031AE13();
	void rva0031B1BC(const Image *a250, const Image *a254, const Image *a258, const Image *a25c, const Image *a260, const Image *a264, const Image *a270, const Image *a274);
private:
	char m_pad00[0x24];
	int m_0024;
	char m_pad28[0x250 - 0x28];
	const Image *m_p0250;
	const Image *m_p0254;
	const Image *m_p0258;
	const Image *m_p025C;
	const Image *m_p0260;
	const Image *m_p0264;
	char m_pad268[0x270 - 0x268];
	const Image *m_p0270;
	const Image *m_p0274;
};

void ControlBar::rva0031B1BC(const Image *a250, const Image *a254, const Image *a258, const Image *a25c, const Image *a260, const Image *a264, const Image *a270, const Image *a274)
{
	m_p0250 = a250;
	m_p0254 = a254;
	m_p0258 = a258;
	m_p025C = a25c;
	m_p0260 = a260;
	m_p0264 = a264;
	m_p0270 = a270;
	m_p0274 = a274;
	rva0031AE13();
}
