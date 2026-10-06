// cl: /O1 /G7 /EHsc /MD /arch:SSE
// Display.cpp -- Display members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. Three static-image slots of 0x18 bytes start at +0x68;
// each draws through its rowed method (0x0025C829) with the display.

typedef int Int;

class W3DDisplay;

class Rva0025C6E2Elem
{
public:
	void rva0025C829(W3DDisplay *display, Int arg);	// 0x0025C829

private:
	unsigned char m_data[0x18];
};

enum { MAX_STATIC_IMAGES = 3 };

class Display
{
public:
	void DrawStaticImage(Int index, Int arg);

private:
	unsigned char m_pad00[0x68];
	Rva0025C6E2Elem m_staticImages[MAX_STATIC_IMAGES];	// +0x68
};

// Display::DrawStaticImage, retail 0x0025D33B.
void Display::DrawStaticImage(Int index, Int arg)
{
	if (index < MAX_STATIC_IMAGES)
		m_staticImages[index].rva0025C829((W3DDisplay *)this, arg);
}
