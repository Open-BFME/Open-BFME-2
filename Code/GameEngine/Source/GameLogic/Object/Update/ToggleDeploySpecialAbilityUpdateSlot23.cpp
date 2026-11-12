// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
// ?rva004AE5B8@ToggleDeploySpecialAbilityUpdate@@QAEXPAX@Z retail 0x004AE5B8 124B
// Evidence: vslot 23 of vtable 0x00855370 for ToggleDeploySpecialAbilityUpdate; audio event via rowed BfmeAudioEventPrefix136 plus CondSetter plus TheAudio slot 0x64 plus DeployStyle helper; caller none
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../Include/GameLogic/Module/Rva002D9531.h"
#include "../../../../Include/Common/GameAudio.h"
extern AudioManager *TheAudio;
#include "../../../../Include/GameLogic/Module/DeployStyleAIUpdateClass.h"
#include "../../../Common/Thing/thing.h"
struct Rva004AE5B8Data08 {
	char m_pad[0x74];
	int m_74;
};
class ModuleData;
class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	Rva0044EF5E();
protected:
	const void *m_vtable; // +0x00
	Thing *m_owner; // +0x04
	Rva004AE5B8Data08 *m_p08; // +0x08
	const void *m_p0C; // +0x0C
	const void *m_p10; // +0x10
	char m_pad14[0xC];
};
class ToggleDeploySpecialAbilityUpdate : public Rva0044EF5E
{
public:
	void rva004AE5B8(void *arg);
private:
	const void *m_p20;
};
struct Rva004AE5B8Arg {
	char m_pad[0x258];
	DeployStyleAIUpdate *m_258;
};
void ToggleDeploySpecialAbilityUpdate::rva004AE5B8(void *argVoid)
{
	Rva004AE5B8Arg *arg = (Rva004AE5B8Arg *)argVoid;
	BfmeAudioEventPrefix136 tmp(*(OpaqueRefElement4 *)((char *)m_owner + 0xCC), 0);
	Rva004AE5B8Data08 *p08 = m_p08;
	((Rva002D9531 *)&tmp)->rva002D9531(p08->m_74);
	TheAudio->addAudioEvent(&tmp);
	arg->m_258->rva0048E6D2();
}
