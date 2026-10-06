// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Retail's call target is the import slot 0x00BBA4E0, which reverse/functions.csv
// rows as ?ji_00629a7e@@YAXXZ -- msvcr71.dll's vsprintf. The donor's placeholder
// name carries no target evidence, so the real export name is used here. The
// donor's void* parameters are kept so the mangled name stays PAUBfmeSinkEQH@@PAX1@Z.
extern "C" __declspec(dllimport) int __cdecl vsprintf(void *buffer, void *format, void *out);
extern char g_bfmeBufferEQH[];					// retail 0x00DFF538

struct BfmeSinkEQH
{
	virtual void bfmeSlot0EQH(void);
	virtual void bfmeSlot1EQH(void);
	virtual void bfmeSendEQH(void *buffer);
};

void __cdecl bfmeReportEQH(BfmeSinkEQH *sink, void *what, void *out)
{
	if (vsprintf(g_bfmeBufferEQH, what, &out) >= 0)
		sink->bfmeSendEQH(g_bfmeBufferEQH);
}
