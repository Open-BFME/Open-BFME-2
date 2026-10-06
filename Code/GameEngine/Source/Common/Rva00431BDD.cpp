// cl: /MD
// FormationTranslator::WaitForSecondButtonDownStateHandler::IsStartOfDrag (WorldBuilder name, FormationTranslator.cpp line 338: message type vs +0x08, pixel proximity via 0x00431978, time delta under 500).
// ?rva00431BDD@Rva00431BDD@@QAE_NPAVGameMessage@@@Z @0x00431BDD 88B: thiscall bool method checking GameMessage+0x10 vs this+8 then pixel proximity via rowed 0x00431978 plus int arg2 minus this+0x18 unsigned < 500. Evidence: chain lane calls rowed 0x00431978 just landed; rowed getArgument 0x0030F4EA; callers 0x00432068; neighbours Rva00431B76 Rva00431C35 same layout. Retail test al proves bool callee; row type H is wrong, bool used.
struct ICoord2D
{
	int m_x;
	int m_y;
};

union GameMessageArgumentType
{
	int integer;
	float real;
	int boolean;
	int objectID;
	struct Pix { int x; int y; } pixel;
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(int argIndex) const;
private:
	char m_pad[0x10];
	int m_10;
};

class Rva00431978
{
	char m_pad[0x0c];
	ICoord2D m_0C;
public:
	bool rva00431978(ICoord2D *p);
};

class FormationTranslator
{
public:
	class WaitForSecondButtonDownStateHandler;
};
class FormationTranslator::WaitForSecondButtonDownStateHandler
{
	void *m_00;
	void *m_04;
	int m_08;
	ICoord2D m_0C;
	int m_14;
	int m_18;
public:
	bool IsStartOfDrag(GameMessage *msg);
};

bool FormationTranslator::WaitForSecondButtonDownStateHandler::IsStartOfDrag(GameMessage *msg)
{
	int t = *(int *)((char *)msg + 0x10);
	if (t == m_08)
		return false;
	const GameMessageArgumentType *a0 = msg->getArgument(0);
	int x = a0->pixel.x;
	int y = a0->pixel.y;
	ICoord2D tmp;
	tmp.m_y = y;
	tmp.m_x = x;
	if (!((Rva00431978 *)this)->rva00431978(&tmp))
		return false;
	int v = msg->getArgument(2)->integer;
	v -= m_18;
	return (unsigned int)v < 0x1f4;
}
