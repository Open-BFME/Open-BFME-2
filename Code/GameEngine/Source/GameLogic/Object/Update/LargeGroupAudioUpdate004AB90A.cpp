// cl: /DNDEBUG /MD
// ?rva004AB90A@LargeGroupAudioUpdate@@QAEXXZ, retail 0x004AB90A, 152 bytes.
// Target evidence: linkbody LINK BONUS 48B; callers jmp at 0x004ABA7C 0x004ABB40 in LargeGroupAudioUpdateSlots.cpp; callees rowed 0x0020D925 0x004AB7C8 0x0044DF71 0x002943B2; layout +4 moduledata +8 object +0x24 host +0x28 position pair +0x30/+0x7C state +0x8C bool +0x8D flag +0x90 GameLogic from slots and 004AB9A2 precedents.
class Object;
class Player;
class LargeGroupAudioUpdate;
#include "LargeGroupAudioUpdateView.h"
class Rva0020DXXX
{
public:
	void registerSubject(int v);
	void rva0020D959(int v);
	void updateSubject(int slot);
};
class Rva0020D959Host;
class LargeGroupAudio; extern LargeGroupAudio *TheLargeGroupAudio;
class Player
{
};
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
inline unsigned char Inv20(unsigned int v)
{
	return (unsigned char)~(v >> 20);
}
void LargeGroupAudioUpdate::rva004AB90A()
{
	if (m_8D)
		return;
	if (((Inv20(m_object->m_94.m_words[1]) & 1) == 0))
		return;
	m_8D = true;
	((Rva0020DXXX *)(*(Rva0020D959Host * *)&TheLargeGroupAudio))->registerSubject((int)static_cast<Rva004ABABCIface *>(this));
	Object *obj = m_object;
	int delay = ((const LargeGroupAudioUpdate *)m_moduleData)->rva004AB7C8();
	setWakeFrame(obj, (UpdateSleepTime)delay);
	*(int *)&m_28.x = *(const int *)&obj->m_position.x;
	*(int *)&m_28.y = *(const int *)&obj->m_position.y;
	m_30 = obj->m_10C;
	m_7C = obj->m_94;
	m_8C = obj->rva002943B2(0);
	m_90 = TheGameLogic->getFrame();
}
