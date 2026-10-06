// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva00224818@Rva00222A8BTarget@@QAEXXZ @0x00224818 311B
// BFME1 donor WindowManager_bfmeRva0046E170.cpp adapted to BFME2 offsets: table at +0x5c via rowed Rva00223CDB, vector<int> finish at +0x300 flag at +0x308, 14 entries stride 0x28 at +0xF0, OnFocus via pin 0x00222A8B with g_00BBFDE0/BBFDDC. Evidence: callers 0x0022523C chain via 0x00223CDB; strings AptLevel0.apt /_level%d OnFocus.
#include "ascii_string.h"

class Rva00223CDB
{
public:
	int rva00223CDB(const AsciiString *key);
};

typedef bool Bool;

struct RvaFlags
{
	Bool m_bit0 : 1;
	Bool m_bit1 : 1;
	Bool m_bit2 : 1;
	Bool m_hasFocus : 1;
};

struct RvaEntry
{
	RvaFlags m_flags;
	char m_pad[0x28 - 1];
};

class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
	void rva00224818();
private:
	char m_pad0[0xF0];
	union
	{
		RvaEntry m_entries[14];
		struct
		{
			char m_pad1[0x20C];
			int *m_vecBegin;
			int *m_vecEnd;
			int *m_vecStorage;
			bool m_needsRefresh;
		};
	};
};

extern const char g_00BBFDDC[];
extern const char g_00BBFDE0[];

void Rva00222A8BTarget::rva00224818()
{
	if (!m_needsRefresh)
		return;
	m_needsRefresh = false;
	int *vecEnd = m_vecEnd;
	if (vecEnd[-1] != 0xe)
	{
		if (vecEnd[-1] == -1)
		{
			AsciiString path;
			AsciiString tmp("AptLevel0.apt");
			path.format("/_level%d", ((Rva00223CDB *)this)->rva00223CDB(&tmp));
		}
		else
		{
			AsciiString path;
			path.format("/_level%d", vecEnd[-1]);
		}
	}
	for (int i = 0; i < 0xe; ++i)
	{
		RvaFlags &flags = m_entries[i].m_flags;
		if (flags.m_bit1)
		{
			bool focused = vecEnd[-1] != 0xe ? (vecEnd[-1] != -1 ? vecEnd[-1] == i : false) : true;
			if (focused != flags.m_hasFocus)
			{
				flags.m_hasFocus = focused;
				invoke((void *)i, "OnFocus", 1, focused ? g_00BBFDE0 : g_00BBFDDC, 0, 0, 0, 0);
			}
		}
	}
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00BBFDDC@@3QBDB=??_C@_01GBGANLPD@0?$AA@")
#pragma comment(linker, "/alternatename:?g_00BBFDE0@@3QBDB=??_C@_01HIHLOKLC@1?$AA@")
