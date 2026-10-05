// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// AudioEventInfo range FieldParse procs (Zero Hour's INIAudioEventInfo.cpp
// statics parseDelay / parsePitchShift), BFME 2 form: both values are stored
// straight into the store as a min/max pair and swapped when out of order
// (Zero Hour asserted instead, and scaled the pitch shift). Target evidence:
// the audio-event FieldParse rows PitchShift (0x00BD9DB8) and PerFilePitchShift
// (0x00BD9DC8) -> 0x0002F5F4, Delay (0x00BD9DE8, store +0x34) -> 0x0002F642.
// The float swap compares with fcompi and copies through SSE (/arch:SSE).

typedef int Int;
typedef float Real;

template <class T> inline void swapRange(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	Int scanInt(const char *token);
	Real scanReal(const char *token);
};

// ?parseDelay@@YAXPAVINI@@PAX1PBX@Z
void parseDelay(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	Int *range = (Int *)store;
	range[0] = ini->scanInt(ini->getNextToken());
	range[1] = ini->scanInt(ini->getNextToken());
	if (range[0] > range[1])
		swapRange(range[0], range[1]);
}

// ?parsePitchShift@@YAXPAVINI@@PAX1PBX@Z
void parsePitchShift(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	Real *range = (Real *)store;
	range[0] = ini->scanReal(ini->getNextToken());
	range[1] = ini->scanReal(ini->getNextToken());
	if (range[0] > range[1])
		swapRange(range[0], range[1]);
}
