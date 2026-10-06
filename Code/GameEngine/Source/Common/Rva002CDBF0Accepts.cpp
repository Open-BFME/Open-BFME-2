// cl: /Ob0
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva002CDBF0Accepts.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?check@Rva002CDBF0@@QAE_NPAVObject@@@Z 0x004A1475 (49B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

class Player;
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

struct Rva2225E0Filter
{
	bool accepts(Object *value, Player *player);
};

struct HoldRva002CDBF0
{
	char m_lead[0x10];
	Rva2225E0Filter m_filter;
};

class Rva002CDBF0
{
public:
	bool check(Object *value);

	char m_pad[0x69];
	unsigned char m_flag;
};

bool Rva002CDBF0::check(Object *value)
{
	Object *ctx = *(Object **)((char *)this - 0x18);
	HoldRva002CDBF0 *hold = *(HoldRva002CDBF0 **)((char *)this - 0x1C);
	if (hold->m_filter.accepts(value, ctx->getControllingPlayer()) && !m_flag)
		return true;
	return false;
}
