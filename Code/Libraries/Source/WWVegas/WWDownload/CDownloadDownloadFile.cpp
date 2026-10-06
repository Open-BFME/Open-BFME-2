// cl: /DNDEBUG /MD /EHs-c- /Ob2
//
// ?DownloadFile@CDownload@@UAEJPBD00000_N@Z,
// retail 0x006C9760, 449 bytes. Dedicated TU.
//
// Zero Hour reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDownload/Download.cpp,
// CDownload::DownloadFile): status-gated download kickoff. The retail body
// follows the reference source exactly: reject unless DONE/FINDINGFILE,
// disconnect on a server switch inside FINDINGFILE, reject null parameters,
// _mkdir the download directory, copy the seven parameters into the member
// buffers, then arm GO unless still FINDINGFILE. The member layout matches
// the reference header exactly (m_Server +0x04, m_Login +0x104, m_Status
// +0x584, m_TryResume +0x598, m_Ftp +0x5C0). The two strcmp calls compile to
// inline byte loops under /O2; strncpy rides the msvcr71 import through a
// register after the first load.

#include <string.h>

typedef const char *LPCSTR;
typedef long HRESULT;

#define S_OK 0
#define DOWNLOADSTATUS_NONE 0
#define DOWNLOADSTATUS_GO 1
#define DOWNLOADSTATUS_FINDINGFILE 4
#define DOWNLOADSTATUS_DONE 0
#define DOWNLOAD_SUCCEEDED S_OK
#define DOWNLOAD_PARAMERROR 0x80040001
#define DOWNLOAD_STATUSERROR 0x80040002
#define E_FAIL 0x80004005

extern "C" __declspec(dllimport) int __cdecl _mkdir(const char *dirname);
extern "C" __declspec(dllimport) char *__cdecl strncpy(
	char *destination, const char *source, unsigned int count);

class Cftp
{
public:
	HRESULT DisconnectFromServer();
};

class IDownload;

class __declspec(novtable) CDownload
{
public:
	virtual HRESULT PumpMessages() = 0;
	virtual HRESULT Abort() = 0;
	virtual HRESULT DownloadFile(LPCSTR server, LPCSTR username, LPCSTR password, LPCSTR file, LPCSTR localfile, LPCSTR regkey, bool tryresume = true) = 0;
	virtual HRESULT GetLastLocalFile(char *local_file, int maxlen) = 0;

private:
	char m_Server[256]; // +0x04
	char m_Login[64]; // +0x104
	char m_Password[64]; // +0x144
	char m_File[256]; // +0x184
	char m_LocalFile[256]; // +0x284
	char m_LastLocalFile[256]; // +0x384
	char m_RegKey[256]; // +0x484
	int m_Status; // +0x584
	int m_TimeStarted; // +0x588
	int m_StartPosition; // +0x58C
	int m_FileSize; // +0x590
	int m_BytesRead; // +0x594
	bool m_TryResume; // +0x598
	int m_predictions; // +0x59C
	int m_predictionTimes[8]; // +0x5A0
	Cftp *m_Ftp; // +0x5C0
	IDownload *m_Listener; // +0x5C4
};

// ?DownloadFile@CDownload@@UAEJPBD00000_N@Z
HRESULT CDownload::DownloadFile(LPCSTR server, LPCSTR username, LPCSTR password, LPCSTR file, LPCSTR localfile, LPCSTR regkey, bool tryresume)
{
	// Check we're not in the middle of another download.
	if ((m_Status != DOWNLOADSTATUS_DONE) && (m_Status != DOWNLOADSTATUS_FINDINGFILE))
	{
		return DOWNLOAD_STATUSERROR;
	}

	// If we're still connected, make sure we're on the right server
	if (m_Status == DOWNLOADSTATUS_FINDINGFILE)
	{
		if ((strcmp(m_Server, server)) || (strcmp(m_Login, username)))
		{
			// Damn, a server switch. Close conn & fix state
			m_Ftp->DisconnectFromServer();
			m_Status = DOWNLOADSTATUS_DONE;
		}
	}

	// Check all parameters are non-null.
	if ((server == NULL) || (username == NULL) ||
		(password == NULL) || (file == NULL) ||
		(localfile == NULL) || (regkey == NULL))
	{
		return DOWNLOAD_PARAMERROR;
	}

	// Make sure we have a download directory
	_mkdir("download");

	// Copy parameters to member variables.
	strncpy(m_Server, server, sizeof(m_Server));
	strncpy(m_Login, username, sizeof(m_Login));
	strncpy(m_Password, password, sizeof(m_Password));
	strncpy(m_File, file, sizeof(m_File));
	strncpy(m_LocalFile, localfile, sizeof(m_LocalFile));

	strncpy(m_LastLocalFile, localfile, sizeof(m_LastLocalFile));

	strncpy(m_RegKey, regkey, sizeof(m_RegKey));
	m_TryResume = tryresume;
	m_StartPosition = 0;

	// Set status so we start to connect at the next PumpMessages()
	if (m_Status != DOWNLOADSTATUS_FINDINGFILE)
		m_Status = DOWNLOADSTATUS_GO;

	return S_OK;
}

// ?GetLastLocalFile@CDownload@@UAEJPADH@Z
HRESULT CDownload::GetLastLocalFile(char *local_file, int maxlen)
{
	if (local_file == 0)
		return E_FAIL;

	strncpy(local_file, m_LastLocalFile, maxlen);
	local_file[maxlen - 1] = 0;

	return S_OK;
}
