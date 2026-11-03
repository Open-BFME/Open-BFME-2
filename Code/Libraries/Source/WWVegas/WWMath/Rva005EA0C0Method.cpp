// cl: /DNDEBUG /MD /EHs-c-
// ?rva005EA0C0@Rva005EA183@@QAEXXZ @0x005EA0C0 47B new-8 link Set tail-slot1 vtable g_00C78174 callers jmp 0x005EA260 0x005EA44A
// new Rva005EA0C0Link(this as system) Set via rowed Rva00575674 tail virtual slot1 on holder ptr
class AABTreeCullSystemClass;
class Object
{
public:
  virtual void f0();
  virtual void f1();
  virtual void f2();
};
#include "../../../../GameEngine/Include/Common/Rva00575674.h"
class Rva005EA183
{
public:
  void rva005EA183();
  void rva005EA5BD();
  void rva005EA0C0();
private:
  char m_pad[0x14];
  Rva00575674 m_holder;
};
extern "C" const void *const __identifier("??_7Rva005EA026@@6B@")[];
struct Rva005EA0C0Link
{
  const void *m_vptr;
  void *m_sys;
  Rva005EA0C0Link(void *system, const void *vt)
  {
    m_sys = system;
    m_vptr = vt;
  }
};
void Rva005EA183::rva005EA0C0()
{
  Rva005EA0C0Link *link = new Rva005EA0C0Link(this, (const void *)__identifier("??_7Rva005EA026@@6B@"));
  m_holder.rva00575674((Object *)link);
  return m_holder.m_ptr->f1();
}
