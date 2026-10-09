// cl: /MD /EHsc
// Native6D0280..6D031E RET0 158B. WB1753F40 is the semantic guide;
// target EH destroys the embedded string at8 after tracker removal and
// state3/4/5 animation cleanup; state2 logs an uncancelled load.
// Destructor ABI is established by member cleanup and the exact C++ body.
// Rva006E5940 remains an address-derived opaque thiscall relocation cleanup:
// native6E5940..6E5F08 RET4 with8B receiver displacement; complete bank has
// matching ABI and providers but unlanded register/switch scheduling residue.
// Original AptFile class identity is not claimed.
class EAStringC{void*data;public:~EAStringC();const char*rva00620090()const;};
class Rva006E5940{public:void rva006E5940(int);};
class Rva006D01D0Tracker{public:void remove(void*);};
class Rva00893030Manager;extern Rva00893030Manager*g_rva00893030Manager;
extern void*g_aptFreeAnimationSlot;
void __cdecl Rva006CC110Log(int,const char*,...);
class Rva006D0280{public:int count;int unused4;EAStringC name;int state;int data;Rva006E5940*object;void*buffer;~Rva006D0280();};
Rva006D0280::~Rva006D0280(){
 ((Rva006D01D0Tracker*)g_rva00893030Manager)->remove(this);
 if(state==3||state==4||state==5){
  ((Rva006E5940*)((char*)object+8))->rva006E5940(data);
  ((void(__cdecl*)(void*))g_aptFreeAnimationSlot)(buffer);
 }else if(state==2)Rva006CC110Log(0,"TODO: should have cancelled load of '%s'\n",name.rva00620090());
}
