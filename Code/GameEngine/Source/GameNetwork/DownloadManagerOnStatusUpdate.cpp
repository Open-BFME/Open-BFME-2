// cl: /O1 /EHsc
// stlport
//
// Retail 0x005E06E5 (312B): DownloadManager::OnStatusUpdate.
//
// Shard: the served DownloadManager.cpp is a ZH-verbatim port that already
// carries the rowed CDownload ctor, so the BFME2-diverged transcription lives
// here. Retail proves the divergences against the ZH donor:
// - the nine FTP:Status* literals are pushed directly (no GameText fetch for
//   the label; the fetch takes the built AsciiString instead),
// - the DOWNLOADSTATUS enum is the WWDownload downloaddefs.h one (DONE=0,
//   GO=1, CONNECTING=2 .. FINISHING=8), which is exactly the retail jump
//   table (index 0 -> Done, 1 -> default, 2..8 -> Connecting..Finishing),
// - GameTextInterface::fetch(AsciiString) lives at slot 0x38 (the const-char
//   overload other TUs prove at 0x3C sits next), takes the string by const
//   reference (retail pushes &s with no copy-ctor call) and returns the
//   UnicodeString through the hidden pointer, which the compiler parks in the
//   dead status-arg slot [ebp+8],
// - m_statusString (UnicodeString) sits at +0x14,
// - no DEBUG_LOG emission (retail has no extra calls; /DNDEBUG would drop it
//   anyway, so the lines are omitted rather than macro-guarded).
// All string-operand callees resolve to existing rows/pins (StringBase
// char ctor 0x37BA0, StringBase char set 0x55F5, StringBase wchar set
// 0x37150, wide releaseBuffer 0x36E70, AsciiString dtor 0x36410).

typedef unsigned short wchar_t;
typedef long HRESULT;
#define S_OK 0

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase(const T *s);
	StringBase(const StringBase<T> &that);
	void releaseBuffer();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;

public:
	void set(const T *s);
	void set(const StringBase<T> &that);
};

class AsciiString
{
public:
	AsciiString(const char *s) : m_data(s) {}
	~AsciiString();
	AsciiString &operator=(const char *s)
	{
		m_data.set(s);
		return *this;
	}

private:
	StringBase<char> m_data;
};

class UnicodeString
{
public:
	UnicodeString &operator=(const UnicodeString &that)
	{
		m_data.set(that.m_data);
		return *this;
	}
	~UnicodeString()
	{
		m_data.releaseBuffer();
	}

private:
	StringBase<wchar_t> m_data;
};

// Retail fetch calls through vtable slot 0x38. The thirteen preceding
// non-destructor methods have not been reconstructed in this TU; the
// const-char overload proven at 0x3C by VersionUnicode.cpp is declared FIRST
// because MSVC7.1 assigns same-name overloaded virtuals in REVERSE
// declaration order (operator== precedent) -- this order puts the AsciiString
// overload at 0x38 and the const-char one at 0x3C, both honest.
class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

enum DownloadStatus
{
	DOWNLOADSTATUS_NONE = 0,
	DOWNLOADSTATUS_GO = 1,
	DOWNLOADSTATUS_CONNECTING = 2,
	DOWNLOADSTATUS_LOGGINGIN = 3,
	DOWNLOADSTATUS_FINDINGFILE = 4,
	DOWNLOADSTATUS_QUERYINGRESUME = 5,
	DOWNLOADSTATUS_DOWNLOADING = 6,
	DOWNLOADSTATUS_DISCONNECTING = 7,
	DOWNLOADSTATUS_FINISHING = 8,
	DOWNLOADSTATUS_DONE = 0
};

enum DownloadEvent
{
	DOWNLOADEVENT_NOSUCHSERVER = 1,
	DOWNLOADEVENT_COULDNOTCONNECT = 2,
	DOWNLOADEVENT_LOGINFAILED = 3,
	DOWNLOADEVENT_NOSUCHFILE = 4,
	DOWNLOADEVENT_LOCALFILEOPENFAILED = 5,
	DOWNLOADEVENT_TCPERROR = 6,
	DOWNLOADEVENT_DISCONNECTERROR = 7
};

class DownloadManager
{
public:
	virtual HRESULT OnStatusUpdate(int status);
	virtual HRESULT OnError(int error);

private:
	unsigned char m_unknown00[8];
	bool m_wasError; // +0x0C
	unsigned char m_unknown0D[3];
	UnicodeString m_errorString; // +0x10
	UnicodeString m_statusString; // +0x14
};

// ?OnStatusUpdate@DownloadManager@@UAEJH@Z
HRESULT DownloadManager::OnStatusUpdate(int status)
{
	AsciiString s = "FTP:StatusNone";
	switch (status)
	{
		case DOWNLOADSTATUS_CONNECTING:
			s = "FTP:StatusConnecting";
			break;
		case DOWNLOADSTATUS_LOGGINGIN:
			s = "FTP:StatusLoggingIn";
			break;
		case DOWNLOADSTATUS_FINDINGFILE:
			s = "FTP:StatusFindingFile";
			break;
		case DOWNLOADSTATUS_QUERYINGRESUME:
			s = "FTP:StatusQueryingResume";
			break;
		case DOWNLOADSTATUS_DOWNLOADING:
			s = "FTP:StatusDownloading";
			break;
		case DOWNLOADSTATUS_DISCONNECTING:
			s = "FTP:StatusDisconnecting";
			break;
		case DOWNLOADSTATUS_FINISHING:
			s = "FTP:StatusFinishing";
			break;
		case DOWNLOADSTATUS_DONE:
			s = "FTP:StatusDone";
			break;
	}
	m_statusString = TheGameText->fetch(s);
	return S_OK;
}

// ?OnError@DownloadManager@@UAEJH@Z
// Retail 0x005E0628 (187B): same fetch idiom over m_errorString at +0x10
// with the m_wasError byte at +0x0C. The DOWNLOADEVENT enum
// (NOSUCHSERVER=1 .. DISCONNECTERROR=7) compiles to a dec/je chain, and the
// m_wasError store rides between the AsciiString call setup (push+lea hoist
// above the mem store) and its call. No DEBUG_LOG emission in retail.
HRESULT DownloadManager::OnError(int error)
{
	m_wasError = true;
	AsciiString s = "FTP:UnknownError";
	switch (error)
	{
		case DOWNLOADEVENT_NOSUCHSERVER:
			s = "FTP:NoSuchServer";
			break;
		case DOWNLOADEVENT_COULDNOTCONNECT:
			s = "FTP:CouldNotConnect";
			break;
		case DOWNLOADEVENT_LOGINFAILED:
			s = "FTP:LoginFailed";
			break;
		case DOWNLOADEVENT_NOSUCHFILE:
			s = "FTP:NoSuchFile";
			break;
		case DOWNLOADEVENT_LOCALFILEOPENFAILED:
			s = "FTP:LocalFileOpenFailed";
			break;
		case DOWNLOADEVENT_TCPERROR:
			s = "FTP:TCPError";
			break;
		case DOWNLOADEVENT_DISCONNECTERROR:
			s = "FTP:DisconnectError";
			break;
	}
	m_errorString = TheGameText->fetch(s);
	return S_OK;
}
