// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy-
//
// ?rva00330A37@Rva00330A37@@QAEXHHHHHHHH@Z @0x00330A37 103B
// Unlock lane: 8-int init with frame base from the dword global at
// 0x009FE77C via its slot 0x7c virtual; -1 sentinel pairs at +38/+3C
// and +44/+4C/+50 with cumulative adds. Statements follow retail order.
// Callers 0x000C58C2 0x000C5A60 0x001091E7 0x0010C74F 0x001E1058.
struct FrameSource
{
	virtual int v00();
	virtual int v01();
	virtual int v02();
	virtual int v03();
	virtual int v04();
	virtual int v05();
	virtual int v06();
	virtual int v07();
	virtual int v08();
	virtual int v09();
	virtual int v10();
	virtual int v11();
	virtual int v12();
	virtual int v13();
	virtual int v14();
	virtual int v15();
	virtual int v16();
	virtual int v17();
	virtual int v18();
	virtual int v19();
	virtual int v20();
	virtual int v21();
	virtual int v22();
	virtual int v23();
	virtual int v24();
	virtual int v25();
	virtual int v26();
	virtual int v27();
	virtual int v28();
	virtual int v29();
	virtual int v30();
	virtual int getFrame();
};

class ClientFrameSubsystem;
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class Rva00330A37
{
public:
	void rva00330A37(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
private:
	char m_pad[0x38];
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
};
void Rva00330A37::rva00330A37(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	int frame = reinterpret_cast<FrameSource *>(((ClientFrameSubsystem *)TheGameClient))->getFrame();
	int base1 = a1 + frame;
	m_38 = base1;
	if (a2 == -1)
		m_3C = -1;
	else
		m_3C = frame + a2;
	m_40 = a3;
	int base2 = a4 + base1;
	m_48 = a5;
	m_44 = base2;
	if (a6 == -1)
	{
		m_4C = -1;
		m_50 = a7;
	}
	else
	{
		m_4C = base2 + a6;
		m_50 = base2 + a6 + a7;
	}
	m_54 = a8;
}
