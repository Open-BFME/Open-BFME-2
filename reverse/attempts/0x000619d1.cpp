// ?rva000619D1@MilesAudioManager@@QAE_N_N@Z
// partial score=0.96 date=2026-10-08
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD
#include "ascii_string.h"

class MilesMutexGuard {
public:
    MilesMutexGuard(void *, int);
    ~MilesMutexGuard();
private:
    void *mutex;
    bool held;
};
class MilesAudioManager {
public:
    bool rva000619D1(bool enabled);
    void rva000606CE(bool accelerated);
private:
    char unknown00[0x6CC];
    struct ProviderInfo { AsciiString name; void *id; int isValid; };
    ProviderInfo m_provider3D[64];
    unsigned int m_providerCount;
    unsigned int m_selectedProvider;
    void *m_mutex;
};
bool MilesAudioManager::rva000619D1(bool enabled)
{
    MilesMutexGuard guard(&m_mutex, 0);
    bool requested = enabled;
    if (m_selectedProvider != (unsigned int)-1) {
        int comparison = m_provider3D[m_selectedProvider].name.compare("Creative Labs EAX 3 (TM)");
        if (comparison == 0) {
            if (requested) return true;
        } else if (!requested) return true;
    }
    rva000606CE(requested);
    if (m_selectedProvider != (unsigned int)-1)
        requested = requested == bool(m_provider3D[m_selectedProvider].name.compare("Creative Labs EAX 3 (TM)") == 0);
    else
        requested = false;
    return requested;
}
