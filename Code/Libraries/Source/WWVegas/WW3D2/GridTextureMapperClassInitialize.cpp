// cl: /MD
//
// GridTextureMapperClass::initialize, retail 0x00182480, 261 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies.
// Extra BFME dword at +0xC is the fps value stored by movss.

// Keep MSVC's float overloads local; the inlined fabs operations remain exact.
#define inline static inline
#include <math.h>
#undef inline

class WW3D
{
public:
private:
	static unsigned int SyncTime;
public:
	static unsigned int Get_Sync_Time() { return SyncTime; }
};

class RefCountClass
{
public:
	virtual void Delete_This();
protected:
	virtual ~RefCountClass();
private:
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
	// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
	// the anchor keeps the noinline body emitted.
	__declspec(noinline) void initialize(float fps, unsigned int gridwidth_log2)
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
	friend void bfmeAnchorGridTextureMapperInitialize(GridTextureMapperClass *, float, unsigned int);

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

struct GridTextureMapperInitializeAccess : GridTextureMapperClass
{
	using GridTextureMapperClass::initialize;
};

#pragma inline_depth(0)
// ?bfmeAnchorGridTextureMapperInitialize absent-from-retail
void bfmeAnchorGridTextureMapperInitialize(GridTextureMapperClass *gridTextureMapper, float fps, unsigned int gridwidth_log2)
{
	reinterpret_cast<GridTextureMapperInitializeAccess *>(gridTextureMapper)->initialize(fps, gridwidth_log2);
}
#pragma inline_depth()
