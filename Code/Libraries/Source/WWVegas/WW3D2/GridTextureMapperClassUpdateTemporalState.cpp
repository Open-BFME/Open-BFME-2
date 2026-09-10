// cl: /O2 /G7 /MD
//
// GridTextureMapperClass::update_temporal_state, retail 0x00182590, 69 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies.

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
	void update_temporal_state();

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

void GridTextureMapperClass::update_temporal_state()
{
	unsigned int now = WW3D::Get_Sync_Time();
	unsigned int delta = now - LastUsedSyncTime;
	Remainder += delta;
	LastUsedSyncTime = now;

	int new_frame = (int)CurrentFrame + ((int)(Remainder / MSPerFrame) * Sign);
	new_frame = (int)((unsigned)new_frame % LastFrame);

	if (new_frame < 0)
		CurrentFrame = LastFrame + new_frame;
	else
		CurrentFrame = (unsigned int)new_frame;
	Remainder = Remainder % MSPerFrame;
}
