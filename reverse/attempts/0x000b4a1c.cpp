// ?pickRandomAnimation@AnimConditionInfo@@QAEHHH@Z
// partial score=0.8 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?pickRandomAnimation@AnimConditionInfo@@QAEHHH@Z, retail 0x000B4A1C..0x000B4A9F (131
// bytes, ret 8). Named by its WorldBuilder twin (AnimConditionInfo::pickRandomAnimation,
// W3DScriptedModelDraw.cpp:1118, callgraph evidence); the animation vector sits at +0x50/+0x54
// in retail (+0x54/+0x58 in the debug build), 0x40 bytes per entry with the draw weight at
// +0x30. Pick a client-random index weighted by those weights over the first `count`
// entries, with the excluded entry's weight reduced by one; fewer than two entries pick 0.
int GetGameClientRandomValue(int lo, int hi, char *file, int line);

struct AnimConditionEntry
{
	char m_pad00[0x30];
	int m_weight;		// +0x30
	char m_pad34[0x40 - 0x34];
};

class AnimConditionInfo
{
public:
	int pickRandomAnimation(int count, int exclude);
	char m_pad00[0x50];
	AnimConditionEntry *m_begin;	// +0x50
	AnimConditionEntry *m_end;	// +0x54
};

int AnimConditionInfo::pickRandomAnimation(int count, int exclude)
{
	int n = m_end - m_begin;
	if (n > count)
		n = count;
	if (n < 2)
		return 0;
	int total = 0;
	for (int i = 0; i < n; ++i) {
		int weight = m_begin[i].m_weight;
		if (i == exclude)
			weight = weight - 1;
		total += weight;
	}
	int roll = GetGameClientRandomValue(0, total - 1,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DScriptedModelDraw.cpp", 0x45E);
	for (int i = 0; i < n; ++i) {
		int weight = m_begin[i].m_weight;
		if (i == exclude)
			weight = weight - 1;
		roll -= weight;
		if (roll < 0)
			return i;
	}
	return 0;
}
