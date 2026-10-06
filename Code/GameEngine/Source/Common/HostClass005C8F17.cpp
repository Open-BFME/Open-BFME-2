// cl: /MD
// ?rva005C8F17@HostClass005C8E0A@@QAEXXZ @0x005C8F17 57B
// Void method on HostClass005C8E0A sharing layout with rva005C8E2C: if pool
// ref at +8 is non-null notify TheAudio slot 0x6c removeAudioEvent with the
// handle at holder+0xc then clear via 0x519BD adjust via Rva005C87F8(false)
// and method_005C8E0A then clear byte +0x46. Evidence: same +8/+0x46 layout
// and callee trio as 0x005C8E2C callers 0x005C8FBD/0x005C901B/0x005C908B.

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct BfmePoolHolder
{
	unsigned char m_pad00[0x0c];
	unsigned int m_audioHandle0C;
	unsigned char m_pad10[0x88 - 0x10];
	OpaqueRefCounted m_ref;
};

class BfmePoolRef10
{
public:
	BfmePoolHolder *m_target;
	void rva000519BD();
};

class Rva005C87F8
{
public:
	void rva005C87F8(bool flag);
};

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern AudioManager *TheAudio;

class HostClass005C8E0A
{
public:
	void method_005C8E0A();
	void rva005C8F17();
private:
	char m_pad00[8];
	BfmePoolRef10 m_pool08;
	char m_pad0C[0x3a];
	unsigned char m_byte46;
};

void HostClass005C8E0A::rva005C8F17()
{
	if (m_pool08.m_target != 0) {
		TheAudio->removeAudioEvent(m_pool08.m_target->m_audioHandle0C);
		m_pool08.rva000519BD();
		((Rva005C87F8 *)this)->rva005C87F8(false);
		method_005C8E0A();
	}
	m_byte46 = 0;
}
