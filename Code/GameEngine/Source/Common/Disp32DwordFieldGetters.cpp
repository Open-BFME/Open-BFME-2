// Disp32 dword getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP32>] / ret
//
// One dword is read at a 32-bit displacement from `this` and returned. The
// displacement does not fit in a signed byte, so MSVC 7.1 emits the disp32
// load `8B 81 <imm32>`, plus `ret`, for seven bytes total. This is the disp32
// sibling of the disp8 Disp8DwordFieldGetters family (four bytes per body);
// the wider displacement is why the two families are kept in separate
// translation units. Identity is not recovered: every name is derived from
// its address.
// No // cl: line (defaults match the frameless seven-byte shape).
#define BFME_DISP32_DWORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value; \
	}

BFME_DISP32_DWORD_GETTER(Rva000515C7DwordField, 0x68C)
BFME_DISP32_DWORD_GETTER(Rva0007E00FDwordField, 0x1784)
BFME_DISP32_DWORD_GETTER(Rva0009DC5ADwordField, 0x22C)
BFME_DISP32_DWORD_GETTER(Rva000B23B7DwordField, 0x360)
BFME_DISP32_DWORD_GETTER(Rva000E009DDwordField, 0x8B4)
BFME_DISP32_DWORD_GETTER(Rva000EFD36DwordField, 0x2094)
BFME_DISP32_DWORD_GETTER(Rva001E42EBDwordField, 0x274)
BFME_DISP32_DWORD_GETTER(Rva0020E323DwordField, 0x268)
BFME_DISP32_DWORD_GETTER(Rva0025DB2DDwordField, 0x1205C)
BFME_DISP32_DWORD_GETTER(Rva002620D4DwordField, 0x410)
BFME_DISP32_DWORD_GETTER(Rva002620F3DwordField, 0x32C)
BFME_DISP32_DWORD_GETTER(Rva002856B0DwordField, 0x4A0)
BFME_DISP32_DWORD_GETTER(Rva002A98CADwordField, 0x7C0)
BFME_DISP32_DWORD_GETTER(Rva002D2CBADwordField, 0x318)
BFME_DISP32_DWORD_GETTER(Rva0035AEBBDwordField, 0x458)
BFME_DISP32_DWORD_GETTER(Rva00376CDDDwordField, 0xC8)
BFME_DISP32_DWORD_GETTER(Rva003888A1DwordField, 0x290)
BFME_DISP32_DWORD_GETTER(Rva003E3C05DwordField, 0x1A160)
BFME_DISP32_DWORD_GETTER(Rva00466AC9DwordField, 0x27C)
BFME_DISP32_DWORD_GETTER(Rva0051C05CDwordField, 0x638)
BFME_DISP32_DWORD_GETTER(Rva00552C39DwordField, 0x101C)

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?get@Rva002620F3DwordField@@QBEHXZ")
