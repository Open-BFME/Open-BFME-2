// cl: /DNDEBUG /MD
//
// ?rva006d4280@@YAPBDPBDPAH@Z, retail 0x006D4280, 868 bytes.
// UTF-8 one-codepoint decoder: returns the pointer past one sequence and
// stores the codepoint through the out parameter. Callers are the cursor
// workers rva006d4d40/rva006d4d80 in Rva006D4CA0Cluster.cpp, the case folds
// rva006D6100/rva006D6170 in Rva006D6100Cluster.cpp, and 0x006D5FFC/0x006D78D6.
// Assert strings, line numbers and the g_bfmeAptAssert/g_bfmeAptBreakOnAssert
// triple are shared with the sibling Rva006D4CA0Cluster.cpp (/O2 /DNDEBUG /MD).
// The three store-and-return tails (one per return site, kept separate by
// _ReadWriteBarrier/_WriteBarrier) reproduce retail's ecx/edx/eax epilogues.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)

// ?rva006d4280@@YAPBDPBDPAH@Z @0x006D4280
const char *rva006d4280(const char *pBuffer, int *pUnicode)
{
	unsigned char cChar0 = (unsigned char)pBuffer[0];
	if ((cChar0 == 0xFE) || (cChar0 == 0xFF))
	{
		g_bfmeAptAssertAtE17734("(cChar0 != 0xFE) && (cChar0 != 0xFF)", ".\\string\\EAString.inl", 0x732);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	int unicode;
	if (cChar0 <= 0x7F)
	{
		unicode = cChar0;
		++pBuffer;
	}
	else
	{
		if ((cChar0 & 0xC0) != 0xC0)
		{
			g_bfmeAptAssertAtE17734("(cChar0 & 0xC0) == 0xC0", ".\\string\\EAString.inl", 0x73A);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		if ((cChar0 & 0xE0) == 0xC0)
		{
			unicode = ((cChar0 & 0x1F) << 6);
			unsigned char cChar1 = (unsigned char)pBuffer[1];
			if ((cChar1 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar1 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x741);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			unicode |= (cChar1 & 0x3F);
			if (unicode < 0x80)
			{
				g_bfmeAptAssertAtE17734("unicode >= 0x80", ".\\string\\EAString.inl", 0x744);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			if (unicode >= 0x800)
			{
				g_bfmeAptAssertAtE17734("unicode < 0x0800", ".\\string\\EAString.inl", 0x745);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			pBuffer += 2;
		}
		else if ((cChar0 & 0xF0) == 0xE0)
		{
			unicode = ((cChar0 & 0x0F) << 12);
			unsigned char cChar1 = (unsigned char)pBuffer[1];
			if ((cChar1 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar1 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x74E);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			unicode |= ((cChar1 & 0x3F) << 6);
			unsigned char cChar2 = (unsigned char)pBuffer[2];
			if ((cChar2 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar2 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x752);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			unicode |= (cChar2 & 0x3F);
			if (unicode < 0x800)
			{
				g_bfmeAptAssertAtE17734("unicode >= 0x800", ".\\string\\EAString.inl", 0x755);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			if (unicode >= 0x10000)
			{
				g_bfmeAptAssertAtE17734("unicode < 0x10000", ".\\string\\EAString.inl", 0x756);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			pBuffer += 3;
		}
		else
		{
			if ((cChar0 & 0xF8) != 0xF0)
			{
				g_bfmeAptAssertAtE17734("(cChar0 & 0xf8) == 0xf0", ".\\string\\EAString.inl", 0x75C);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			unicode = ((cChar0 & 0x07) << 18);
			unsigned char cChar1 = (unsigned char)pBuffer[1];
			if ((cChar1 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar1 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x760);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			unicode |= ((cChar1 & 0x3F) << 12);
			unsigned char cChar2 = (unsigned char)pBuffer[2];
			if ((cChar2 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar2 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x764);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			unicode |= ((cChar2 & 0x3F) << 6);
			unsigned char cChar3 = (unsigned char)pBuffer[3];
			if ((cChar3 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar3 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x768);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			unicode |= (cChar3 & 0x3F);
			if (unicode < 0x10000)
			{
				g_bfmeAptAssertAtE17734("unicode >= 0x10000", ".\\string\\EAString.inl", 0x76B);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			if (unicode > 0x10FFFF)
			{
				g_bfmeAptAssertAtE17734("unicode <= 0x10FFFF", ".\\string\\EAString.inl", 0x76C);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			pBuffer += 4;
		}
	}
	if (unicode > 0x10FFFF)
	{
		g_bfmeAptAssertAtE17734("UTF8_IsValid(unicode)", ".\\string\\EAString.inl", 0x772);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
		{
			__debugbreak();
			_ReadWriteBarrier();
			*pUnicode = unicode;
			return pBuffer;
		}
		_WriteBarrier();
		*pUnicode = unicode;
		return pBuffer;
	}
	*pUnicode = unicode;
	return pBuffer;
}
