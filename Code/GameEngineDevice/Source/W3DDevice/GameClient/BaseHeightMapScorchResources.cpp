// cl: /O1 /MD /EHsc
// Native6B3F3..6B4CC full217 including EH2; BFME1 f989
// BaseHeightMapRva006CB080 gives scorch buffer/texture initialization purpose.
// ActualVB/IB CC/D0 owned texture D4 counters D8/DC/3794 and existing
// EF966 one-pointer constructor /424D0 counted assignment independently verified.
// Same-valued receiver PHI in the inline slot accessor keeps the native
// LEA-before-PUSH assignment order. No condition load survives optimization.
//
// ?rva0006B3F3@Rva00067878@@QAEXXZ, retail 0x0006B3F3, 217 bytes.
// Chain lane: calls 0x00067878 just landed; allocates VB/IB at +0xCC/+0xD0
// then sets texture at +0xD4 via BNH helper. Same class as Rva00067878.
// Evidence: same +CC/D0/D4 offsets, rowed callees, EH new states.

typedef unsigned int Uint;
typedef unsigned short UShort;
void *__cdecl operator new(Uint s);

class RefCountClass
{
public:
	virtual void Delete_This();
	int m_refs;
};

class BfmeDynamicNativeVB : public RefCountClass
{
public:
	BfmeDynamicNativeVB(Uint a, UShort b, Uint c, Uint d);
private:
	char _t[0x18];
};

class DX8IndexBufferClass : public RefCountClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };
	DX8IndexBufferClass(Uint count, UsageType u);
private:
	char _t[0x10];
};

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

template<class T>
class RefCountPtr
{
public:
	__declspec(noinline) RefCountPtr(int kind);
	T *Referent;
	~RefCountPtr()
	{
		if (Referent != 0)
			Referent->Release_Ref();
	}
	const RefCountPtr &operator=(const RefCountPtr &other);
};

class Rva0006B3F3ScorchTexture:public RefCountPtr<TextureClass>{public:Rva0006B3F3ScorchTexture(int);};
class Rva00067878
{
public:
	void rva00067878();
	void rva0006B3F3();__forceinline RefCountPtr<TextureClass>&scorchSlot(){return this?m_tex:m_tex;}

private:
	unsigned char m_pad[0xCC];
	BfmeDynamicNativeVB *m_vb;
	DX8IndexBufferClass *m_ib;
	RefCountPtr<TextureClass> m_tex;
	int m_d8;
	int m_dc;
	unsigned char m_pad2[0x3794 - 0xE0];
	int m_3794;
};


void Rva00067878::rva0006B3F3()
{
	if (m_vb != 0 || m_ib != 0)
		rva00067878();
	m_vb = new BfmeDynamicNativeVB(0x142, 0x2002, 0, 0);
	m_ib = new DX8IndexBufferClass(0xC00C, DX8IndexBufferClass::USAGE_DEFAULT);
	scorchSlot()=Rva0006B3F3ScorchTexture(3);
	m_3794 = 0;
	m_d8 = 0;
	m_dc = 0;
}
