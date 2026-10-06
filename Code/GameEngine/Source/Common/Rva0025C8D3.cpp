// cl: /MD
// ?rva0025C8D3@Rva0025C6E2Elem@@QAEXPAVW3DDisplay@@HH@Z @0x0025C8D3 171B
// Element image draw: early-out on null image or id mismatch, then single
// W3DDisplay draw call whose four float coords are unsigned virtual results
// scaled by the element floats. Evidence: this layout int+4 floats+int matches
// Rva0025C6E2Elem in Rva0025C6E2.cpp; callee W3DDisplay::rva0004D6B3 0x0004D6B3
// row W3DDisplayDrawImageMode.cpp; virtual slots 0x40/0x44 no-arg unsigned;
// float const 0x007C26EC is 2^32 for unsigned conversion; caller 0x0025D2F0.
class Image;

class W3DDisplay
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual unsigned unused16();
	virtual unsigned unused17();
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
};

class Rva0025C6E2Elem
{
public:
	void rva0025C8D3(W3DDisplay *disp, int id, int color);
	void rva0025C829(W3DDisplay *disp, int id);
private:
	Image *m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	int m_14;
};
void Rva0025C6E2Elem::rva0025C8D3(W3DDisplay *disp, int id, int color)
{
	if (m_00 == 0)
		return;
	if (id != m_14)
		return;
	disp->rva0004D6B3(m_00,
		(float)(unsigned)disp->unused16() * m_04,
		(float)(unsigned)disp->unused17() * m_08,
		(float)(unsigned)disp->unused16() * m_0c,
		(float)(unsigned)disp->unused17() * m_10,
		color, 2);
}

void Rva0025C6E2Elem::rva0025C829(W3DDisplay *disp, int id)
{
	if (m_00 == 0)
		return;
	if (id != m_14)
		return;
	disp->rva0004D6B3(m_00,
		(float)(unsigned)disp->unused16() * m_04,
		(float)(unsigned)disp->unused17() * m_08,
		(float)(unsigned)disp->unused16() * m_0c,
		(float)(unsigned)disp->unused17() * m_10,
		-1, 2);
}
