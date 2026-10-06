// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva004D3AB2@DisconnectManager@@QAEEH@Z 0x004D3AB2 48 timeout check vs GlobalData threshold, early 0 when slot == -1
// Evidence: between 0x004D3A06 and 0x004D3CA8 in DisconnectManager.cpp; array at +0x14 indexed slot*4; IAT timeGetTime; TheWritableGlobalData+0xc24; caller at 0x004D3F61.

typedef int Int;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class GlobalData
{
public:
	char m_pad[0xc24];
	unsigned int m_0c24;
};

extern GlobalData *TheWritableGlobalData;

class DisconnectManager
{
public:
	unsigned char rva004D3AB2(int slot);
private:
	unsigned char m_pad[0x14];
	long m_playerTimeouts[1];
};

unsigned char DisconnectManager::rva004D3AB2(int slot)
{
	if (slot == -1)
		return 0;
	unsigned long elapsed = timeGetTime() - m_playerTimeouts[slot];
	return (unsigned char)(elapsed >= TheWritableGlobalData->m_0c24);
}
