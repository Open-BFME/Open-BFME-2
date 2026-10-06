// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva005E7529@@QAE@XZ @0x005E7529 53B
// Non-virtual dtor over AsciiString at +0x0C and rowed base ??1Rva0022167C at +0.
// Retail lea ecx [esi+0x0C] call releaseBuffer 0x00036410 then mov ecx esi call
// base 0x0022167C under __EH_prolog with and [ebp-4] 0 and or [ebp-4] -1.
// Same 53B EH shape as ??1Rva0022D094 at 0x0022D094. Evidence: chain lane via
// just-landed 0x0022167C plus prev/next Rva005E74AADeleting flags.
#include "ascii_string.h"

class __declspec(novtable) Rva0022167C
{
public:
	~Rva0022167C();
	virtual void _pure() = 0;
private:
	char m_pad4[4];
};

class __declspec(novtable) Rva005E7529 : public Rva0022167C
{
public:
	~Rva005E7529();
private:
	char m_pad8[4];
	AsciiString m_str;
};

Rva005E7529::~Rva005E7529()
{
}
