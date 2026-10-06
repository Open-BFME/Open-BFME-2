// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva004CE3B9@Rva004CE3B9@@QAEABVAsciiString@@XZ retail 0x004CE3B9 64B
// First-set-upgrade name via TheUpgradeCenter mask-index walk; empty string if none.
// Evidence: 1 caller 0x004B555F tail-jmp plus rowed rva0026EEA0 0x0026EEA0 plus TheUpgradeCenter 0x009FEB60 plus TheEmptyString 0x009E0878; unlocks 1 ready.
#include "ascii_string.h"
class UpgradeTemplate {
public:
    char m_pad[8];
    AsciiString m_name;
};
class UpgradeCenter {
public:
    const UpgradeTemplate *rva0026EEA0(int key) const;
};
extern UpgradeCenter *TheUpgradeCenter;
class Rva004CE3B9 {
public:
    const AsciiString &rva004CE3B9();
private:
    unsigned int m_bits[32];
};
const AsciiString &Rva004CE3B9::rva004CE3B9()
{
    for (int i = 0; i < 0x400; ++i) {
        if (m_bits[(unsigned int)i >> 5] & (1 << (i & 31))) {
            const UpgradeTemplate *t = TheUpgradeCenter->rva0026EEA0(i);
            if (t)
                return t->m_name;
        }
    }
    return AsciiString::TheEmptyString;
}
