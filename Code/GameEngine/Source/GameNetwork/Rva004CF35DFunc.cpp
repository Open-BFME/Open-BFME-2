// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva004CF35D@Rva004CF35D@@QAEXPAVNetWrapperCommandMsg@@@Z @ 0x004CF35D 85B
// Thiscall with one NetWrapperCommandMsg arg, void return, ret 4. Checks
// msg->getData() as small int index 0-7 via 4 separate rowed getData calls
// plus rowed getDataLength, flags at +0x12080 and lens at +0x120a0.
// Row getData returns UnsignedByte* but body uses value 0-7 as index;
// declare as pointer to match row (cf Rva0023C666Check GetsData==1).
// Evidence: caller 0x004D3031 in 0x004D2F04, callees rowed 0x0030F2C7
// getData and 0x0030D377 getDataLength, neighbours Connection TUs.
class NetWrapperCommandMsg
{
public:
	unsigned char *getData();
	unsigned int getDataLength();
};

class Rva004CF35D
{
public:
	void rva004CF35D(NetWrapperCommandMsg *msg);
	bool rva004CF316(unsigned int arg);

private:
	char m_pad00[4];
	unsigned int m_04[8];
	char m_pad24[0x12060 - 0x24];
	unsigned int m_12060[8];
	int m_12080[8];
	int m_120a0[8];
};

void Rva004CF35D::rva004CF35D(NetWrapperCommandMsg *msg)
{
	if ((unsigned int)msg->getData() >= 8)
		return;
	if (m_12080[(unsigned int)msg->getData()] != 0)
		return;
	m_12080[(unsigned int)msg->getData()] = 1;
	unsigned int len = msg->getDataLength();
	m_120a0[(unsigned int)msg->getData()] = len;
}

bool Rva004CF35D::rva004CF316(unsigned int arg)
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_04[i] == 0)
			continue;
		if (m_12060[i] < arg)
			return false;
	}
	return true;
}
