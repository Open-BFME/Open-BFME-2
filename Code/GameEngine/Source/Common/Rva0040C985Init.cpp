// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0040C985@ArmySummary@@QAEXH@Z, retail 0x0040C985, 31 bytes.
// Target evidence: leaf with 3 callers at 0x002B7A97 0x0040D3AE 0x0040F860; no vtable slot;
// touches +0x2C +0x30 +0x34 +0x38; prev ringobj.cpp next Disp8SubDwordFieldGetters.cpp.
class Rva00DFE78C
{
public:
	char m_pad[0x40];
	int m_40;
};
class GameLogic;
extern GameLogic *TheGameLogic;

class Rva00DFE758
{
public:
	char m_pad[0x134];
	int m_timeOfDay;
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
#include "../../Include/GameLogic/ArmySummary.h"

void ArmySummary::rva0040C985(int startFrame)
{
	if (field2C == 0) {
		field2C = 2;
		field38 = startFrame;
		field34 = field30 + startFrame;
	}
}
int ArmySummary::rva0040C9F4()
{
	int frame = ((Rva00DFE78C *)TheGameLogic)->m_40;
	int val = field34;
	if (frame < val)
		return val - frame;
	return 0;
}
void ArmySummary::rva0040CA09()
{
	int frame = ((Rva00DFE78C *)TheGameLogic)->m_40;
	if ((unsigned)frame < (unsigned)field34)
		return;
	if (field2C != 2)
		return;
	field2C = 3;
}
int ArmySummary::rva0040CA24()
{
	if (((Rva00DFE758 *)TheWritableGlobalData)->m_timeOfDay == 4)
		return field28;
	return field24;
}

extern float LOGICFRAMES_PER_SECONDS_REAL;
// g_00DBA4F4: matched references place it at VA 0xdba4f4 (retail .data initial value 5.0f).
float LOGICFRAMES_PER_SECONDS_REAL = 5.0f;

void ArmySummary::rva0040CA3A(int delaySeconds)
{
	field2C &= 0;
	field30 = (int)((float)delaySeconds * LOGICFRAMES_PER_SECONDS_REAL);
}
