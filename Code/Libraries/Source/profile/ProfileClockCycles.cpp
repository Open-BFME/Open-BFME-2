// cl: /MD /Oi
//
// GetClockCyclesFast, retail 0x006C5570 (569 bytes): the initializer of
// Profile::m_clockCycles in Zero Hour's profile.cpp, which also registers
// the built-in result functions. BFME2 adds a third one, file_gtt_dot
// (ProfileResultFileGTT, a DOT graph by global time); everything else is
// Zero Hour's measurement: three 20 ms rdtsc windows scaled by the
// performance counter, the two closest averaged and rounded to the MHz.

typedef union _LARGE_INTEGER *PLARGE_INTEGER;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(PLARGE_INTEGER count);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(PLARGE_INTEGER frequency);

class ProfileResultInterface;

class ProfileCmdInterface
{
public:
	static void AddResultFunction(ProfileResultInterface *(*func)(int, const char *const *),
		const char *name, const char *arg);
};


class ProfileResultFileCSV
{
public:
	static ProfileResultInterface *Create(int argn, const char *const *argv);
};

class ProfileResultFileDOT
{
public:
	static ProfileResultInterface *Create(int argn, const char *const *argv);
};

class ProfileResultFileGTT
{
public:
	static ProfileResultInterface *Create(int argn, const char *const *argv);
};

__forceinline void ProfileGetTime(__int64 &t)
{
	_asm
	{
		mov ecx,[t]
		push eax
		push edx
		rdtsc
		mov [ecx],eax
		mov [ecx+4],edx
		pop edx
		pop eax
	};
}

// ?GetClockCyclesFast@@YA_JXZ
__int64 GetClockCyclesFast(void)
{
	// this is where we're adding our internal result functions
	ProfileCmdInterface::AddResultFunction(ProfileResultFileCSV::Create,
		"file_csv",
		"");
	ProfileCmdInterface::AddResultFunction(ProfileResultFileDOT::Create,
		"file_dot",
		"[ file [ frame_name [ fold_threshold ] ] ]");
	ProfileCmdInterface::AddResultFunction(ProfileResultFileGTT::Create,
		"file_gtt_dot",
		"[ file [ frame_name [ percent_threshold, 10000=100%, def=1% ] ] ]");

	// this must not take a very huge CPU hit...

	// measure clock cycles 3 times for 20 msec each
	// then take the 2 counts that are closest, average
	__int64 n[3];
	for (int k = 0; k < 3; k++)
	{
		// wait for end of current tick
		unsigned timeEnd = timeGetTime() + 2;
		while (timeGetTime() < timeEnd);

		// get cycles
		__int64 start, startQPC, endQPC;
		QueryPerformanceCounter((PLARGE_INTEGER)&startQPC);
		ProfileGetTime(start);
		timeEnd += 20;
		while (timeGetTime() < timeEnd);
		ProfileGetTime(n[k]);
		n[k] -= start;

		// convert to 1 second
		if (QueryPerformanceCounter((PLARGE_INTEGER)&endQPC))
		{
			__int64 freq;
			QueryPerformanceFrequency((PLARGE_INTEGER)&freq);
			n[k] = (n[k] * freq) / (endQPC - startQPC);
		}
		else
		{
			n[k] = (n[k] * 1000) / 20;
		}
	}

	// find two closest values
	__int64 d01 = n[1] - n[0], d02 = n[2] - n[0], d12 = n[2] - n[1];
	if (d01 < 0) d01 = -d01;
	if (d02 < 0) d02 = -d02;
	if (d12 < 0) d12 = -d12;
	__int64 avg;
	if (d01 < d02)
	{
		avg = d01 < d12 ? n[0] + n[1] : n[1] + n[2];
	}
	else
	{
		avg = d02 < d12 ? n[0] + n[2] : n[1] + n[2];
	}

	// return result
	// (rounded to the next MHz)
	return ((avg / 2 + 500000) / 1000000) * 1000000;
}
