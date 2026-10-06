// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005F6F0C@Rva005F6F0C@@QAEXXZ retail 0x005F6F0C 57B
// Evidence: flag at +0x28 gates TheGameText fetch STRATEGICHUD:ConstructionTurnsRemainingTooltip at slot 0x3c plus Mouse rva001EEA6D with -1 0 1.0f; callers 0x005F7455 0x005F7462; precedent Rva005F06EF in Rva005F0647Deleting.cpp
#include "unicode_string.h"

struct RGBColor { float red, green, blue; };

class Mouse
{
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};

class GameTextInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;
extern Mouse *TheMouse;

struct Rva005F6F0C
{
	char m_pad[0x28];
	bool m_flag28;
	void rva005F6F0C();
};

void Rva005F6F0C::rva005F6F0C()
{
	if (m_flag28)
		TheMouse->rva001EEA6D(TheGameText->fetch("STRATEGICHUD:ConstructionTurnsRemainingTooltip"), -1, 0, 1.0f);
}
