// ?rva004CED15@Rva004CED15Owner@@QAEXVRva004CEAB7@@@Z
// partial score=0.93 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /EHsc- /MD
class Rva004CEAB7 {
public: float x,y,z;
~Rva004CEAB7(){}
Rva004CEAB7(const Rva004CEAB7& a):x(a.x),y(a.y),z(a.z){}
};
struct Rva004CEB14List {void*head;};
void Rva004CEB76(Rva004CEB14List&,Rva004CEAB7);
class Rva004CED15Owner {public:void rva004CED15(Rva004CEAB7 comp);};
void Rva004CED15Owner::rva004CED15(Rva004CEAB7 comp) {
Rva004CEB76(*(Rva004CEB14List*)this,comp);
}
