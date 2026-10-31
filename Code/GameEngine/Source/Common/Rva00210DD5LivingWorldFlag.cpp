// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Three thiscall bodies at 0x00210DD5 (25B), 0x00210DEE (68B) and 0x00210E32
// (41B), between Rva00210DC9 and the 0x00210E5B forwarder, sharing a receiver
// byte at +0x2C0 and TheLivingWorld's +0x14 mode word:
// - 0x00210DD5 clears the byte and passes 0.0f to TheLivingWorld's virtual
//   slot 0x7C;
// - 0x00210DEE clears it unless the mode is 2, then in mode 1 shows the engine
//   mouse cursor (rowed Mouse::_bfme_setEngineVisibility 0x001EE5BE) unless
//   TheLivingWorldLogic's rowed 0x002B5073 check of 8 holds;
// - 0x00210E32 is true in mode 1 when neither the byte nor
//   TheLivingWorldLogic's +0xE8 byte is set.
// Retail bytes establish every shape; the receiver class is not recovered,
// so the names are address-derived.

class LivingWorld; extern LivingWorld *TheLivingWorld;
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
class Mouse; extern Mouse *TheMouse;

class Mouse
{
public:
	void _bfme_setEngineVisibility(bool visible);
};

class Rva002B5073
{
public:
	bool rva002B5073(int what);
};

struct Rva00210DD5World
{
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void slot31(float value);						// +0x7C
	int m_04[4];
	int m_mode;												// +0x14
};

struct Rva00210DD5Logic
{
	char m_pad00[0xE8];
	bool m_E8;												// +0xE8
};

class Rva00210DD5
{
public:
	void rva00210DD5();
	void updateCursorVisibility();
	bool rva00210E32();
private:
	char m_pad00[0x2C0];
	bool m_2C0;												// +0x2C0
};

void Rva00210DD5::rva00210DD5()
{
	m_2C0 = false;
	((Rva00210DD5World *)TheLivingWorld)->slot31(0.0f);
}

void Rva00210DD5::updateCursorVisibility()
{
	if (((Rva00210DD5World *)TheLivingWorld)->m_mode != 2)
		m_2C0 = false;
	if (((Rva00210DD5World *)TheLivingWorld)->m_mode == 1 && TheLivingWorldLogic != 0
		&& !((Rva002B5073 *)TheLivingWorldLogic)->rva002B5073(8) && TheMouse != 0)
		TheMouse->_bfme_setEngineVisibility(true);
}

bool Rva00210DD5::rva00210E32()
{
	if (((Rva00210DD5World *)TheLivingWorld)->m_mode == 1 && !m_2C0
		&& !((Rva00210DD5Logic *)TheLivingWorldLogic)->m_E8)
		return true;
	return false;
}
