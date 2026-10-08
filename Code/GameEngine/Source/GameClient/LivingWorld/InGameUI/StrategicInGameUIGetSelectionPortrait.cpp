// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::GetSelectionPortrait (WorldBuilder
// StrategicInGameUIGetSelectionPortrait.cpp). Target facts for 0x005D23BB
// (cdecl): finds the player owning the selection (+0x1C -> +0x13C) through
// TheLivingWorldLogic (0x002B51F8) and, when that player's template (+0x40)
// names a portrait (+0x2C), returns the image TheMappedImageCollection has
// for it; else NULL. The selection and player types are viewed by offset.
#include "ascii_string.h"

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

struct Rva005D23BBTemplate
{
	char m_pad00[0x2C];
	AsciiString m_portrait; // +0x2C
};

class Rva002E2903Player
{
public:
	char m_pad00[0x40];
	Rva005D23BBTemplate *m_template; // +0x40
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva005D23BBOwner
{
	char m_pad00[0x13C];
	int m_playerId; // +0x13C
};

struct Rva005D23BBSelection
{
	char m_pad00[0x1C];
	Rva005D23BBOwner *m_owner; // +0x1C
};

namespace StrategicInGameUI
{
const Image *__cdecl GetSelectionPortrait(const Rva005D23BBSelection *selection);
}

const Image *__cdecl StrategicInGameUI::GetSelectionPortrait(const Rva005D23BBSelection *selection)
{
	int playerId = selection->m_owner->m_playerId;
	Rva002E2903Player *player = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerId, 0);
	if (player)
	{
		const AsciiString &portrait = player->m_template->m_portrait;
		if (!((const StringBase<char> *)&portrait)->isEmpty())
			return TheMappedImageCollection->findImageByName(portrait);
	}
	return 0;
}
