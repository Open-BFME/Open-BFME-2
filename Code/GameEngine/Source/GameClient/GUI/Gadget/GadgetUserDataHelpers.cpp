// cl: /O1 /Ob0

// ?Rva004BCB20@@YAXPAVGameWindow@@H@Z, retail 0x00328543 (60B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetUserDataHelpers.cpp
// (BFME1 0x004BCB20). The one gadget helper that CREATES the user data: a
// window with none gets fresh push-button data before the field is written.
// Trimmed TU: only this body is defined here; the donor's four unplaced
// siblings stay out so the unmatched gate has nothing to refuse.

class GameWindow
{
public:
	void *winGetUserData(void);
	void winSetUserData(void *data);
	void winSetStatus(unsigned int status);
};

// Push-button data: the same accessor, a different record. The 0x38-byte
// layout below is retail-measured: five byte members ride with three bytes
// of pad each while the nine int members sit at +0x04/+0x08/+0x10/+0x14/
// +0x18/+0x1C/+0x24/+0x2C/+0x30 (natural alignment, no donor; BFME1 keeps
// this struct empty). Member names stay positional: their semantics are
// unproven, only the offsets and access widths are.
struct _PushButtonData
{
	_PushButtonData() throw();

	char m_byte00;			// +0x00
	int m_int04;			// +0x04
	int m_int08;			// +0x08
	char m_byte0C;			// +0x0C
	int m_int10;			// +0x10
	int m_int14;			// +0x14
	int m_int18;			// +0x18
	int m_int1C;			// +0x1C
	char m_byte20;			// +0x20
	int m_int24;			// +0x24
	char m_byte28;			// +0x28
	int m_int2C;			// +0x2C
	int m_int30;			// +0x30
	char m_byte34;			// +0x34
};

// ??0_PushButtonData@@QAE@XZ, retail 0x00327E22 (46B).
// Zeroing leaf: xor-shared zero, this homed in eax, stores in retail order.
_PushButtonData::_PushButtonData() throw()
{
	m_byte00 = 0;
	m_int04 = 0;
	m_int08 = 0;
	m_byte0C = 0;
	m_int10 = 0;
	m_int14 = 0;
	m_int18 = 0;
	m_int1C = 0;
	m_byte20 = 0;
	m_int24 = 0;
	m_byte28 = 0;
	m_int2C = 0;
	m_int30 = 0;
	m_byte34 = 0;
}

extern _PushButtonData *getNewPushButtonData(void);

struct Rva004BCB20Data
{
	char m_prefix[0x24];
	int m_value;						// +0x24
};

// ?Rva004BCB20@@YAXPAVGameWindow@@H@Z
void Rva004BCB20(GameWindow *window, int value)
{
	if (window != 0)
	{
		Rva004BCB20Data *data =
			(Rva004BCB20Data *)window->winGetUserData();
		if (data == 0)
		{
			data = (Rva004BCB20Data *)getNewPushButtonData();
			window->winSetUserData(data);
		}
		data->m_value = value;
		window->winSetStatus(0x02000000);
	}
}

// ?getNewPushButtonData@@YAPAU_PushButtonData@@XZ @0x0032843E
_PushButtonData *getNewPushButtonData(void)
{
	return new _PushButtonData;
}
