// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ScriptActions float setter over the writable GlobalData singleton, retail 0x003BC37C
// (22 bytes, ret 4): movss the argument into [TheWritableGlobalData+0xD40]. Boundary
// by ret-scan; no E8 caller image-wide (likely vtable-reached or dead), so
// the true identity stays open and the row carries an address token
// (opaque-holder precedent). The /arch:SSE flag reproduces the movss pair
// (RadiusDecal_setOpacity precedent).

class GlobalData
{
public:
	unsigned char pad[0xD40];
	float float0D40;
};

extern GlobalData *TheWritableGlobalData;

struct Rva003BC37CHolder
{
	void set(float value);
};

// ?set@Rva003BC37CHolder@@QAEXM@Z
void Rva003BC37CHolder::set(float value)
{
	TheWritableGlobalData->float0D40 = value;
}
// Retail operand VA 0x00DFE758 is TheWritableGlobalData, defined in
// GameClient.cpp. GameLogic is a different global at VA 0x00DFE78C.
