// cl: /DNDEBUG /MD
// Retail 0x006D3E40, 844 bytes including the epilogue beyond Ghidra's split.
// Decode one UTF-8 sequence to its Unicode value. Identity and assertion
// constants come from retail; the matched 006D4280 cursor decoder and BFME1
// 9cbfb551 Rva0089DF20Utf8Decode.cpp supply the semantic reference.
// MSVC's __debugbreak intrinsic pools assertion tails (804 bytes). The inline
// int 3 debug trap preserves the retail control-flow boundaries (844 bytes).
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

// ?rva006d3e40@@YAHPBD@Z @0x006D3E40
int rva006d3e40(const char *pBuffer)
{
	unsigned char cChar0 = (unsigned char)pBuffer[0];
	if ((cChar0 == 0xFE) || (cChar0 == 0xFF))
	{
		g_bfmeAptAssertAtE17734("(cChar0 != 0xFE) && (cChar0 != 0xFF)", ".\\string\\EAString.inl", 0x674);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__asm { int 3 }
	}
	int unicode;
	if (cChar0 <= 0x7F)
	{
		unicode = cChar0;

	}
	else
	{
		if ((cChar0 & 0xC0) != 0xC0)
		{
			g_bfmeAptAssertAtE17734("(cChar0 & 0xC0) == 0xC0", ".\\string\\EAString.inl", 0x67b);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__asm { int 3 }
		}
		if ((cChar0 & 0xE0) == 0xC0)
		{
			unicode = ((cChar0 & 0x1F) << 6);
			unsigned char cChar1 = (unsigned char)pBuffer[1];
			if ((cChar1 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar1 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x682);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}
			unicode |= (cChar1 & 0x3F);
			if (unicode < 0x80)
			{
				g_bfmeAptAssertAtE17734("unicode >= 0x80", ".\\string\\EAString.inl", 0x685);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}
			if (unicode >= 0x800)
			{
				g_bfmeAptAssertAtE17734("unicode < 0x0800", ".\\string\\EAString.inl", 0x686);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}

		}
		else if ((cChar0 & 0xF0) == 0xE0)
		{
			unicode = ((cChar0 & 0x0F) << 12);
			unsigned char cChar1 = (unsigned char)pBuffer[1];
			if ((cChar1 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar1 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x68d);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}
			unicode |= ((cChar1 & 0x3F) << 6);
			unsigned char cChar2 = (unsigned char)pBuffer[2];
			if ((cChar2 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar2 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x691);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}
			unicode |= (cChar2 & 0x3F);
			if (unicode < 0x800)
			{
				g_bfmeAptAssertAtE17734("unicode >= 0x800", ".\\string\\EAString.inl", 0x694);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}
			if (unicode >= 0x10000)
			{
				g_bfmeAptAssertAtE17734("unicode < 0x10000", ".\\string\\EAString.inl", 0x695);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}

		}
		else
		{
			if ((cChar0 & 0xF8) != 0xF0)
			{
				g_bfmeAptAssertAtE17734("(cChar0 & 0xf8) == 0xf0", ".\\string\\EAString.inl", 0x699);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}
			unicode = ((cChar0 & 0x07) << 18);
			unsigned char cChar1 = (unsigned char)pBuffer[1];
			if ((cChar1 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar1 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x69d);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}
			unicode |= ((cChar1 & 0x3F) << 12);
			unsigned char cChar2 = (unsigned char)pBuffer[2];
			if ((cChar2 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar2 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x6a1);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}
			unicode |= ((cChar2 & 0x3F) << 6);
			unsigned char cChar3 = (unsigned char)pBuffer[3];
			if ((cChar3 & 0xC0) != 0x80)
			{
				g_bfmeAptAssertAtE17734("(cChar3 & 0xC0) == 0x80", ".\\string\\EAString.inl", 0x6a5);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}
			unicode |= (cChar3 & 0x3F);
			if (unicode < 0x10000)
			{
				g_bfmeAptAssertAtE17734("unicode >= 0x10000", ".\\string\\EAString.inl", 0x6a8);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}
			if (unicode > 0x10FFFF)
			{
				g_bfmeAptAssertAtE17734("unicode <= 0x10FFFF", ".\\string\\EAString.inl", 0x6a9);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__asm { int 3 }
			}

		}
	}
	if (unicode > 0x10FFFF)
	{
		g_bfmeAptAssertAtE17734("UTF8_IsValid(unicode)", ".\\string\\EAString.inl", 0x6ad);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
		{
			__asm { int 3 }

			return unicode;
		}

		return unicode;
	}

	return unicode;
}
