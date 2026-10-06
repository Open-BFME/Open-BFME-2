// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0035BD3F@Rva0035BD3F@@QAEXXZ retail 0x0035BD3F 30B
// Evidence: unlock lane; TheAudio 0x009FE6E8 slot 0x6c removeAudioEvent precedent Rva0033FF2BDtor plus memory.md AudioLoopUpgrade; member +0x68 disp8; callers 0x002B5195 0x0035BF4C 0x0035C087 0x0051508B 0x005157EE 0x0051511D; prev Disp8CmpBoolGetters same /O1.
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

class Rva0035BD3F
{
public:
	void rva0035BD3F();
private:
	char m_pad[0x68];
	AudioHandle m_handle;
};

void Rva0035BD3F::rva0035BD3F()
{
	if (TheAudio != 0) {
		TheAudio->removeAudioEvent(m_handle);
		m_handle = 1;
	}
}
