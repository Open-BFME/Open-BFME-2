// cl: /O1 /arch:SSE /G7 /MD
// ?rva005CCB73@Rva005CCB73@@QAEXPAX@Z @0x005CCB73 8B evidence: tail-jmp to rowed 0x005CCACA; chain from own landing; callers 0x00575435 0x005CD215
class Rva005CCACA
{
public:
  void rva005CCACA(int value);
};
class Rva005CCB73
{
public:
  void rva005CCB73(void *arg);
  char m_lead[8];
  Rva005CCACA *m_ptr;
};
void Rva005CCB73::rva005CCB73(void *arg)
{
  m_ptr->rva005CCACA((int)arg);
}
