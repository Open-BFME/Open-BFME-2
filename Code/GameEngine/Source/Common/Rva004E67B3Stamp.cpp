// cl: /O1
//
// ?rva004E67B3@Rva004E67B3@@QAEXI@Z @0x004E67B3 29B.
// Timestamp the +0x48 slot when m_8 holds 2: flip m_8 to 3, then sample the
// timeGetTime import at IAT 0x00BBA918 into m_48. Same import precedent as
// TransportRva004D53B5.cpp.
extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime(void);

class Rva004E67B3
{
public:
	void rva004E67B3(unsigned int flags);
private:
	char m_pad[8];
	int m_8;
	char m_pad0C[0x48 - 0x0C];
	int m_48;
};

void Rva004E67B3::rva004E67B3(unsigned int flags)
{
	(void)flags;
	if (m_8 == 2) {
		m_8 = 3;
		m_48 = (int)timeGetTime();
	}
}
