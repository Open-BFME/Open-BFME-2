// cl: /DNDEBUG /MD
// ?rva004AB9A2@LargeGroupAudioUpdate@@QAEXXZ @0x004AB9A2 51B
// When +0x8D set: unregister +0x24 via rowed-pin 0x0020D959 on global 0x00DFE1A8 then sleep forever via rowed UpdateModule::setWakeFrame and clear flag.
// Evidence: linkbody LINK BONUS 48B; callers jmp at 0x004ABA74 0x004ABB46; callees pin 0x0020D959 row 0x0044DF71; layout +8 Object +0x24 host +0x8D flag from slots and Rva0028572A precedents.
class Object;
#include "LargeGroupAudioUpdateView.h"
class Rva0020D959Host;
// The ledger row at 0x0020D959 is Rva0020DXXX::rva0020D959(int).
class Rva0020DXXX
{
public:
	void registerSubject(int v);
	void rva0020D959(int v);
	void updateSubject(int slot);
};

class LargeGroupAudio; extern LargeGroupAudio *TheLargeGroupAudio;
void LargeGroupAudioUpdate::rva004AB9A2()
{
	if (m_8D)
	{
		((Rva0020DXXX *)(*(Rva0020D959Host * *)&TheLargeGroupAudio))->rva0020D959((int)static_cast<Rva004ABABCIface *>(this));
		setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
		m_8D = false;
	}
}
