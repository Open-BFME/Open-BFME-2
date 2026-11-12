// cl: /Ireference/shims/bfme2_ascii /EHsc
// ??1Rva0050FAEC@@UAE@XZ retail 0x0050FAEC 11B
// Trivial dtor: stores vtable 0x00865518 then tail-jmps to pinned base dtor
// 0x005248D0. Evidence: 11B mov-plus-jmp shape, no EH prolog, caller 0x0050E7C8,
// unwind funclets at 0x007948B2/0x00794921/0x00794956 reference it.
// Retail calls _mbscpy through the import thunk at 0x00629176.
#include <mbstring.h>
#include "../../../Include/GameClient/Rva005248D0.h"

// _snprintf goes through the CRT import table (FF15): read <stdio.h> with
// _CRTIMP redefined to dllimport for the include only.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdio.h>
#undef _CRTIMP

// The list row built by 0x0050F85D, whose constructor binds
// "_level<n>.<name>_color" to color as a member pointer.
class Rva0050FAEC : public Rva005248D0
{
public:
	virtual ~Rva0050FAEC();

	void color(int query, char *result, bool skip);

private:
	int m_color; // +0x58
};

Rva0050FAEC::~Rva0050FAEC()
{
}

// Retail 0x0050E7EB, 54 bytes: "_level<n>.<name>_color", an Apt query
// answering the row's color ("0" when skipped).
void Rva0050FAEC::color(int query, char *result, bool skip)
{
	_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>("0"));
	if (!skip)
		_snprintf(result, 0xFF, "%d", m_color);
}
