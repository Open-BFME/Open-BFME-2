// W3DDisplay: canonical declarations for the members 29 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_W3DDISPLAY_H
#define CANONICAL_W3DDISPLAY_H

class Image;

class W3DDisplay
{
public:
	void rva0004D664(float x0, float y0, float x1, float y1, float w, int color);
	void rva0004D6B3(Image *image, float startX, float startY, float endX, float endY, int color = -1, int mode = 2);
	void rva0008EEF0(float x0, float y0, float w, float h, float a1, int a0);
	void rva0025D2F6();
	void takeScreenShot(const char *filename);
private:
	void rva00045213(char *image, unsigned int rowBytes);
	void rva00047BC0(char *image, unsigned int width, unsigned int height, const char *filename);
};

#endif // CANONICAL_W3DDISPLAY_H
