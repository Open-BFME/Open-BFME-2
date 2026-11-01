// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0035BD3F@Rva0035BD3F@@QAEXXZ retail 0x0035BD3F 30B
// Evidence: unlock lane; TheAudio 0x009FE6E8 slot 0x6c removeAudioEvent precedent Rva0033FF2BDtor plus memory.md AudioLoopUpgrade; member +0x68 disp8; callers 0x002B5195 0x0035BF4C 0x0035C087 0x0051508B 0x005157EE 0x0051511D; prev Disp8CmpBoolGetters same /O1.
typedef unsigned int AudioHandle;

#include "../../Include/Common/GameAudio.h"

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
