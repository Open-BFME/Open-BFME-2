// cl: /O1 /DNDEBUG /MD /EHsc
// ?regainFocus@AudioManager@@QAEXXZ
// retail 0x0035D2F7, 47 bytes. Dedicated TU: WinMain.cpp owns the class
// declaration (stub `class AudioManager { void regainFocus(); }`) and the
// call site (WndProc WM_ACTIVATE arm); this unit carries the byte-exact body.
// Retail restores three channel volumes in a loop: per-channel float from the
// focus-volume helper, applied with the channel bit through virtual slot 60
// of the global mixer object.

class AudioMixer
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void _M_slot_70();
	virtual void _M_slot_74();
	virtual void _M_slot_78();
	virtual void _M_slot_7c();
	virtual void _M_slot_80();
	virtual void _M_slot_84();
	virtual void _M_slot_88();
	virtual void _M_slot_8c();
	virtual void _M_slot_90();
	virtual void _M_slot_94();
	virtual void _M_slot_98();
	virtual void _M_slot_9c();
	virtual void _M_slot_a0();
	virtual void _M_slot_a4();
	virtual void _M_slot_a8();
	virtual void _M_slot_ac();
	virtual void _M_slot_b0();
	virtual void _M_slot_b4();
	virtual void _M_slot_b8();
	virtual void _M_slot_bc();
	virtual void _M_slot_c0();
	virtual void _M_slot_c4();
	virtual void _M_slot_c8();
	virtual void _M_slot_cc();
	virtual void _M_slot_d0();
	virtual void _M_slot_d4();
	virtual void _M_slot_d8();
	virtual void _M_slot_dc();
	virtual void _M_slot_e0();
	virtual void _M_slot_e4();
	virtual void _M_slot_e8();
	virtual void _M_slot_ec();
	virtual void setChannelVolume(float volume, int channelBit);
};

class AudioManager
{
public:
	void regainFocus();
};

extern AudioMixer *g_audioMixer;

float LookupFocusChannelVolume(int channelIndex);

// ?regainFocus@AudioManager@@QAEXXZ
void AudioManager::regainFocus()
{
	for (int channel = 0; channel < 3; ++channel) {
		float volume = LookupFocusChannelVolume(channel);
		g_audioMixer->setChannelVolume(volume, 1 << channel);
	}
}
