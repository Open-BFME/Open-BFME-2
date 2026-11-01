// cl: /O1 /DNDEBUG /MD /EHsc
//
// OpenContain::containReactToTransformChange, retail 0x004624E3 (8 bytes).
//
// The OpenContain ctor 0x004649F8 stores the ContainModuleInterface vftable
// 0x00C433B0 at +0x20; its slot 3 holds this body, the slot
// Object::reactToTransformChange 0x00292D49 dispatches through getContain()
// (call [eax+0x0C] at 0x00292E0F). As in Zero Hour the body only calls the
// virtual redeployOccupants, here slot 18 of the primary table 0x00C435E8
// (BFME 2 has one more primary virtual and one more word ahead of the
// interface than the Zero Hour header the main OpenContain unit compiles).

class OpenContainPrimaryView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void redeployOccupants();

	int m_04[7];
};

#include "../../../../Include/GameLogic/Module/ContainModule.h"

class OpenContain : public OpenContainPrimaryView, public ContainModuleInterface
{
public:
	virtual void containReactToTransformChange();
};

// our object changed position... react as appropriate.
void OpenContain::containReactToTransformChange()
{
	// Our transform changed, which means our bones moved, and we keep people positioned on bones.
	redeployOccupants();
}
