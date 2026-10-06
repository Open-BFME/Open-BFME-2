// cl: /MD
// Target-owned handle/critical-section ABI views; original class names,
// abstractness and full sizes remain unknown. Three-slot tables independently
// prove virtual lock / unlock / scalar-destructor ordering. Base BC16B8 is
// {40EF8;3B810;41184}; derived BC16DC is {41004;41024;411F2}.
// Ghidra proves cleanup40EDB29 and cleanup40FE531. Vtable-selected complete
// CFG/RET4 and adjacent40F1E prove wait40EF838; CFG/RET and adjacent41037
// prove unlock4102419. PE independently names all six kernel32 imports below.
// Existing constructor411C149; enter4100432; scalars41184/411F228 retain their
// exact bytes. No historical donor identities are inferred from these names.
#include "../../Include/Common/Rva00041004Lock.h"
extern "C" {
__declspec(dllimport) int __stdcall CloseHandle(void *handle) throw();
__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long time) throw();
__declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *section) throw();
__declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *section) throw();
__declspec(dllimport) void __stdcall InitializeCriticalSection(CRITICAL_SECTION *section) throw();
__declspec(dllimport) void __stdcall DeleteCriticalSection(CRITICAL_SECTION *section) throw();
__declspec(dllimport) int __stdcall ReleaseMutex(void *handle) throw();
}
// ??1Rva0040EDB@@UAE@XZ @0x00040EDB 29B
Rva0040EDB::~Rva0040EDB()
{
    if (m_handle04) {
        CloseHandle(m_handle04);
        m_handle04 = 0;
    }
}
// ?lock@Rva0040EDB@@UAE_NH@Z @0x00040EF8 38B
bool Rva0040EDB::lock(int time) throw()
{
    if (!m_handle04)
        return false;
    switch (WaitForSingleObject(m_handle04, time)) {
    case 0:
    case 0x80:
        return true;
    default:
        return false;
    }
}
// ??1Rva00041004@@UAE@XZ @0x00040FE5 31B
Rva00041004::~Rva00041004()
{
    DeleteCriticalSection(&m_cs);
    m_flag = 1;
}
// ?unlock@Rva00041004@@UAE_NXZ @0x00041024 19B
bool Rva00041004::unlock()
{
    if (!m_flag)
        LeaveCriticalSection(&m_cs);
    return true;
}
// ?lock@Rva00041004@@UAE_NH@Z @0x00041004 32B
bool Rva00041004::lock(int time) throw()
{
    if (time != -1)
        return false;
    if (m_flag)
        return true;
    EnterCriticalSection(&m_cs);
    return true;
}
// ??0Rva00041004@@QAE@H@Z @0x000411C1 49B
// Target singleton storage spans36B; the inline base initializer zeroes +4.
Rva00041004::Rva00041004(int x) : m_flag(0)
{
    InitializeCriticalSection(&m_cs);
    if (x == 0)
        lock(-1);
}
// ?unlock@Rva000411BC@@UAE_NXZ @0x00040F4C 24B
// Table BC16C4 {40EF8;40F4C;411A0}: the base wait method, this mutex release
// and the rowed ??_GRva000411BC scalar destructor.
class Rva000411BC : public Rva0040EDB
{
public:
    virtual bool unlock();
};
bool Rva000411BC::unlock()
{
    if (m_handle04)
        return ReleaseMutex(m_handle04) != 0;
    return false;
}
