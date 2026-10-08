// cl: /MD
// ?rva0023D29F@Rva0023D29F@@QAEXXZ, retail 0x0023D29F, 57 bytes.
// If TheNetwork set and !isPacketRouter return; else emit GameMessage 0x6a5 with +0x38 and set +0x3c.
// Evidence: leaf lane; caller 0x0023DA1E; slots 0xAC bool and 0x48 GameMessage*(int) per NetworkInterfaceFramePacing/Rva0051B09BEnable; rowed appendIntegerArgument 0x0030F936.
class GameMessage
{
public:
	void appendIntegerArgument(int arg);
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
	virtual GameMessage *v18(int type);
};
extern class MessageStream *TheMessageStream;
class NetworkInterface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual bool isPacketRouter();
};
extern NetworkInterface *TheNetwork;
class Rva0023D29F
{
public:
	void rva0023D29F();
private:
	char m_pad[0x38];
	int m_38;
	unsigned char m_3c;
};
void Rva0023D29F::rva0023D29F()
{
	if (TheNetwork != 0 && !TheNetwork->isPacketRouter())
		return;
	GameMessage *msg = TheMessageStream->v18(0x6a5);
	msg->appendIntegerArgument(m_38);
	m_3c = 1;
}
