// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ?rva000619D1@MilesAudioManager@@QAE_N_N@Z @ 0x000619D1 172B, ret 4
//
// Asks for the EAX 3 3D provider to be on or off and reports whether the
// selected provider now agrees. Under the +0x9D4 Miles mutex: if a provider
// is selected (+0x9D0, index into the 64 twelve-byte entries at +0x6CC) and
// its name already is (or is not) "Creative Labs EAX 3 (TM)" as requested,
// true at once; otherwise the provider is reselected through 0x000606CE with
// the request, and the result is whether the newly selected provider's name
// matches it (false when none is selected).
//
// Evidence: retail body and WorldBuilder's unoptimized twin at 0x0079DA00,
// which has the same four returns. Taking a reference to the provider entry
// and naming the comparison, in both halves, gives retail's evaluation order
// and its 8-bit compare. The original method name is not established.

#include "ascii_string.h"

#include "../../Include/MilesAudioDevice/MilesMutexGuard.h"
class MilesAudioManager {
public:
    virtual bool rva000619D1(bool enabled);
    void rva000606CE(bool accelerated);
private:
    char unknown00[0x6C8];
    struct ProviderInfo { AsciiString name; void *id; int isValid; };
    ProviderInfo m_provider3D[64];
    unsigned int m_providerCount;
    unsigned int m_selectedProvider;
    void *m_mutex;
};
bool MilesAudioManager::rva000619D1(bool enabled)
{
    MilesMutexGuard guard(&m_mutex, 0);
    if (m_selectedProvider != (unsigned int)-1) {
        ProviderInfo &info = m_provider3D[m_selectedProvider];
        if (info.name.compare("Creative Labs EAX 3 (TM)") == 0) {
            if (enabled)
                return true;
        } else if (!enabled)
            return true;
    }
    rva000606CE(enabled);
    if (m_selectedProvider != (unsigned int)-1) {
        ProviderInfo &info = m_provider3D[m_selectedProvider];
        bool isEAX3 = info.name.compare("Creative Labs EAX 3 (TM)") == 0;
        return enabled == isEAX3;
    }
    return false;
}
