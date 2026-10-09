// cl: /O1 /G7 /arch:SSE /EHsc /MD
// Native instruction boundary0058A6A8..0058ACA9 (1537B); its 41-entry
// switch table0058ACA9..0058AD4D (164B) is part of this emitted symbol.
// The following rowed constructor starts0058AD4D, so full extent is1701B.
// cdecl one int selector, RET0; allocates the target-observed class sizes
// then calls each rowed constructor. Cases22/23 construct Rva005D8317
// with0/1; original switch order follows retail block addresses rather
// than numeric selector order. No original factory/type-enum name is
// established. All Rva class names are existing constructor storage views;
// sizes below are retail allocations, not asserted original member layouts.
// Case35's established AISpellBookTreeKiller name is carried from its
// provider. The unnamed WorldBuilder twin0148B910 has39 cases (retail41)
// and the same constructor-call factory semantics; it supplies no new name.
// Compatible BFME1/ZeroHour named factory source was not available.
class Rva005DA353 {public:Rva005DA353();virtual ~Rva005DA353();private:char storage04[24];};
class Rva005DA0E2 {public:Rva005DA0E2();virtual ~Rva005DA0E2();private:char storage04[28];};
class Rva005D9F70 {public:Rva005D9F70();virtual ~Rva005D9F70();private:char storage04[24];};
class Rva005D9DC1 {public:Rva005D9DC1();virtual ~Rva005D9DC1();private:char storage04[56];};
class Rva005D9D5A {public:Rva005D9D5A();virtual ~Rva005D9D5A();private:char storage04[56];};
class Rva005D99BD {public:Rva005D99BD();virtual ~Rva005D99BD();private:char storage04[56];};
class Rva005D9CD5 {public:Rva005D9CD5();virtual ~Rva005D9CD5();private:char storage04[36];};
class Rva005D9C6C {public:Rva005D9C6C();virtual ~Rva005D9C6C();private:char storage04[36];};
class Rva005D95A8 {public:Rva005D95A8();virtual ~Rva005D95A8();private:char storage04[36];};
class Rva005D9BA5 {public:Rva005D9BA5();virtual ~Rva005D9BA5();private:char storage04[24];};
class Rva005D9A1E {public:Rva005D9A1E();virtual ~Rva005D9A1E();private:char storage04[24];};
class Rva005D96FA {public:Rva005D96FA();virtual ~Rva005D96FA();private:char storage04[36];};
class Rva005D944A {public:Rva005D944A();virtual ~Rva005D944A();private:char storage04[36];};
class Rva005D91AB {public:Rva005D91AB();virtual ~Rva005D91AB();private:char storage04[36];};
class Rva005D8EE8 {public:Rva005D8EE8();virtual ~Rva005D8EE8();private:char storage04[36];};
class Rva005D8C25 {public:Rva005D8C25();virtual ~Rva005D8C25();private:char storage04[36];};
class Rva005D8BD5 {public:Rva005D8BD5();virtual ~Rva005D8BD5();private:char storage04[24];};
class Rva005D8AE4 {public:Rva005D8AE4();virtual ~Rva005D8AE4();private:char storage04[36];};
class Rva005D8964 {public:Rva005D8964();virtual ~Rva005D8964();private:char storage04[24];};
class Rva005D8883 {public:Rva005D8883();virtual ~Rva005D8883();private:char storage04[24];};
class Rva005D8723 {public:Rva005D8723();virtual ~Rva005D8723();private:char storage04[28];};
class Rva005D86E6 {public:Rva005D86E6();virtual ~Rva005D86E6();private:char storage04[36];};
class Rva005D8317 {public:Rva005D8317(int);virtual ~Rva005D8317();private:char storage04[40];};
class Rva005D84F6 {public:Rva005D84F6();virtual ~Rva005D84F6();private:char storage04[36];};
class Rva005D8223 {public:Rva005D8223();virtual ~Rva005D8223();private:char storage04[36];};
class Rva005D817D {public:Rva005D817D();virtual ~Rva005D817D();private:char storage04[36];};
class Rva005D7D88 {public:Rva005D7D88();virtual ~Rva005D7D88();private:char storage04[36];};
class Rva005D7C17 {public:Rva005D7C17();virtual ~Rva005D7C17();private:char storage04[36];};
class Rva005D7B3E {public:Rva005D7B3E();virtual ~Rva005D7B3E();private:char storage04[36];};
class Rva005D7AC5 {public:Rva005D7AC5();virtual ~Rva005D7AC5();private:char storage04[36];};
class Rva005D7A1B {public:Rva005D7A1B();virtual ~Rva005D7A1B();private:char storage04[36];};
class Rva005D791C {public:Rva005D791C();virtual ~Rva005D791C();private:char storage04[48];};
class Rva005D7855 {public:Rva005D7855();virtual ~Rva005D7855();private:char storage04[36];};
class Rva005D7F5D {public:Rva005D7F5D();virtual ~Rva005D7F5D();private:char storage04[72];};
class AISpellBookTreeKiller {public:AISpellBookTreeKiller();virtual ~AISpellBookTreeKiller();private:char storage04[36];};
class Rva005D7531 {public:Rva005D7531();virtual ~Rva005D7531();private:char storage04[36];};
class Rva005D736E {public:Rva005D736E();virtual ~Rva005D736E();private:char storage04[36];};
class Rva005D72FA {public:Rva005D72FA();virtual ~Rva005D72FA();private:char storage04[24];};
class Rva005D724B {public:Rva005D724B();virtual ~Rva005D724B();private:char storage04[24];};
class Rva005D719C {public:Rva005D719C();virtual ~Rva005D719C();private:char storage04[24];};

void *Rva0058A6A8_Create(int type)
{
 switch(type) {
 case 0: return new Rva005DA353();
 case 1: return new Rva005DA0E2();
 case 2: return new Rva005D9F70();
 case 3: return new Rva005D9DC1();
 case 4: return new Rva005D9D5A();
 case 6: return new Rva005D9CD5();
 case 7: return new Rva005D9C6C();
 case 9: return new Rva005D9BA5();
 case 10: return new Rva005D9A1E();
 case 5: return new Rva005D99BD();
 case 11: return new Rva005D96FA();
 case 8: return new Rva005D95A8();
 case 12: return new Rva005D944A();
 case 13: return new Rva005D91AB();
 case 14: return new Rva005D8EE8();
 case 15: return new Rva005D8C25();
 case 16: return new Rva005D8BD5();
 case 17: return new Rva005D8AE4();
 case 18: return new Rva005D8964();
 case 19: return new Rva005D8883();
 case 20: return new Rva005D8723();
 case 21: return new Rva005D86E6();
 case 24: return new Rva005D84F6();
 case 22: return new Rva005D8317(0);
 case 23: return new Rva005D8317(1);
 case 25: return new Rva005D8223();
 case 26: return new Rva005D817D();
 case 34: return new Rva005D7F5D();
 case 27: return new Rva005D7D88();
 case 28: return new Rva005D7C17();
 case 29: return new Rva005D7B3E();
 case 30: return new Rva005D7AC5();
 case 31: return new Rva005D7A1B();
 case 32: return new Rva005D791C();
 case 33: return new Rva005D7855();
 case 35: return new AISpellBookTreeKiller();
 case 36: return new Rva005D7531();
 case 37: return new Rva005D736E();
 case 38: return new Rva005D72FA();
 case 39: return new Rva005D724B();
 case 40: return new Rva005D719C();
 default:return 0;
 }
}
