// cl: /O1 /G7 /MD
// Native318F42..318F64: the vector-like view returned twice by318B83
// must exist and have a nonzero unsigned16-byte record count. Original
// application names remain unknown; WB131AA30 order drain corroborates uses.
// The neutral getter ABI is a complete17B byte/relocation twin of the
// existing getWheelInfo row; that donor name is not asserted for this view.
struct Rva00318F42Record { unsigned char bytes[16]; };
struct Rva00318F42View { Rva00318F42Record *first,*finish,*end; };
struct Rva00318F42Holder { unsigned char pad[0x3C]; Rva00318F42View view; };

struct Rva00538CEFPair {int a,b;};
class Rva00538CEF {public:void rva00538DC1(const Rva00538CEFPair *,int);bool rva00538D17(Rva00538CEFPair *);};
class Rva003195C9Owner {public:void rva003195C9();};
class Rva003197EEListener {public:virtual void notify(void *);virtual void slot04(void *);virtual void slot08(void *);virtual void slot0c(void *);virtual void slot10(void *);};
class Rva003197EEList {public:void forEach(void (Rva003197EEListener::*)(void *),void *);};
class Rva00318F42 {
public:
 __declspec(noinline) Rva00318F42View *rva00318B83() const;
 bool rva00318F42();
 void rva0031986B(const Rva00538CEFPair *,int);
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

// Native31986B..3198B8,77B; WB102B1B0 independently preserves the
// getter and unsigned16-byte count, two-word update/copy and listener walk.
// This view preserves the original owner/type uncertainty. The pushed
// compiler vcall thunk is the existing5B slot10 provider at5CB26A;
// listener slot declarations describe only the witnessed dispatch offsets.
void Rva00318F42::rva0031986B(const Rva00538CEFPair *pair,int word){
 Rva00318F42View *v=rva00318B83();
 if(v){int *span=(int*)v;if((unsigned)((span[1]-span[0])>>4)>0){
  ((Rva00538CEF*)v)->rva00538DC1(pair,word);
  ((Rva00538CEF*)v)->rva00538D17((Rva00538CEFPair*)((char*)this+0x3c));
  ((Rva003195C9Owner*)this)->rva003195C9();
  ((Rva003197EEList*)((char*)this+8))->forEach(&Rva003197EEListener::slot10,this);
 }}
}
