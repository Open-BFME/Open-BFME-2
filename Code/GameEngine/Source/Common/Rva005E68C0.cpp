// cl: /O1 /G7 /MD /EHsc /arch:SSE /Oy-
// Native5E68C0..5E6938 complete120B: complement of roster clear5E6938.
// Same observed fields and existing calls; original class identity unresolved.
class Rva005F6037ByteChaseField {public:unsigned char get()const;};
class Rva005F62FE {public:void rva005F62FE(bool);};
class Rva005E3B1A {public:bool rva005E3B1A(int)const;};
class Rva005E508F {public:void rva005E5097(int);void rva005E508F(int);};
struct Rva005E68C0Entry {int first,second;};
class Rva0040CC0EIndexedField {public:int get(int)const;char pad0[0x40];Rva005E68C0Entry *first,*last;};
struct Rva005E68C0Owner {char pad0[0x78];Rva0040CC0EIndexedField *catalog;};
class Rva005E68C0 {public:void rva005E68C0();void rva005E69AC();private:char pad0[4];Rva005F6037ByteChaseField *guard;char pad8[4];Rva005E68C0Owner *owner;char pad10[4];int selected;};
void Rva005E68C0::rva005E68C0(){
 Rva005F6037ByteChaseField *view=guard;
 if(view->get())return;
 Rva0040CC0EIndexedField *catalog=owner->catalog;
 int count=catalog->last-catalog->first;
 for(int index=0;index<count;++index){
  int item=catalog->get(index);
  if(item!=selected && !((Rva005E3B1A*)((char*)guard+0xC))->rva005E3B1A(item))
   ((Rva005E508F*)((char*)guard+0xC))->rva005E508F(item);
 }
 ((Rva005F62FE*)view)->rva005F62FE(true);
}

class Rva005E6938 {public:void rva005E6938();};
void Rva005E68C0::rva005E69AC(){
 if(guard->get())((Rva005E6938*)this)->rva005E6938();
 else rva005E68C0();
}
