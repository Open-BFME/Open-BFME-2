// cl: /DNDEBUG /MD
// ?utf8EncodedLength@@YAHH@Z @0x006D3DB0 (133B). UTF-8 encoded length of a
// code point with BFME2 validation. Donor is open-bfme-1
// Code/Libraries/Source/EA/Apt/AptString/utf8EncodedLength.cpp
// (?utf8EncodedLength@@YAHH@Z, 46B, same 0x80/0x800/0x10000 thresholds and
// 1/2/3/4 returns); retail adds the EAString.inl asserts
// "UTF8_IsValid(iCharacter)" (0x604) and "iCharacter < 00200000" (0x613)
// via the shared Apt assert/import/flag triple. Callers at 0x006D4E29 and
// 0x006D61FE (length then ChangeBuffer then encode) fit an Assign(codepoint)
// worker; neighbours SetSize 0x006D3BC0 and ChangeBuffer 0x006D4AA0 share
// the /O2 /DNDEBUG /MD flags.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

int utf8EncodedLength(int c)
{
	if (!(c <= 0x10FFFF)) {
		g_bfmeAptAssertAtE17734("UTF8_IsValid(iCharacter)", ".\\string\\EAString.inl", 0x604);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			__asm int 3
		}
	}
	if (c < 0x80)
		return 1;
	if (c < 0x800)
		return 2;
	if (c < 0x10000)
		return 3;
	g_bfmeAptAssertAtE17734("iCharacter < 00200000", ".\\string\\EAString.inl", 0x613);
	if (g_bfmeAptBreakOnAssertAtDDC01C) {
		__asm int 3
	}
	return 4;
}
