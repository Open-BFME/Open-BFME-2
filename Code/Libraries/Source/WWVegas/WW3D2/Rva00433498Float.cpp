// cl: /MD
// ?rva00433498@Rva00433498@@QAEXM@Z @0x00433498 23B: or dword [ecx+0xC4],0x40 then call 0x00210C91 (dup of RenderObjClass::_bfme_ro_set_98 float setter); caller 0x00433A3D; row type YAXXZ is gen-alias placeholder, true use is thiscall float (object-symbol ?_bfme_ro_set_98@RenderObjClass@@UAEXM@Z)
class RenderObjClass
{
public:
  virtual void _bfme_ro_set_98(float v);
};
class Rva00433498
{
public:
  void rva00433498(float v);
private:
  char _pad[0xC4];
  int m_flags;
};
void Rva00433498::rva00433498(float v)
{
  m_flags |= 0x40;
  ((RenderObjClass *)this)->RenderObjClass::_bfme_ro_set_98(v);
}
