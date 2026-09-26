// ??1W3DProjectileStreamDraw@@UAE@XZ
// partial score=0.95 date=2026-09-26
// ??1W3DProjectileStreamDraw@@UAE@XZ
// partial score=0.95 date=2026-09-26
// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1W3DProjectileStreamDraw@@UAE@XZ, retail 0x000D146B, 142 bytes.
// Dtor completing the W3DProjectileStreamDraw file-unit (ctor rowed at
// 0xD1370, pool key at 0xD140A, deleting dtor unclaimed at 0xD144F slot 0
// of vtable 0x7CE010).
//
// Donor: Zero Hour W3DProjectileStreamDraw.cpp dtor (loop over m_allLines
// with Peek_Scene at +0x48, Remove_Render_Object via W3DDisplay::m_3DScene,
// REF_PTR_RELEASE, then texture Release_Ref). BFME2 layout from ctor TU:
// Rva000B19A1 base size 0xC (vtable 0x7C9690), texture at +0x0C, 0x14 lines
// at +0x10, count at +0x60. Base dtor folded at 0x49B47C (twin pin
// ??1Rva000B19A1). Texture Release_Ref rowed at 0x61ED10.

class Thing;
class ModuleData;

class Rva000B19A1
{
public:
	virtual ~Rva000B19A1();

protected:
	void *m_unk04;
	int m_unk08;
};

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
	int m_pad[2];
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(0) {}
	const RefCountPtr &operator=(const RefCountPtr &other);
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }

public:
	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

class SegmentedLineClass
{
public:
	virtual void Delete_This();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void *Peek_Scene();

	void Release_Ref()
	{
		if (--m_refCount == 0)
			Delete_This();
	}

private:
	int m_refCount;
};

class SceneClass
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void Remove_Render_Object(SegmentedLineClass *line);
};

class W3DDisplay
{
public:
	static SceneClass *m_3DScene;
};

class W3DProjectileStreamDraw : public Rva000B19A1
{
public:
	virtual ~W3DProjectileStreamDraw();

private:
	RefCountPtr<TextureClass> m_texture;
	SegmentedLineClass *m_allLines[0x14];
	int m_linesValid;
};

// ??1W3DProjectileStreamDraw@@UAE@XZ
W3DProjectileStreamDraw::~W3DProjectileStreamDraw()
{
	for (int lineIndex = 0; lineIndex < m_linesValid; lineIndex++)
	{
		SegmentedLineClass *deadLine = m_allLines[lineIndex];
		if (deadLine)
		{
			if (deadLine->Peek_Scene())
				W3DDisplay::m_3DScene->Remove_Render_Object(deadLine);
			deadLine->Release_Ref();
		}
	}
}
