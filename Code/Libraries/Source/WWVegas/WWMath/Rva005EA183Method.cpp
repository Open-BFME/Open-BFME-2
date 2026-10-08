// cl: /DNDEBUG /MD /EHs-c-
// ?rva005EA183@Rva005EA183@@QAEXXZ @0x005EA183 46B thiscall new-Link Set tail-slot1 caller 0x005EA5BD
// new AABTreeLinkClass(this as system) Set via rowed Rva00575674 tail virtual slot1 on holder ptr
class AABTreeCullSystemClass;
class AABTreeLinkClass
{
public:
  AABTreeLinkClass(AABTreeCullSystemClass *sys);
  char m_pad[0x10];
};
class Object
{
public:
  virtual void f0();
  virtual void f1();
  virtual void f2();
};
class Rva00575674
{
public:
  void rva00575674(Object *p);
  Object *m_ptr;
};
class Rva005EA183
{
public:
  void rva005EA183();
  void rva005EA0F6();
  void rva005EA125();
  void rva005EA5BD();
private:
  char m_pad[0x14];
  Rva00575674 m_holder;
};
void Rva005EA183::rva005EA183()
{
  AABTreeLinkClass *link = new AABTreeLinkClass((AABTreeCullSystemClass *)this);
  m_holder.rva00575674((Object *)link);
  return m_holder.m_ptr->f1();
}
// ?rva005EA5BD@Rva005EA183@@QAEXXZ @0x005EA5BD 17B chain calls 0x005EA183 tail slot2 callers 0x005EAD00 0x005EAE75
void Rva005EA183::rva005EA5BD()
{
  rva005EA183();
  return m_holder.m_ptr->f2();
}
// ?rva005EA125@Rva005EA183@@QAEXXZ @0x005EA125 17B tail slot2 after callee 0x005EA0F6
void Rva005EA183::rva005EA125()
{
  rva005EA0F6();
  return m_holder.m_ptr->f2();
}
