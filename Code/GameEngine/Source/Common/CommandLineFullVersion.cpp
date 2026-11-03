// cl: /DNDEBUG /MD
// EA BFME1/Zero Hour CommandLine.cpp parseFullVersion, with BFME2's
// return 2 when a value is consumed and return 1 otherwise.
// Retail command table maps -fullVersion to RVA3B9647 (complete 50B body).
// TheVersion is VA DFE770; m_showFullVersion is at +2C; atoi is an audited import.
#include <stdlib.h>
#include "../../Include/Common/VersionClass.h"
extern Version *TheVersion;
int parseFullVersion(char *args[],int num) {
    if(TheVersion && num>1) {
        TheVersion->setShowFullVersion(atoi(args[1])!=0);
        return 2;
    }
    return 1;
}
