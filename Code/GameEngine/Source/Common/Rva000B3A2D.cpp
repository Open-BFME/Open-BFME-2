// cl: /MD
// ?rva000B3A2D@Rva000B3A2D@@QAEXXZ @0x000B3A2D 59B
// Unlock lane: validate wide string at +0, int global g_Va00DE1B40 to +0xb8,
// TheGameClient slot 0x7c int to g_Va00DB3BDC, if int at +0x214 >=0 call
// subobject at +0xc slot 0x60 with (val != 0). Callers 0x000CDE4A 0x000CEA3C
// 0x000CA132. Neighbours Rva000B3814/Rva000B3A68.
template <typename T>
class StringBase
{
	friend class Rva000B3A2D;
	void validate() const;
};

class ClientFrameSubsystem
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual int s31();
};

class ClientFrameSubsystem; extern class GameClient *TheGameClient;

extern int g_Va00DE1B40;
extern int g_Va00DB3BDC;

class Sub0C
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(bool x);
};

class Rva000B3A2D
{
public:
	void rva000B3A2D();
private:
	char m_pad00[0xb8];
	int m_b8;
	char m_padBC[0x214 - 0xbc];
	int m_214;
};

void Rva000B3A2D::rva000B3A2D()
{
	((StringBase<unsigned short> *)this)->validate();
	m_b8 = g_Va00DE1B40;
	g_Va00DB3BDC = ((ClientFrameSubsystem *)TheGameClient)->s31();
	int v = m_214;
	if (v < 0)
		return;
	((Sub0C *)((char *)this + 0xc))->s24(v != 0);
}
