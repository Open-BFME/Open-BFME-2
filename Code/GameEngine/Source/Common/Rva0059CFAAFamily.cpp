// cl: -GR- -EHsc-
// The twin forwarders 0x0059D1A9 / 0x0059D1C3, spelled as
// LivingWorldAIBuilder thiscall members returning float (WorldBuilder twins
// 0x014FE620 / 0x014FE650 save ECX and pass it on with mov ecx this; the
// retail bodies never touch ECX so it reaches the callee unchanged).
class Rva0059CFAACallee;
struct Rva0059CFAARegion;
class LivingWorldAIBuilder
{
public:
	float rva0059CF34(int playerId, int count, Rva0059CFAACallee *armies,
		Rva0059CFAARegion *const &region);
	float rva0059CFAA(int playerId, int count, Rva0059CFAACallee *armies,
		Rva0059CFAARegion *const &region);
	float rva0059D1A9(int playerId, int count, Rva0059CFAACallee *armies,
		Rva0059CFAARegion *const &region);
	float rva0059D1C3(int playerId, int count, Rva0059CFAACallee *armies,
		Rva0059CFAARegion *const &region);
};

float LivingWorldAIBuilder::rva0059D1A9(int playerId, int count,
	Rva0059CFAACallee *armies, Rva0059CFAARegion *const &region)
{
	return rva0059CF34(playerId, count + 1, armies, region);
}

float LivingWorldAIBuilder::rva0059D1C3(int playerId, int count,
	Rva0059CFAACallee *armies, Rva0059CFAARegion *const &region)
{
	return rva0059CFAA(playerId, count + 1, armies, region);
}
