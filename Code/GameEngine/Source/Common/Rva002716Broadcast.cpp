// cl: /MD
// Rva002716 broadcast family: 5 homogeneous thiscall helpers iterating NULL-terminated
// Rva002716Entry array at holder+0x14c, calling virtual 0xA8 to get Rva002716Target then
// virtual 0x1C/0x20/0x40/0x48/0x4C with 3/2/1/0/1 int args. Honest address names; identity unproven.
// ?Rva00271619Broadcast@Rva002716Holder@@QAEXHHH@Z 0x00271619 53B slot 0x1C 3 args caller 0x0028DC6C
// ?Rva0027164EBroadcast@Rva002716Holder@@QAEXHH@Z 0x0027164E 49B slot 0x20 2 args callers 8x incl 0x004A7E60 0x00290799
// ?Rva0027167FBroadcast@Rva002716Holder@@QAEXH@Z 0x0027167F 45B slot 0x40 1 arg caller 0x004686CD
// ?Rva002716ACBroadcast@Rva002716Holder@@QAEXXZ 0x002716AC 39B slot 0x48 0 args caller 0x000C80F1
// ?Rva002716D3Broadcast@Rva002716Holder@@QAEXH@Z 0x002716D3 45B slot 0x4C 1 arg callers 0x00467C78 0x004686C6
// Evidence: all callees virtual (gate-resolvable); loop shape push esi/mov esi [ecx+14C]/jmp-test/mov eax [ecx]/call [eax+A8]; siblings via neighbors 0x0027164E.
struct Rva002716Target {
  virtual void v00();
  virtual void v01();
  virtual void v02();
  virtual void v03();
  virtual void v04();
  virtual void v05();
  virtual void v06();
  virtual void m1c3(int a, int b, int c);
  virtual void m20_2(int a, int b);
  virtual void v09();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void m40_1(int a);
  virtual void v17();
  virtual void do48();
  virtual void m4c_1(int a);
};
struct Rva002716Entry {
  virtual void w00();
  virtual void w01();
  virtual void w02();
  virtual void w03();
  virtual void w04();
  virtual void w05();
  virtual void w06();
  virtual void w07();
  virtual void w08();
  virtual void w09();
  virtual void w10();
  virtual void w11();
  virtual void w12();
  virtual void w13();
  virtual void w14();
  virtual void w15();
  virtual void w16();
  virtual void w17();
  virtual void w18();
  virtual void w19();
  virtual void w20();
  virtual void w21();
  virtual void w22();
  virtual void w23();
  virtual void w24();
  virtual void w25();
  virtual void w26();
  virtual void w27();
  virtual void w28();
  virtual void w29();
  virtual void w30();
  virtual void w31();
  virtual void w32();
  virtual void w33();
  virtual void w34();
  virtual void w35();
  virtual void w36();
  virtual void w37();
  virtual void w38();
  virtual void w39();
  virtual void w40();
  virtual void w41();
  virtual Rva002716Target* getTarget();
};
struct Rva002716Holder {
  void Rva00271619Broadcast(int a, int b, int c);
  void Rva0027164EBroadcast(int a, int b);
  void Rva0027167FBroadcast(int a);
  void Rva002716ACBroadcast();
  void Rva002716D3Broadcast(int a);
  unsigned char m_pad[0x14c];
  Rva002716Entry** m_array;
};
void Rva002716Holder::Rva00271619Broadcast(int a, int b, int c)
{ Rva002716Entry** p = m_array; Rva002716Entry* e; while ((e = *p) != 0) { Rva002716Target* t = e->getTarget(); if (t) t->m1c3(a, b, c); ++p; } }
void Rva002716Holder::Rva0027164EBroadcast(int a, int b)
{ Rva002716Entry** p = m_array; Rva002716Entry* e; while ((e = *p) != 0) { Rva002716Target* t = e->getTarget(); if (t) t->m20_2(a, b); ++p; } }
void Rva002716Holder::Rva0027167FBroadcast(int a)
{ Rva002716Entry** p = m_array; Rva002716Entry* e; while ((e = *p) != 0) { Rva002716Target* t = e->getTarget(); if (t) t->m40_1(a); ++p; } }
void Rva002716Holder::Rva002716ACBroadcast()
{ Rva002716Entry** p = m_array; Rva002716Entry* e; while ((e = *p) != 0) { Rva002716Target* t = e->getTarget(); if (t) t->do48(); ++p; } }
void Rva002716Holder::Rva002716D3Broadcast(int a)
{ Rva002716Entry** p = m_array; Rva002716Entry* e; while ((e = *p) != 0) { Rva002716Target* t = e->getTarget(); if (t) t->m4c_1(a); ++p; } }
