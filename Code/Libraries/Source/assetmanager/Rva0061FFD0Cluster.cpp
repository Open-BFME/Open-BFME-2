// Try-lock/backoff helper that sits after the asset-manager bodies. The
// object's critical section is at +0x68; the guard spins on the DX8 try-lock
// and thread assert (0x0011F600 / 0x00120F50 / 0x0011F520, all rowed), leaves
// and re-enters the section, and releases the DX8 lock once per acquired
// count. The wait between the leave and re-enter is kernel32 Sleep(1). Names
// are address-derived; identity is not recovered. No // cl: line: the
// frameless /O2 shape is the default.

struct CRITICAL_SECTION
{
	unsigned char data[24];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *section);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

int bfmeRva0011F600();
bool BFME_DX8_Thread_Assert();
void BFME_DX8_Thread_Lock();

class Rva0061FFD0
{
public:
	char m_pad00[0x68];
	CRITICAL_SECTION m_cs;
	void rva0061FFD0();
};

void Rva0061FFD0::rva0061FFD0()
{
	int count = 0;

	if ((char)bfmeRva0011F600() != 0)
	{
		do
		{
			++count;
		} while (BFME_DX8_Thread_Assert() == 0);
	}

	LeaveCriticalSection(&m_cs);
	Sleep(1);
	EnterCriticalSection(&m_cs);

	while (count != 0)
	{
		BFME_DX8_Thread_Lock();
		--count;
	}
}

// ?rva0061FCE0GetClockCyclesFast@@YA_JXZ
// 0x0061FCE0 505B: the asset manager's private copy of profile.cpp's
// GetClockCyclesFast (the profile library's own copy is rowed at 0x006C5570).
// Three 20 ms timeGetTime windows each measure rdtsc ticks, scaled by
// QueryPerformanceFrequency over the QueryPerformanceCounter delta (or by
// 1000/20 without a counter); the closest pair is averaged and rounded to a
// whole MHz. Its one caller is the asset thread function at 0x00623600, which
// caches the result behind a local-static guard (0x00E09C18, value at
// 0x00E09C10). The name stays address-derived: retail keeps no string for it.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *count);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *freq);

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

__int64 rva0061FCE0GetClockCyclesFast(void)
{
	__int64 n[3];
	for (int k = 0; k < 3; k++)
	{
		unsigned timeEnd = timeGetTime() + 2;
		while (timeGetTime() < timeEnd);

		__int64 start, startQPC, endQPC;
		QueryPerformanceCounter(&startQPC);
		ProfileGetTime(start);
		timeEnd += 20;
		while (timeGetTime() < timeEnd);
		ProfileGetTime(n[k]);
		n[k] -= start;

		if (QueryPerformanceCounter(&endQPC))
		{
			__int64 freq;
			QueryPerformanceFrequency(&freq);
			n[k] = (n[k] * freq) / (endQPC - startQPC);
		}
		else
		{
			n[k] = (n[k] * 1000) / 20;
		}
	}

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

	return ((avg / 2 + 500000) / 1000000) * 1000000;
}
