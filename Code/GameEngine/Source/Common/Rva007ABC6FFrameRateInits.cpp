// cl: /MD
//
// Dynamic initializers from the 0x007AB7DA strip that derive an int from the
// logic frame rate: BfmeLogicFramesPerSecond (LOGICFRAMES_PER_SECOND, 30) or BfmeClientFramesPerSecond
// (the second frame-rate int the HalfRateInits strip divides) scaled by a
// constant, the BFME 2 spelling of Zero Hour's frame-count constants once the
// rate became a variable. Each is one translation unit's compiler-generated
// initializer; the owning TUs are unrecovered, so each keeps an honest
// address name. A destination some recovered TU already reads keeps that TU's
// name and type; one never read in .text stays a TU-local static here.
// /G7: retail scales by 3, 5 and 10 with imul where blended /O1 emits lea.

extern int BfmeLogicFramesPerSecond;
extern int BfmeClientFramesPerSecond;

extern int g_00DE1B50;
int g_00DE1B50 = 0;	// owned here; retail .data starts it at 0
extern int g_00DFEFCC;
int g_00DFEFCC = 0;	// owned here; retail .data starts it at 0
extern int g_00E033D0;
// Owned here: written by rva007B07F5 below; retail .data starts it at 0.
int g_00E033D0 = 0;
extern int g_00E05F24;
int g_00E05F24 = 0;	// owned here; retail .data starts it at 0
extern int g_00E062F4;
// Owned here: written by rva007B3FCA below; retail .data starts it at 0.
int g_00E062F4 = 0;
extern int g_00E063E0;
int g_00E063E0 = 0;	// owned here; retail .data starts it at 0
extern int g_00E063E8;
int g_00E063E8 = 0;	// owned here; retail .data starts it at 0
extern int g_Va00DFE18C;
extern unsigned g_00E063CC;
unsigned g_00E063CC = 0;	// owned here; retail .data starts it at 0
extern unsigned int g_00DFEE08;
unsigned int g_00DFEE08 = 0;	// owned here; retail .data starts it at 0

static int s_rva007ADE88;
static int s_rva007AE043;
static int s_rva007AEE6B;
static int s_rva007B042B;

struct Rva007ABC6FFrameRateInits
{
	static void rva007ABC6F();
	static void rva007AD7F3();
	static void rva007ADE88();
	static void rva007AE043();
	static void rva007AE0AD();
	static void rva007AE27C();
	static void rva007AEE6B();
	static void rva007B042B();
	static void rva007B07F5();
	static void rva007B3B50();
	static void rva007B3FCA();
	static void rva007B4316();
	static void rva007B43BD();
	static void rva007B440F();
};

// ?rva007ABC6F@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007ABC6F (16B): global at VA 0x00DE1B50, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007ABC6F()
{
	g_00DE1B50 = BfmeLogicFramesPerSecond / 2;
}

// ?rva007AD7F3@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AD7F3 (14B): global at VA 0x00DFE18C, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007AD7F3()
{
	g_Va00DFE18C = BfmeLogicFramesPerSecond * 5;
}

// ?rva007ADE88@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007ADE88 (16B): TU-local static at VA 0x00DFEB5C, never read in .text
void Rva007ABC6FFrameRateInits::rva007ADE88()
{
	s_rva007ADE88 = BfmeLogicFramesPerSecond / 2;
}

// ?rva007AE043@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AE043 (16B): TU-local static at VA 0x00DFECD8, never read in .text
void Rva007ABC6FFrameRateInits::rva007AE043()
{
	s_rva007AE043 = BfmeLogicFramesPerSecond / 2;
}

// ?rva007AE0AD@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AE0AD (11B): global at VA 0x00DFEE08, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007AE0AD()
{
	g_00DFEE08 = BfmeLogicFramesPerSecond;
}

// ?rva007AE27C@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AE27C (14B): global at VA 0x00DFEFCC, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007AE27C()
{
	g_00DFEFCC = BfmeLogicFramesPerSecond * 4;
}

// ?rva007AEE6B@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007AEE6B (16B): TU-local static at VA 0x00E01ED8, never read in .text
void Rva007ABC6FFrameRateInits::rva007AEE6B()
{
	s_rva007AEE6B = BfmeLogicFramesPerSecond / 2;
}

// ?rva007B042B@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B042B (16B): TU-local static at VA 0x00E0320C, never read in .text
void Rva007ABC6FFrameRateInits::rva007B042B()
{
	s_rva007B042B = BfmeLogicFramesPerSecond / 2;
}

// ?rva007B07F5@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B07F5 (11B): global at VA 0x00E033D0, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007B07F5()
{
	g_00E033D0 = BfmeLogicFramesPerSecond;
}

// ?rva007B3B50@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B3B50 (16B): global at VA 0x00E05F24, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007B3B50()
{
	g_00E05F24 = BfmeClientFramesPerSecond / 2;
}

// ?rva007B3FCA@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B3FCA (14B): global at VA 0x00E062F4, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007B3FCA()
{
	g_00E062F4 = BfmeLogicFramesPerSecond * 60;
}

// ?rva007B4316@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B4316 (14B): global at VA 0x00E063CC, named as the TU that reads it names it
void Rva007ABC6FFrameRateInits::rva007B4316()
{
	g_00E063CC = BfmeLogicFramesPerSecond * 120;
}

// ?rva007B43BD@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B43BD (14B): global at VA 0x00E063E0, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007B43BD()
{
	g_00E063E0 = BfmeLogicFramesPerSecond * 10;
}

// ?rva007B440F@Rva007ABC6FFrameRateInits@@SAXXZ @ 0x007B440F (16B): global at VA 0x00E063E8, also read elsewhere in .text
void Rva007ABC6FFrameRateInits::rva007B440F()
{
	g_00E063E8 = BfmeClientFramesPerSecond / 2;
}

