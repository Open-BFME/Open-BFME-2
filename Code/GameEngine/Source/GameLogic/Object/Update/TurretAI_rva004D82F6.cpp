// cl: /DNDEBUG /MD
// ?rva004D82F6@TurretAI@@QAEXXZ, retail 0x004D82F6, 26 bytes.
// Evidence: unlock lane; TheAudio at VA 0xdfe6e8 (?TheAudio@@3PAVAudioManager@@A);
// slot 0x6c removeAudioEvent precedent Drawable_rva002743D7; +0x20 audio handle then store 1;
// callers 0x004D86C1 0x004D8DEA; neighbours TurretAI_isWeaponSlotOnTurret + OpaqueScalarDeletingDtors.
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

class TurretAI
{
	char m_pad[0x20];
	unsigned m_audio20;
public:
	void rva004D82F6();
};

void TurretAI::rva004D82F6()
{
	TheAudio->removeAudioEvent(m_audio20);
	m_audio20 = 1;
}
