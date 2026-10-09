// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [00113C07,00113DE0),473B, RET44. WorldBuilder places the body in
// W3DTerrainBackground.cpp (unnamed there). It asks checkUnsetEdges
// (0x00112FC0) which edges of the square (x, y, width) are open, then hands
// one or two halves of the square to the recursive filler 0x00113399
// (rectangle form of ZH fillVBRecursive: index buffer, auxiliary buffer,
// x, y, w, h, ndx, curIndex) and reports through four flags which quarter
// edges it has emitted. The flag order, half splits and argument
// pass-through are target facts; method names are address-derived.

class Rva00112ED3TerrainPrefix
{
public:
	void checkUnsetEdges(int xOffset, int yOffset, int width,
		bool *top, bool *right, bool *bottom, bool *left);
};

class W3DTerrainBackground
{
public:
	void rva00113399(unsigned short *ib, void *aux, int x, int y, int w, int h,
		unsigned short *ndx, int &curIndex);
	void rva00113C07(unsigned short *ib, void *aux, int x, int y, int width,
		bool *done0, bool *done1, bool *done2, bool *done3,
		unsigned short *ndx, int &curIndex);
};

void W3DTerrainBackground::rva00113C07(unsigned short *ib, void *aux, int x, int y, int width,
	bool *done0, bool *done1, bool *done2, bool *done3,
	unsigned short *ndx, int &curIndex)
{
	*done3 = false;
	*done2 = false;
	*done1 = false;
	*done0 = false;

	bool top, right, bottom, left;
	((Rva00112ED3TerrainPrefix *)this)->checkUnsetEdges(x, y, width, &top, &right, &bottom, &left);
	int half = width / 2;

	if (right) {
		if (top) {
			rva00113399(ib, aux, x, y, half, width, ndx, curIndex);
			rva00113399(ib, aux, x, y + half, width, half, ndx, curIndex);
			*done3 = true;
		} else if (bottom) {
			rva00113399(ib, aux, x, y + half, width, half, ndx, curIndex);
			rva00113399(ib, aux, x + half, y, half, width, ndx, curIndex);
			*done2 = true;
		} else {
			rva00113399(ib, aux, x, y + half, width, half, ndx, curIndex);
			*done3 = true;
			*done2 = true;
		}
	} else if (left) {
		if (top) {
			rva00113399(ib, aux, x, y, half, width, ndx, curIndex);
			rva00113399(ib, aux, x, y, width, half, ndx, curIndex);
			*done1 = true;
		} else {
			rva00113399(ib, aux, x, y, width, half, ndx, curIndex);
			if (bottom) {
				rva00113399(ib, aux, x + half, y, half, width, ndx, curIndex);
			} else {
				*done1 = true;
			}
			*done0 = true;
		}
	} else if (top) {
		*done3 = true;
		*done1 = true;
		rva00113399(ib, aux, x, y, half, width, ndx, curIndex);
		return;
	} else if (bottom) {
		*done2 = true;
		*done0 = true;
		rva00113399(ib, aux, x + half, y, half, width, ndx, curIndex);
		return;
	} else {
		*done3 = true;
		*done2 = true;
		*done1 = true;
		*done0 = true;
	}
}
