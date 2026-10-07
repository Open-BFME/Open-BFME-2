// cl: /O1 /arch:SSE /G7 /MD
// Native 003FA781..003FA7D3 RET4 toggles byte +14 and resets float +18.
// Turning off also forwards +10 and the resolved template's float +14 to
// 003FA705 (64B RET8). The matched lookup caller 00210E5B
// supplies this receiver and a word argument whose low byte is tested here.
// The original owner/template names and meanings of the floats are open.
// The folded OVERRIDE getter is used only for its proven pointer-chain ABI.
class LocomotorTemplate;
template<class T> class OVERRIDE
{
public:
 const T *operator->() const;
private:
 const T *head;
};
struct Rva003FA781Template { char pad[0x14]; float value; };
class Rva003FA835
{
public:
 void rva003FA781(int enabled);
 void rva003FA705(void *target, float value);
private:
 char m_pad[8];
 OVERRIDE<LocomotorTemplate> m_template;
 unsigned m_unknown0C;
 void *m_target;
 bool m_enabled;
 char m_pad15[3];
 float m_elapsed;
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
