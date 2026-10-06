// cl: /MD
//
// ?rva002714CA@Rva002714CA@@QAEXXZ retail 0x002714CA 28 bytes.
// TheAudio slot 0x6c removeAudioEvent with handle at +0x148 then set to 1.
// Unblocks 0x002793F0 0x002785FB 0x002791E7. Prev/next in Common with /O1 /MD.
// Evidence: caller 0x00274412 plus TheAudio 0x009FE6E8 plus slot 0x6c.

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

class Rva002714CA
{
public:
	void rva002714CA();

private:
	unsigned char m_pre[0x148];
	AudioHandle m_handle;
};

void Rva002714CA::rva002714CA()
{
	TheAudio->removeAudioEvent(m_handle);
	m_handle = 1;
}
