// cl: /DNDEBUG /MD
//
// The unit-timing log object (the 408-byte global at VA 0x00DFE7A8). Zero
// Hour runs this setup inline in GameLogic::startNewGame under its unit
// timing debug switch; BFME 1 already moves it into a method
// (Open-BFME-1 TimingLog003851E0.cpp, the donor of rva0023D494) and BFME 2
// keeps that split.
//
// ?rva0023C641@Rva0023C641@@QAEXPBD@Z @0x0023C641, 37B.
// File-write helper: if m_file18 then fputs(str,m_file) plus fflush(m_file).
// Retail: push esi; mov esi,ecx; mov eax,[esi+0x18]; test; je end;
// push eax; push [esp+0xC]; call fputs; push [esi+0x18]; call fflush;
// add esp,0xC; pop esi; ret 4.
// Evidence: callers 0x0023D5C2 and 0x0024367D pass string arg; the FILE* at
// +0x18 is the "TimingLog<date>.csv" handle rva0023D494 opens; imports
// fputs/fflush are IAT (FF 15) so dllimport. Flags from sibling
// Rva0023C6A4Check.cpp (/O1 /DNDEBUG /MD).

#include "../../../Libraries/Include/Lib/Coord3D.h"

struct FILE;

extern "C"
{
	__declspec(dllimport) int __cdecl fputs(const char *str, FILE *file);
	__declspec(dllimport) int __cdecl fflush(FILE *file);
	__declspec(dllimport) FILE *__cdecl fopen(const char *name, const char *mode);
	char *__cdecl strcpy(char *dest, const char *src);
	char *__cdecl strcat(char *dest, const char *src);
	unsigned int __cdecl strlen(const char *str);
}

struct SYSTEMTIME
{
	unsigned short wYear;
	unsigned short wMonth;
	unsigned short wDayOfWeek;
	unsigned short wDay;
	unsigned short wHour;
	unsigned short wMinute;
	unsigned short wSecond;
	unsigned short wMilliseconds;
};

extern "C"
{
	__declspec(dllimport) void __stdcall GetLocalTime(SYSTEMTIME *time);
	__declspec(dllimport) int __stdcall GetDateFormatA(unsigned long locale, unsigned long flags, const SYSTEMTIME *date, const char *format, char *buffer, int size);
	__declspec(dllimport) int __stdcall GetTimeFormatA(unsigned long locale, unsigned long flags, const SYSTEMTIME *time, const char *format, char *buffer, int size);
}

// The four flags the donor clears, in its order (there +0xCF4, +0x1E and
// the shadow volume/decal pair +0x64/+0x65); BFME 2's offsets are the
// retail stores.
class GlobalData
{
public:
	unsigned char m_pad000[0x26];
	bool m_flag026; // donor m_useFpsLimit
	unsigned char m_pad027[0x60 - 0x27];
	bool m_flag060; // donor m_useShadowVolumes
	bool m_flag061; // donor m_useShadowDecals
	unsigned char m_pad062[0xC69 - 0x62];
	bool m_flagC69; // donor m_unk0CF4
};

extern GlobalData *TheWritableGlobalData;

// The thing factory's first template sits at +0x0C (the donor's +8).
class ThingFactory
{
public:
	unsigned char m_pad000[0x0C];
	void *m_firstTemplate; // +0x0C
};

extern ThingFactory *TheThingFactory;

// The tactical view's slot 21 is ZH's lookAt.
class View
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20();
	virtual void lookAt(const Coord3D *pos);
};

extern View *TheTacticalView;

void bfmeClearReceiverFlag(int value);
void rva0038780();
void HideControlBar(bool immediate);

class Rva0023C641
{
public:
	void rva0023C641(const char *str);
	void rva0023D494();

private:
	unsigned char m_pad00[0x0C];
	bool m_gotUnit; // +0x0C
	void *m_curThing; // +0x10
	bool m_startTiming; // +0x14
	FILE *m_file18; // +0x18
	unsigned char m_pad1C[0x24 - 0x1C];
	int m_24; // +0x24
	bool m_28; // +0x28
	unsigned char m_pad29[0x4C - 0x29];
	int m_4C; // +0x4C
};

void Rva0023C641::rva0023C641(const char *str)
{
	if (m_file18) {
		fputs(str, m_file18);
		fflush(m_file18);
	}
}

// Retail 0x0023D494, 371 bytes; sole caller the startNewGame tail
// 0x0023F52C after its enable-byte test. Opens "TimingLog<date>-<time>.csv"
// (the date's '/' and ':' turned into '_'), writes the column header through
// rva0023C641 and parks the tactical view at (50, 50, 0).
void Rva0023C641::rva0023D494()
{
	bfmeClearReceiverFlag(0);
	TheWritableGlobalData->m_flagC69 = false;
	TheWritableGlobalData->m_flag026 = false;
	TheWritableGlobalData->m_flag060 = false;
	TheWritableGlobalData->m_flag061 = false;
	rva0038780();
	HideControlBar(true);

	m_curThing = TheThingFactory->m_firstTemplate;
	m_startTiming = true;
	m_gotUnit = false;

	SYSTEMTIME now;
	char dateBuf[0x104];
	char fileName[0x104];

	GetLocalTime(&now);
	GetDateFormatA(0x800, 1, &now, 0, dateBuf, 0x104);
	int n = strlen(dateBuf);
	dateBuf[n] = '-';
	++n;
	dateBuf[n] = 0;
	GetTimeFormatA(0x800, 2, &now, 0, dateBuf + n, 0x104 - n);

	if (dateBuf[0])
	{
		char *p = dateBuf;
		do
		{
			if (*p == '/' || *p == ':')
				*p = '_';
		} while (*++p);
	}

	strcpy(fileName, "TimingLog");
	strcat(fileName, dateBuf);
	strcat(fileName, ".csv");
	m_file18 = fopen(fileName, "w");
	rva0023C641("Full,TotalVerts/Skin/Sort,Less Fill,NoParticles,No Spawn-NoPart,Logic,Thing,Model,Kind,Side,DrawCalls All,DrawCalls NoPart-NoSpawn,DrawCalls NoSpawn\n");

	TheWritableGlobalData->m_flag060 = false;
	Coord3D thePos;
	thePos.x = 50.0f;
	thePos.y = 50.0f;
	thePos.z = 0.0f;
	TheTacticalView->lookAt(&thePos);

	m_24 = 0;
	m_4C = 0;
	m_28 = true;
}
