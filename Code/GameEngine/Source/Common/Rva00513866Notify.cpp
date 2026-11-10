// cl: /O1 /G7 /MD /EHsc
// Native513866..513888 complete34B body uses no input arguments. Target
// data row identifies AptCreateAHero::s_instance at RVA A048D4; only its
// presence is tested. MessageStream slot18 receives29, then existing Apt
// enable owner222479 is tail-called through the canonical Apt manager global.
// The original method name and containing-class ownership are unresolved.
#include "../../Include/Common/AptCreateAHero.h"
class GameMessage;
#include "../../Include/Common/MessageStream.h"
extern MessageStream *TheMessageStream;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#include "../../Include/Common/Rva00222479ByteOneSetter.h"
void Rva00513866(){if(AptCreateAHero::s_instance){TheMessageStream->appendMessage(29);((Rva00222479ByteOneSetter*)g_bfmeAptWindowManager)->enable();}}
