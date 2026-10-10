// cl: /MD
// ?rva0029AA3F@Rva0029AA3F@@QAEXXZ @0x0029AA3F 35B. Emit 0x467 then location at +0x9B8. Evidence: rowed appendLocationArgument 0x0030F9BB global MessageStreamSubsystem slot 0x48 appendType pattern Rva005D1F45 caller 0x00431A21.
struct Coord3D
{
	float m_x;
	float m_y;
	float m_z;
};
class GameMessage
{
public:
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
extern class MessageStream *TheMessageStream;
class GameClient;
extern GameClient *TheGameClient;
#define GAMECLIENT_UNUSED_8(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3(); 	virtual void n##4(); virtual void n##5(); virtual void n##6(); virtual void n##7()
struct GameClientFrameSlots
{
	GAMECLIENT_UNUSED_8(s00); GAMECLIENT_UNUSED_8(s20); GAMECLIENT_UNUSED_8(s40);
	virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6C();
	virtual void s70(); virtual void s74(); virtual void s78();
	virtual unsigned int getFrame();	// +0x7C
};
#undef GAMECLIENT_UNUSED_8
class Rva0029AA3F
{
public:
	void rva0029AA3F();
	void rva0029A9FF(const Coord3D *src);
	void rva0029AA62(const Coord3D *src);
	void rva0029AAC8(const Coord3D *src);
private:
	unsigned char m_pad[0x59C];
	int m_59C;
	unsigned char m_pad5A0[0x5AC - 0x5A0];
	unsigned int m_frame5AC;
	bool m_5B0;
	unsigned char m_pad5B1[0x98C - 0x5B1];
	bool m_active98C;
	bool m_98D;
	unsigned char m_pad98E[0x990 - 0x98E];
	Coord3D m_start;
	Coord3D m_unknown;
	unsigned char m_pad2[0x8];
	int m_9B0;
	bool m_has;
	unsigned char m_pad3[0x3];
	Coord3D m_pos;
};

void Rva0029AA3F::rva0029AA3F()
{
	GameMessage *msg = TheMessageStream->appendType(0x467);
	msg->appendLocationArgument(m_pos);
}

void Rva0029AA3F::rva0029A9FF(const Coord3D *src)
{
	if (src != 0) {
		m_has = true;
		m_pos = *src;
	} else {
		m_has = false;
	}
}

void Rva0029AA3F::rva0029AAC8(const Coord3D *src)
{
	if (src != 0)
		m_unknown = *src;
}

// Native 0x0029AA62..0x0029AAC8 (102B, RET 4), the InGameUI vtable slot
// (0x7C7B4C) between 0x0036739C and rva0029AAC8: given a position it seeds
// both the +0x990 and +0x99C points from it, marks +0x98C active, stamps the
// game client frame (vtable +0x7C) at +0x5AC and clears +0x59C/+0x98D;
// without one it only clears +0x98C. Either way +0x9B0 becomes -1 and +0x5B0
// false. Field roles beyond these stores are not established.
void Rva0029AA3F::rva0029AA62(const Coord3D *src)
{
	if (src != 0) {
		m_start = *src;
		m_unknown = *src;
		m_active98C = true;
		m_frame5AC = reinterpret_cast<GameClientFrameSlots *>(TheGameClient)->getFrame();
		m_59C = 0;
		m_98D = false;
	} else {
		m_active98C = false;
	}
	m_9B0 = -1;
	m_5B0 = false;
}
