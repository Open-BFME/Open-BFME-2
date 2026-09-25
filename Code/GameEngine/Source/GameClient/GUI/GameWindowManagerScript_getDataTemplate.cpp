// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?getDataTemplate@@YAPAXPADPAH@Z, retail 0x00315445, 245 bytes.
// Dedicated TU.
//
// Battle for Middle-earth 2 adaptation of the Zero Hour reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// getDataTemplate): BFME2 passes the template size back through a second
// out-parameter so the createGadget wrapper can copy that many bytes over
// the static before creating the gadget.
//
// BFME2 facts (all retail-measured):
// - signature is (char *type, Int *sizeOut); the Zero Hour (char *) only
//   shape is gone. Unmatched types return NULL without touching sizeOut.
// - each arm pushes a literal size (sliders 0x10, listbox 0x4C,
//   tab-control 0x54, entry 0x28, static-text 8, radio 8, combo 0x34).
// - the shared tail stores the size through sizeOut when non-NULL, clears
//   the first word of the static with memset(data, 0, 4) and returns it.
// - VERTSLIDER/HORZSLIDER share the trailing arm (forward je pair).
// - strcmp/memset are plain externs (no dllimport) so the calls stay
//   direct E8 to the thunks at 0x006291C6/0x006291AE; string and static
//   addresses fill from retail.

typedef int Int;

#ifndef NULL
#define NULL 0
#endif

extern "C" int strcmp(const char *a, const char *b);
extern "C" void *memset(void *dst, int val, unsigned int n);

// Template statics. Only the address of each is witnessed by retail (DIR32
// fill); sizes below mirror the sibling minimal models, the byte counts
// travel as immediates.
struct SliderGadgetData
{
	Int minVal;
	Int maxVal;
	Int numTicks;
	Int position;
};

struct ListboxGadgetData
{
	unsigned char raw[0x4C];
};

struct TabControlGadgetData
{
	unsigned char raw[0x54];
};

struct EntryGadgetData
{
	unsigned char raw[0x28];
};

struct StaticTextGadgetData
{
	Int text;
	Int flags;
};

struct RadioGadgetData
{
	Int screen;
	Int group;
};

struct ComboGadgetData
{
	unsigned char raw[0x34];
};

// ?getDataTemplate@@YAPAXPADPAH@Z
void *getDataTemplate(char *type, Int *sizeOut)
{
	static EntryGadgetData entryData;
	static SliderGadgetData sliderData;
	static ListboxGadgetData listboxData;
	static StaticTextGadgetData textData;
	static RadioGadgetData radioData;
	static TabControlGadgetData tabControlData;
	static ComboGadgetData comboData;
	void *data;
	Int size;

	if (!strcmp(type, "VERTSLIDER") || !strcmp(type, "HORZSLIDER"))
	{
		size = 0x10;
		data = &sliderData;
	}
	else if (!strcmp(type, "SCROLLLISTBOX"))
	{
		size = 0x4C;
		data = &listboxData;
	}
	else if (!strcmp(type, "TABCONTROL"))
	{
		size = 0x54;
		data = &tabControlData;
	}
	else if (!strcmp(type, "ENTRYFIELD"))
	{
		size = 0x28;
		data = &entryData;
	}
	else if (!strcmp(type, "STATICTEXT"))
	{
		size = 8;
		data = &textData;
	}
	else if (!strcmp(type, "RADIOBUTTON"))
	{
		size = 8;
		data = &radioData;
	}
	else if (!strcmp(type, "COMBOBOX"))
	{
		size = 0x34;
		data = &comboData;
	}
	else
	{
		return NULL;
	}

	if (sizeOut)
	{
		*sizeOut = size;
	}

	memset(data, 0, 4);

	return data;
}
