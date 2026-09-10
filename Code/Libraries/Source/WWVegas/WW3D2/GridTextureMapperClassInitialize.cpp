// cl: /O2 /arch:SSE2 /G7 /MD
//
// GridTextureMapperClass::initialize, retail 0x00182480, 261 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies.
// Extra BFME dword at +0xC is the fps value stored by movss.

#include <math.h>

class WW3D
{
public:
	static unsigned int SyncTime;
	static unsigned int Get_Sync_Time() { return SyncTime; }
};

class RefCountClass
{
public:
	virtual ~RefCountClass();
	int NumRefs;
};

class TextureMapperClass : public RefCountClass
{
public:
	virtual ~TextureMapperClass();
	unsigned Stage;
};

class GridTextureMapperClass : public TextureMapperClass
{
protected:
	void initialize(float fps, unsigned int gridwidth_log2);

	float Fps;
	int Sign;
	unsigned MSPerFrame;
	float OOGridWidth;
	unsigned GridWidthLog2;
	unsigned LastFrame;
	unsigned Offset;
	unsigned Remainder;
	unsigned CurrentFrame;
	unsigned LastUsedSyncTime;
};

void GridTextureMapperClass::initialize(float fps, unsigned int gridwidth_log2)
{
	unsigned int grid_width = (1u << gridwidth_log2);

	if (LastFrame == 0)
		LastFrame = (grid_width * grid_width);
	Offset = Offset % LastFrame;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
	GridWidthLog2 = gridwidth_log2;
	OOGridWidth = 1.0f / (float)grid_width;
	Fps = fps;
	if (fps == 0.0f) {
		Sign = 0;
		MSPerFrame = 1;
		CurrentFrame = Offset;
	} else if (fps < 0.0f) {
		Sign = -1;
		MSPerFrame = (unsigned int)(1000.0f / fabs(fps));
		CurrentFrame = (LastFrame - 1) - Offset;
	} else {
		Sign = 1;
		MSPerFrame = (unsigned int)(1000.0f / fabs(fps));
		CurrentFrame = Offset;
	}
	Remainder = 0;
}
