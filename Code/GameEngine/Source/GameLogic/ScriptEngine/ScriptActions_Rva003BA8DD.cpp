// cl: /DNDEBUG /MD /EHsc
//
// ScriptActions float setter over the writable GlobalData singleton, retail 0x003BA8DD
// (22 bytes, ret 4): movss the argument into [TheWritableGlobalData+0x950]. Boundary
// by ret-scan; no E8 caller image-wide (likely vtable-reached or dead), so
// the true identity stays open and the row carries an address token
// (opaque-holder precedent). The /arch:SSE flag reproduces the movss pair
// (ScriptActions_Rva003BC37C precedent).

class GlobalData
{
public:
	unsigned char pad[0x950];
	float float0950;
};

extern GlobalData *TheWritableGlobalData;

struct Rva003BA8DDHolder
{
	void set(float value);
};

// ?set@Rva003BA8DDHolder@@QAEXM@Z
void Rva003BA8DDHolder::set(float value)
{
	TheWritableGlobalData->float0950 = value;
}
// Retail operand VA 0x00DFE758 is TheWritableGlobalData, defined in
// GameClient.cpp. GameLogic is a different global at VA 0x00DFE78C.
