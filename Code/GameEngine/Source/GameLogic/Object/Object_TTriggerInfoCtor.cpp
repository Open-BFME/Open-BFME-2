// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// Retail 0x0028A60A (19B). Default constructor zeroing the trigger info
// word at +0x00 and the flag bytes at +0x04..0x07. Transferred from the
// BFME1 reconstruction (BFME1 0x001BD370, 19B, same Object.cpp TU family).

class TTriggerInfo
{
public:
	TTriggerInfo();

private:
	int m_value;
	unsigned char m_flag04;
	unsigned char m_flag05;
	unsigned char m_flag06;
	unsigned char m_flag07;
};

TTriggerInfo::TTriggerInfo()
{
	m_value = 0;
	m_flag04 = 0;
	m_flag05 = 0;
	m_flag06 = 0;
	m_flag07 = 0;
}
