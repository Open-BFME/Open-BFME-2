// cl: /O2 /G7 /MD
//
// GridTextureMapperClass::update_temporal_state, retail 0x00182590, 69 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies.

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
	void update_temporal_state();
	friend void _bfmeGridTextureMapperUpdateTemporalStateInlineAnchor(GridTextureMapperClass *mapper);

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

inline void GridTextureMapperClass::update_temporal_state(void)
{
	unsigned int now = WW3D::Get_Sync_Time();
	unsigned int delta = now - LastUsedSyncTime;
	Remainder += delta;
	LastUsedSyncTime = now;

	int new_frame = (int)CurrentFrame + ((int)(Remainder / MSPerFrame) * Sign);
	new_frame=new_frame % LastFrame;

	if (new_frame<0) {
		CurrentFrame=LastFrame+new_frame;
	} else {
		CurrentFrame=(unsigned int) new_frame;
	}
	Remainder = Remainder % MSPerFrame;
}

struct GridTextureMapperTemporalAccess : GridTextureMapperClass
{
	using GridTextureMapperClass::update_temporal_state;
};

// This method is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeGridTextureMapperUpdateTemporalStateInlineAnchor@@YAXPAVGridTextureMapperClass@@@Z absent-from-retail
void _bfmeGridTextureMapperUpdateTemporalStateInlineAnchor(GridTextureMapperClass *mapper)
{
	reinterpret_cast<GridTextureMapperTemporalAccess *>(mapper)->update_temporal_state();
}
#pragma inline_depth()
