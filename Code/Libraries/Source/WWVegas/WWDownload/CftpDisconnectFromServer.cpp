// cl: /DNDEBUG /MD /EHs-c- /Ob2
// Cftp::DisconnectFromServer, retail 0x006CA490 (12 bytes).
// Ported from the Zero Hour reference (Libraries/Source/WWVegas/WWDownload/FTP.CPP):
// closes the command socket, returns FTP_SUCCEEDED. m_iCommandSocket sits
// at +4 (retail displacement, matching the Zero Hour layout where it is the
// first member after the vptr). closesocket rides the ILT through the
// _closesocket@4 thunk pin (plain extern, no dllimport).

typedef long HRESULT;

#define FTP_SUCCEEDED 0

extern "C" int __stdcall closesocket(int s);

class Cftp
{
public:
	HRESULT DisconnectFromServer();

private:
	int m_pad0;
	int m_iCommandSocket;
};

HRESULT Cftp::DisconnectFromServer()
{
	closesocket(m_iCommandSocket);
	return FTP_SUCCEEDED;
}
