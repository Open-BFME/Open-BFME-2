// cl: /O1 /G7 /MD /EHsc /arch:SSE
// Native5E6938..5E69AC complete116B. Guard via existing byte getter
// on field4; clear leader state through verified5F62FE; enumerate the
// eight-byte records of fieldC->78 and append IDs other than field14
// only when existing contains5E3B1A returns true. Semantics and original
// class identity beyond this observed call graph remain unresolved.
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
struct Rva005E6938Entry {int first,second;};
class Rva0040CC0EIndexedField {public:int get(int)const;char pad0[0x40];Rva005E6938Entry *first,*last;};
struct Rva005E6938Owner {char pad0[0x78];Rva0040CC0EIndexedField *catalog;};
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
void Rva005E6938::rva005E6938(){
 Rva005F6037ByteChaseField *view=guard;
 if(!view->get())return;
 ((Rva005F62FE*)view)->rva005F62FE(false);
 Rva0040CC0EIndexedField *catalog=owner->catalog;
 int count=catalog->last-catalog->first;
 for(int index=0;index<count;++index){
  int item=catalog->get(index);
  if(item!=selected && ((Rva005E3B1A*)((char*)guard+0xC))->IsSelected(item))
   ((Rva005E508F*)((char*)guard+0xC))->rva005E5097(item);
 }
}
