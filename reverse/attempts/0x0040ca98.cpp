// ?Rva0040CA98@@YAXXZ
// partial score=1.0 date=2026-10-08
// cl: /O1 /MD /EHsc
class Rva0040C985 {
public: void rva0040CA09();
char pad[0x2c]; int state;
};
class Rva003F498ACallback { public: virtual bool invoke(int)=0; };
class Rva002B31DB : public Rva003F498ACallback {
public:
 virtual bool invoke(int);
 ~Rva002B31DB() {}
};
bool Rva002B31DB::invoke(int value)
{
 Rva0040C985 *state=*(Rva0040C985 **)((char *)value+0x78);
 if (state->state==2) state->rva0040CA09();
 return true;
}
class LivingWorldBattle { public: void rva003F498A(Rva003F498ACallback *); };
class Rva003F468D;
class Rva0020E6B7RegionManager { public: Rva003F468D *rva0020E6B7(); };
class Rva002B4AF8 {
public: void rva002B4AF8();
 char pad[0xb0]; Rva0020E6B7RegionManager *manager;
 unsigned char fieldB4; bool fieldB5;
};
void Rva002B4AF8::rva002B4AF8()
{
 if (!fieldB5) {
  LivingWorldBattle *battle=(LivingWorldBattle *)manager->rva0020E6B7();
  if (battle) {
   Rva002B31DB visitor;
   battle->rva003F498A(&visitor);
  }
 }
}

// Native global TheDisplay and virtual slot +0x160, tested as a byte.
// The slot's original name is unknown; earlier slots are ABI placeholders.
class Display {
public:
 virtual void unused00();
 virtual void unused01();
 virtual void unused02();
 virtual void unused03();
 virtual void unused04();
 virtual void unused05();
 virtual void unused06();
 virtual void unused07();
 virtual void unused08();
 virtual void unused09();
 virtual void unused0A();
 virtual void unused0B();
 virtual void unused0C();
 virtual void unused0D();
 virtual void unused0E();
 virtual void unused0F();
 virtual void unused10();
 virtual void unused11();
 virtual void unused12();
 virtual void unused13();
 virtual void unused14();
 virtual void unused15();
 virtual void unused16();
 virtual void unused17();
 virtual void unused18();
 virtual void unused19();
 virtual void unused1A();
 virtual void unused1B();
 virtual void unused1C();
 virtual void unused1D();
 virtual void unused1E();
 virtual void unused1F();
 virtual void unused20();
 virtual void unused21();
 virtual void unused22();
 virtual void unused23();
 virtual void unused24();
 virtual void unused25();
 virtual void unused26();
 virtual void unused27();
 virtual void unused28();
 virtual void unused29();
 virtual void unused2A();
 virtual void unused2B();
 virtual void unused2C();
 virtual void unused2D();
 virtual void unused2E();
 virtual void unused2F();
 virtual void unused30();
 virtual void unused31();
 virtual void unused32();
 virtual void unused33();
 virtual void unused34();
 virtual void unused35();
 virtual void unused36();
 virtual void unused37();
 virtual void unused38();
 virtual void unused39();
 virtual void unused3A();
 virtual void unused3B();
 virtual void unused3C();
 virtual void unused3D();
 virtual void unused3E();
 virtual void unused3F();
 virtual void unused40();
 virtual void unused41();
 virtual void unused42();
 virtual void unused43();
 virtual void unused44();
 virtual void unused45();
 virtual void unused46();
 virtual void unused47();
 virtual void unused48();
 virtual void unused49();
 virtual void unused4A();
 virtual void unused4B();
 virtual void unused4C();
 virtual void unused4D();
 virtual void unused4E();
 virtual void unused4F();
 virtual void unused50();
 virtual void unused51();
 virtual void unused52();
 virtual void unused53();
 virtual void unused54();
 virtual void unused55();
 virtual void unused56();
 virtual void unused57();
 virtual bool slot160();
};
extern Display *TheDisplay;
class GameLogic;
extern GameLogic *TheGameLogic;
class Rva002034E9Host { public: bool rva002034E9(); };
class Rva002BA8F1Logic;
extern Rva002BA8F1Logic *g_009FEF10;
void Rva0040CA98()
{
 if (!TheDisplay->slot160() && ((Rva002034E9Host *)TheGameLogic)->rva002034E9())
  ((Rva002B4AF8 *)g_009FEF10)->rva002B4AF8();
}
