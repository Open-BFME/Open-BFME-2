// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?rva00594A06@UDP@@QAEHXZ @0x00594A06 118B WSA error to internal code map.
// Retail reads int at +0x1c, returns 0 if 0, else maps 0x2714->-10 0x2734->-3
// 0x274D->-9 0x2726->-14 0x2748->-2 0x2736->-11 0x274C->-15 0x2735->-4
// 0x2733->-13 0x2719->-8 (plus tail). Evidence: unlock lane; neighbours
// udp.cpp/Rva00594C12Write share flags; push-pop negatives imply /O1;
// callers at 0x004D54E4/0x004D5515; unblocks 0x00595213/0x004D54C1/0x00594B56.
class UDP
{
public:
	int rva00594A06();

private:
	unsigned char m_pre[0x04];
	unsigned int m_ip;
	unsigned short m_port;
	unsigned char m_pad[0x1C - 0x0A];
	int m_err;
};

int UDP::rva00594A06()
{
	int e = m_err;
	if (e == 0)
		return e;
	if (e == 0x2714)
		return -10;
	if (e == 0x2734)
		return -3;
	if (e == 0x274D)
		return -9;
	if (e == 0x2726)
		return -14;
	if (e == 0x2748)
		return -2;
	if (e == 0x2736)
		return -11;
	if (e == 0x274C)
		return -15;
	if (e == 0x2735)
		return -4;
	if (e == 0x2733)
		return -13;
	if (e == 0x2719)
		return -8;
	return e;
}
