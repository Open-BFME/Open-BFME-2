// ??1Rva000F82F5Dtor@@QAE@XZ
// partial score=0.85 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva000F82F5Dtor@@QAE@XZ @0x000F82F5 83B try/catch-EH shape under /EHs.
// 82B with EH prolog plus states; wall is prologue-only: retail has
// push-esi-only plus this-home and states 1/0/-1 with NO esp-save;
// any try/catch adds push-ebx plus esp-save (funclet frame), plain/EHs/
// EHsc/EHa/throw() drop EH entirely. Partial-try variant shown.
extern "C" void __cdecl free(void *block);

class TextureBaseClass
{
public:
	void Release_Ref();
};

class Rva000F82F5Dtor
{
public:
	~Rva000F82F5Dtor();

private:
	char m_pad00[0x10];
	TextureBaseClass *m_10;
	TextureBaseClass *m_14;
	char m_pad18[0x2C - 0x18];
	void *m_2C;
};

Rva000F82F5Dtor::~Rva000F82F5Dtor()
{
	if (m_2C)
		free(m_2C);
	try {
	if (m_14)
		m_14->Release_Ref();
	if (m_10)
		m_10->Release_Ref();
	} catch (...) {
	}
}
