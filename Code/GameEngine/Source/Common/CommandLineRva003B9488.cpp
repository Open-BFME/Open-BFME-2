// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD

class GlobalData
{
	public:
	char m_padToRva003B9488[0xB00];
	unsigned char m_rva003B9488Flag;
};

extern GlobalData *TheWritableGlobalData;

// ?Rva003B9488Parse@@YAHPAPADH@Z @0x003B9488 20B
// Target evidence: direct call from the following command-line helper and
// matched global TheWritableGlobalData; byte +0xB00 is address-derived layout.
int Rva003B9488Parse(char **, int)
{
	if (TheWritableGlobalData != 0)
		TheWritableGlobalData->m_rva003B9488Flag = 0;
	return 1;
}
