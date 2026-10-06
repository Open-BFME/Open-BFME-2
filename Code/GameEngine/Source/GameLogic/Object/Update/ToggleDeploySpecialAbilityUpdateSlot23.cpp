// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
// ?rva004AE5B8@ToggleDeploySpecialAbilityUpdate@@QAEXPAX@Z retail 0x004AE5B8 124B
// Evidence: vslot 23 of vtable 0x00855370 for ToggleDeploySpecialAbilityUpdate; audio event via rowed BfmeAudioEventPrefix136 plus CondSetter plus TheAudio slot 0x64 plus DeployStyle helper; caller none
#include "Common/BfmeAudioEventPrefix136.h"
class Rva002D9531
{
public:
	void rva002D9531(int v);
};
class AudioManager
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
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual int v25(BfmeAudioEventPrefix136 *p);
};
extern AudioManager *TheAudio;
class DeployStyleAIUpdate
{
public:
	void rva0048E6D2();
};
struct Thing {
	char m_pad[0xCC];
	OpaqueRefElement4 m_opaque;
};
struct Rva004AE5B8Data08 {
	char m_pad[0x74];
	int m_74;
};
class Rva0044EF5E
{
public:
	Rva0044EF5E();
protected:
	const void *m_vtable;
	Thing *m_owner;
	Rva004AE5B8Data08 *m_p08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
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
	TheAudio->v25(&tmp);
	arg->m_258->rva0048E6D2();
}
