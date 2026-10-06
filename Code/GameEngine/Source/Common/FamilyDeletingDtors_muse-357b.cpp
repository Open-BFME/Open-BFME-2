// cl: /MD
// ??_GCDownload@@QAEPAXI@Z @0x005E046F 28B: deleting dtor calls the rowed
// ??1CDownload@@QAE@XZ at 0x006C9730 then rowed operator delete 0x0002FD60
// on flag; chain-unlocked by the CDownload dtor landing.
// ??_GDownloadManager@@UAEPAXI@Z @0x005E0AF3 28B: slot 5 of vtable 0x00877944;
// calls the rowed ??1DownloadManager@@UAE@XZ at 0x005E0994 then rowed operator
// delete 0x0002FD60 on flag.
class CDownload
{
public:
	~CDownload();
};

void CDownload_Delete(CDownload *p) { delete p; }

class DownloadManager
{
public:
	__declspec(noinline) virtual ~DownloadManager();
private:
	int m_famgen;
};

DownloadManager::~DownloadManager() { m_famgen = 0; }
void DownloadManager_Delete(DownloadManager *p) { delete p; }
