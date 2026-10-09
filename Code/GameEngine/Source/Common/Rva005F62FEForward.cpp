// cl: /O1 /G7 /MD /EHsc
// Native5F62FE..5F6306 8B; no new semantic identity. The receiver's
// pointer at8 forwards the same bool input to verified setter5F618E.
class Rva005F618E {public:void rva005F618E(bool);};
class Rva005F62FE {public:void rva005F62FE(bool);private:char pad0[8];Rva005F618E *target;};
void Rva005F62FE::rva005F62FE(bool value){target->rva005F618E(value);}
