// cl: /MD /EHsc
// ??1RoadType@@QAE@XZ retail 0x000D4F4F 108B
// RoadType dtor (TU-local replica, mangles identically). Under EH state 1 the
// two ref-counted render buffers at +8 and +0xC are released inline
// (decrement the count at +4, slot-0 Delete_This at zero) and cleared; then
// the two texture handle members at +4 and +0 run their inline dtors, each
// calling the rowed ?Release_Ref@TextureClass@@QAEXXZ 0x0061ED10.

class TextureClass
{
public:
	void Release_Ref();
};

class RoadTypeRefCounted
{
public:
	virtual void Delete_This();

	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}

	int m_numRefs; // +0x04
};

class RoadTypeTextureHandle
{
public:
	~RoadTypeTextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	TextureClass *m_texture;
};

class RoadType
{
public:
	~RoadType();

private:
	RoadTypeTextureHandle m_roadTexture; // +0x00
	RoadTypeTextureHandle m_capTexture; // +0x04
	RoadTypeRefCounted *m_vertexRoad; // +0x08
	RoadTypeRefCounted *m_indexRoad; // +0x0C
};

RoadType::~RoadType()
{
	if (m_vertexRoad)
	{
		m_vertexRoad->Release_Ref();
		m_vertexRoad = 0;
	}
	if (m_indexRoad)
	{
		m_indexRoad->Release_Ref();
		m_indexRoad = 0;
	}
}
