// cl: /O1 /G7 /MD
//
// Dynamic initializers from the 0x007AB7DA strip that derive an int from the
// logic frame rate: g_Va00DBA4E4 (LOGICFRAMES_PER_SECOND, 30) or g_00DBA4E8
// (the second frame-rate int the HalfRateInits strip divides) scaled by a
// constant, the BFME 2 spelling of Zero Hour's frame-count constants once the
// rate became a variable. Each is one translation unit's compiler-generated
// initializer; the owning TUs are unrecovered, so each keeps an honest
// address name. A destination some recovered TU already reads keeps that TU's
// name and type; one never read in .text stays a TU-local static here.
// /G7: retail scales by 3, 5 and 10 with imul where blended /O1 emits lea.

extern int g_Va00DBA4E4;
extern int g_00DBA4E8;

extern int g_00DE1B50;
extern int g_00DFEB98;
extern int g_00DFEBB0;
extern int g_00DFEFCC;
extern int g_00E01E04;
extern int g_00E02D9C;
extern int g_00E033D0;
extern int g_00E035C8;
extern int g_00E03994;
extern int g_00E05F24;
extern int g_00E062F4;
extern int g_00E063E0;
extern int g_00E063E8;
extern int g_Va00DE204C;
extern int g_Va00DFE18C;
extern int g_Va00E03BBC;
extern unsigned g_00E063CC;
extern unsigned int g_00DFEE08;
extern unsigned int g_00E06648;

static int s_rva007ADD08;
static int s_rva007ADD72;
static int s_rva007ADE88;
static int s_rva007AE043;
static int s_rva007AE2CE;
static int s_rva007AEE6B;
static int s_rva007B014F;
static int s_rva007B042B;
static int s_rva007B08B2;
static int s_rva007B0BA0;
static int s_rva007B1122;
static int s_rva007B1328;

struct Rva007ABC6FFrameRateInits
{
	static void rva007ABC6F();
	static void rva007AC08C();
	static void rva007AD7F3();
	static void rva007ADD08();
	static void rva007ADD72();
	static void rva007ADE88();
	static void rva007ADEF6();
	static void rva007ADF60();
	static void rva007AE043();
	static void rva007AE0AD();
	static void rva007AE27C();
	static void rva007AE2CE();
	static void rva007AEBAA();
	static void rva007AEE6B();
	static void rva007AF85F();
	static void rva007B014F();
	static void rva007B042B();
	static void rva007B07F5();
	static void rva007B08B2();
	static void rva007B0BA0();
	static void rva007B0C0F();
	static void rva007B1122();
	static void rva007B1328();
	static void rva007B15B2();
	static void rva007B1A27();
	static void rva007B3B50();
	static void rva007B3FCA();
	static void rva007B4316();
	static void rva007B43BD();
	static void rva007B440F();
	static void rva007B4BC6();
};

// ?rva007ABC6F@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007ABC6F (16B): global at VA 0x00DE1B50, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007ABC6F()
{
	g_00DE1B50 = g_Va00DBA4E4 / 2;
}

// ?rva007AC08C@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AC08C (18B): global at VA 0x00DE204C, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007AC08C()
{
	g_Va00DE204C = 1000 / g_00DBA4E8;
}

// ?rva007AD7F3@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AD7F3 (14B): global at VA 0x00DFE18C, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007AD7F3()
{
	g_Va00DFE18C = g_Va00DBA4E4 * 5;
}

// ?rva007ADD08@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007ADD08 (16B): TU-local static at VA 0x00DFE968, never read in .text
void Rva007ABC6FFrameRateInits::rva007ADD08()
{
	s_rva007ADD08 = g_Va00DBA4E4 / 2;
}

// ?rva007ADD72@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007ADD72 (17B): TU-local static at VA 0x00DFE980, never read in .text
void Rva007ABC6FFrameRateInits::rva007ADD72()
{
	s_rva007ADD72 = g_Va00DBA4E4 / 4;
}

// ?rva007ADE88@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007ADE88 (16B): TU-local static at VA 0x00DFEB5C, never read in .text
void Rva007ABC6FFrameRateInits::rva007ADE88()
{
	s_rva007ADE88 = g_Va00DBA4E4 / 2;
}

// ?rva007ADEF6@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007ADEF6 (16B): global at VA 0x00DFEB98, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007ADEF6()
{
	g_00DFEB98 = g_00DBA4E8 / 2;
}

// ?rva007ADF60@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007ADF60 (14B): global at VA 0x00DFEBB0, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007ADF60()
{
	g_00DFEBB0 = g_Va00DBA4E4 * 3;
}

// ?rva007AE043@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AE043 (16B): TU-local static at VA 0x00DFECD8, never read in .text
void Rva007ABC6FFrameRateInits::rva007AE043()
{
	s_rva007AE043 = g_Va00DBA4E4 / 2;
}

// ?rva007AE0AD@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AE0AD (11B): global at VA 0x00DFEE08, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007AE0AD()
{
	g_00DFEE08 = g_Va00DBA4E4;
}

// ?rva007AE27C@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AE27C (14B): global at VA 0x00DFEFCC, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007AE27C()
{
	g_00DFEFCC = g_Va00DBA4E4 * 4;
}

// ?rva007AE2CE@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AE2CE (16B): TU-local static at VA 0x00DFEFD4, never read in .text
void Rva007ABC6FFrameRateInits::rva007AE2CE()
{
	s_rva007AE2CE = g_Va00DBA4E4 / 2;
}

// ?rva007AEBAA@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AEBAA (13B): global at VA 0x00E01E04, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007AEBAA()
{
	g_00E01E04 = g_Va00DBA4E4 * 2;
}

// ?rva007AEE6B@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AEE6B (16B): TU-local static at VA 0x00E01ED8, never read in .text
void Rva007ABC6FFrameRateInits::rva007AEE6B()
{
	s_rva007AEE6B = g_Va00DBA4E4 / 2;
}

// ?rva007AF85F@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AF85F (16B): global at VA 0x00E02D9C, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007AF85F()
{
	g_00E02D9C = g_00DBA4E8 / 2;
}

// ?rva007B014F@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B014F (16B): TU-local static at VA 0x00E030F0, never read in .text
void Rva007ABC6FFrameRateInits::rva007B014F()
{
	s_rva007B014F = g_Va00DBA4E4 / 2;
}

// ?rva007B042B@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B042B (16B): TU-local static at VA 0x00E0320C, never read in .text
void Rva007ABC6FFrameRateInits::rva007B042B()
{
	s_rva007B042B = g_Va00DBA4E4 / 2;
}

// ?rva007B07F5@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B07F5 (11B): global at VA 0x00E033D0, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007B07F5()
{
	g_00E033D0 = g_Va00DBA4E4;
}

// ?rva007B08B2@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B08B2 (16B): TU-local static at VA 0x00E033F8, never read in .text
void Rva007ABC6FFrameRateInits::rva007B08B2()
{
	s_rva007B08B2 = g_Va00DBA4E4 / 2;
}

// ?rva007B0BA0@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B0BA0 (17B): TU-local static at VA 0x00E0359C, never read in .text
void Rva007ABC6FFrameRateInits::rva007B0BA0()
{
	s_rva007B0BA0 = g_Va00DBA4E4 / 4;
}

// ?rva007B0C0F@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B0C0F (16B): global at VA 0x00E035C8, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007B0C0F()
{
	g_00E035C8 = g_Va00DBA4E4 / 2;
}

// ?rva007B1122@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B1122 (16B): TU-local static at VA 0x00E037D0, never read in .text
void Rva007ABC6FFrameRateInits::rva007B1122()
{
	s_rva007B1122 = g_Va00DBA4E4 / 2;
}

// ?rva007B1328@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B1328 (16B): TU-local static at VA 0x00E03888, never read in .text
void Rva007ABC6FFrameRateInits::rva007B1328()
{
	s_rva007B1328 = g_Va00DBA4E4 / 2;
}

// ?rva007B15B2@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B15B2 (11B): global at VA 0x00E03994, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007B15B2()
{
	g_00E03994 = g_Va00DBA4E4;
}

// ?rva007B1A27@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B1A27 (17B): global at VA 0x00E03BBC, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007B1A27()
{
	g_Va00E03BBC = g_Va00DBA4E4 / 4;
}

// ?rva007B3B50@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B3B50 (16B): global at VA 0x00E05F24, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007B3B50()
{
	g_00E05F24 = g_00DBA4E8 / 2;
}

// ?rva007B3FCA@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B3FCA (14B): global at VA 0x00E062F4, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007B3FCA()
{
	g_00E062F4 = g_Va00DBA4E4 * 60;
}

// ?rva007B4316@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B4316 (14B): global at VA 0x00E063CC, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007B4316()
{
	g_00E063CC = g_Va00DBA4E4 * 120;
}

// ?rva007B43BD@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B43BD (14B): global at VA 0x00E063E0, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007B43BD()
{
	g_00E063E0 = g_Va00DBA4E4 * 10;
}

// ?rva007B440F@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B440F (16B): global at VA 0x00E063E8, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007B440F()
{
	g_00E063E8 = g_00DBA4E8 / 2;
}

// ?rva007B4BC6@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B4BC6 (14B): global at VA 0x00E06648, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007B4BC6()
{
	g_00E06648 = g_Va00DBA4E4 * 10;
}
