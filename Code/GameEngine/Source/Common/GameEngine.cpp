// cl: /O1 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /arch:SSE /G7
//
// GameEngine.cpp: GameEngine bodies retail links from this TU (tu_map
// approved), folded from the frame-admission and stopHeadlessClients split
// units, which shared these exact flags. Their two layout views agree: the
// child-process table ends at +0x33 and the client-frame pacing state starts
// at +0x34.
//
// Frame admission:
// BFME2's 108-byte frame-admission helper at RVA 0x00225BA6 is the local
// counterpart to BFME1's _bfme_shouldSkipClientFrame.  The GameEngine vtable
// and the caller at 0x00225C59 establish the member ownership; the retail
// body queries the network object's vtable slot +0x58, advances the client
// frame counter at +0x38, and maintains the headroom limit at +0x44.

#include <windows.h>
#include <string.h>
extern "C" __declspec(dllimport) char *__stdcall GetEnvironmentStrings(void);
extern "C" void __cdecl free(void *);
extern "C" void *__cdecl memset(void *,int,unsigned int);
#pragma function(memset)
namespace _STL { template<class T> class allocator { public: static T *allocate(unsigned int,const void *); }; }
extern float g_Va00BBB8D8;

// g_Va00DBA2F8: VA 0x00dba2f8 (.data); retail initial bytes 00 00 80 3f (1.0f).
float g_Va00DBA2F8 = 1.0f;

extern class NetworkInterface *TheNetwork;

#define TheNetwork (*(class NetworkInterface **)&TheNetwork)
#define LogicTimeScale g_Va00DBA2F8
#define One g_Va00BBB8D8

class NetworkInterface
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual int getFramePacingStatus(void);
};

// stopHeadlessClients:
// ?stopHeadlessClients@GameEngine@@AAEXXZ, retail 0x002260F7 42B.
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/Common/GameEngineTerminateChildProcesses.cpp
// (GameEngine::stopHeadlessClients, TerminateProcess loop then count=0).
// BFME2 retail shifts count 0x10->0x14 and array 0x14->0x18 (+4 vs BFME1); modeled as gap at 0x10.
// Evidence: TerminateProcess IAT call at 0x62610A; callers at 0x2297B9 0x37A67C and tail-jmp at 0x444407.
typedef void *HANDLE;
typedef int BOOL;
typedef unsigned char EngineBool;

struct AsciiStringLayout
{
	void *m_data;
};

extern "C" __declspec(dllimport) BOOL __stdcall TerminateProcess(
	HANDLE hProcess, unsigned int uExitCode);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	virtual void slot00(void);
	void startHeadlessClients(int numClients);

private:
	void stopHeadlessClients(void);
	bool _bfme_shouldSkipClientFrame(void);

	AsciiStringLayout m_name; // 0x04, inherited SubsystemInterface::m_name
	int m_maxFPS; // 0x08
	EngineBool m_quitting; // 0x0C
	EngineBool m_isActive; // 0x0D
	char m_align0E[2]; // 0x0E
	int m_bfme2Gap10; // 0x10, BFME2 +4 vs BFME1 (retail count at 0x14 proves the shift)
	int m_childProcessCount; // 0x14
	HANDLE m_childProcesses[7]; // 0x18..0x33
	int m_clientFramePeriod; // 0x34
	int m_clientFrameCounter; // 0x38
	float m_clientFrameRatio; // 0x3C
	char m_gap40[4];
	float m_clientFrameLimit; // 0x44
};


bool GameEngine::_bfme_shouldSkipClientFrame(void)
{
	NetworkInterface *network = TheNetwork;
	if (network != 0)
	{
		if (!(LogicTimeScale < One))
		{
			if (m_clientFramePeriod != 1)
			{
				if (m_clientFramePeriod > m_clientFrameCounter)
				{
					if (network->getFramePacingStatus() > 1)
						return true;

					if ((float)++m_clientFrameCounter > m_clientFrameLimit)
						m_clientFrameLimit = (float)m_clientFrameCounter;
					return false;
				}
				if (network->getFramePacingStatus() > 3)
				{
					if ((float)m_clientFramePeriod < m_clientFrameLimit)
						m_clientFrameLimit = (float)m_clientFramePeriod;
					return true;
				}
			}
		}
	}

	return false;
}


void GameEngine::stopHeadlessClients(void)
{
	for (int index = 0; index < m_childProcessCount; ++index)
		TerminateProcess(m_childProcesses[index], 0);
	m_childProcessCount = 0;
}

// Clean BFME1 donor: game/GameEngine/Source/Common/GameEngineRva0006C180.cpp
// at 9cbfb551fe20dae985f91f2319d8997287b6a705. Retail 0x00225F81..0x002260F7
// proves the +4 process-table shift and the ordinary, unaligned path buffer.
// BFME2 uses the local allocator/free thunks; O1/Ob1 matches this body and
// both previously recovered siblings. Full 374 bytes, strings and imports verified.
void GameEngine::startHeadlessClients(int numClients)
{
	char modulePath[0x200];

	if (m_childProcessCount > 0)
		return;
	if (numClients < 1)
		return;
	if (numClients > 7)
		numClients = 7;

	GetModuleFileNameA(0, modulePath, 0x200);
	char *environment = GetEnvironmentStrings();
	int environmentLength = 0;
	{
		char *entry = environment;
		while (*entry != 0)
		{
			int length = (int)strlen(entry);
			environmentLength += length + 1;
			entry += length + 1;
		}
	}

	environmentLength += 0x3e8;
	char *commandLine = GetCommandLineA();
	char *environmentCopy;
	environmentCopy = _STL::allocator<char>::allocate(environmentLength,0);
	int count = 0;
	if (numClients > 0)
	{
		PROCESS_INFORMATION processInformation;
		int number = 1;
		HANDLE *processSlot = m_childProcesses;
		for (int remaining = numClients; remaining > 0; --remaining)
		{
			char *cursor = environmentCopy;
			cursor += sprintf(cursor, "_EA_RTS_HEADLESS=%i", number) + 1;
			cursor += sprintf(cursor, "_EA_RTS_FILENAME=");
			GetModuleFileNameA(0, cursor, 0x100);
			char *extension = strrchr(cursor, '.');
			int suffixLength = sprintf(extension, "-%i.exe", number);
			cursor = extension + suffixLength + 1;

			{
				char *entry = environment;
				while (*entry != 0)
				{
					do
						*cursor++ = *entry++;
					while (cursor[-1] != 0);
				}
			}
			*cursor = 0;

			STARTUPINFOA startupInformation;
			memset(&startupInformation, 0, sizeof(startupInformation));
			startupInformation.cb = 0x44;
			CreateProcessA(modulePath, commandLine, 0, 0, 0, 0x208,
				environmentCopy, 0, &startupInformation, &processInformation);
			*processSlot++ = processInformation.hProcess;
			++number;
			++count;
		}
	}

	m_childProcessCount = count;
	free(environmentCopy);
}
