// cl: /O1 /G7 /MD /EHsc
// Native5D10B0..5D10BA/10B tail-dispatch; C755A4 slot04.
// Target owner pointer4 -> state pointer0 -> virtual slot04; names structural.
class Rva005D10B0State {public:virtual void slot0();virtual void slot1();};
struct Rva005D10B0Owner{Rva005D10B0State*state;};
class Rva005D10D6 {public:virtual ~Rva005D10D6();virtual void slot1();Rva005D10B0Owner*owner;};
void Rva005D10D6::slot1(){owner->state->slot1();}
