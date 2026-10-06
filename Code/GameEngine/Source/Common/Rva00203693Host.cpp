// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00203693@Rva00203693Host@@QAEHXZ at retail 0x00203693 (22B).
// Returns 2 when TheGameLogic->rva001DCD1C() is true, else 1.
// Target evidence: mov ecx,[0xDFE78C]; call rowed
// ?rva001DCD1C@GameLogic@@QAE_NXZ; xor ecx,ecx; test al,al;
// setne cl; inc ecx; mov eax,ecx. Callers at 0x002096E7, 0x0020C5F5,
// 0x0020CB0C pass this in ecx (ignored) and test the int result.

class GameLogic
{
public:
	bool rva001DCD1C();
};
extern GameLogic *TheGameLogic;


class Rva00203693Host
{
public:
	int rva00203693();
};

int Rva00203693Host::rva00203693()
{
	return TheGameLogic->rva001DCD1C() ? 2 : 1;
}
