// Six B2-native flag-word clearers sharing the GlobalFlagClearers shape:
//
//     mov eax,[<address>] / and eax,<mask> / mov [<address>],eax / ret
//
// Unlike the BFME1-donor families in GlobalFlagClearers_04.cpp, these flag
// words exist only in this image (no BFME1 counterpart survived the
// mask-sequence sweep). Each body was placed by whole-.text shape search
// with VA-consistency (both address slots agree), C3/CC/C2 boundary and a
// free interval; the 0x774965/0x774975 pair is a contiguous run over one
// word. Identity is not recovered; every name is derived from an address.

extern unsigned int g_Va00DE084C;
extern unsigned int g_Va00DE0874;
extern unsigned int g_Va00DFEDE4;
extern unsigned int g_Va00E09E2C;
extern unsigned int g_Va00E176C4;

unsigned int Rva0075CCA0ClearFlag(void)
{
	return g_Va00DE084C &= 0xFFFFFFFEu;
}

unsigned int Rva0075CCC0ClearFlag(void)
{
	return g_Va00DE0874 &= 0xFFFFFFFEu;
}

unsigned int Rva00774965ClearFlag(void)
{
	return g_Va00DFEDE4 &= 0xFFFEFFFFu;
}

unsigned int Rva00774975ClearFlag(void)
{
	return g_Va00DFEDE4 &= 0xFFFDFFFFu;
}

unsigned int Rva007A7950ClearFlag(void)
{
	return g_Va00E09E2C &= 0xFFFFFFFEu;
}

unsigned int Rva007A7FF0ClearFlag(void)
{
	return g_Va00E176C4 &= 0xFFFFFFFEu;
}
