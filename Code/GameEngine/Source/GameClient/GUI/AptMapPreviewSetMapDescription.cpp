// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// Recovered map-preview description update at RVA 0x0057C892.
// Descriptive bfme names do not claim original source spellings. The metadata
// getter calls the cached map.str text loader, then returns its first line.

#include "unicode_string.h"


class GameWindow
{
public:
	int winEnable(bool enable);
};
extern "C" void __cdecl free(void *p);
void GadgetListBoxReset(GameWindow *listbox);
int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
    int color, int row, int column, bool overwrite);
int __cdecl Rva00322910(GameWindow *comboBox);
void *__cdecl GadgetComboBoxGetItemData(GameWindow *comboBox, int index);

class MapMetaData
{
public:
    UnicodeString bfme_getDescriptionFirstLine();
};

class AptMapPreview
{
public:
    void bfmeSetMapDescription(MapMetaData *map);
    void rva0057C597(bool show);
    void rva0057CC43(struct Rva0057CC43Node *head);
    void *GetStrategicScenarioComboBoxSelectedCampaign();
    void SelectCampaign(int campaign);
    void rva0057CD66();
    int rva0057C57B(int value);
private:
    char m_unmodelled[0x2C];
    GameWindow *m_descriptionList;
    GameWindow *m_windows[8];
    GameWindow *m_combo50;
};

struct Rva0057CC43Node
{
    char m_pad00[8];
    Rva0057CC43Node *m_next;
    Rva0057CC43Node *m_child;
};

void AptMapPreview::bfmeSetMapDescription(MapMetaData *map)
{
    if (m_descriptionList)
    {
        GadgetListBoxReset(m_descriptionList);
        if (map)
            GadgetListBoxAddEntryText(m_descriptionList,
                map->bfme_getDescriptionFirstLine(), -1, -1, -1, true);
    }
}

void AptMapPreview::rva0057C597(bool show)
{
    for (int i = 0; i < 8; ++i) {
        GameWindow *w = m_windows[i];
        if (w) {
            w->winEnable(show);
        }
    }
}

void AptMapPreview::rva0057CC43(Rva0057CC43Node *head)
{
    for (Rva0057CC43Node *node = head; node; ) {
        rva0057CC43(node->m_child);
        Rva0057CC43Node *next = node->m_next;
        free(node);
        node = next;
    }
}

void *AptMapPreview::GetStrategicScenarioComboBoxSelectedCampaign()
{
    if (!m_combo50)
        return (void *)-1;
    int index = Rva00322910(m_combo50);
    return GadgetComboBoxGetItemData(m_combo50, index);
}

// ?rva0057CD66@AptMapPreview@@QAEXXZ @0x0057CD66 18B
// Evidence: callees rowed 0x0057C649 GetStrategicScenarioComboBoxSelectedCampaign
// and 0x0057CA2D SelectCampaign; caller 0x0057CDA1; neighbours AptMapPreview.
void AptMapPreview::rva0057CD66()
{
    SelectCampaign((int)GetStrategicScenarioComboBoxSelectedCampaign());
}

int AptMapPreview::rva0057C57B(int value)
{
    for (int i = 0; i < 8; ++i)
    {
        if (value == (int)m_windows[i])
            return i;
    }
    return -1;
}

class Rva0043DA65
{
public:
	int rva0043DA65();
};

class GameSlot
{
public:
	virtual void reset();
	int m_state;
	char m_pad08[8];
	int m_startPos;
};

class GameInfo
{
public:
	GameSlot *getSlot(int slotNum);
};

struct Rva0057C688
{
	char m_pad0[0x18];
	Rva0043DA65 *m_ptr18;
	GameSlot *rva0057C688(int value);
};

GameSlot *Rva0057C688::rva0057C688(int value)
{
	if (value == -1)
		return 0;
	GameInfo *info = (GameInfo *)m_ptr18->rva0043DA65();
	if (!info)
		return 0;
	for (int i = 0; i < 8; ++i)
	{
		GameSlot *slot = info->getSlot(i);
		if (!slot)
			continue;
		if (slot->m_startPos == value)
			return slot;
	}
	return 0;
}
