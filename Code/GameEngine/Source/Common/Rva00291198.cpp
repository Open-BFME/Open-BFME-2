// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Native2910B7..291198225B RET4 fills an output record. WBCE2CF0 confirms
// the RespawnUpdate template-name override plus tracker and mask copies.
// The existing291198 wrapper names this accessed Object view; preserve its
// address-derived provider name and output ABI. Original method names and
// complete record semantics remain unresolved; no donor identity is asserted.
#include "ascii_string.h"
enum NameKeyType { NAMEKEY_UNKNOWN=0 };
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
class Object {friend class Rva00291198Host;protected:Module *findModule(NameKeyType) const;};
class RespawnUpdate {public:void *rva004AF25D();};
class Rva001EAFC1 {
public:
 Rva001EAFC1 &operator=(const Rva001EAFC1&);
 int a,b,c;
 StringBase<unsigned short> unicode;
 AsciiString ascii;
 unsigned char flag;
};
struct SnapshotMask2910B7 {unsigned int words[32];};
struct Rva00291198Dest {
 unsigned int unknown00;
 AsciiString templateName;
 int tracker10;
 int tracker24;
 SnapshotMask2910B7 mask;
 unsigned int hasOther;
 Rva001EAFC1 other;
 unsigned char unknownAC[0xC0-0xAC];
 int m_C0;
};
struct SnapshotTemplate2910B7 {
 unsigned char unknown00[0x64];
 AsciiString name;
 unsigned char unknown68[0x113-0x68];
 unsigned char flag113;
};
struct SnapshotTracker2910B7 {
 unsigned char unknown00[0x10];
 int value10;
 unsigned char unknown14[0x24-0x14];
 int value24;
};
class Rva00291198Host {
public:
 void rva00291198(Rva00291198Dest*);
 void rva002910B7(Rva00291198Dest*);
private:
 unsigned char unknown00[4];
 SnapshotTemplate2910B7 *m_template;
 unsigned char unknown08[0x264-8];
 SnapshotTracker2910B7 *m_tracker;
 unsigned char unknown268[0x284-0x268];
 SnapshotMask2910B7 m_mask;
 unsigned char unknown304[0x460-0x304];
 int m_460;
 unsigned char unknown464[4];
 Rva001EAFC1 m_other;
};
// ?rva00291198@Rva00291198Host@@QAEXPAURva00291198Dest@@@Z
void Rva00291198Host::rva00291198(Rva00291198Dest *d)
{
 rva002910B7(d);
 d->m_C0=m_460;
}
// ?rva002910B7@Rva00291198Host@@QAEXPAURva00291198Dest@@@Z
void Rva00291198Host::rva002910B7(Rva00291198Dest *destination)
{
 SnapshotTracker2910B7 *tracker=m_tracker;
 if (m_template->flag113 & 4) {
  static const NameKeyType respawnKey=TheNameKeyGenerator->nameToKey("RespawnUpdate");
  RespawnUpdate *respawn=reinterpret_cast<RespawnUpdate*>(reinterpret_cast<const Object*>(this)->findModule(respawnKey));
  if (respawn) {
   SnapshotTemplate2910B7 *respawnTemplate=reinterpret_cast<SnapshotTemplate2910B7*>(respawn->rva004AF25D());
   if (respawnTemplate) destination->templateName.set(respawnTemplate->name);
  }
 }
 if (destination->templateName.isEmpty()) destination->templateName.set(m_template->name);
 destination->tracker10=tracker->value10;
 destination->tracker24=tracker->value24;
 destination->mask=m_mask;
 destination->hasOther=true;
 destination->other=m_other;
}
