// cl: /O1 /arch:SSE /G7 /MD /EHsc
// ??1Rva005764F9@@UAE@XZ @0x005764F9 87B evidence: vtable 0x00C6E78C; calls rowed get 0x00574AA5 and rowed 0x005CC20D 0x005CD5FA and base dtor 0x005D0D85; caller deleting dtor 0x005767A7
class Rva00574AA5AddDwordField
{
public:
  int get() const;
};
class Rva005CC20D
{
public:
  void rva005CC20D(unsigned char value);
};
class Rva005CD5FA
{
public:
  void rva005CD5FA(unsigned char value);
};
class Rva005D0D85
{
public:
  virtual ~Rva005D0D85();
};
struct Rva005764F9Mid
{
  char m_pad[4];
  Rva00574AA5AddDwordField *m_04;
};
struct Rva005764F9Holder
{
  char m_pad[16];
  Rva005764F9Mid *m_10;
  char m_pad2[28];
  Rva005CD5FA m_30;
};
class Rva005764F9 : public Rva005D0D85
{
public:
  virtual ~Rva005764F9();
  char m_pad[4];
  Rva005764F9Holder *m_08;
};
Rva005764F9::~Rva005764F9()
{
  ((Rva005CC20D *)m_08->m_10->m_04->get())->rva005CC20D(1);
  m_08->m_30.rva005CD5FA(1);
}
