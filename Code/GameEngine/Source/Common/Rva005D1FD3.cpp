// cl: /MD
// ?rva005D1FD3@Rva005D1F45@@QAEHPAVGameMessage@@@Z @0x005D1FD3 51B: message-type 0x1b dispatcher that forwards arg0 region plus arg1 int to rva005D1F45. Evidence: chain lane calls 0x005D1F45 just landed; callers 0x005771F4 0x005CDE28; callees rowed getArgument 0x0030F4EA.
struct IRegion2D
{
	int m_loX;
	int m_loY;
	int m_hiX;
	int m_hiY;
};
union GameMessageArgumentType
{
	int integer;
	float real;
	struct PixReg
	{
		int loX;
		int loY;
		int hiX;
		int hiY;
	} pixelRegion;
};
class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(int argIndex) const;
	int getType() const;
	unsigned char m_pad[0x10];
	int m_type;
};
class Rva005D1F45
{
public:
	int rva005D1F45(IRegion2D *region, int val);
	int rva005D1FD3(GameMessage *msg);
};
int Rva005D1F45::rva005D1FD3(GameMessage *msg)
{
	if (msg->m_type != 0x1b)
		return 0;
	return rva005D1F45((IRegion2D *)msg->getArgument(0), msg->getArgument(1)->integer);
}
