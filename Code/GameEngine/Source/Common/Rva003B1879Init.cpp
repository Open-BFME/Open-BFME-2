// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
//
// ?rva003B1879@Rva003B1820@@QAEXXZ @0x003B1879 (123B):
// Table initializer for Rva003B1820 (owner of the 6-entry lookup at
// 0x003B1820 and the entry setter at 0x003B1853 which this calls).
// Builds a 6-pair local table {value name} on the stack with the retail
// literals (note 5 before 4) then calls the rowed entry setter for each
// pair at entry[value]. String literals link; the setter resolves by its
// row name through a cast since entries are opaque 0x14 pads here.
// Evidence: chain lane after 0x003B1853, all callees rowed, no callers.
class Rva003B1853
{
public:
	void rva003B1853(const char *name, int value);
};

class Rva003B1820
{
public:
	void rva003B1879();
private:
	char m_pad[0x0C]; // +0x00..+0x0B
	char m_entries[6][0x14]; // +0x0C opaque entries stride 0x14
};

void Rva003B1820::rva003B1879()
{
	struct Pair
	{
		int value;
		const char *name;
	};
	Pair pairs[6] =
	{
		{ 0, "RiverTextures" },
		{ 1, "WaterBumpMapTextures" },
		{ 2, "RiverAlphaEdgeTextures" },
		{ 3, "WaterSkyTextures" },
		{ 5, "RiverSparkleTextures" },
		{ 4, "RiverNoiseTextures" },
	};
	for (int i = 0; i < 6; ++i)
		((Rva003B1853 *)&m_entries[pairs[i].value])->rva003B1853(pairs[i].name, pairs[i].value);
}
