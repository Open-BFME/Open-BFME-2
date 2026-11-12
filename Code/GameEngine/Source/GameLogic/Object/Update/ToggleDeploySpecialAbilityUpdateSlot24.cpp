// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
// ?rva004AE6D7@ToggleDeploySpecialAbilityUpdate@@QAEXPAX@Z retail 0x004AE6D7 183B
// Evidence: vslot 24 of vtable 0x00855370 for ToggleDeploySpecialAbilityUpdate; audio event via rowed BfmeAudioEventPrefix136 plus CondSetter plus TheAudio slot 0x64 plus DeployStyle helper; caller none. Row ?rva0028B7C8@Object@@QBEHXZ declares int but retail tests al so TU declares bool per-code-use.
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
class Rva004AE6D7P20
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual bool v08(int v);
};
enum KindOfType
{
	KINDOF_BFME_5E = 0x5e,
	KINDOF_BFME_60 = 0x60
};
#include "../object.h"
enum CommandSourceType {
	kCommandSourceInvalid = 0,
	kCommandSourcePlayer = 1,
	kCommandSourceAI = 2
};
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
class ToggleDeploySpecialAbilityUpdate : public Rva0044EF5E
{
public:
	void rva004AE6D7(void *arg);
private:
	Rva004AE6D7P20 m_p20;
};
struct Rva004AE5B8Arg {
	char m_pad[0x258];
	DeployStyleAIUpdate *m_258;
};
// ?rva004AE6D7@ToggleDeploySpecialAbilityUpdate@@QAEXPAX@Z retail 0x004AE6D7 183B
// Evidence: vslot 24 of same vtable via first gate plus Object gate plus DeployStyle virtual plus aiIdle plus same audio tail with plus 0xC8 plus final helper
void ToggleDeploySpecialAbilityUpdate::rva004AE6D7(void *argVoid)
{
	if (!m_p20.v08(0))
		return;
	Rva004AE5B8Arg *arg = (Rva004AE5B8Arg *)argVoid;
	DeployStyleAIUpdate *ds = arg->m_258;
	if (!ds)
		return;
	if ((unsigned char)((Object *)arg)->rva0028B7C8() || ds->rva00262D8F()) {
		((AICommandInterface *)((char *)ds + 0x20))->aiIdle(kCommandSourceAI);
	}
	BfmeAudioEventPrefix136 tmp(*(OpaqueRefElement4 *)((char *)m_owner + 0xC8), 0);
	Rva004AE5B8Data08 *moduleData = m_p08;
	((Rva002D9531 *)&tmp)->rva002D9531(moduleData->m_74);
	TheAudio->addAudioEvent(&tmp);
	ds->rva0048E6AB();
}
