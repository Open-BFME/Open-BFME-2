// cl: /MD
// ?rva004A7E43@Rva004A7D55@@UAEXXZ 0x004A7E43 36B virtual slot 5 (offset 0x14) of vtable 0x00853790
// class of ??1Rva004A7D55@@UAE@XZ in Rva0058A0F4Derived.cpp. Broadcasts via rowed
// ?Rva0027164EBroadcast@Rva002716Holder@@QAEXHH@Z (0x0027164E) using BuildListInfo::getDesiredGatherers
// (0x005508E2) as Holder*. Honest address name: class plus slot proven via vtable; method identity unproven.
class BuildListInfo { public: int getDesiredGatherers(); };
struct Rva002716Holder { void Rva0027164EBroadcast(int a, int b); };
struct Rva004A7E43Aux { unsigned char m_pad[0x10]; int m_10; };
class Rva004A7D55 {
public:
  virtual void s0();
  virtual void s1();
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void rva004A7E43();
private:
  Rva004A7E43Aux* m_04;
  BuildListInfo* m_08;
  unsigned char m_pad0C[0x88 - 0x0C];
  int m_88;
};
void Rva004A7D55::rva004A7E43()
{
  Rva002716Holder* h = (Rva002716Holder*)m_08->getDesiredGatherers();
  if (!h) return;
  h->Rva0027164EBroadcast(m_04->m_10, m_88);
}
