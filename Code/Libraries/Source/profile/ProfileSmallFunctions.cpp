// cl: /MD /Oi
//
// Small profile.cpp functions (Zero Hour source, _PROFILE build):
//   0x006C5300 ProfileFreeMemory
//   0x006C53C0 Profile::GetFrameName
//   0x006C53E0 Profile::GetClockCyclesPerSecond
//   0x006C5400 ProfileShutdown (the atexit hook: BFME2 shuts down only the
//              high-level recorder and drops the CPU-speed log line)

extern "C" __declspec(dllimport) void *__stdcall GlobalFree(void *mem);

class ProfileId
{
public:
	static void Shutdown(void);
};

class ProfileCmdInterface
{
public:
	void RunResultFunctions(void);
};

// ?ProfileFreeMemory@@YAXPAX@Z
void ProfileFreeMemory(void *ptr)
{
	if (ptr)
		GlobalFree(ptr);
}

class Profile
{
public:
	static const char *GetFrameName(unsigned frame);
	static __int64 GetClockCyclesPerSecond(void);

private:
	static unsigned m_rec;
	static char **m_recNames;
	static __int64 m_clockCycles;
};

// ?GetFrameName@Profile@@SAPBDI@Z
const char *Profile::GetFrameName(unsigned frame)
{
	return frame >= m_rec ? 0 : m_recNames[frame];
}

// ?GetClockCyclesPerSecond@Profile@@SA_JXZ
__int64 Profile::GetClockCyclesPerSecond(void)
{
	return m_clockCycles;
}

extern ProfileCmdInterface *cmd;

// ?ProfileShutdown@@YAXXZ
void ProfileShutdown(void)
{
	ProfileId::Shutdown();
	cmd->RunResultFunctions();
}
