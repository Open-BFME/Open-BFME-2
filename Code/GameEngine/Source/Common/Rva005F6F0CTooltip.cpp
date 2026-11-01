// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Update@Rva005F6F0C@@QAEXXZ retail 0x005F6F0C 57B
// Evidence: flag at +0x28 gates TheGameText fetch STRATEGICHUD:ConstructionTurnsRemainingTooltip at slot 0x3c plus Mouse rva001EEA6D with -1 0 1.0f; callers 0x005F7455 0x005F7462; precedent Rva005F06EF in Rva005F0647Deleting.cpp
#include "unicode_string.h"

#include "../../../Libraries/Include/Lib/RGBColor.h"

#include "../../Include/GameClient/Mouse.h"

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;
extern Mouse *TheMouse;

struct Rva005F6F0C
{
	char m_pad[0x28];
	bool m_flag28;
	void Update();
};

void Rva005F6F0C::Update()
{
	if (m_flag28)
		TheMouse->rva001EEA6D(TheGameText->fetch("STRATEGICHUD:ConstructionTurnsRemainingTooltip"), -1, 0, 1.0f);
}
