// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc

template<class T> class StringBase
{
public:
	void set(const T *);
};

class GlobalData
{
public:
	char m_padToFlag40[0x40];
	char m_flag40;
	char m_padToFlag9BF[0x9BF - 0x41];
	char m_flag9BF;
	char m_padToString[0xD38 - 0x9C0];
	StringBase<char> m_cinematicDirectory;
	char m_padToFlagD45[0xD45 - 0xD38 - sizeof(StringBase<char>)];
	char m_flagD45;
};

class SubsystemInterfaceList
{
public:
	char m_padToFlag[4];
	unsigned char m_initialized;
};

extern GlobalData *TheWritableGlobalData;
extern SubsystemInterfaceList *TheSubsystemList;
extern "C" char clean_list[9];

// ?Rva003B9E0FInit@@YAXXZ @0x003B9E0F 73B
// Target evidence: called by the following command-line helper; retail
// writes TheSubsystemList and TheWritableGlobalData fields and sets the
// "Mods\\cinematics" string. Field identities beyond those globals are inferred.
void Rva003B9E0FInit()
{
	if (TheWritableGlobalData != 0)
	{
		((unsigned char *)&TheSubsystemList)[4] = 1;
		TheWritableGlobalData->m_flagD45 = 1;
		TheWritableGlobalData->m_flag9BF = 0;
		TheWritableGlobalData->m_flag40 = 0;
		clean_list[8] = 0;
		TheWritableGlobalData->m_cinematicDirectory.set("Mods\\cinematics");
	}
}
