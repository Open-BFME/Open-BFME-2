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
class Xfer {public:

 virtual void slot00();
 virtual bool IsLoading()const;
 virtual void slot02();
 virtual bool IsCRC()const;

 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual Xfer &xferVersion(XferVersion *);

 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual Xfer &xferAsciiString(AsciiString *);
};
class Eva
{
public:
 void xferEvaEventID(Xfer *,int *);
 int rva001DE78E(const AsciiString *);
 AsciiString messageToName(int);};
extern Eva *TheEva;
void Eva::xferEvaEventID(Xfer *xfer,int *message) {
 if(xfer->IsCRC())return;
 XferVersion version;version.fields.version=1;version.fields.current=1;xfer->xferVersion(&version);
 if(xfer->IsLoading()) {
  AsciiString name;xfer->xferAsciiString(&name);
  if(!name.isEmpty())*message=TheEva->rva001DE78E(&name);else *message=-1;
 }else {
  AsciiString name;
  if(*message!=-1)name=TheEva->messageToName(*message);
  xfer->xferAsciiString(&name);
 }
}
