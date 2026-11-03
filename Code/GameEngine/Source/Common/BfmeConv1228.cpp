// Open-BFME5 conversions.

#include <string.h>

struct BfmeW1228
{
	const char *m_bfme00;
	int m_bfme04;
};

// Initializers read from the retail VAs referenced by bfmeFind1228's matched
// DIR32 slots: six 8-byte words at 0x00DDCF54, six lengths at 0x00DDCF84,
// and the 16-entry signed lookup at 0x00DDCF8C.
BfmeW1228 g_bfmeWords1228[] =
{
	{ "align", 1 },
	{ "height", 2 },
	{ "scaleMode", 4 },
	{ "width", 3 },
	{ "addListener", 100 },
	{ "removeListener", 101 }
};

signed char g_bfmeLookup1228[16] =
{
	-1, -1, -1, -1, -1, 0, 1, -1,
	-1, 2, 3, 4, -1, -1, 5, 0
};

unsigned char g_bfmeLens1228[6] = { 5, 6, 9, 5, 11, 14 };

extern "C" int bfmeHash1228(const char *str, unsigned int len)
{
	const unsigned char asso_values[256] =
	{
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 0, 0, 0, 15, 0, 15, 0, 15, 15, 0, 15, 15, 0,
	15, 15, 15, 15, 5, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	};
	register unsigned int hval = len;

	switch (hval)
	{
	default:
		hval += asso_values[(unsigned char)str[7]];
		/*FALLTHROUGH*/
	case 7:
	case 6:
	case 5:
	case 4:
		hval += asso_values[(unsigned char)str[3]];
		/*FALLTHROUGH*/
	case 3:
	case 2:
		hval += asso_values[(unsigned char)str[1]];
		break;
	}
	return hval;
}

const BfmeW1228 *bfmeFind1228(const char *str, unsigned int len)
{
	int key;
	int index;
	const char *s;

	if (len <= 14 && len >= 5) {
		key = bfmeHash1228(str, len);
		if (key <= 14 && key >= 0) {
			index = g_bfmeLookup1228[key];
			if (index >= 0) {
				if (len == g_bfmeLens1228[index]) {
					s = g_bfmeWords1228[index].m_bfme00;
					if (*str == *s && !memcmp(str + 1, s + 1, len - 1))
						return &g_bfmeWords1228[index];
				}
			}
		}
	}
	return 0;
}
