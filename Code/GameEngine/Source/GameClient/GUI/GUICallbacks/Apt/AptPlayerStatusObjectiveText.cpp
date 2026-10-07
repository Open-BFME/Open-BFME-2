// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004E4553@AptPlayerStatus@@QAEXHPAD_N@Z @0x004E4553 167B
// AptPlayerStatus handler answering "$<text>" for a row. Evidence: between
// Objective 0x004E4446 and PlayerColor 0x004E45FA in same TU family; same
// m_state +0x288 zero check and row range 0-12 and bool skip as Objective;
// same Rva004E43F2 index plus g_00E031E8 list plus Rva004266A1 text record.
#include "ascii_string.h"

extern "C" char *__cdecl _mbscpy(char *destination, const char *source);

int __cdecl Rva004E43F2(int row);

class Rva004266A1
{
public:
	void *rva004267E9(int index);
};

struct Rva0039B95FHolder;
extern Rva0039B95FHolder *g_00E031E8;

struct AptPlayerStatusObjectives
{
	unsigned char m_pad00[0x10];
	Rva004266A1 *m_list;
};

class AptPlayerStatus
{
public:
	void rva004E4553(int row, char *result, bool skip);

private:
	unsigned char m_pad000[0x288];
	int m_state;
};

void AptPlayerStatus::rva004E4553(int row, char *result, bool skip)
{
	*result = 0;
	if (m_state == 0 && row >= 0 && row < 12 && !skip)
	{
		AsciiString tmp;
		int index = Rva004E43F2(row);
		if (index >= 0 && g_00E031E8 && ((AptPlayerStatusObjectives *)g_00E031E8)->m_list)
			tmp = *(const AsciiString *)((AptPlayerStatusObjectives *)g_00E031E8)->m_list->rva004267E9(index);
		if (!tmp.isEmpty() && tmp.getLength() + 2 < 0xFF)
		{
			result[0] = '$';
			_mbscpy(result + 1, tmp.str());
		}
	}
}
