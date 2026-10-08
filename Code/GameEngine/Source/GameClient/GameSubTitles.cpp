// cl: /DNDEBUG /MD /GX-
// ?getXFromAlignment@GameSubTitle@@SAHHHHMM@Z @0x0025FF8F 175B.
// WB 0x00DA61E0 names GameSubTitle::getXFromAlignment in GameSubTitles.cpp;
// the full retail boundary ends at 0x0026003E. Five stack arguments, caller
// cleanup, and no receiver use establish this utility's cdecl ABI. Original
// alignment enum spelling is unknown; retain its 32-bit integer representation.
// Donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngineDevice/Source/VideoDevice/Bink/SubtitleEntryAlignment.cpp.
// The clean donor compiled under BFME2 /O1 /arch:SSE /G7 placed no bodies.
// Target adaptations: the owned theDebug pointer and the observed three-zero
// argument report factory at slot 0x6C. Math, cases, reference-returning minimum
// and diagnostic text are retained; all 175 bytes match under region flags.

#include <math.h>

typedef int Int;
typedef float Real;

class BfmeDebugReport
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeDebugReport *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(Int value);
};

class BfmeDebugManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeDebugReport *slot6C(void *first, void *second, void *third);
};

class Debug;
extern Debug *theDebug;
extern void _bfme_debugRecordCallsite(Int kind);

static const Int &bfmeMin(const Int &first, const Int &second)
{
	return first < second ? first : second;
}

// ?getXFromAlignment@GameSubTitle@@SAHHHHMM@Z
class GameSubTitle { public: static Int getXFromAlignment(Int alignment, Int base, Int unused, Real low, Real high); };
Int GameSubTitle::getXFromAlignment(Int alignment, Int base, Int unused, Real low, Real high)
{
	Int difference = (Int)fabs(high - low);

	switch (alignment)
	{
	case 1:
		return 0;
	case 0:
	{
		Int highInt = (Int)high;
		Int lowInt = (Int)low;
		const Int &minimum = bfmeMin(highInt, lowInt);
		return minimum + ((difference - base) >> 1);
	}
	case 2:
	{
		Int highInt = (Int)high;
		Int lowInt = (Int)low;
		const Int &minimum = bfmeMin(highInt, lowInt);
		return minimum - base + difference;
	}
	default:
		_bfme_debugRecordCallsite(1);
		reinterpret_cast<BfmeDebugManager *>(theDebug)->slot60();
		BfmeDebugReport *report = reinterpret_cast<BfmeDebugManager *>(theDebug)->slot6C(0, 0, 0);
		report = report->slot38("Invalid Subtitle alignment!");
		report->slot4C(1);
		return 0;
	}
}
