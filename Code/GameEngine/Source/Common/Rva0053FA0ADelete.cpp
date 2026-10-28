// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
//
// ?destroy@Rva0053FA0A@@QAEXXZ @ 0x0053FA0A 40B
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
#include <new>
class Rva0053FA0A {
public:
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void *v6(int);
  void destroy();
  void release();
  void setName(const AsciiString &name);
  void rva0053FA74(int value);
  void rva0053FA96(int value);
private:
  Rva0053F9ECList m_list04;
  int m_ref14;
  AsciiString m_name18;
  int m_1c;
  int m_20;
};
// Listener view for the slot 0 and slot 1 vcall thunks (0x001FF3A9 and
// 0x005CB260) the two setters below pass to forEach.
class Rva0053FA74Listener {
public:
  virtual void slot0(void *);
  virtual void slot1(void *);
};
void Rva0053FA0A::destroy()
{
  m_list04.forEach(reinterpret_cast<void (Rva0053F9ECListener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::updateAnimateWindow), this);
  void *p = 0;
  if (this != 0) {
    p = this->v6(0);
  }
  ::operator delete(p);
}
void Rva0053FA0A::release()
{
  --m_ref14;
  if (m_ref14 > 0) {
    return;
  }
  destroy();
}
void Rva0053FA0A::setName(const AsciiString &name)
{
  if (((const StringBase<char> &)name).compare((const StringBase<char> &)m_name18) != 0) {
    ((StringBase<char> &)m_name18).set((const StringBase<char> &)name);
    m_list04.forEach(reinterpret_cast<void (Rva0053F9ECListener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow), this);
  }
}

// 0x0053FA74 (34B) and 0x0053FA96 (33B), after rva0053FA41: guarded int
// setters for +0x1C (values from 1) and +0x20 (values from 0) that store a
// changed value and broadcast slot 1 / slot 0 to the listener list.
void Rva0053FA0A::rva0053FA74(int value)
{
  if (value < 1 || value == m_1c)
    return;
  m_1c = value;
  m_list04.forEach(reinterpret_cast<void (Rva0053F9ECListener::*)(void *)>(&Rva0053FA74Listener::slot1), this);
}
void Rva0053FA0A::rva0053FA96(int value)
{
  if (value < 0 || value == m_20)
    return;
  m_20 = value;
  m_list04.forEach(reinterpret_cast<void (Rva0053F9ECListener::*)(void *)>(&Rva0053FA74Listener::slot0), this);
}
