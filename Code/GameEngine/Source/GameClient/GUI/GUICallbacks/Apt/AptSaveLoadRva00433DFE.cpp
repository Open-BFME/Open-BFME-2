// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// Target evidence at 0x00433DFE: Apt query callback over the Save/Load label
// and the Campaign/Skirmish/Replay/WOTR/WOTRMP mode bits. The surrounding
// save/load callbacks establish the screen and state field at +0x27C.
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
extern "C" char *__cdecl _mbscpy(char *, const char *);
extern "C" char *__cdecl _mbscat(char *, const char *);

#pragma comment(linker, "/alternatename:_mbscpy=?ji_00629176@@YAXXZ")
#pragma comment(linker, "/alternatename:_mbscat=?ji_0062988c@@YAXXZ")

class AptSaveLoad
{
public:
	void Rva00433DFE(int query, char *value, bool set);

private:
	unsigned char m_pad000[0x27C];
	int m_state;
	unsigned char m_pad280[0x294 - 0x280];
	int m_fileType;
	unsigned char m_filterEnabled;
	unsigned char m_pad299[0x2A0 - 0x299];
	int m_mode;
};

void AptSaveLoad::Rva00433DFE(int query, char *value, bool set)
{
	if (!set)
	{
		value[0] = '0';
		value[1] = 0;
	}

	switch (query)
	{
	case 0:
		if (!set)
		{
			if (m_fileType == 3)
				_mbscpy(value, "Save");
			else if (m_fileType == 2)
				_mbscpy(value, "Load");
		}
		break;
	case 1:
		if (set)
			return;
		value[0] = set;
		if (m_filterEnabled & 1)
			_mbscat(value, "Campaign");
		if (m_filterEnabled & 2)
			_mbscat(value, "Skirmish");
		if (m_filterEnabled & 4)
			_mbscat(value, "Replay");
		if (m_filterEnabled & 8)
			_mbscat(value, "WOTR");
		if (m_filterEnabled & 16)
			_mbscat(value, "WOTRMP");
		break;
	case 2:
		if (!set)
			return;
		if (_strcmpi(value, "Campaign") == 0)
			m_mode = 1;
		else if (_strcmpi(value, "Skirmish") == 0)
			m_mode = 2;
		else if (_strcmpi(value, "Replay") == 0)
			m_mode = 4;
		else if (_strcmpi(value, "WOTR") == 0)
			m_mode = 8;
		else if (_strcmpi(value, "WOTRMP") == 0)
			m_mode = 16;
		if (m_state == 0)
			m_state = 2;
		break;
	}
}
