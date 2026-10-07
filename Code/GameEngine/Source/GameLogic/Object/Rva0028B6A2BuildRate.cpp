// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ghidra FUN_0068b6a2 gives a 52-byte boundary. Retail asks Object for its
// controlling player, then calls the pinned ThingTemplate helper with
// (player, 0, -1) and divides the shared 1.0f literal by its integer result.
// With no controlling player it loads the shared zero at VA 0x00BBAEAC.
// The host's +4 template pointer and the helper's existing target identity
// provide the layout evidence; the method label remains address-derived.

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class ThingTemplate
{
public:
	int rva0033AA1F(const Player *player, int second, int third) const;
};

extern float g_00BBB8D8;
extern const float BfmeZeroRange; // data-ledger zero at VA 0x00BBAEAC

class Rva0028B6A2Host
{
public:
	float rva0028B6A2();

private:
	char m_pad00[4];
	const ThingTemplate *m_template;
};

float Rva0028B6A2Host::rva0028B6A2()
{
	const Player *player = ((const Object *)this)->getControllingPlayer();
	if (!player)
		return BfmeZeroRange;
	int buildFrames = m_template->rva0033AA1F(player, 0, -1);
	return g_00BBB8D8 / (float)buildFrames;
}
