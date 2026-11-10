// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
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
#include "ascii_string.h"

// platformsdk
#include <stdio.h>
#include <string.h>
#include <windows.h>

// Retail calls the game's _mbscat import thunk through REL32. The /MD
// mbstring.h declaration would call its IAT slot directly and changes bytes,
// so read <mbstring.h> without dllimport.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP

// The four flags the donor clears, in its order (there +0xCF4, +0x1E and
// the shadow volume/decal pair +0x64/+0x65); BFME 2's offsets are the
// retail stores.
#include "../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;

// The thing factory's first template sits at +0x0C (the donor's +8).
#include "../../Include/Common/ThingFactory.h"

extern ThingFactory *TheThingFactory;

// The tactical view's slot 21 is ZH's lookAt.
#include "../../Include/GameClient/View.h"

extern View *TheTacticalView;

void bfmeClearReceiverFlag(int value);
void rva0038780();
void HideControlBar(bool immediate);

class Rva0023C641
{
public:
	Rva0023C641();
	void rva0023C641(const char *str);
	void rva0023D494();

private:
	bool m_enabled;
	AsciiString m_name04, m_name08;
	bool m_gotUnit; // +0x0C
	const void *m_curThing; // +0x10
	bool m_startTiming; // +0x14
	FILE *m_file18; // +0x18
	unsigned int m_1C, m_20;
	int m_24; // +0x24
	bool m_28; // +0x28
	unsigned int m_2C; // not written by the constructor
	unsigned int m_30, m_34, m_38, m_3C, m_40, m_44, m_48;
	int m_4C; // +0x4C
	double m_50, m_58, m_60, m_68, m_70, m_78, m_80;
	float m_88, m_8C, m_90, m_94;
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
	TheWritableGlobalData->field0C69 = false;
	TheWritableGlobalData->m_useFpsLimit = false;
	TheWritableGlobalData->m_useShadowVolumes = false;
	TheWritableGlobalData->m_useShadowDecals = false;
	rva0038780();
	HideControlBar(true);

	m_curThing = TheThingFactory->firstTemplate();
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
	_mbscat((unsigned char *)fileName, (const unsigned char *)dateBuf);
	_mbscat((unsigned char *)fileName, (const unsigned char *)".csv");
	m_file18 = fopen(fileName, "w");
	rva0023C641("Full,TotalVerts/Skin/Sort,Less Fill,NoParticles,No Spawn-NoPart,Logic,Thing,Model,Kind,Side,DrawCalls All,DrawCalls NoPart-NoSpawn,DrawCalls NoSpawn\n");

	TheWritableGlobalData->m_useShadowVolumes = false;
	Coord3D thePos;
	thePos.x = 50.0f;
	thePos.y = 50.0f;
	thePos.z = 0.0f;
	TheTacticalView->lookAt(&thePos);

	m_24 = 0;
	m_4C = 0;
	m_28 = true;
}

// Native23DBF9..23DC7F,134B; CRT initializer7ADCAE constructs the
// global atDFE7A8 then registers cleanup7B7786 -> dtor23DBC3. The latter
// proves the two string members at4/8. BF1 a7c38d3b TimingLog003851E0
// supplies subsystem context; each field offset is from this native body.
Rva0023C641::Rva0023C641() : m_enabled(false)
{
    m_gotUnit=false; m_curThing=0; m_startTiming=false;
    m_file18=0; m_1C=0; m_20=0; m_24=0; m_28=false;
    m_30=0; m_34=0; m_38=0; m_3C=0; m_40=0; m_44=0; m_48=0; m_4C=0;
    m_50=0.0; m_58=0.0; m_60=0.0; m_68=0.0; m_70=0.0; m_78=0.0; m_80=0.0;
    m_88=0.0f; m_8C=0.0f; m_90=0.0f; m_94=0.0f;
}
