// cl: /O1 /DNDEBUG /MD /EHsc
//
// Drawable forwarders to its first draw module (the head of the module list
// at this+0x14C), retail 0x00272971..0x00272A02, just before the
// broadcaster 0x00272A02 (Drawable_rva00272A02.cpp). Each does nothing
// without a module and otherwise hands its arguments to one DrawModule slot:
//   0x00272971 41B  slot 0x84 (dword, float, dword)
//   0x0027299A 27B  slot 0x74, only for a nonzero argument
//   0x002729B5 22B  slot 0x78
//   0x002729CB 30B  slot 0x7C (float)
//   0x002729E9 25B  slot 0x80
// The slots' names are unknown; argument types are read from the bodies.

class DrawModuleForRva272971
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74(int value) = 0;
	virtual void slot78(int value) = 0;
	virtual void slot7C(float value) = 0;
	virtual void slot80(int value) = 0;
	virtual void slot84(int a, float b, int c) = 0;
};

class Drawable
{
public:
	void rva00272971(int a, float b, int c);
	void rva0027299A(int value);
	void rva002729B5(int value);
	void rva002729CB(float value);
	void rva002729E9(int value);

private:
	unsigned char m_pad[0x14C];
	DrawModuleForRva272971 **m_drawModules;	// +0x14C
};

void Drawable::rva00272971(int a, float b, int c)
{
	DrawModuleForRva272971 **dms = m_drawModules;
	if (*dms)
		(*dms)->slot84(a, b, c);
}

void Drawable::rva0027299A(int value)
{
	if (value)
	{
		DrawModuleForRva272971 *dm = *m_drawModules;
		if (dm)
			dm->slot74(value);
	}
}

void Drawable::rva002729B5(int value)
{
	DrawModuleForRva272971 **dms = m_drawModules;
	if (*dms)
		(*dms)->slot78(value);
}

void Drawable::rva002729CB(float value)
{
	DrawModuleForRva272971 **dms = m_drawModules;
	if (*dms)
		(*dms)->slot7C(value);
}

void Drawable::rva002729E9(int value)
{
	DrawModuleForRva272971 **dms = m_drawModules;
	if (*dms)
		(*dms)->slot80(value);
}
