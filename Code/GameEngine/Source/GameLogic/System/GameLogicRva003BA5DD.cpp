// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva003BA5DD@GameLogic@@QAEXH@Z @0x003BA5DD 21B: GameLogic clamp-min-1 setter at +0x118.
// Evidence: mov eax,[esp+4] cmp eax,1 jge store xor eax,eax inc eax store at
// [ecx+0x118] ret 4; sole caller 0x003BC6C7 loads TheGameLogic 0x00DFE78C and
// tail-jmps here proving GameLogic ownership; +0x110 gameMode +0x114 unk proven
// by siblings; clamp to >=1 suggests rank/limit-style field.

class GameLogic
{
public:
	void rva003BA5DD(int value);
private:
	char m_pad[0x118];
	int m_118;
};

void GameLogic::rva003BA5DD(int value)
{
	if (value < 1)
		value = 1;
	m_118 = value;
}
