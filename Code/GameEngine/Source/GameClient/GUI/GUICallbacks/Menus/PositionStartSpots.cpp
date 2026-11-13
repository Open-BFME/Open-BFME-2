// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?positionStartSpots@@YAXVAsciiString@@PAPAVGameWindow@@PAV2@2@Z
// Retail 0x00303ED4..0x00304259 (901 bytes).
// ZH SkirmishGameOptionsMenu.cpp positionStartSpots(AsciiString) with a
// BFME 2 fourth argument: the map-description listbox (reset first and
// filled with MapMetaData::getDescription at the end). A map missing from
// TheMapCache clears both additional-image lists in place of
// positionAdditionalImages(NULL); both branches then set APT:MapTitle through
// the Apt window manager (L" " or the map's display name).
// Evidence: caller 0x00304259 (the GameInfo wrapper) forwards [ebp+0x14];
// callees GadgetListBoxReset 0x003247E5 / MapCache _M_find 0x001F8437 /
// MapMetaData copy 0x003039E8 and dtor 0x0022DBC6 / getMapPreviewImage
// 0x00300EB4 / MapCache::findMap 0x003024BC / positionAdditionalImages
// 0x00301656 / positionStartSpotControls 0x003001CD / bfmeSetText 0x00225301 /
// GadgetListBoxAddEntryText 0x00326BEC; MissingMap and Player_%d_Start
// literals as in retail.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <list>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

class Image;
#include "../../../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../../../Include/GameClient/Image.h"
extern ImageCollection *TheMappedImageCollection;

struct Rva0057DA21Waypoint
{
	Coord3D pos;
};

#include "../../../../../Include/GameClient/MapMetaData.h"

// MapMetaData +0x38 (opaque in the canonical header): the waypoint map.
typedef _STL::map<AsciiString, Rva0057DA21Waypoint> WaypointMap;
static inline WaypointMap &waypoints(MapMetaData &mmd)
{ return reinterpret_cast<WaypointMap &>(mmd.field38); }

#include "../../../../../Include/GameClient/MapCache.h"
extern MapCache *TheMapCache;

#include "../../../../../../Libraries/Include/Lib/ICoord2D.h"
typedef _STL::list<ICoord2D> ICoord2DList;
#include "../../../../../Include/GameClient/TechAndSupplyImages.h"
extern TechAndSupplyImages TheSupplyAndTechImageLocations;

#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

void GadgetListBoxReset(GameWindow *listbox);
int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);
Image *getMapPreviewImage(AsciiString mapName);
void positionAdditionalImages(MapMetaData *mmd, GameWindow *mapWindow, bool force);
void positionStartSpotControls(GameWindow *win, GameWindow *mapWindow, Coord3D *pos, MapMetaData *mmd, GameWindow *buttonMapStartPositions[]);

enum { WIN_STATUS_IMAGE = 0x80, MAX_SLOTS = 8 };

void positionStartSpots(AsciiString mapName, GameWindow **buttonMapStartPositions, GameWindow *mapWindow, GameWindow *listBox)
{
	if (listBox)
		GadgetListBoxReset(listBox);
	AsciiString lowerMap = mapName;
	((StringBase<char> &)(lowerMap)).toLower();
	MapCache::iterator it = TheMapCache->find(lowerMap);
	if (it == TheMapCache->end())
	{
		mapWindow->winSetUserData(0);

		static const Image *unknownImage = 0;
		if (!unknownImage)
			unknownImage = TheMappedImageCollection->findImageByName("MissingMap");
		if (unknownImage)
		{
			mapWindow->winSetStatus(WIN_STATUS_IMAGE);
			mapWindow->winSetEnabledImage(0, unknownImage);
		}
		else
		{
			mapWindow->winClearStatus(WIN_STATUS_IMAGE);
		}

		TheSupplyAndTechImageLocations.m_supplyPosList.clear();
		TheSupplyAndTechImageLocations.m_techPosList.clear();
		for (int i = 0; i < MAX_SLOTS; ++i)
		{
			if (buttonMapStartPositions[i] != 0)
				buttonMapStartPositions[i]->winHide(true);
		}
		g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:MapTitle"), UnicodeString(L" "), false);
	}
	else
	{
		MapMetaData mmd = it->second;

		Image *image = getMapPreviewImage(mapName);
		if (mapWindow != 0)
		{
			mapWindow->winSetUserData((void *)TheMapCache->findMap(mapName));
			if (image)
			{
				mapWindow->winSetStatus(WIN_STATUS_IMAGE);
				mapWindow->winSetEnabledImage(0, image);
			}
			else
			{
				static const Image *unknownImage = 0;
				if (!unknownImage)
					unknownImage = TheMappedImageCollection->findImageByName("MissingMap");
				if (unknownImage)
				{
					mapWindow->winSetStatus(WIN_STATUS_IMAGE);
					mapWindow->winSetEnabledImage(0, unknownImage);
				}
				else
				{
					mapWindow->winClearStatus(WIN_STATUS_IMAGE);
				}
			}
		}

		positionAdditionalImages(&mmd, mapWindow, true);

		AsciiString waypointName;
		for (int i = 0; i < mmd.m_numPlayers && mmd.m_isMultiplayer; ++i)
		{
			waypointName.format("Player_%d_Start", i + 1);
			WaypointMap::iterator wmIt = waypoints(mmd).find(waypointName);
			if (wmIt != waypoints(mmd).end())
			{
				Coord3D *pos = &(*wmIt).second.pos;
				positionStartSpotControls(buttonMapStartPositions[i], mapWindow, pos, &mmd, buttonMapStartPositions);
				if (buttonMapStartPositions[i] != 0)
					buttonMapStartPositions[i]->winHide(false);
			}
		}
		for (; i < MAX_SLOTS; ++i)
		{
			if (buttonMapStartPositions[i] != 0)
				buttonMapStartPositions[i]->winHide(true);
		}
		{
			AsciiString key("APT:MapTitle");
			g_bfmeAptWindowManager->bfmeSetText(key, mmd.bfme_getDisplayName(true), false);
		}
		if (listBox)
			GadgetListBoxAddEntryText(listBox, mmd.getDescription(), -1, -1, -1, true);
	}
}
