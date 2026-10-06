// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
//
// ?getFileLengthMS@MilesAudioManager@@UBEMVAsciiString@@@Z, retail 0x00054930.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerGetFileLengthMS.cpp,
// getFileLengthMS at retail 0x0069F8F0): open-stream plus ms-position plus
// close-stream over the digital driver handle with an empty-string guard and
// an int-to-float tail. BFME2 adaptations (all retail-measured):
// - Digital driver handle at this+0x9DC (retail push dword [ecx+0x9DC]; BFME1
//   prefix 0x95C plus vptr gives 0x960). Prefix here is 0x9D8 so the vptr plus
//   prefix lands the handle at +0x9DC, matching the createListener-proven
//   provider-count at +0x9CC and selected-provider at +0x9D0.
// - Identity: sole tight cluster of the three AIL stream imports in one body
//   (open at 0xBBAA80 called from 0x54956, ms-position at 0xBBAAC8 from
//   0x5496E, close at 0xBBAACC from 0x54975), plus the isEmpty guard and the
//   cvtsi2ss tail. No other body calls all three.

typedef void *HSTREAM;
typedef void *HDIGDRIVER;
extern "C" __declspec(dllimport) HSTREAM __stdcall AIL_open_stream(
	HDIGDRIVER driver, const char *filename, int stream_mem);
extern "C" __declspec(dllimport) void __stdcall AIL_stream_ms_position(
	HSTREAM stream, long *total_milliseconds, long *current_milliseconds);
extern "C" __declspec(dllimport) void __stdcall AIL_close_stream(HSTREAM stream);

typedef bool Bool;
typedef float Real;

#define INT_TO_REAL(x) ((Real) (x))

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


// Only the digital-driver offset is observed by this body. The prefix includes
// the vptr already present in the retail MilesAudioManager object.
class MilesAudioManager
{
private:
	// The compiler supplies the four-byte vptr before this explicit prefix.
	unsigned char m_retailPrefix[0x9D8];
	HDIGDRIVER m_digitalHandle;

public:
	virtual Real getFileLengthMS(AsciiString strToLoad) const;
};

Real MilesAudioManager::getFileLengthMS(AsciiString strToLoad) const
{
	if (strToLoad.isEmpty()) {
		return 0.0f;
	}

	const char *filename = strToLoad.str();
	HSTREAM stream = AIL_open_stream(m_digitalHandle, filename, 0);
	if (stream == 0) {
		return 0.0f;
	}

	long result;
	AIL_stream_ms_position(stream, &result, 0);
	AIL_close_stream(stream);

	return INT_TO_REAL(result);
}
