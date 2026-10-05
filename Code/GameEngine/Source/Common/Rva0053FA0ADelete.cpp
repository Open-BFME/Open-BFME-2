// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva0053FA0A@Rva0053FA0A@@QAEXXZ @ 0x0053FA0A 40B
// Evidence: forEach row 0x0053F9EC plus reverseAnimateWindow row 0x005CB265; virtual slot 6 plus operator delete row 0x0002FD60; unblocks Release 0x0053FA32 with refcount at +0x14; list at +4 per Rva0053F97FListenerWalks.
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
private:
  Rva0053F9ECList m_list04;
  int m_ref14;
};
void Rva0053FA0A::rva0053FA0A()
{
  m_list04.forEach(reinterpret_cast<void (Rva0053F9ECListener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow), this);
  void *p = 0;
  if (this != 0) {
    p = this->v6(0);
  }
  ::operator delete(p);
}
