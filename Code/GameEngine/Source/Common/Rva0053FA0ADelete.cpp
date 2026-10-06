// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
//
// ?rva0053FA0A@Rva0053FA0A@@QAEXXZ @ 0x0053FA0A 40B
// Evidence: forEach row 0x0053F9EC plus slot-3 update dispatch at 0x005CB265;
// virtual slot 6 plus operator delete row 0x0002FD60; Release 0x0053FA32
// uses refcount +0x14; list +4 per Rva0053F97FListenerWalks.
class Rva0053F9ECListener {
public:
  virtual void notify(void *);
};
class Rva0053F9ECList {
public:
  void forEach(void (Rva0053F9ECListener::*notify)(void *), void *arg);
private:
  Rva0053F9ECListener **m_begin;
  Rva0053F9ECListener **m_end;
  Rva0053F9ECListener **m_capacity;
  unsigned int m_index;
};
class AnimateWindow;
class ProcessAnimateWindowSlideFromBottomTimed {
public:
  virtual ~ProcessAnimateWindowSlideFromBottomTimed();
  virtual void initAnimateWindow(AnimateWindow *);
  virtual void initReverseAnimateWindow(AnimateWindow *, unsigned int);
  virtual bool updateAnimateWindow(AnimateWindow *);
  virtual bool reverseAnimateWindow(AnimateWindow *);
};
void operator delete(void *p);
class Rva0053FA0A {
public:
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void *v6(int);
  void rva0053FA0A();
  void rva0053FA32();
  void rva0053FA41(const AsciiString &name);
private:
  Rva0053F9ECList m_list04;
  int m_ref14;
  AsciiString m_name18;
};
void Rva0053FA0A::rva0053FA0A()
{
  m_list04.forEach(reinterpret_cast<void (Rva0053F9ECListener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::updateAnimateWindow), this);
  void *p = 0;
  if (this != 0) {
    p = this->v6(0);
  }
  ::operator delete(p);
}
void Rva0053FA0A::rva0053FA32()
{
  --m_ref14;
  if (m_ref14 > 0) {
    return;
  }
  rva0053FA0A();
}
void Rva0053FA0A::rva0053FA41(const AsciiString &name)
{
  if (((const StringBase<char> &)name).compare((const StringBase<char> &)m_name18) != 0) {
    ((StringBase<char> &)m_name18).set((const StringBase<char> &)name);
    m_list04.forEach(reinterpret_cast<void (Rva0053F9ECListener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow), this);
  }
}
