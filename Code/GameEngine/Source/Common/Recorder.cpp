// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc

#include "string_base.h"

typedef long time_t;

extern "C" __declspec(dllimport) time_t __cdecl time(time_t *value);
extern "C" __declspec(dllimport) long __cdecl ftell(void *stream);
extern "C" __declspec(dllimport) int __cdecl fseek(void *stream, long offset, int origin);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buffer, unsigned int size,
	unsigned int count, void *stream);

#include "ascii_string.h"

// BFME1 donor 9cbfb551fe20dae985f91f2319d8997287b6a705:
// game/GameEngine/Source/Common/System/RecorderLogGameStart.cpp.
// ZH Recorder.cpp gives the logGameStart purpose, independently corroborated
// by WB F54AE0. Native37B1FA..37B287 proves FILE at+10, by-value string
// cleanup, persistent timestamp and replay header offset8; full141B exact.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass {
	unsigned char m_prefix[0x10];
	void *m_file;

protected:
	void logGameStart(AsciiString options);
};

// Target time() and fwrite() use the same persistent timestamp at VA E0228C.
// Donor source calls it startTime; the target does not independently name it.
static time_t startTime;

void RecorderClass::logGameStart(AsciiString options)
{
	if (!m_file)
		return;

	time(&startTime);
	unsigned int fileSize = ftell(m_file);
	if (!fseek(m_file, 8, 0))
		fwrite(&startTime, sizeof(time_t), 1, m_file);
	fseek(m_file, fileSize, 0);
}
