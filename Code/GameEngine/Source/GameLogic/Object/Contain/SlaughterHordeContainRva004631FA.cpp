// cl: /DNDEBUG /MD
// SlaughterHordeContain::rva004631FA, retail 0x004631FA (50 bytes). Built from
// the banked attempt reverse/attempts/0x004631fa.cpp; fix: the list walk
// starts at the node after the head (end = *m04, cur = *end), which is
// retail's second load.

struct Rva0046247DPair { void *m00; void *m04; };

class Rva0046247D { public: void rva0046247D(Rva0046247DPair &p); };

class SlaughterHordeContain { public:
  virtual void dslot0();
  virtual void dslot1();
  virtual void dslot2();
  virtual void dslot3();
  virtual void dslot4();
  virtual void dslot5();
  virtual void dslot6();
  virtual void dslot7();
  virtual void dslot8();
  virtual void dslot9();
  virtual void dslot10();
  virtual void dslot11();
  virtual void dslot12();
  virtual void dslot13();
  virtual void dslot14();
  virtual void dslot15();
  virtual void dslot16();
  virtual void dslot17();
  virtual void dslot18();
  virtual void dslot19();
  virtual void dslot20();
  virtual void dslot21();
  virtual void dslot22();
  virtual void dslot23();
  virtual void dslot24();
  virtual void dslot25();
  virtual void dslot26();
  virtual void dslot27();
  virtual void dslot28();
  virtual void dslot29();
  virtual void dslot30();
  virtual void dslot31();
  virtual void dslot32();
  virtual void dslot33();
  virtual void dslot34();
  virtual void dslot35();
  virtual void dslot36();
  virtual void dslot37();
  virtual void dslot38();
  virtual void dslot39();
  virtual void dslot40();
  virtual void dslot41();
  virtual void dslot42();
  virtual void dslot43();
  virtual void dslot44();
  virtual void dslot45();
  virtual void dslot46();
  virtual void dslot47();
  virtual void dslot48();
  virtual void dslot49();
  virtual void dslot50();
  virtual void dslot51();
  virtual void dslot52();
  virtual void dslot53();
  virtual void dslot54();
  virtual void dslot55();
  virtual void dslot56();
  virtual void dslot57();
  virtual void dslot58();
  virtual void dslot59();
  virtual void dslot60();
  virtual void dslot61();
  virtual void dslot62();
  virtual void dslot63();
  virtual void dslot64();
  virtual void dslot65();
  virtual void dslot66();
  virtual void dslot67();
  virtual void dslot68();
  virtual void dslot69();
  virtual void dslot70();
  virtual void dslot71();
  virtual void dslot72();
  virtual void dslot73();
  virtual void dslot74();
  virtual void dslot75();
  virtual void dslot76();
  virtual void dslot77();
  virtual void dslot78();
  virtual void dslot79();
  virtual void dslot80();
  virtual void dslot81();
  virtual void dslot82();
  virtual void dslot83();
  virtual void dslot84();
  virtual void dslot85();
  virtual void dslot86();
  virtual void dslot87();
  virtual void dslot88();
  virtual void dslot89();
  virtual void dslot90();
  virtual void dslot91();
  virtual void dslot92();
  virtual void dslot93();
  virtual void dslot94();
  virtual void dslot95();
  virtual bool rva004631FA(int arg);
};

bool SlaughterHordeContain::rva004631FA(int arg)
{
  Rva0046247DPair p;
  ((Rva0046247D *)((char *)this - 0x20))->rva0046247D(p);
  void *end = *(void * *)p.m04;
  void *cur = *(void * *)end;
  for (; cur != end; cur = *(void * *)cur) {
    if (*(int *)((char *)cur + 8) == arg)
      return true;
  }
  return false;
}
