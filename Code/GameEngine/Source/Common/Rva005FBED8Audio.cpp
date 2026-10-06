// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /EHsc /MD /DNDEBUG
// ?rva005FBED8@Rva005FBEBA@@QAEXH@Z @0x005FBED8 157B.
// Audio refresh through callback slot 0x00879F0C (constant at 0x005FC31A):
// if flag +0x1c clear, call slot4 on +0, set flag, run rva005FBEBA, then if
// TheAudio and TheLivingWorldLogic chain present, build BfmeAudioEventPrefix136
// from ([edi+0x40]+0x3c, 1), set +0x70 from [edi+0x14], add via TheAudio slot
// 0x64 storing handle at +0x24.
#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class AudioView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *evt);
};

struct Inner40
{
	char m_pad[0x3c];
	OpaqueRefElement4 m_ref;
};

struct Inner98
{
	char m_pad00[0x14];
	int m_14;
	char m_pad18[0x40 - 0x14 - 4];
	Inner40 *m_40;
};

struct LivingWorldView
{
	char m_pad[0x98];
	Inner98 *m_98;
};

class Slot4Obj
{
public:
	virtual void slot0();
	virtual void slot1();
};

class Rva005FBEBA
{
public:
	void rva005FBEBA();
	void rva005FBED8(int unused);
private:
	Slot4Obj *m_obj00;
	char m_pad04[0x1c - 4];
	int m_flag1c;
	char m_pad20[0x24 - 0x1c - 4];
	int m_handle24;
};

void Rva005FBEBA::rva005FBED8(int)
{
	if (m_flag1c != 0)
		return;
	Slot4Obj *tmp = m_obj00;
	m_flag1c = 1;
	tmp->slot1();
	rva005FBEBA();
	if (TheAudio == 0)
		return;
	LivingWorldView *lw = (LivingWorldView *)TheLivingWorldLogic;
	if (lw == 0)
		return;
	Inner98 *inner = lw->m_98;
	if (inner == 0)
		return;
	BfmeAudioEventPrefix136 evt(inner->m_40->m_ref, 1);
	*(int *)((char *)&evt + 0x70) = inner->m_14;
	m_handle24 = ((AudioView *)TheAudio)->addAudioEvent(&evt);
}
