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

	unsigned char m_pad000[0x29c];
	AptMapPreviewMapInfo *m_info;		// +0x29C
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

class GameWindow;

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

class AptMapPreview
{
public:
	Bool AllowsStartInRegion(Int region);
	void SelectCampaign(Int campaign);
	void UpdateStrategicScenarioDesc();	// 0x0057C99E
	Int rva0057C621();
	void rva0057C5B9(const Coord2D *pos, const Coord2D *size, void *unused3, void *unused4);

private:
	unsigned char m_pad00[0x4];
	unsigned char m_field04[0x50 - 0x4];	// +0x04, handed to the campaign owner
	GameWindow *m_strategicScenarioComboBox;	// +0x50
	GameWindow *m_strategicScenarioDesc;	// +0x54
	unsigned char m_pad58[0x5c - 0x58];
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
