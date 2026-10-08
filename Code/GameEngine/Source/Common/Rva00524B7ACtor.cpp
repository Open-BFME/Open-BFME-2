// cl: /MD
// ??0MovieWindowPlayback@@QAE@XZ @0x00524B7A 58B
// Ctor with explicit vtable in the middle via single-class model plus
// baseConstruct through a cast. Calls rowed base 0x001B4E63; sole caller
// Locomotor 0x005C9716 at +0x218. Single-class keeps source order per
// Rva005A7A90Ctor precedent. Honest owner.
extern const void *const g_00C67DFC[];

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class MovieWindowPlayback
{
public:
	MovieWindowPlayback();

private:
	void *m_vtable;
	char m_basePad[8];
	void *m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	unsigned char m_24;
	char m_pad25[3];
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
};
MovieWindowPlayback::MovieWindowPlayback()
{
	((BFME2NativeNetwork *)this)->baseConstruct();
	m_24 &= 0xF8;
	m_28 = -1;
	m_0C = 0;
	m_20 = 0;
	m_2C = 0;
	m_30 = 0;
	m_vtable = (void *)g_00C67DFC;
	_ReadWriteBarrier();
	m_34 = 0;
	m_38 = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
}
