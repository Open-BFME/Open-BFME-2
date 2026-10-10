// ??0W3DStatusCircle@@QAE@XZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Retail 0x0008E54F, 97 bytes. Identity: W3DStatusCircle (RenderObjClass
// derived; rowed methods updateScreenVB 0x8E335 / updateCircleVB 0x8E623
// use the same +0xC4 triangle count, +0xE4 screen VB). Layout facts from
// target: base ctor RenderObjClass() 0x13BF00, vptrs 0xBC7850/+0 and
// 0xBC784C/+8, -1.0f at +0xCC/+0xD0, shader bits 0x10441B at +0xD8, other
// fields zero. Donor (BF1/ZH W3DStatusCircle ctor) only nulls the four
// buffer pointers; the -1.0f pair and +0xD4 are BFME 2 additions whose
// names are unknown (fieldCC/fieldD0/fieldD4).

class RefCountClass
{
public:
	RefCountClass();
	virtual void Delete_This();
	virtual ~RefCountClass();
	int NumRefs;
};

class MultiListObjectClass
{
public:
	MultiListObjectClass();
	virtual ~MultiListObjectClass();
	void *ListNode;
};

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	RenderObjClass();
	virtual int Class_ID() const;
	virtual ~RenderObjClass();

protected:
	char m_tail[0xB4];
};

struct StatusShaderBits
{
	StatusShaderBits() : bits(0x10441B) {}
	unsigned int bits;
};

class W3DStatusCircle : public RenderObjClass
{
public:
	W3DStatusCircle();
	virtual ~W3DStatusCircle();

private:
	int m_numTriangles;
	void *m_indexBuffer;
	float fieldCC;
	float fieldD0;
	int fieldD4;
	StatusShaderBits m_shaderClass;
	void *m_vertexMaterialClass;
	void *m_vertexBufferCircle;
	void *m_vertexBufferScreen;
};

W3DStatusCircle::W3DStatusCircle() :
	m_numTriangles(0), m_indexBuffer(0), fieldCC(-1.0f), fieldD0(-1.0f), fieldD4(0)
{
	m_vertexMaterialClass = 0;
	m_vertexBufferCircle = 0;
	m_vertexBufferScreen = 0;
}
