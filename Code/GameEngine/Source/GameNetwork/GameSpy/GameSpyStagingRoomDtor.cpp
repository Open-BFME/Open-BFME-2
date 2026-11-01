// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
//
// ??1GameSpyStagingRoom@@UAE@XZ, retail 0x00382C4A 132B: virtual dtor over
// GameInfo base (0xDC) with 8x0x1E0 Rva00382398 array at +0xDC destroyed via
// eh vector destructor then four narrow AsciiString members at
// +0xFDC/+0xFE8/+0xFFC/+0x1000 destroyed in reverse with EH states 4..0 then
// the pinned base dtor. Identity from pin plus caller 0x00383768 deleting dtor
// and vtable 0x00C19440 name getter GameSpyStagingRoom; array shape 8x0x1E0 from
// 0xDC+0xF00=0xFDC landing exactly on first string; sibling Rva004482FB pattern.
#include "ascii_string.h"

#include "../../../Include/GameNetwork/GameInfo.h"

class Rva00382398
{
public:
	virtual ~Rva00382398();
	char m_pad[0x1E0 - 4];
};

class __declspec(novtable) GameSpyStagingRoom : public GameInfo
{
public:
	virtual ~GameSpyStagingRoom();
private:
	Rva00382398 m_items[8];
	AsciiString m_fdc;
	char m_gapFE0[8];
	AsciiString m_fe8;
	char m_gapFEC[0x10];
	AsciiString m_ffc;
	AsciiString m_1000;
};

GameSpyStagingRoom::~GameSpyStagingRoom()
{
}
