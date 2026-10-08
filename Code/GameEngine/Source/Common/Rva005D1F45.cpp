// cl: /MD
// ?rva005D1F45@Rva005D1F45@@QAEHPAUIRegion2D@@H@Z @0x005D1F45 142B: click-region handler that ignores drags then emits MSG 0x6a8 with two ints plus world location. Evidence: unlock lane; caller 0x005D1FD3 passes region pointer plus int with ret 8; callees rowed appendIntegerArgument 0x0030F936 appendLocationArgument 0x0030F9BB; globals g_009FEF10 MessageStreamSubsystem; IRegion2D layout from GameMessageStructArgs donor.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct IRegion2D
{
	int m_loX;
	int m_loY;
	int m_hiX;
	int m_hiY;
};
struct ICoord2D
{
	int m_x;
	int m_y;
};
struct Coord3D
{
	float m_x;
	float m_y;
	float m_z;
};
class GameMessage
{
public:
	void appendIntegerArgument(int arg);
	void appendLocationArgument(const Coord3D &arg);
};
class MessageStream
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *appendType(int type);
};
class Rva002BA8F1Logic;

extern MessageStream *TheMessageStream;
class ViewConv
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void w10();
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void conv(const ICoord2D *cell, Coord3D *pos);
};
class SubData
{
public:
	unsigned char m_pad[0x12C];
	int m_12C;
};
class Holder8
{
public:
	unsigned char m_pad[0x1C];
	SubData *m_1C;
};
class OtherC
{
public:
	unsigned char m_pad[0x20];
	int m_20;
};
class Rva005D1F45
{
public:
	int rva005D1F45(IRegion2D *region, int unused);
private:
	void *m_00;
	ViewConv *m_04;
	Holder8 *m_08;
	OtherC *m_0C;
};
int Rva005D1F45::rva005D1F45(IRegion2D *region, int unused)
{
	(void)unused;
	if (region->m_hiX - region->m_loX > 0)
		return 0;
	if (region->m_hiY - region->m_loY > 0)
		return 0;
	if ((*(Rva002BA8F1Logic **)&TheLivingWorldLogic) == 0)
		return 0;
	Holder8 *holder = m_08;
	SubData *sub = holder->m_1C;
	if (sub == 0)
		return 0;
	ICoord2D cell;
	Coord3D pos;
	cell.m_x = region->m_loX;
	cell.m_y = region->m_loY;
	m_04->conv(&cell, &pos);
	GameMessage *msg = TheMessageStream->appendType(0x6A8);
	msg->appendIntegerArgument(m_0C->m_20);
	msg->appendIntegerArgument(sub->m_12C);
	msg->appendLocationArgument(pos);
	return 0;
}
