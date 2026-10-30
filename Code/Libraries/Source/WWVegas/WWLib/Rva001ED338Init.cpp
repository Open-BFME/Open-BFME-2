// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva001ED338@Rva001ED338@@QAEXPAX@Z @0x001ED338 18B.
// Forwards to rowed INI::initFromINI 0x0002DE78 with the class FieldParse table.
// Evidence: callee rowed 0x0002DE78; table g_00BDF1D8; caller 0x001ED61C in 0x001ED580.
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };
enum INILoadType { INI_LOAD_INVALID, INI_LOAD_OVERWRITE };
class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	__declspec(dllimport) __forceinline INILoadType getLoadType() const { return loadType; }
	void initFromINI(void *, const FieldParse *);
	char m_pad00[0x8];
	INILoadType loadType; // +0x08 +0x08, overwrite for the startup files
};
extern "C" {
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiStringVectorAppend@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva001ED2C5Parse@@YAXPAVINI@@PAXPAV?$vector@UBfmeRecord001ECAF9@@V?$allocator@UBfmeRecord001ECAF9@@@_STL@@@_STL@@@Z")();
}
// The retail table at 0x007DF1D8: 4 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00BDF1D8[5] = {
	{ "CampaignDisplayNameLabel", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "OverallCampaignIntroMovie", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
	{ "CarryoverUnit", (FieldParseProc)&__identifier("?parseAsciiStringVectorAppend@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
	{ "Mission", (FieldParseProc)&__identifier("?Rva001ED2C5Parse@@YAXPAVINI@@PAXPAV?$vector@UBfmeRecord001ECAF9@@V?$allocator@UBfmeRecord001ECAF9@@@_STL@@@_STL@@@Z"), 0, 0x18 },
	{ 0, 0, 0, 0 }
};
class Rva001ED338
{
public:
	void rva001ED338(void *);
};
void Rva001ED338::rva001ED338(void *ini)
{
	((INI *)ini)->initFromINI(this, g_00BDF1D8);
}
