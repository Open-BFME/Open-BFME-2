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
	int winGetSize(int *width, int *height);
};

// BFME1's GadgetListBoxSetColumnWidths donor sets percentage widths then
// asks its listbox worker to convert them to pixels. Retail 0x003252EA
// confirms the +2 count and +4 percentage buffer; the call target after
// this body is the donor's j_000272fa. Its 246B retail body at 0x003251F4
// recalculates pixel widths, so GadgetListBoxUpdateColumnWidths is a
// descriptive target-local name inferred from that behavior.
struct GadgetListboxColumnData
{
	unsigned char m_prefix[2];
	short m_columnCount;				// +0x02 (signed: retail movsx proves signed)
	int *m_percentageWidths;			// +0x04
	unsigned char m_gap08[12];			// +0x08..+0x13
	int *m_pixelWidths;				// +0x14
	unsigned char m_gap18[12];			// +0x18..+0x23
	GameWindow *m_slider;				// +0x24
};

extern void *__cdecl operator new[](unsigned int size);
extern void __cdecl operator delete[](void *memory);
void GadgetListBoxUpdateColumnWidths(GameWindow *listbox);

void GadgetListBoxSetColumnWidths(GameWindow *listbox, int count, int *widths)
{
	if (count <= 0)
		return;
	if (listbox == 0)
		return;

	GadgetListboxColumnData *data =
		(GadgetListboxColumnData *)listbox->winGetUserData();
	if (data == 0)
		return;

	data->m_columnCount = (unsigned short)count;
	operator delete[](data->m_percentageWidths);
	data->m_percentageWidths = new int[count];

	if (widths != 0)
	{
		for (int index = 0; index < count; ++index)
			data->m_percentageWidths[index] = widths[index];
	}
	else
	{
		int eachWidth = 100 / count;
		int extraPixels = 100 % count;
		for (int index = 0; index < count; ++index)
		{
			if (extraPixels != 0)
			{
				--extraPixels;
				data->m_percentageWidths[index] = eachWidth + 1;
			}
			else
			{
				data->m_percentageWidths[index] = eachWidth;
			}
		}
	}

	GadgetListBoxUpdateColumnWidths(listbox);
}

// ?GadgetListBoxUpdateColumnWidths@@YAXPAVGameWindow@@@Z, retail 0x003251F4 (246B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// (BFME1 0x004B8230 Rva004B8230UpdateColumnWidths). Same percent-to-pixel worker:
// single column stores the window width minus the slider, otherwise rebuilds the
// pixel buffer from the percentage buffer. Retail proves +2 count (signed short,
// movsx), +4 percentage, +0x14 pixel, +0x24 slider; callers are
// GadgetListBoxSetColumnWidths at 0x0032537E and the 0x002C1465 site.
struct ListboxSliderSize
{
	int x;
	int y;
};

void GadgetListBoxUpdateColumnWidths(GameWindow *listbox)
{
	if (listbox == 0)
		return;

	GadgetListboxColumnData *data =
		(GadgetListboxColumnData *)listbox->winGetUserData();
	if (data == 0)
		return;

	int width;
	int height;
	listbox->winGetSize(&width, &height);

	if (data->m_columnCount == 1)
	{
		data->m_pixelWidths = new int[1];
		data->m_pixelWidths[0] = width;

		if (data->m_slider == 0)
			return;

		ListboxSliderSize sliderSize;
		data->m_slider->winGetSize(&sliderSize.x, &sliderSize.y);
		data->m_pixelWidths[0] += -2 - sliderSize.x;
		return;
	}

	if (data->m_percentageWidths == 0)
	{
		GadgetListBoxSetColumnWidths(listbox, data->m_columnCount, 0);
		return;
	}

	if (data->m_pixelWidths != 0)
	{
		operator delete[](data->m_pixelWidths);
		data->m_pixelWidths = 0;
	}
	data->m_pixelWidths = new int[data->m_columnCount];

	int totalWidth = width;
	if (data->m_slider != 0)
	{
		ListboxSliderSize sliderSize;
		data->m_slider->winGetSize(&sliderSize.x, &sliderSize.y);
		totalWidth += -2 - sliderSize.x;
	}

	for (int index = 0; index < data->m_columnCount; ++index)
		data->m_pixelWidths[index] =
			data->m_percentageWidths[index] * totalWidth / 100;
}

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
