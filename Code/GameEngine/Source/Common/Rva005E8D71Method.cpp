// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Retail5E8CF8..5E8D38 whole64B, virtual primary receiver whose deleting
// destructor5E8E64 and vtableC77F88 identify the existing Rva005E8D71 view.
// Native queries living-world availability then slot20 with the32-bit field at+20;
// the resulting bool is passed to owned5E1160 on the embedded flag at+8.
// Actual UI/class names remain unproved. Neutral layouts follow target access;
// the query byte selection and legacy thiscall pin256E are independently
// consistent with native calls. Thiscall256E ignores ECX in its11B body.
// No new pin or class-layout claim is added.
class Rva002B254F { public: int rva002B254F(); };
class Rva002B256E { public: void* rva002B256E(); };
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva005E1160Flag { public: void rva005E1160(bool); };
class Rva005E8CF8QueryInterface { public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04();virtual void s05();virtual void s06();virtual void s07();virtual bool s08(unsigned);
};
class Rva005E8D71 { public: virtual void rva005E8CF8(); private:
 char pad04[0x1c]; unsigned value20;
};
void Rva005E8D71::rva005E8CF8(){
 bool enabled=true;
 if((unsigned char)((Rva002B254F*)TheLivingWorldLogic)->rva002B254F()){
  Rva005E8CF8QueryInterface* system=(Rva005E8CF8QueryInterface*)((Rva002B256E*)TheLivingWorldLogic)->rva002B256E();
  enabled=system->s08(value20);
 }
 ((Rva005E1160Flag*)((char*)this+8))->rva005E1160(enabled);
}
