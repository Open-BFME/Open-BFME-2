// cl: /DNDEBUG /MD
//
// ?rva006d4ca0@@YAHPBD@Z @0x006D4CA0 (151B). UTF-8 lead-byte sequence-size
// worker: retail first runs the lead-byte codepoint decoder (rva006d3e40
// 0x006D3E40) for its assertions, then derives 1/2/3/4 from pBuffer[0] with
// the EAString.inl assertions at lines 0x5D9/0x5E0. Assert strings and the
// /O2 /DNDEBUG /MD flags are shared with Utf8EncodedLength.cpp and
// EAStringCUtf8Encode.cpp in this directory.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

int __cdecl rva006d3e40(const char *pBuffer);
int __cdecl utf8EncodedLength(int c);

int __cdecl rva006d4ca0(const char *pBuffer)
{
	rva006d3e40(pBuffer);
	unsigned char cChar0 = (unsigned char)pBuffer[0];
	if ((cChar0 == 0xFE) || (cChar0 == 0xFF))
	{
		g_bfmeAptAssertAtE17734("(cChar0 != 0xFE) && (cChar0 != 0xFF)", ".\\string\\EAString.inl", 0x5D9);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (cChar0 <= 0x7F)
		return 1;
	if ((cChar0 & 0xC0) != 0xC0)
	{
		g_bfmeAptAssertAtE17734("(cChar0 & 0xC0) == 0xC0", ".\\string\\EAString.inl", 0x5E0);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if ((cChar0 & 0xE0) == 0xC0)
		return 2;
	return ((cChar0 & 0xF0) != 0xE0) ? 4 : 3;
}

// ?rva006d4280@@YAPBDPBDPAH@Z @0x006D4280 (856B, unrowed). The cursor decoder
// both workers below call: it returns the pointer past one UTF-8 sequence and
// stores the decoded codepoint through the out parameter.
const char *__cdecl rva006d4280(const char *pBuffer, int *pUnicode);

// ?rva006d4d40@@YAPAXPAXH@Z @0x006D4D40 (51B). Advances a UTF-8 cursor by
// `count` codepoints and returns the new cursor, or null at the terminator.
// Called by EAStringC::rva006d5e70 0x006D5E70 with the payload and an index.
void *__cdecl rva006d4d40(void *pBuffer, int count)
{
	const char *p = (const char *)pBuffer;
	int i = 0;
	if (count <= 0)
		return (void *)p;
	do
	{
		int value;
		p = rva006d4280(p, &value);
		if (value == 0)
			return 0;
		++i;
	} while (i < count);
	return (void *)p;
}

// ?rva006d4d80@@YAHPBD@Z @0x006D4D80 (59B). Counts the codepoints in a UTF-8
// byte string, stopping at the terminator, via the same cursor decoder.
int __cdecl rva006d4d80(const char *pBuffer)
{
	const char *p = pBuffer;
	int count = 0;
	for (;;)
	{
		int value;
		p = rva006d4280(p, &value);
		if (value == 0)
			return count;
		++count;
	}
}

// ?rva006d4dc0@@YAXPADH@Z @0x006D4DC0 313B: UTF-8 encode iCharacter into pBuffer 1-4 bytes with EAString.inl asserts 0x6C5-0x6C8. Same assert triple and /O2 flags as neighbours.
void __cdecl rva006d4dc0(char *pBuffer, int iCharacter)
{
	if (iCharacter == 0)
	{
		g_bfmeAptAssertAtE17734("iCharacter != 0", ".\\string\\EAString.inl", 0x6C5);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (rva006d3e40(pBuffer) == 0)
	{
		g_bfmeAptAssertAtE17734("UTF8_GetCharacter(pBuffer) != 0", ".\\string\\EAString.inl", 0x6C6);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	int sizeBuf = rva006d4ca0(pBuffer);
	int sizeChar = utf8EncodedLength(iCharacter);
	if (sizeBuf != sizeChar)
	{
		g_bfmeAptAssertAtE17734("UTF8_GetCharacterSize(pBuffer) == UTF8_GetCharacterSize(iCharacter)", ".\\string\\EAString.inl", 0x6C7);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (iCharacter > 0x10FFFF)
	{
		g_bfmeAptAssertAtE17734("UTF8_IsValid(iCharacter)", ".\\string\\EAString.inl", 0x6C8);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (iCharacter < 0x80)
	{
		pBuffer[0] = (char)iCharacter;
		return;
	}
	if (iCharacter < 0x800)
	{
		pBuffer[0] = (char)(0xC0 | (iCharacter >> 6));
		pBuffer[1] = (char)(0x80 | (iCharacter & 0x3F));
		return;
	}
	if (iCharacter < 0x10000)
	{
		pBuffer[0] = (char)(0xE0 | (iCharacter >> 12));
		pBuffer[1] = (char)(0x80 | ((iCharacter >> 6) & 0x3F));
		pBuffer[2] = (char)(0x80 | (iCharacter & 0x3F));
		return;
	}
	pBuffer[0] = (char)(0xF0 | (iCharacter >> 18));
	pBuffer[1] = (char)(0x80 | ((iCharacter >> 12) & 0x3F));
	pBuffer[2] = (char)(0x80 | ((iCharacter >> 6) & 0x3F));
	pBuffer[3] = (char)(0x80 | (iCharacter & 0x3F));
}
