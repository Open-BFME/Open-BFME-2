// ??1Rva000F82F5Dtor@@QAE@XZ
// partial score=0.7 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHa
// ??1Rva000F82F5Dtor@@QAE@XZ @0x000F82F5 83B.
// Non-virtual dtor releasing a malloc block at +0x2C via rowed free
// 0x00030830 and two refcounted textures at +0x14/+0x10 via rowed
// TextureBaseClass::Release_Ref 0x0061ED10, under EH states 1/0/-1.
// Name reuses the existing pin (thunk 0x007B6EAE tail-jumps here);
// the QAE (non-virtual) spelling matches the absent vtable store.
extern "C" void __cdecl free(void *block);

class TextureBaseClass
{
public:
	void Release_Ref();
};

class Rva000F82F5Dtor
{
public:
	~Rva000F82F5Dtor() throw();

private:
	char m_pad00[0x10];
	TextureBaseClass *m_10; // +0x10
	TextureBaseClass *m_14; // +0x14
	char m_pad18[0x2C - 0x18];
	void *m_2C; // +0x2C
};

Rva000F82F5Dtor::~Rva000F82F5Dtor()
{
	try {
	if (m_2C)
		free(m_2C);
	if (m_14)
		m_14->Release_Ref();
	if (m_10)
		m_10->Release_Ref();
	} catch (...) {
	}
}
