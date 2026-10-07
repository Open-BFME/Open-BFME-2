// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD

class GlobalData
{
public:
	char m_padToFlag26[0x26];
	char m_flag26;
	char m_padToValue28[1];
	int m_value28;
};

extern GlobalData *TheWritableGlobalData;

// ?Rva003B998EParse@@YAHPAPADH@Z @0x003B998E 29B
// Target evidence: called with command-line arguments by the adjacent parser;
// writes GlobalData fields at +0x26 and +0x28. Field meanings are inferred.
int Rva003B998EParse(char **, int)
{
	if (TheWritableGlobalData != 0)
	{
		TheWritableGlobalData->m_flag26 = 0;
		TheWritableGlobalData->m_value28 = 30000;
	}
	return 1;
}
