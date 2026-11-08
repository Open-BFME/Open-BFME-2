// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/gametext_fetch14 /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameNetwork/DownloadManager.cpp); this unit had no counterpart under Code/.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: DownloadManager.cpp //////////////////////////////////////////////////////
// Generals download manager code
// Author: Matthew D. Campbell, July 2002

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

// CDownload's header-inline ctor/dtor (WWDownload/download.h) are emitted as
// select-any copies in every TU that news a CDownload. The kept copy
// (CDownloadCtorEmit.cpp) uses default speed flags, while this TU is /O1
// (framed SEH plus rep-stos versus frameless plus discrete stores), so this
// TU's copy differs. Pre-include the header under speed flags so the copy
// matches the kept one; the guards make the later transitive include a no-op.
//
// ~CDownload is the one header inline this TU must not emit: retail calls the
// rowed out-of-line body 0x006C9730 (CDownloadDtor.cpp, an unfolded vf0(0) +
// free shape the ZH inline `delete m_Ftp` does not compile to), and this TU's
// select-any copy came first in link order. The class below is the ZH
// WWDownload/download.h declaration verbatim except that the destructor is
// declared only; its guard makes the later transitive include a no-op.
#pragma optimize("ty", on)
#include "WWDownload/ftp.h"
#include "WWDownload/downloaddefs.h"
#define __DOWNLOAD_H_

class IDownload
{
 public:
	virtual HRESULT OnError( int error )=0;
	virtual HRESULT OnEnd()=0;
	virtual HRESULT OnQueryResume()=0;
	virtual HRESULT OnProgressUpdate(int bytesread, int totalsize, int timetaken, int timeleft)=0;
	virtual HRESULT OnStatusUpdate(int status)=0;
};

class CDownload
{
public:
	CDownload(IDownload *listener) :
		Listener(listener)
	{
		m_Status			= DOWNLOADSTATUS_NONE;
		m_TimeStarted		= 0;
		m_StartPosition		= 0;
		m_FileSize			= 0;
		m_BytesRead			= 0;
		m_Server[ 0 ]		= '\0';
		m_Login[ 0 ]		= '\0';
		m_Password[ 0 ]		= '\0';
		m_File[ 0 ]			= '\0';
		m_LocalFile[ 0 ]	= '\0';
		m_RegKey[ 0 ]		= '\0';
		m_Ftp				= new( Cftp );
		m_TryResume = false;

		m_predictions = 0;
		for (int i=0; i<8; ++i)
		{
			m_predictionTimes[i] = 0;
		}
	}
	~CDownload();

public:
	virtual HRESULT PumpMessages();
	virtual HRESULT Abort();
	virtual HRESULT DownloadFile(LPCSTR server, LPCSTR username, LPCSTR password, LPCSTR file, LPCSTR localfile, LPCSTR regkey, bool tryresume=true);
	virtual HRESULT GetLastLocalFile(char *local_file, int maxlen);

private:
	char m_Server[ 256 ];
	char m_Login[ 64 ];
	char m_Password[ 64 ];
	char m_File[ 256 ];
	char m_LocalFile[ 256 ];

	char m_LastLocalFile[ 256 ];

	char m_RegKey[ 256 ];
	int  m_Status;
	int  m_TimeStarted;
	int  m_StartPosition;
	int  m_FileSize;
	int  m_BytesRead;
	bool m_TryResume;

	int m_predictions;
	int m_predictionTimes[8];

	Cftp			*m_Ftp;
	IDownload	*Listener;
};
#pragma optimize("", on)

#include "GameClient/GameText.h"
#include "GameNetwork/DownloadManager.h"
// bfme link decl-only begin
namespace _STL { template <> _List_iterator<QueuedDownload, _Nonconst_traits<QueuedDownload> > list<QueuedDownload, allocator<QueuedDownload> >::insert(_List_iterator<QueuedDownload, _Nonconst_traits<QueuedDownload> >, QueuedDownload const &); }
// bfme link decl-only end

DownloadManager *TheDownloadManager;

DownloadManager::DownloadManager()
{
	m_download = NEW CDownload(this);
	m_wasError = m_sawEnd = false;
	
	//Added By Sadullah Nader
	//Initializations missing and needed
	
	m_queuedDownloads.clear();
	
	//

	// Zero Hour's inline UnicodeString::operator= calls UnicodeString::set;
	// retail's body is StringBase<unsigned short>::set 0x00037150, called here.
	((StringBase<WideChar> &)m_statusString).set(*(const StringBase<WideChar> *)&TheGameText->fetch("FTP:StatusIdle"));

	// ----- Initialize Winsock -----
	m_winsockInit = true;
	WORD verReq = MAKEWORD(2, 2);
	WSADATA wsadata;

	int err = WSAStartup(verReq, &wsadata);
	if (err != 0)
	{
		m_winsockInit = false;
	}
	else
	{
		if ((LOBYTE(wsadata.wVersion) != 2) || (HIBYTE(wsadata.wVersion) !=2))
		{
			WSACleanup();
			m_winsockInit = false;
		}
	}

}

DownloadManager::~DownloadManager()
{
	delete m_download;
	if (m_winsockInit)
	{
		WSACleanup();
		m_winsockInit = false;
	}
}

// ?init@DownloadManager@@ present-unmatched
void DownloadManager::init( void )
{
}

// ?reset@DownloadManager@@ present-unmatched
void DownloadManager::reset( void )
{
}

// DownloadManager::update is defined and rowed in DownloadManagerOnStatusUpdate.cpp.
// Shared declaration and the CDownload pointer contract are unchanged.

HRESULT DownloadManager::downloadFile( AsciiString server, AsciiString username, AsciiString password, AsciiString file, AsciiString localfile, AsciiString regkey, Bool tryResume )
{
	return m_download->DownloadFile( server.str(), username.str(), password.str(), file.str(), localfile.str(), regkey.str(), tryResume );
}

void DownloadManager::queueFileForDownload( AsciiString server, AsciiString username, AsciiString password, AsciiString file, AsciiString localfile, AsciiString regkey, Bool tryResume )
{
	QueuedDownload q;
	q.file = file;
	q.localFile = localfile;
	q.password = password;
	q.regKey = regkey;
	q.server = server;
	q.tryResume = tryResume;
	q.userName = username;

	m_queuedDownloads.push_back(q);
}

HRESULT DownloadManager::downloadNextQueuedFile( void )
{
	QueuedDownload q;
	std::list<QueuedDownload>::iterator it = m_queuedDownloads.begin();
	if (it != m_queuedDownloads.end())
	{
		q = *it;
		m_queuedDownloads.pop_front();
		m_wasError = m_sawEnd = false;
		return downloadFile( q.server, q.userName, q.password, q.file, q.localFile, q.regKey, q.tryResume );
	}
	else
	{
		DEBUG_CRASH(("Starting non-existent download!"));
		return S_OK;
	}
}

AsciiString DownloadManager::getLastLocalFile( void )
{
	char buf[256] = "";
	m_download->GetLastLocalFile(buf, 256);
	return buf;
}

// DownloadManager::OnError: defined in DownloadManagerOnStatusUpdate.cpp (its row's unit).

HRESULT DownloadManager::OnEnd()
{
	m_sawEnd = true;
	DEBUG_LOG(("DownloadManager::OnEnd()\n"));
	return S_OK;
}

HRESULT DownloadManager::OnQueryResume()
{
	DEBUG_LOG(("DownloadManager::OnQueryResume()\n"));
	//return DOWNLOADEVENT_DONOTRESUME;
	return DOWNLOADEVENT_RESUME;
}

HRESULT DownloadManager::OnProgressUpdate( Int bytesread, Int totalsize, Int timetaken, Int timeleft )
{
	DEBUG_LOG(("DownloadManager::OnProgressUpdate(): %d/%d %d/%d\n", bytesread, totalsize, timetaken, timeleft));
	return S_OK;
}

// DownloadManager::OnStatusUpdate: defined in DownloadManagerOnStatusUpdate.cpp (its row's unit).
