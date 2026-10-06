// stlport
// cl: /O1 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad04() = 0;
	virtual void _pad08() = 0;
	virtual void _pad0C() = 0;
	virtual void _pad10() = 0;
	virtual void _pad14() = 0;
	virtual void _pad18() = 0;
	virtual void _pad1C() = 0;
	virtual void _pad20() = 0;
	virtual void _pad24() = 0;
	virtual void _pad28() = 0;
	virtual void _pad2C() = 0;
	virtual void _pad30() = 0;
	virtual void _pad34() = 0;
	virtual void _pad38() = 0;
	virtual void _pad3C() = 0;
	virtual void _pad40() = 0;
	virtual void _pad44() = 0;
	virtual void _pad48() = 0;
	virtual void _pad4C() = 0;
	virtual void _pad50() = 0;
	virtual void _pad54() = 0;
	virtual void _pad58() = 0;
	virtual void _pad5C() = 0;
	virtual void _pad60() = 0;
	virtual void _pad64() = 0;
	virtual void _pad68() = 0;
	virtual void _pad6C() = 0;
	virtual void _pad70() = 0;
	virtual void _pad74() = 0;
	virtual void _pad78() = 0;
	virtual void _pad7C() = 0;
	virtual void _pad80() = 0;
	virtual void _pad84() = 0;
	virtual void _pad88() = 0;
	virtual void _pad8C() = 0;
	virtual void _pad90() = 0;
	virtual void _pad94() = 0;
	virtual void _pad98() = 0;
	virtual void _pad9C() = 0;
	virtual void _padA0() = 0;
	virtual void _padA4() = 0;
	virtual void _padA8() = 0;
	virtual void _padAC() = 0;
	virtual void _padB0() = 0;
	virtual void _padB4() = 0;
	virtual void _padB8() = 0;
	virtual void _padBC() = 0;
	virtual void _padC0() = 0;
	virtual void _padC4() = 0;
	virtual void _padC8() = 0;
	virtual void _padCC() = 0;
	virtual void _padD0() = 0;
	virtual void _padD4() = 0;
	virtual void _padD8() = 0;
	virtual void method_DC(int handle, float val, int flag) = 0;
};
extern AudioManager *TheAudio;

class Matrix3D
{
public:
	void Set_Z_Translation(float z);
};

struct BfmePoolHolder
{
	char m_pad00[0x0c];
	int m_audioHandle0C;
	char m_pad10[0x1c];
	float m_float2C;
};

struct Rva005C8D17Inner
{
	unsigned char m_pad[0x10];
	float m_10;
};

struct Rva005C8D17Mid
{
	unsigned char m_pad[8];
	Rva005C8D17Inner *m_08;
};

class Rva005C8D17
{
public:
	float rva005C8D17();
protected:
	char m_pad00[8];
	BfmePoolHolder *m_target08;
	char m_pad0C[0x20];
	Rva005C8D17Mid *m_2C;
	int m_30;
};

float Rva005C8D17::rva005C8D17()
{
	if (m_30 == 0)
		return 1.0f;
	return m_2C->m_08->m_10;
}

class TargetObj005C8DBF : public Rva005C8D17
{
public:
	void method_005C8D6B();
};

void TargetObj005C8DBF::method_005C8D6B()
{
	BfmePoolHolder *target = m_target08;
	if (!target)
		return;
	float val = rva005C8D17();
	if (val != target->m_float2C)
	{
		((Matrix3D *)target)->Set_Z_Translation(val);
		TheAudio->method_DC(m_target08->m_audioHandle0C, val, 0);
	}
}
