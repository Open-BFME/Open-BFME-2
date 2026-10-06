// cl: /EHsc /MD
// ??0Rva005C7792@@QAE@XZ, retail 0x005C7792 247B.
// Ctor initializes the four FX draw-category ShareBuffers (pos Vector3, RGBA Vector4,
// size float, angle unsigned char) with size 0x200 or 0x400 by TheWritableGlobalData+0xd45.
// Evidence: callees rowed operator new 0x0002FDA0 and four ShareBuffer ctors
// 0x00169780 0x00169B90 0x001A7B80 0x001698A0; string literals name the buffers;
// globals g_00E065C8 g_00E065CC g_00E065D0 g_00E065D4; caller 0x005C78AD;
// prev Rva005C76C0Ctor gives TU and flags plus EH for new states.
class Vector3;
class Vector4;

template <class T> class ShareBufferClass
{
public:
	ShareBufferClass(int size, const char *name, int x);

private:
	char _pad[0x18];
};

class GlobalData
{
public:
	char _pad[0xd45];
	unsigned char m_flag; // +0xd45
};

extern GlobalData *TheWritableGlobalData;
extern ShareBufferClass<Vector3> *g_00E065C8;
// g_00E065C8: matched references place it at VA 0xe065c8 (zero-filled .bss).
ShareBufferClass<Vector3> * g_00E065C8;
extern ShareBufferClass<Vector4> *g_00E065CC;
// g_00E065CC: matched references place it at VA 0xe065cc (zero-filled .bss).
ShareBufferClass<Vector4> * g_00E065CC;
extern ShareBufferClass<float> *g_00E065D0;
// g_00E065D0: matched references place it at VA 0xe065d0 (zero-filled .bss).
ShareBufferClass<float> * g_00E065D0;
extern ShareBufferClass<unsigned char> *g_00E065D4;
// g_00E065D4: matched references place it at VA 0xe065d4 (zero-filled .bss).
ShareBufferClass<unsigned char> * g_00E065D4;

class Rva005C7792
{
public:
	Rva005C7792();
};

Rva005C7792::Rva005C7792()
{
	int size = 0x200;
	if (TheWritableGlobalData->m_flag != 0)
		size = 0x400;
	int zero = 0;
	g_00E065C8 = new ShareBufferClass<Vector3>(size, "FXParticleSystem::CategoryModule<CAT_DRAW>::m_posBuffer", zero);
	g_00E065CC = new ShareBufferClass<Vector4>(size, "FXParticleSystem::CategoryModule<CAT_DRAW>::m_RGBABuffer", zero);
	g_00E065D0 = new ShareBufferClass<float>(size, "FXParticleSystem::CategoryModule<CAT_DRAW>::m_sizeBuffer", zero);
	g_00E065D4 = new ShareBufferClass<unsigned char>(size, "FXParticleSystem::CategoryModule<CAT_DRAW>::m_angleBuffer", zero);
}
