// cl: /O1 /MD
//
// Static-initializer strip: frame counts derived from LOGICFRAMES_PER_SECOND
// (the int at VA 0x00DBA4E4) by a float factor and truncated back to int
// through __ftol2: fild the frame rate, fmul the factor constant, convert.
// The factor is read from each initializer's .rdata constant (3.0f, 10.0f,
// 15.0f, 30.0f). The owning TUs are unrecovered, so each initializer keeps an
// honest address name; the two destinations AISpellBookAssistBattle.cpp
// already reads keep its names.

extern int g_Va00DBA4E4;

// AISpellBookAssistBattle.cpp's frame thresholds.
extern int g_00E06650;
extern int g_00E06660;
// Read by 0x005D85F5 and 0x005D85EF.
extern int g_00E06668;
extern int g_00E0666C;

struct Rva007B4C70FrameScaleInits
{
	static void rva007B4C70();
	static void rva007B4C87();
	static void rva007B4CD5();
	static void rva007B4CEC();
};

// 0x007B4C70 (23B): VA 0x00E06650 = (int)(LOGICFRAMES_PER_SECOND * 3.0f)
void Rva007B4C70FrameScaleInits::rva007B4C70()
{
	g_00E06650 = (int)( g_Va00DBA4E4 * 3.0f );
}

// 0x007B4C87 (23B): VA 0x00E06660 = (int)(LOGICFRAMES_PER_SECOND * 10.0f)
void Rva007B4C70FrameScaleInits::rva007B4C87()
{
	g_00E06660 = (int)( g_Va00DBA4E4 * 10.0f );
}

// 0x007B4CD5 (23B): VA 0x00E06668 = (int)(LOGICFRAMES_PER_SECOND * 15.0f)
void Rva007B4C70FrameScaleInits::rva007B4CD5()
{
	g_00E06668 = (int)( g_Va00DBA4E4 * 15.0f );
}

// 0x007B4CEC (23B): VA 0x00E0666C = (int)(LOGICFRAMES_PER_SECOND * 30.0f)
void Rva007B4C70FrameScaleInits::rva007B4CEC()
{
	g_00E0666C = (int)( g_Va00DBA4E4 * 30.0f );
}
