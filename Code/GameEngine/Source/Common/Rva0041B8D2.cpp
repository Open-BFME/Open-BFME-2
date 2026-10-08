// cl: /MD
// ABI repair: retail 29C823 and named WB DBA3A0 dispatch through TheActionManager.
// The unused manager this is still part of the calling convention. Existing
// return representations are preserved. No additional name or pin is introduced.
// ?Rva0041B8D2Check@ActionManager@@QAEEPAVRva0041B8D2Obj@@0H@Z @0x0041B8D2 70B
// Evidence: caller 0x0029C8B9 in 0x0029C823; unblocks 0x0029C823; offsets +4/+0x5ec/+0x258; virtual slots +0x178/+0x18.
struct Rva0041B8D2Inner { char pad[0x5ec]; unsigned char flag; };
struct Rva0041B8D2Holder {
 virtual void d00();
 virtual void d01();
 virtual void d02();
 virtual void d03();
 virtual void d04();
 virtual void d05();
 virtual void d06();
 virtual void d07();
 virtual void d08();
 virtual void d09();
 virtual void d10();
 virtual void d11();
 virtual void d12();
 virtual void d13();
 virtual void d14();
 virtual void d15();
 virtual void d16();
 virtual void d17();
 virtual void d18();
 virtual void d19();
 virtual void d20();
 virtual void d21();
 virtual void d22();
 virtual void d23();
 virtual void d24();
 virtual void d25();
 virtual void d26();
 virtual void d27();
 virtual void d28();
 virtual void d29();
 virtual void d30();
 virtual void d31();
 virtual void d32();
 virtual void d33();
 virtual void d34();
 virtual void d35();
 virtual void d36();
 virtual void d37();
 virtual void d38();
 virtual void d39();
 virtual void d40();
 virtual void d41();
 virtual void d42();
 virtual void d43();
 virtual void d44();
 virtual void d45();
 virtual void d46();
 virtual void d47();
 virtual void d48();
 virtual void d49();
 virtual void d50();
 virtual void d51();
 virtual void d52();
 virtual void d53();
 virtual void d54();
 virtual void d55();
 virtual void d56();
 virtual void d57();
 virtual void d58();
 virtual void d59();
 virtual void d60();
 virtual void d61();
 virtual void d62();
 virtual void d63();
 virtual void d64();
 virtual void d65();
 virtual void d66();
 virtual void d67();
 virtual void d68();
 virtual void d69();
 virtual void d70();
 virtual void d71();
 virtual void d72();
 virtual void d73();
 virtual void d74();
 virtual void d75();
 virtual void d76();
 virtual void d77();
 virtual void d78();
 virtual void d79();
 virtual void d80();
 virtual void d81();
 virtual void d82();
 virtual void d83();
 virtual void d84();
 virtual void d85();
 virtual void d86();
 virtual void d87();
 virtual void d88();
 virtual void d89();
 virtual void d90();
 virtual void d91();
 virtual void d92();
 virtual void d93();
 virtual void *Get();
};
struct Rva0041B8D2Iface {
 virtual void e00();
 virtual void e01();
 virtual void e02();
 virtual void e03();
 virtual void e04();
 virtual void e05();
 virtual unsigned char Check();
};
class Rva0041B8D2Obj {
public:
 char _0[4];
 Rva0041B8D2Inner *m_inner;
 char _8[0x258-8];
 Rva0041B8D2Holder *m_holder;
};
class ActionManager { public: unsigned char Rva0041B8D2Check(Rva0041B8D2Obj*, Rva0041B8D2Obj*, int); };

unsigned char ActionManager::Rva0041B8D2Check(Rva0041B8D2Obj *a, Rva0041B8D2Obj *b, int unused)
{
 if (b != 0) {
  if (b->m_inner->flag != 0) {
   Rva0041B8D2Holder *h = a->m_holder;
   void *p;
   if (h != 0) p = h->Get();
   else p = 0;
   if (p != 0) {
    Rva0041B8D2Iface *iface = (Rva0041B8D2Iface *)p;
    if (iface->Check() != 0) return true;
   }
  }
 }
 return false;
}
