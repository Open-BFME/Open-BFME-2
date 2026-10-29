// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?ExternsObjective@AptPlayerStatus@@QAEXHPAD_N@Z @0x004E4553 167B
// AptPlayerStatus handler answering "$<text>" for a row. Evidence: between
// Objective 0x004E4446 and PlayerColor 0x004E45FA in same TU family; same
// m_state +0x288 zero check and row range 0-12 and bool skip as Objective;
// same GetNthVisibleObjectiveIndex index plus TheMissionObjectiveTracker list plus Rva004266A1 text record.
#include "ascii_string.h"

extern "C" unsigned char *__cdecl _mbscpy(unsigned char *destination, const unsigned char *source);

int __cdecl GetNthVisibleObjectiveIndex(int row);

class Rva004266A1
{
public:
	void *rva004267E9(int index);
};

struct Rva0039B95FHolder;
extern Rva0039B95FHolder *TheMissionObjectiveTracker;

struct AptPlayerStatusObjectives
{
	unsigned char m_pad00[0x10];
	Rva004266A1 *m_list;
};

class AptPlayerStatus
{
public:
	void ExternsObjective(int row, char *result, bool skip);

private:
	unsigned char m_pad000[0x288];
	int m_state;
};

void AptPlayerStatus::ExternsObjective(int row, char *result, bool skip)
{
	*result = 0;
	if (m_state == 0 && row >= 0 && row < 12 && !skip)
	{
		AsciiString tmp;
		int index = GetNthVisibleObjectiveIndex(row);
		if (index >= 0 && TheMissionObjectiveTracker && ((AptPlayerStatusObjectives *)TheMissionObjectiveTracker)->m_list)
			tmp = *(const AsciiString *)((AptPlayerStatusObjectives *)TheMissionObjectiveTracker)->m_list->rva004267E9(index);
		if (!tmp.isEmpty() && tmp.getLength() + 2 < 0xFF)
		{
			result[0] = '$';
			_mbscpy(reinterpret_cast<unsigned char *>(result + 1),
				reinterpret_cast<const unsigned char *>(tmp.str()));
		}
	}
}
