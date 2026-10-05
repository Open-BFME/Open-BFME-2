// cl: /O1 /arch:SSE /MD
//
// Static-initializer strip: float rates derived from LOGICFRAMES_PER_SECOND
// (the int at VA 0x00DBA4E4) times 1.5f and 3.0f. Retail converts with
// cvtsi2ss and multiplies with mulss, so the owning units were built with
// /arch:SSE. The owning TUs are unrecovered, so each initializer keeps an
// honest address name.

extern int g_Va00DBA4E4;

// Never read elsewhere in .text.
static float s_rva007AF1DE;
// Read by 0x003942FD.
extern float g_00E027C4;

struct Rva007AF1DEFrameScaleSseInits
{
	static void rva007AF1DE();
	static void rva007AF1F7();
};

// 0x007AF1DE (25B): VA 0x00E027C0 = LOGICFRAMES_PER_SECOND * 1.5f
void Rva007AF1DEFrameScaleSseInits::rva007AF1DE()
{
	s_rva007AF1DE = g_Va00DBA4E4 * 1.5f;
}

// 0x007AF1F7 (25B): VA 0x00E027C4 = LOGICFRAMES_PER_SECOND * 3.0f
void Rva007AF1DEFrameScaleSseInits::rva007AF1F7()
{
	g_00E027C4 = g_Va00DBA4E4 * 3.0f;
}
