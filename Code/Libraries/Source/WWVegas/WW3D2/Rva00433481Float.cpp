// cl: /MD
// ?rva00433481@Rva00433481@@QAEXM@Z @0x00433481 23B: or dword [ecx+0xC4],0x20 then call rowed Rva001D972BFloatField::set 0x001D972B; caller 0x00433A13
class Rva001D972BFloatField
{
public:
  void set(float v);
};
class Rva00433481
{
public:
  void rva00433481(float v);
private:
  char _pad[0xC4];
  int m_flags;
};
void Rva00433481::rva00433481(float v)
{
  m_flags |= 0x20;
  ((Rva001D972BFloatField *)this)->Rva001D972BFloatField::set(v);
}
