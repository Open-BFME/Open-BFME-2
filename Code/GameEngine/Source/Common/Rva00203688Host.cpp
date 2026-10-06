// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00203688@Rva00203688Host@@QAE_NXZ at retail 0x00203688 (11B).
// Opaque-host tail-jump wrapper: return TheGameLogic->rva001DCD1C().
// Target evidence: mov ecx,[0xDFE78C] then jmp to rowed
// ?rva001DCD1C@GameLogic@@QAE_NXZ; caller at 0x003B245A loads
// TheScriptEngine and compares the bool result. Precedent:
// Rva00203B47Host::rva00203B47 (opaque host ignoring this, // cl: /O1).

class GameLogic
{
public:
	bool rva001DCD1C();
};
extern GameLogic *TheGameLogic;


class Rva00203688Host
{
public:
	bool rva00203688();
};

bool Rva00203688Host::rva00203688()
{
	return TheGameLogic->rva001DCD1C();
}
