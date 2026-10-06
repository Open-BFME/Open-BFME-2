// cl: /MD
// ?rva004A6E8E@Rva004A6EHolder@@QAE_NXZ 0x004A6E8E 56B and ?rva004A6EC6@Rva004A6EHolder@@QAE_NH@Z 0x004A6EC6 68B
// Two bool helpers sharing the rowed broadcast ?Rva0027164EBroadcast (0x0027164E) via BuildListInfo::getDesiredGatherers.
// this is interior (Module at Object+0x3E0): [esi-0x3E0]=obj+0 (Aux with +0x64), [esi-0x3DC]=obj+4 (BuildListInfo), [esi+0x1C]=counter.
// Honest address names; class identity unproven.
class BuildListInfo { public: int getDesiredGatherers(); };
struct Rva002716Holder { void Rva0027164EBroadcast(int a, int b); };
struct Rva004A6EAux { unsigned char m_pad[0x64]; int m_64; };
struct Rva004A6EObj { Rva004A6EAux* m_00; BuildListInfo* m_04; };
class Rva004A6EHolder {
public:
  bool rva004A6E8E();
  bool rva004A6EC6(int unused);
private:
  unsigned char m_pad[0x1c];
  int m_1c;
};
bool Rva004A6EHolder::rva004A6E8E()
{
  if (m_1c == 0) return false;
  Rva004A6EObj* obj = (Rva004A6EObj*)((char*)this - 0x3e0);
  BuildListInfo* info = obj->m_04;
  --m_1c;
  Rva002716Holder* h = (Rva002716Holder*)info->getDesiredGatherers();
  if (!h) return true;
  h->Rva0027164EBroadcast(obj->m_00->m_64, m_1c);
  return true;
}
bool Rva004A6EHolder::rva004A6EC6(int unused)
{
  (void)unused;
  Rva004A6EObj* obj = (Rva004A6EObj*)((char*)this - 0x3e0);
  if (obj->m_00 && m_1c >= obj->m_00->m_64) return false;
  BuildListInfo* info6 = obj->m_04;
  ++m_1c;
  Rva002716Holder* h = (Rva002716Holder*)info6->getDesiredGatherers();
  if (!h) return true;
  h->Rva0027164EBroadcast(obj->m_00->m_64, m_1c);
  return true;
}
