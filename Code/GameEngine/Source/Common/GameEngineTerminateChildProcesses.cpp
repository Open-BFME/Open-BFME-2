// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?_bfme_terminateChildProcesses@GameEngine@@AAEXXZ, retail 0x002260F7 42B.
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/Common/GameEngineTerminateChildProcesses.cpp
// (GameEngine::_bfme_terminateChildProcesses, TerminateProcess loop then count=0).
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

private:
	void _bfme_terminateChildProcesses(void);

	AsciiStringLayout m_name; // 0x04, inherited SubsystemInterface::m_name
	int m_maxFPS; // 0x08
	EngineBool m_quitting; // 0x0C
	EngineBool m_isActive; // 0x0D
	char m_align0E[2]; // 0x0E
	int m_bfme2Gap10; // 0x10, BFME2 +4 vs BFME1 (retail count at 0x14 proves the shift)
	int m_childProcessCount; // 0x14
	HANDLE m_childProcesses[7]; // 0x18..0x33
};

void GameEngine::_bfme_terminateChildProcesses(void)
{
	for (int index = 0; index < m_childProcessCount; ++index)
		TerminateProcess(m_childProcesses[index], 0);
	m_childProcessCount = 0;
}
