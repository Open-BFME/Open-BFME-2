// cl: /O1 /MD
//
// NetProgressCommandMsg::getPercentage, retail 0x004C54EC, 4 bytes. Dedicated
// TU so ConnectionManager.cpp keeps its matched bodies.

class NetProgressCommandMsg
{
public:
	unsigned char getPercentage();

private:
	char _pad[0x1C];
	unsigned char m_percent;
};

unsigned char NetProgressCommandMsg::getPercentage()
{
	return m_percent;
}
