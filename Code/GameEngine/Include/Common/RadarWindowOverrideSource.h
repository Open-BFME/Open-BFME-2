// RadarWindowOverrideSource: canonical declarations for the members 20 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RADARWINDOWOVERRIDESOURCE_H
#define CANONICAL_RADARWINDOWOVERRIDESOURCE_H

struct BfmePod8;
class GameWindow;
class RadarEventRefSlot;
struct TreeHintRef00217D4C;

class RadarWindowOverrideSource
{
public:
	void ShowHelpBox(const TreeHintRef00217D4C &hint);
	GameWindow *getOverrideWindow() const;
	bool hasOverrideWindow() const;
	void rva002D337F();
	void rva002D3615(bool value);
	void rva002D370A();
	void rva002D3772(int a, float b);
	void rva002D4240(bool hide);
	RadarEventRefSlot rva002D508B(const char *name);
	void rva002D55D2(const BfmePod8 *corners);
	void rva002D55EF();
};

#endif // CANONICAL_RADARWINDOWOVERRIDESOURCE_H
