// cl: /Ireference/shims/bfme2_ascii /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1Rva00151632@@UAE@XZ, retail 0x00151632, 90 bytes. Virtual dtor twin of
// ~Rva0017FB41_Prototype 0x0017FB94 (89B) and Rva0014CD63 (82B): stores vtable 0x007D3A6C, deletes
// the +0x14 link via slot-0 virtual get(0) plus operator delete 0x0002FD60,
// tears down +0x18 AsciiString via pinned ??1AsciiString 0x00036410, then
// delegates to base pinned ??1Rva0061ED80 0x0061ED80 (same bytes as rowed
// ?bfmeResetUB). Called from deleting dtor 0x00151717. Layout mirrors the
// twins: vtable + pad 0x10 + link + String. EH via /GX like the twins.

class FXShaderAssetImpl
{
public:
	virtual void *get(int x);
};

#include "ascii_string.h"

#include "../../Include/Common/Rva0061ED80.h"

class Rva00151632 : public Rva0061ED80
{
public:
	virtual ~Rva00151632();

private:
	char m_pad04[0x10];
	FXShaderAssetImpl *m_link;
	AsciiString m_name;
};

Rva00151632::~Rva00151632()
{
	void *allocation = m_link ? m_link->get(0) : 0;
	delete allocation;
}
