// W3DDisplay: canonical declarations for the members units call through private views of it;
// each call resolves to the unit's ledger row or pin. Only the retail size, m_averageFPS and two debug-string
// tables are laid out; everything else, the vptr and the Display base included, stays opaque storage.
#ifndef CANONICAL_W3DDISPLAY_H
#define CANONICAL_W3DDISPLAY_H

class DisplayString;
class Image;
class RTS2DScene;
class RTS3DInterfaceScene;
class RTS3DScene;

class W3DDisplay
{
public:
	W3DDisplay();
	void updateAverageFPS();
	void rva0004387E();
	void drawAnimStats();
	void rva0004D664(float x0, float y0, float x1, float y1, float w, int color);
	void rva0004D6B3(Image *image, float startX, float startY, float endX, float endY, int color = -1, int mode = 2);
	void rva0008EEF0(float x0, float y0, float w, float h, float a1, int a0);
	void rva0025D2F6();
	void takeScreenShot(const char *filename);

	// The scene globals (static data members: no layout). Retail .data, each zero-filled and rowed in
	// reverse/data_rows.csv at its one defining unit: m_3DScene RVA 0x009E1B34 (76 read/write xrefs),
	// m_2DScene 0x009E1B38 (4), m_3DInterfaceScene 0x009E1B3C (9), per reverse/data_xrefs.tsv; all three are
	// written by W3DDisplay::init (0x00046A50) and W3DDisplay::W3DDisplay (0x00049DEA).
	static RTS3DScene *m_3DScene;
	static RTS2DScene *m_2DScene;
	static RTS3DInterfaceScene *m_3DInterfaceScene;
private:
	void rva00045213(char *image, unsigned int rowBytes);
	void rva00047BC0(char *image, unsigned int width, unsigned int height, const char *filename);

	// Retail allocates 0x2B0 bytes (factory 0x0004C45D); the constructor 0x00049DEA and
	// updateAverageFPS 0x000437A1 write the float at +0x180.
	unsigned char m_opaque000[0x180];
	float m_averageFPS;
	unsigned char m_opaque184[0x18C - 0x184];
	// Debug-string tables of 16 and 25 entries: the destructor 0x00049FCB frees each through the
	// display-string manager; rva0004387E and drawAnimStats (0x00043BF9) draw them.
	DisplayString *m_18C[16];
	unsigned char m_opaque1CC[0x1D0 - 0x1CC];
	DisplayString *m_1D0[25];
	unsigned char m_opaque234[0x2B0 - 0x234];
};

#endif // CANONICAL_W3DDISPLAY_H
