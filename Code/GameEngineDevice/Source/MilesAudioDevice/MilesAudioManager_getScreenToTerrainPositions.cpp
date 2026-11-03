// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
// ?getScreenToTerrainPositions@MilesAudioManager@@QAEXPAUScreenToTerrainSet@@@Z @0x0005294A 499B.
// MilesAudioManager::getScreenToTerrainPositions: fills five listener sample
// points (screen centre and the four corners, in that order) with the terrain
// position under each pixel. The mode at +0x678 selects the tactical view
// (screenToTerrain, vslot 90, result is the validity byte) or the second
// host (g_00DFEF18 vslot 14, validity always true); any other mode, or a
// missing host, leaves five zeroed invalid entries.
// Evidence (target): WorldBuilder twin 0x78A0C0 is
// MilesAudioManager::getScreenToTerrainPositions (MilesAudioManager.cpp 4934).
// Display widths and heights are unsigned (shr 1); the tactical view's are
// signed (cdq/sub/sar). Entry stride 0x10 = Coord3D + validity byte at +0xC.
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"

struct ScreenToTerrainEntry
{
	Coord3D m_pos;
	bool m_valid;
};

class ScreenToTerrainSet
{
public:
	ScreenToTerrainEntry m_entry[5];
};

#include "../../../GameEngine/Include/GameClient/View.h"

#include "../../../GameEngine/Include/GameClient/Display.h"

class Rva002D3627Host
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world);	// slot 14
};

extern View *TheTacticalView;
extern Display *TheDisplay;
class LivingWorld; extern LivingWorld *TheLivingWorld;

#include "../../Include/MilesAudioDevice/MilesAudioManager.h"

void MilesAudioManager::getScreenToTerrainPositions(ScreenToTerrainSet *out)
{
	ICoord2D pixel;
	switch (m_678) {
	case 1:
		if (((Rva002D3627Host *)TheLivingWorld) != 0 && TheDisplay != 0) {
			pixel.x = TheDisplay->getWidth() >> 1;
			pixel.y = TheDisplay->getHeight() >> 1;
			out->m_entry[0].m_valid = true;
			((Rva002D3627Host *)TheLivingWorld)->screenToTerrain(&pixel, &out->m_entry[0].m_pos);
			pixel.x = 0;
			pixel.y = 0;
			out->m_entry[1].m_valid = true;
			((Rva002D3627Host *)TheLivingWorld)->screenToTerrain(&pixel, &out->m_entry[1].m_pos);
			pixel.y = TheDisplay->getHeight() - 1;
			out->m_entry[2].m_valid = true;
			((Rva002D3627Host *)TheLivingWorld)->screenToTerrain(&pixel, &out->m_entry[2].m_pos);
			pixel.x = TheDisplay->getWidth() - 1;
			out->m_entry[3].m_valid = true;
			((Rva002D3627Host *)TheLivingWorld)->screenToTerrain(&pixel, &out->m_entry[3].m_pos);
			pixel.y = 0;
			out->m_entry[4].m_valid = true;
			((Rva002D3627Host *)TheLivingWorld)->screenToTerrain(&pixel, &out->m_entry[4].m_pos);
			return;
		}
		break;
	case 0:
		if (TheTacticalView != 0) {
			pixel.x = TheTacticalView->getWidth() / 2;
			pixel.y = TheTacticalView->getHeight() / 2;
			out->m_entry[0].m_valid = TheTacticalView->screenToTerrain(&pixel, &out->m_entry[0].m_pos, false);
			pixel.x = 0;
			pixel.y = 0;
			out->m_entry[1].m_valid = TheTacticalView->screenToTerrain(&pixel, &out->m_entry[1].m_pos, false);
			pixel.y = TheTacticalView->getHeight() - 1;
			out->m_entry[2].m_valid = TheTacticalView->screenToTerrain(&pixel, &out->m_entry[2].m_pos, false);
			pixel.x = TheTacticalView->getWidth() - 1;
			out->m_entry[3].m_valid = TheTacticalView->screenToTerrain(&pixel, &out->m_entry[3].m_pos, false);
			pixel.y = 0;
			out->m_entry[4].m_valid = TheTacticalView->screenToTerrain(&pixel, &out->m_entry[4].m_pos, false);
			return;
		}
		break;
	}
	for (int i = 0; i < 5; ++i) {
		out->m_entry[i].m_valid = false;
		out->m_entry[i].m_pos.x = 0.0f;
		out->m_entry[i].m_pos.y = 0.0f;
		out->m_entry[i].m_pos.z = 0.0f;
	}
}
