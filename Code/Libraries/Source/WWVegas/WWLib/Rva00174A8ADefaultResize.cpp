// cl: /O1 /EHsc /MD
// Native 35B ret4 wrapper constructs the 32B entry at its argument slot.
// Constructor1736D6 and by-value resize17480C are independently matched.
struct Rva0017480CRecord { Rva0017480CRecord(); Rva0017480CRecord(const Rva0017480CRecord&); ~Rva0017480CRecord(); unsigned char consumed[32]; };
class Rva0017480CVector {Rva0017480CRecord*start,*finish,*limit;public:void resize(unsigned,Rva0017480CRecord);void resizeDefault(unsigned);};
void Rva0017480CVector::resizeDefault(unsigned n){resize(n,Rva0017480CRecord());}
#pragma comment(linker, "/alternatename:??0Rva0017480CRecord@@QAE@XZ=??0BfmeAssignRecord32@@QAE@XZ")
