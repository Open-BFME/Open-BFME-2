// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// AptMapPreview.cpp -- AptMapPreview members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. The preview drives its living-world window
// at +0x68 (WB member m_livingWorldWindow); start regions come from that
// window's +0x29C -> +0x1C set, asked through 0x004FD8A8 (unnamed).

#include "../../../../../../Libraries/Include/Lib/Coord2D.h"

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

class Rva004FD8A8Set
{
public:
	Bool rva004FD8A8(Int region);		// 0x004FD8A8

	unsigned char m_pad00[8];
	AsciiString m_descKey;		// +0x08, passed to TheGameText->fetch
};

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void reset() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void initMapStringFile(const AsciiString &filename) = 0;
};

extern GameTextInterface *TheGameText;

struct AptMapPreviewMapInfo
{
	unsigned char m_pad00[0x1c];
	Rva004FD8A8Set *m_startRegions;		// +0x1C
};

class AptLivingWorldWindow
{
public:
	void SelectCampaign(Int campaign);	// 0x0056DB19

	unsigned char m_pad000[0x280];
	unsigned char m_listeners[0x29c - 0x280];	// +0x280, see below
	AptMapPreviewMapInfo *m_info;		// +0x29C
};

// The living-world window's +0x280 listener vector, erased through
// 0x002B7250 and appended through 0x005A0B4C (both rowed under address
// names, with their own views of the vector).
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *listener);
};

struct Rva002BA8F1Listener;
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

// The singleton at 0x00DFE1C8 owns, at +0x268, the object that is told the
// preview's campaign (0x003EF008, unrowed and unnamed in WB).
class Rva003EF008
{
public:
	void rva003EF008();			// 0x003EF008

	unsigned char m_pad00[0x44];
	Int m_field44;				// +0x44
	void *m_field48;			// +0x48
};

struct Rva00DFE1C8Host
{
	char m_pad[0x268];
	Rva003EF008 *m_field268;		// +0x268
};

extern Rva00DFE1C8Host *g_00DFE1C8;

// The campaign manager (0x00E02D6C): the index of a campaign in its +0x14
// vector, -1 when absent (0x003B8BC8, unrowed).
class Rva00E02D6C
{
public:
	Int rva003B8BC8(void *campaign);	// 0x003B8BC8
};

extern Rva00E02D6C *TheCampaignManager;

class GameWindow
{
public:
	int winHide(bool hide);
	unsigned int winSetStatus(unsigned int status);
	GameWindow *winGetChild();
	GameWindow *winGetNext();
};

class BfmeObjENK;
void bfmeGoENK(BfmeObjENK *o, char v);
void BfmeGadgetListBoxSetAudioFeedback(GameWindow *listbox, bool enable);

void GadgetListBoxReset(GameWindow *listbox);
int Rva00326CF0AddLines(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);
void GadgetListBoxSetTopVisibleEntry(GameWindow *window, int newPos);


class Image;
class Display;
extern Display *TheDisplay;

class W3DDisplay
{
public:
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
};

extern "C" __declspec(dllimport) int __stdcall IsBadReadPtr(const void *address, unsigned int size);
extern "C" char *__cdecl strcpy(char *destination, const char *source);
extern "C" int __cdecl strcmp(const char *a, const char *b);

// AptCallbackAdders.cpp's by-value callback reference (defined below).
template <class T> class AptRef;

class AptCustomRender;
class AptExternHandler;

// The Apt player (0x00DFE4CC): both adders are pinned by address.
class AptPlayer
{
public:
	void AddExternHandler(const AsciiString &name, Int arg, AptRef<AptExternHandler> handler);	// 0x0022445D
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);		// 0x0022464C
};

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#define TheAptPlayer ((AptPlayer *)g_bfmeAptWindowManager)

// 0x00411458 (pinned; see MpGameSetupSlots.cpp) stores the screen
// reference under the name.
class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

// The preview's +0x18 object; the registration clears its +0x08.
struct Rva0057E45COwner
{
	int m_00;
	int m_04;
	int m_08;
};

class AptMapPreview
{
public:
	Bool AllowsStartInRegion(Int region);
	void SelectCampaign(Int campaign);
	void UpdateStrategicScenarioDesc();	// 0x0057C99E
	Int rva0057C621();
	void rva0057C5B9(const Coord2D *pos, const Coord2D *size, void *unused3, void *unused4);
	void GameMapType(int query, char *result, bool skip);
	void MapGadgetInit(const char *name, void *argument, GameWindow *window);
	void rva0057E45C();
	void rva0057D4F3();	// fills the strategic scenario combo box
	void rva0057E058();	// refreshes the preview

private:
	unsigned char m_pad00[0x4];
	unsigned char m_field04[0x18 - 0x4];	// +0x04, handed to the campaign owner
	Rva0057E45COwner *m_18;	// +0x18
	int m_mode;	// +0x1C (OpenPlay 0, Strategic 1)
	GameWindow *m_currentMap;	// +0x20
	GameWindow *m_mapPicture;	// +0x24
	GameWindow *m_mapInfo;	// +0x28
	GameWindow *m_mapDescription;	// +0x2C
	GameWindow *m_currentMapChildren[8];	// +0x30
	GameWindow *m_strategicScenarioComboBox;	// +0x50
	GameWindow *m_strategicScenarioDesc;	// +0x54
	GameWindow *m_strategicTerritoryDesc;	// +0x58
	Image *m_picture;	// +0x5C
	unsigned char m_pad60[0x68 - 0x60];
	AptLivingWorldWindow *m_livingWorldWindow;	// +0x68
};

// AptMapPreview::AllowsStartInRegion, retail 0x0057C525.
Bool AptMapPreview::AllowsStartInRegion(Int region)
{
	if (m_livingWorldWindow == 0)
		return false;
	if (m_livingWorldWindow->m_info == 0)
		return false;
	if (m_livingWorldWindow->m_info->m_startRegions == 0)
		return false;
	return m_livingWorldWindow->m_info->m_startRegions->rva004FD8A8(region);
}

// AptMapPreview::SelectCampaign, retail 0x0057CA2D. WB asserts the window
// exists.
void AptMapPreview::SelectCampaign(Int campaign)
{
	if (m_livingWorldWindow == 0)
		return;
	m_livingWorldWindow->SelectCampaign(campaign);
	Rva003EF008 *owner = g_00DFE1C8->m_field268;
	if (owner)
	{
		owner->m_field44 = 1;
		if (m_livingWorldWindow->m_info)
		{
			owner->m_field48 = m_field04;
			owner->rva003EF008();
		}
	}
	UpdateStrategicScenarioDesc();
}

// AptMapPreview::rva0057C621, retail 0x0057C621: the selected campaign's
// index in the campaign manager, -1 without the strategic scenario combo
// box (+0x50, as GetStrategicScenarioComboBoxSelectedCampaign 0x0057C649
// reads it) or a selected campaign.
Int AptMapPreview::rva0057C621()
{
	if (m_strategicScenarioComboBox != 0 && m_livingWorldWindow != 0 && m_livingWorldWindow->m_info != 0)
		return TheCampaignManager->rva003B8BC8(m_livingWorldWindow->m_info);
	return -1;
}

// ?UpdateStrategicScenarioDesc@AptMapPreview@@QAEXXZ @0x0057C99E 143B
// Evidence: pinned name; callers 0x0057CA6F SelectCampaign plus 0x0057D5BF
// 0x0057E186 0x0057E374; callees rowed GadgetListBoxReset 0x003247E5
// StringBase copy 0x00037050 AddLines 0x00326CF0 SetTop 0x0032544C
// releaseBuffer 0x00036E70; TheGameText fetch slot 0x38; living +0x68
// info +0x29C set +0x1C key +0x08 AsciiString.
void AptMapPreview::UpdateStrategicScenarioDesc()
{
	if (m_strategicScenarioDesc == 0)
		return;
	GadgetListBoxReset(m_strategicScenarioDesc);
	AptMapPreviewMapInfo *info = m_livingWorldWindow->m_info;
	if (info == 0)
		return;
	Rva004FD8A8Set *set = info->m_startRegions;
	if (set == 0)
		return;
	UnicodeString text = TheGameText->fetch(set->m_descKey, 0);
	Rva00326CF0AddLines(m_strategicScenarioDesc, text, -1, 0, -1, true);
	GadgetListBoxSetTopVisibleEntry(m_strategicScenarioDesc, 0);
}

// AptMapPreview::rva0057C5B9, retail 0x0057C5B9: the "AptMapPreview::Picture"
// custom render (bound by 0x0057E4C2): draws the +0x5C picture over the
// given rectangle, dropping a picture that is no longer readable.
void AptMapPreview::rva0057C5B9(const Coord2D *pos, const Coord2D *size, void *unused3, void *unused4)
{
	if (m_picture == 0)
		return;
	if (IsBadReadPtr(m_picture, 0x34))
	{
		m_picture = 0;
		return;
	}
	((W3DDisplay *)TheDisplay)->rva0004D6B3(m_picture, pos->x, pos->y, pos->x + size->x, pos->y + size->y, -1, 2);
}

// Retail 0x0057C549, 50 bytes: bound as "AptMapPreview::GameMapType" by
// 0x0057E45C, an Apt query answering the map type of the +0x1C mode.
void AptMapPreview::GameMapType(int query, char *result, bool skip)
{
	if (query == 0 && !skip)
	{
		switch (m_mode)
		{
		case 0:
			strcpy(result, "OpenPlay");
			break;
		case 1:
			strcpy(result, "Strategic");
			break;
		}
	}
}

// Retail 0x0057E25D, 382 bytes: "AptMapPreview::MapGadgetInit", the screen
// reference bound by 0x0057E45C. Files each named gadget in its member,
// hides the first eight children of "CurrentMap", moves the preview's
// listener to a new "LivingWorld" window, then refreshes the preview
// (0x0057E058).
void AptMapPreview::MapGadgetInit(const char *name, void *argument, GameWindow *window)
{
	if (window == 0)
		return;
	if (strcmp(name, "MapInfo") == 0)
	{
		m_mapInfo = window;
		bfmeGoENK((BfmeObjENK *)window, 1);
		BfmeGadgetListBoxSetAudioFeedback(m_mapInfo, true);
	}
	else if (strcmp(name, "MapDescription") == 0)
	{
		m_mapDescription = window;
		bfmeGoENK((BfmeObjENK *)window, 1);
		BfmeGadgetListBoxSetAudioFeedback(m_mapDescription, true);
	}
	else if (strcmp(name, "MapPicture") == 0)
	{
		m_mapPicture = window;
	}
	else if (strcmp(name, "CurrentMap") == 0)
	{
		int count = 0;
		m_currentMap = window;
		GameWindow *child = window->winGetChild();
		while (child != 0 && count < 8)
		{
			m_currentMapChildren[count++] = child;
			child->winHide(true);
			child->winSetStatus(0x20000);
			child = child->winGetNext();
		}
	}
	else if (strcmp(name, "StrategicScenarioType") == 0)
	{
		m_strategicScenarioComboBox = window;
		rva0057D4F3();
	}
	else if (strcmp(name, "StrategicScenarioDescription") == 0)
	{
		m_strategicScenarioDesc = window;
		UpdateStrategicScenarioDesc();
	}
	else if (strcmp(name, "StrategicTerritoryDescription") == 0)
	{
		m_strategicTerritoryDesc = window;
	}
	else if (strcmp(name, "LivingWorld") == 0)
	{
		if (m_livingWorldWindow != 0)
			((Rva002B7250 *)m_livingWorldWindow->m_listeners)->rva002B7250((CreateAHeroData *)this);
		m_livingWorldWindow = (AptLivingWorldWindow *)window;
		((Rva005A0B4CList *)m_livingWorldWindow->m_listeners)->append((Rva002BA8F1Listener *)this);
		SelectCampaign(0);
	}
	rva0057E058();
}

// The handlers are bound as {object, method} pairs, built in place by the
// rowed constructor 0x00579E47 (Rva00579E47Delegate.cpp; the user-declared
// copy constructor makes cl build it in the argument slot); the callee
// releases the reference.
typedef void (AptMapPreview::*AptMapPreviewHandler)(void);

struct DelegateDesc
{
	DelegateDesc(AptMapPreview *object, AptMapPreviewHandler method) : m_object(object), m_method(method) {}

	AptMapPreview *m_object;
	AptMapPreviewHandler m_method;
};

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	~Rva00579E47();

private:
	void *m_ptr;
};

template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(DelegateDesc desc) : Rva00579E47(desc) {}
};

// Retail 0x0057E45C, 250 bytes. Name unknown. The preview's Apt
// registration (called by AptMpGameSetup::rva0044303D on its +0x60
// member): binds "AptMapPreview::MapGadgetInit" as the screen reference,
// "AptMapPreview::Picture" as a custom render and
// "AptMapPreview::GameMapType" as extern handler 0. Retail packs the last
// block's AsciiString fresh but keeps its pair in the shared slot
// (sub esp,0x14), which needs the trailing scope.
void AptMapPreview::rva0057E45C()
{
	m_18->m_08 = 0;
	{
		AsciiString name("AptMapPreview::MapGadgetInit");
		_bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(DelegateDesc(this, reinterpret_cast<AptMapPreviewHandler>(&AptMapPreview::MapGadgetInit))));
	}
	{
		AsciiString name("AptMapPreview::Picture");
		TheAptPlayer->AddCustomRender(name, AptRef<AptCustomRender>(DelegateDesc(this, reinterpret_cast<AptMapPreviewHandler>(&AptMapPreview::rva0057C5B9))));
	}
	{
		AsciiString name("AptMapPreview::GameMapType");
		TheAptPlayer->AddExternHandler(name, 0, AptRef<AptExternHandler>(DelegateDesc(this, reinterpret_cast<AptMapPreviewHandler>(&AptMapPreview::GameMapType))));
		{
			DelegateDesc unused(0, 0);
			(void)unused;
		}
	}
}
