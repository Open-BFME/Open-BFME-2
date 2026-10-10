// cl: /O1 /G7 /MD /EHsc
// Native5CFB35..5CFB81/76B, WB15B9FF0. The existing48B destructor
// and C752EC scalar deleting destructor establish the address-derived
// owner and its base8/member4 lifetimes. Retail C75290 and C752EC
// each contain two function entries; the following entries start other
// tables/string data. Keep the two-slot primary interface here; 76B Tactical ctor5D1064 is
// a byte-and-relocation twin except the independently owned vtable.
class Rva005EC832Owner{public:Rva005EC832Owner*rva005EC832(int);};
class Rva005EC422{public:Rva005EC422(void*p){((Rva005EC832Owner*)this)->rva005EC832((int)p);}~Rva005EC422();void*ptr;};
class Rva005CF872{public:Rva005CF872(void*p):owner(p){}virtual~Rva005CF872(){}virtual void slot1();void*owner;};
class StrategicVeterancy{public:bool Show();};
class Rva005CFFB8:public Rva005CF872{public:Rva005CFFB8(void*,void*);virtual~Rva005CFFB8();virtual void slot1();Rva005EC422 view;};
Rva005CFFB8::Rva005CFFB8(void*p,void*s):Rva005CF872(p),view(s){((StrategicVeterancy*)&view)->Show();}
