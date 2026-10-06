// cl: /O1 /arch:SSE /G7 /MD
// ?rva005CCB7B@Rva005CCB7B@@QAEX_N@Z @0x005CCB7B 8B evidence: tail-jmp to rowed 0x005CCAEC; chain from own landing; prev Rva005CCB6B next Rva005CCB83
class Rva005CCAEC
{
public:
  void rva005CCAEC(bool value);
};
class Rva005CCB7B
{
public:
  void rva005CCB7B(bool b);
  char m_lead[8];
  Rva005CCAEC *m_ptr;
};
void Rva005CCB7B::rva005CCB7B(bool b)
{
  m_ptr->rva005CCAEC(b);
}
