// cl: /O1 /DNDEBUG /MD
//
// Animatable3DObjClass::Set_Animation(HAnimComboClass *), retail 0x001A4D90,
// 39 bytes. Dedicated TU so animobj.cpp and hlod.cpp cannot see this body.
// Release, MULTIPLE_ANIM (4) at +0x100, combo pointer at +0x104, clear
// hierarchy-valid at +0xF4.

class HAnimComboClass;

class Animatable3DObjClass
{
	char pad[0xF0];
	char m_hierarchyValid;
	char pad_f5[0xB];
	int CurMotionMode;
	HAnimComboClass *ModeCombo;

protected:
	void Release();

public:
	virtual void Set_Animation(HAnimComboClass *anim_combo);
};

void Animatable3DObjClass::Set_Animation(HAnimComboClass *anim_combo)
{
	Release();
	CurMotionMode = 4;
	ModeCombo = anim_combo;
	m_hierarchyValid = 0;
}
