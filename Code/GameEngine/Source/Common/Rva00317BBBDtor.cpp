// cl: /EHsc
// ??1Rva00317BBB@@UAE@XZ @0x00317BBB 93B: virtual dtor draining the intrusive list at +0xC node by node through virtual slot 0 with arg 0 plus global operator delete, then base 0x001B4E74. Evidence: vtable 0x0080C62C store plus deleting-dtor caller 0x00317C18 plus rowed operator delete 0x0002FD60; node slot-0 identity unproven so TU-local ListNode facade.
class AsciiStringMember {
public:
  ~AsciiStringMember();
};
class GameEngineDeletingBase {
public:
  virtual ~GameEngineDeletingBase();
private:
  char m_pad04[4];
  AsciiStringMember m_member08;
};
struct ListNode {
  virtual void *destroy(int flags);
  char m_pad04[0x1C];
  ListNode *m_next;
};
class Rva00317BBB : public GameEngineDeletingBase {
public:
  virtual ~Rva00317BBB();
private:
  ListNode *m_head;
};
void __cdecl operator delete(void *p);
Rva00317BBB::~Rva00317BBB()
{
  if (m_head != 0) {
    ListNode *next;
    do {
      ListNode *p = m_head;
      next = p->m_next;
      void *mem;
      if (m_head != 0)
        mem = p->destroy(0);
      else
        mem = 0;
      ::operator delete(mem);
      m_head = next;
    } while (next != 0);
  }
}
