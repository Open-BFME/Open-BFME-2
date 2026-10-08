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
class Rva0029AA3F
{
public:
	void rva0029AA3F();
	void rva0029A9FF(const Coord3D *src);
	void rva0029AAC8(const Coord3D *src);
private:
	unsigned char m_pad[0x99C];
	Coord3D m_unknown;
	unsigned char m_pad2[0xC];
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
