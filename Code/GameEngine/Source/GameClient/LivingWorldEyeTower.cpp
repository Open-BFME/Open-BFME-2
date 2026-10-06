// cl: /DNDEBUG /MD /GX-
// ?getPair@LivingWorldEyeTower@@AAEPAXXZ @0x003F9A2B 110B
// LivingWorldEyeTower::getPair transferred from BFME1 donor
// reference/open-bfme-1/game/GameEngine/Source/GameClient/LivingWorldEyeTower.cpp.
// Retail evidence: file literal GameClient/LivingWorld/LivingWorldEyeTower.cpp line 355 (0x163),
// GetGameLogicRandomValue(0 count-1) shape, vector at +0x3C/+0x40 with 8B elements,
// callers 0x003F9A99 and 0x003F9B5A share the same +0x3C/+0x40 layout. Donor default
// 1930.0f/210.0f kept; constant values are relocations and do not affect code bytes.
// Return is void* to avoid inventing the 8B element struct name; access private per donor.

int GetGameLogicRandomValue(int low, int high, char *file, int line);

struct EyeTowerPair
{
	EyeTowerPair(float x, float y) : first(x), second(y) {}
	~EyeTowerPair() {}
	float first;
	float second;
};

class LivingWorldEyeTower
{
	char m_head[0x3C];
	EyeTowerPair *m_begin;
	EyeTowerPair *m_end;
	EyeTowerPair *m_capacity;
	void *getPair();
};

void *LivingWorldEyeTower::getPair()
{
	static EyeTowerPair defaultPoint(1930.0f, 210.0f);
	unsigned int count = (unsigned int)(m_end - m_begin);
	if (count == 0)
		return &defaultPoint;
	int index = GetGameLogicRandomValue(0, count - 1,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\LivingWorld\\LivingWorldEyeTower.cpp", 355);
	return &m_begin[index];
}
