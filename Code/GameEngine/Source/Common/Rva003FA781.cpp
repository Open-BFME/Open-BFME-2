// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native 003FA781..003FA7D3 RET4 toggles byte +14 and resets float +18.
// Turning off also forwards +10 and the resolved template's float +14 to
// 003FA705 (64B RET8). The matched lookup caller 00210E5B
// supplies this receiver and a word argument whose low byte is tested here.
// The original owner/template names and meanings of the floats are open.
// The folded OVERRIDE getter is used only for its proven pointer-chain ABI.
#include "ascii_string.h"
class LocomotorTemplate;
class RenderObjClass;
bool Rva0010E676_SetEmissive(RenderObjClass *, float, float, float);
template<class T> class OVERRIDE
{
public:
 const T *operator->() const;
private:
public:
 OVERRIDE() : head(0) {}
 const T *head;
};
struct Rva003FA781Template { char pad[0x14]; float value; };
struct Rva00539926Base { unsigned references; Rva00539926Base() : references(0) {} virtual ~Rva00539926Base(); };
class Rva003FA835 : public Rva00539926Base
{
public:
 Rva003FA835(int kind, void *target, unsigned word);
 virtual ~Rva003FA835() {}
 void rva003FA781(int enabled);
 void rva003FA7D3(int enabled);
 void rva003FA705(void *target, float value);
private:

 OVERRIDE<LocomotorTemplate> m_template;
 unsigned m_unknown0C;
 void *m_target;
 bool m_enabled;
 char m_pad15[3];
 float m_elapsed;
 float m_unknown1C;
 float m_20;
};

void Rva003FA835::rva003FA781(int enabled)
{
 if (m_enabled && !(unsigned char)enabled)
 {
  m_enabled = false;
  m_elapsed = 0.0f;
  rva003FA705(m_target, ((const Rva003FA781Template *)m_template.operator->())->value);
 }
 else if (!m_enabled && (unsigned char)enabled)
 {
  m_enabled = true;
  m_elapsed = 0.0f;
 }
}

void Rva003FA835::rva003FA705(void *target, float value)
{
 if (value != m_unknown1C)
 {
  m_unknown1C = value;
  Rva0010E676_SetEmissive(*(RenderObjClass **)((char *)target + 8), value, value, value);
 }
}

// ?rva003FA7D3@Rva003FA835@@QAEXH@Z @0x003FA7D3 98B.
// Ghidra-missed leaf called from 00210E95: when m_20 is non-zero and the
// low byte is clear, clears m_20/m_elapsed and forwards m_target and the
// template float to rva003FA705; otherwise when disabled and the low byte
// is set, sets m_20 to 1.0 and clears m_elapsed. Evidence: prev/next in
// same TU, rowed callees OVERRIDE::operator-> and rva003FA705, literal
// 1.0f, caller 0x00210E95.
void Rva003FA835::rva003FA7D3(int enabled)
{
 if (m_20 != 0.0f && !(unsigned char)enabled)
 {
  m_20 = 0.0f;
  m_elapsed = 0.0f;
  rva003FA705(m_target, ((const Rva003FA781Template *)m_template.operator->())->value);
 }
 else if (!m_enabled && (unsigned char)enabled)
 {
  m_20 = 1.0f;
  m_elapsed = 0.0f;
 }
}

// Target 003FA9FB..003FAA9F RET12; WB 01062D30 confirms all fields and
// the six-entry template table at VA DBE980. No original class/enum identity
// is asserted. The inline zeroing counted base and its existing 7B virtual
// destructor alias supply the native EH cleanup; its +4 field is witnessed
// by the constructor, not inherited from a donor layout.
// Exact six-entry retail table; the enum names are unresolved.
const char *EmissiveTemplateNames[] = {
 "ARMY", "BATTLE_MARKER", "REGION_AWARD_DISPUTE", "CLOUD", "BUILDING", "DEFAULT"
};
class Rva00DFE1C8Host { public: int rva002122FD(const AsciiString &); };
extern Rva00DFE1C8Host *g_00DFE1C8;
Rva003FA835::Rva003FA835(int kind, void *target, unsigned word)
 : m_unknown0C(word), m_target(target), m_enabled(false), m_elapsed(0.0f), m_20(0.0f)
{
 { AsciiString name(EmissiveTemplateNames[kind]);
   m_template.head = (const LocomotorTemplate *)g_00DFE1C8->rva002122FD(name); }
 m_unknown1C = -1.0f;
 if (m_target) rva003FA705(m_target, 0.0f);
}
