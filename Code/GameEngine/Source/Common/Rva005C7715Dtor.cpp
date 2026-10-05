// cl: /O1 /G7 /arch:SSE /MD /Ireference/shims/sweep
// ??1Rva005C7792@@QAE@XZ, retail 0x005C7715 125B.
// Dtor releases the four FX draw-category ShareBuffers created by ctor 0x005C7792
// (pos Vector3, RGBA Vector4, size float, angle unsigned char) via inlined
// Release_Ref plus nulling. Evidence: ctor string literals name the buffers;
// globals g_00E065C8 g_00E065CC g_00E065D0 g_00E065D4; atexit thunk 0x007B970C
// (mov ecx 0x00E065D8 plus jmp here) registered by Init 0x005C7889; gap between
// 0x005C76C0 and 0x005C7792 gives TU and flags.
class Vector3;
class Vector4;

class RefCountClass
{
public:
	virtual void Delete_This();
protected:
	virtual ~RefCountClass() {}
private:
	int NumRefs;
public:
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
};

template <class T> class ShareBufferClass : public RefCountClass
{
};

extern ShareBufferClass<Vector3> *g_00E065C8;
extern ShareBufferClass<Vector4> *g_00E065CC;
extern ShareBufferClass<float> *g_00E065D0;
extern ShareBufferClass<unsigned char> *g_00E065D4;

class Rva005C7792
{
public:
	Rva005C7792();
	~Rva005C7792();
};

Rva005C7792::~Rva005C7792()
{
	if (g_00E065C8) {
		g_00E065C8->Release_Ref();
		g_00E065C8 = 0;
	}
	if (g_00E065CC) {
		g_00E065CC->Release_Ref();
		g_00E065CC = 0;
	}
	if (g_00E065D0) {
		g_00E065D0->Release_Ref();
		g_00E065D0 = 0;
	}
	if (g_00E065D4) {
		g_00E065D4->Release_Ref();
		g_00E065D4 = 0;
	}
}
