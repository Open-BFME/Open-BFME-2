// AptMapPreview: canonical declarations for the members 11 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTMAPPREVIEW_H
#define CANONICAL_APTMAPPREVIEW_H

class AsciiString;
class MapMetaData;

class AptMapPreview
{
public:
	int GetCurrentStrategicScenario();
	int GetMaxNumPlayers();
	void *GetStartPositionInfoForSlot(int slot);
	bool IsValidStartPosition(int value);
	void UpdateMapTitle(MapMetaData *map);
	void UpdateStrategicStartSpots();
	int rva0057C57B(int window);
	void rva0057C597(bool enable);
	void rva0057CD66();
	void rva0057D5E5();
	MapMetaData *rva0057D922(const AsciiString &mapName);
	void rva0057E058();
	void rva0057E45C();
};

#endif // CANONICAL_APTMAPPREVIEW_H
