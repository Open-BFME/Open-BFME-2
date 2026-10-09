// cl: /O1 /G7 /MD
// Native318F42..318F64: the vector-like view returned twice by318B83
// must exist and have a nonzero unsigned16-byte record count. Original
// application names remain unknown; WB131AA30 order drain corroborates uses.
// The neutral getter ABI is a complete17B byte/relocation twin of the
// existing getWheelInfo row; that donor name is not asserted for this view.
struct Rva00318F42Record { unsigned char bytes[16]; };
struct Rva00318F42View { Rva00318F42Record *first,*finish,*end; };
struct Rva00318F42Holder { unsigned char pad[0x3C]; Rva00318F42View view; };
class Rva00318F42 {
public:
 __declspec(noinline) Rva00318F42View *rva00318B83() const;
 bool rva00318F42();
private:
 unsigned char pad[0x88];
 Rva00318F42Holder *holder;
};
Rva00318F42View *Rva00318F42::rva00318B83() const {
 return holder ? &holder->view : 0;
}
bool Rva00318F42::rva00318F42() {
 if(rva00318B83()) { Rva00318F42View *v=rva00318B83(); return (unsigned int)(v->finish-v->first)>0; }
 return false;
}
