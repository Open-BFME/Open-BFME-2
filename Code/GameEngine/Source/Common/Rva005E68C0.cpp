// cl: /O1 /G7 /MD /EHsc /arch:SSE /Oy-
// Native5E68C0..5E6938 complete120B: complement of roster clear5E6938.
// Same observed fields and existing calls; original class identity unresolved.
class Rva005F6037ByteChaseField {public:unsigned char get()const;};
class Rva005F62FE {public:void rva005F62FE(bool);};
class Rva005E3B1A {public:bool IsSelected(int)const;};
class Rva005E508F
{
public:
	void rva005E509F();
	void rva005E508F(int);
	void rva005E5097(int);
};
struct Rva005E68C0Entry {int first,second;};
class Rva0040CC0EIndexedField {public:int get(int)const;char pad0[0x40];Rva005E68C0Entry *first,*last;};
struct Rva005E68C0Owner {char pad0[0x78];Rva0040CC0EIndexedField *catalog;};
class Rva005E68C0
{
public:
	void rva005E68C0();
	void rva005E69AC();
	char m_pad00[0x4];
private:
	Rva005F6037ByteChaseField *guard; // +0x04
	char m_pad08[0x4];
	Rva005E68C0Owner *owner; // +0x0C
	char m_pad10[0x4];
	int selected; // +0x14
};
void Rva005E68C0::rva005E68C0(){
 Rva005F6037ByteChaseField *view=guard;
 if(view->get())return;
 Rva0040CC0EIndexedField *catalog=owner->catalog;
 int count=catalog->last-catalog->first;
 for(int index=0;index<count;++index){
  int item=catalog->get(index);
  if(item!=selected && !((Rva005E3B1A*)((char*)guard+0xC))->IsSelected(item))
   ((Rva005E508F*)((char*)guard+0xC))->rva005E508F(item);
 }
 ((Rva005F62FE*)view)->rva005F62FE(true);
}

struct Rva005E6938Owner;
class Rva005E6938
{
public:
	void rva005E6938();
	char m_pad00[0x4];
private:
	Rva005F6037ByteChaseField *guard; // +0x04
	char m_pad08[0x4];
	Rva005E6938Owner *owner; // +0x0C
	char m_pad10[0x4];
	int selected; // +0x14
};
void Rva005E68C0::rva005E69AC(){
 if(guard->get())((Rva005E6938*)this)->rva005E6938();
 else rva005E68C0();
}
