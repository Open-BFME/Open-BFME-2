// cl: /Ireference/shims/bfme2_ascii
// ?rva0030D606@Rva0030D606@@QAEXXZ, retail 0x0030D606, 43B.
// Audio-handle release plus holder clear twin of Drawable stopAmbientSound:
// TheAudio slot 0x6c removeAudioEvent with +0x54 handle guarded by null plus 5 then store 1 then tail to rowed clear 0x000A8C9B on +0x58 holder.
// Evidence: packet disasm plus TheAudio ?TheAudio@@3PAVAudioManager@@A plus rowed clear plus callers 0x0030DC32 0x0030E068 0x0030E09D plus jmp 0x0030D68D.
typedef unsigned int AudioHandle;

#include "../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

struct Rva000A8C9B
{
	void *m_ptr;
	void clear();
};

class Rva0030D606
{
public:
	void rva0030D606();
private:
	unsigned char m_pad0[0x54];
	unsigned int m_audio54;
	Rva000A8C9B m_holder58;
};

void Rva0030D606::rva0030D606()
{
	if (TheAudio != 0 && m_audio54 >= 5)
	{
		TheAudio->removeAudioEvent(m_audio54);
		m_audio54 = 1;
	}
	return m_holder58.clear();
}
