// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP=
// WB ACE450 names Eva::xferEvaEventID in GameClient/Eva.cpp. Complete
// native1DEC48..1DED2B returns8 and uses CRC3/version10/load1/string27.
// Loading resolves a nonempty event name through TheEva; storing translates
// every ID except -1 and transfers the resulting string. EvaMessageName.cpp
// and EvaRva001DE78E.cpp provide the verified target lookups. BF1 ba7ddda's
// Eva.cpp and ZH Eva.cpp supply message-name semantics but no transfer donor.
// The four-byte version-local view follows verified sibling Xfer recoveries;
// only the two announced version bytes are read. No new pins or aliases.
#include "ascii_string.h"
struct XferVersionBytes {unsigned char version,current;};
union XferVersion {XferVersionBytes fields;unsigned int storage;};
#include "../Common/System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"
#include "../../Include/GameClient/Eva.h"
extern Eva *TheEva;
void Eva::xferEvaEventID(Xfer *xfer,int *message) {
 if(xfer->IsCRC())return;
 XferVersion version;version.fields.version=1;version.fields.current=1;*xfer == reinterpret_cast<Xfer::Version &>(version);
 if(xfer->IsLoading()) {
  AsciiString name;*xfer == name;
  if(!name.isEmpty())*message=TheEva->rva001DE78E(&name);else *message=-1;
 }else {
  AsciiString name;
  if(*message!=-1)name=TheEva->messageToName(*message);
  *xfer == name;
 }
}
