// Open-BFME5 conversions.

// The BFME1 donor's bfmeGo1062A and bfmeGo1062D have no BFME 2 row and read
// globals with no BFME 2 address (unresolved at link), so they stay out of
// the build; only bfmeGo1062B (0x006E8EF0) is rowed.
#if 0
class BfmeA1062
{
public:
	void bfmeF1062A(void);
};

class BfmeB1062
{
public:
	void bfmeF1062B(void);
};

extern BfmeA1062 *g_bfmeA1062;
extern BfmeB1062 *g_bfmeB1062;

void bfmeGo1062A(void)
{
	if (g_bfmeA1062)
		g_bfmeA1062->bfmeF1062A();
	if (g_bfmeB1062)
		g_bfmeB1062->bfmeF1062B();
}

#endif

#include "../../../Libraries/Source/Apt/BfmeC1062.h"

extern BfmeC1062 *g_bfmeC1062;
// g_bfmeC1062: matched references place it at VA 0xe1816c (zero-filled .bss).
BfmeC1062 * g_bfmeC1062;
extern BfmeC1062 *g_bfmeD1062;
// g_bfmeD1062: matched references place it at VA 0xe18170 (zero-filled .bss).
BfmeC1062 * g_bfmeD1062;

void bfmeGo1062B(void)
{
	if (g_bfmeC1062) {
		g_bfmeC1062->bfmeSlot1062C_1();
		g_bfmeC1062 = 0;
	}
	if (g_bfmeD1062) {
		g_bfmeD1062->bfmeSlot1062C_1();
		g_bfmeD1062 = 0;
	}
}

#if 0
struct BfmeP1062
{
	char m_bfmePad[0x50];
	int m_bfme50;
};

extern BfmeP1062 *g_bfmeP1062;
extern char g_bfmeLit1_1062[];
extern char g_bfmeLit2_1062[];
extern char g_bfmeLit3_1062[];
extern char g_bfmeLitC1062[];

class BfmeX1062;
extern BfmeX1062 *g_bfmeX1062;

class BfmeR1062
{
public:
	void bfmeRun1062(BfmeX1062 *a, char *b, int c, char *d, int e, int f, int g, int h);
};

extern BfmeR1062 *g_bfmeR1062;

void bfmeGo1062D(void)
{
	char *s;

	switch (g_bfmeP1062->m_bfme50) {
		case 1:
			s = g_bfmeLit1_1062;
			break;
		case 2:
			s = g_bfmeLit2_1062;
			break;
		default:
			s = g_bfmeLit3_1062;
			break;
	}
	g_bfmeR1062->bfmeRun1062(g_bfmeX1062, g_bfmeLitC1062, 1, s, 0, 0, 0, 0);
}
#endif
