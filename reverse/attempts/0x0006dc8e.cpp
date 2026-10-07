// ?updateView@Rva000677CAHost@@QAEX_NHHHH@Z
// partial score=1.0 date=2026-10-08
// cl: /O1 /Oy- /DNDEBUG /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
#include <vector>
struct Rva0006DC8EDimensions {char opaque00[8]; int width; int height;};
class Rva000677CAHost
{
public:
    void updateView(bool partial, int minX, int maxX, int minY, int maxY);
	bool rva000677CA(int a, int b, float f);
	void rva00067494(int a1, int a2, int a3, int a4, int a5, int a6, unsigned char *p, bool *out);
private:
    char opaque00[0x37A0];
    float slope;
    char opaque37A4[0x37C0-0x37A4];
    Rva0006DC8EDimensions *map;
    char opaque37C4[0x3800-0x37C4];
    _STL::vector<bool> bits;
};

bool Rva000677CAHost::rva000677CA(int a, int b, float f)
{
	bool out = false;
	unsigned char *p = &((unsigned char *)&f)[3];
	int fi = (int)f;
	rva00067494(a, b, 0x100, 0, fi, 0, p, &out);
	return out == false;
}

void Rva000677CAHost::updateView(bool partial, int minX, int maxX, int minY, int maxY)
{
    int xSize=map->width;
    int ySize=map->height;
    if (bits.size()!=xSize*ySize)
        bits.resize(xSize*ySize);
    if (!partial) {
        minX=0; minY=0; maxX=xSize; maxY=ySize;
    }
    for (int j=minY; j<maxY; ++j)
        for (int i=minX; i<maxX; ++i)
            bits[i+j*xSize]=rva000677CA(i,j,slope);
}
