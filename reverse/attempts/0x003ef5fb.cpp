// ?test@Rva003EF5FB@@QAEEH@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /MD
// Native003EF5FB..003EF634 RET4: flag2C gates the predicate; either
// -1 id yields true, otherwise lookup id18 then test the supplied id.
// Direct chained member expression preserves retail's argument evaluation.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E2903Player;
class Rva002BA8F1Logic {public:Rva002E2903Player *find(int,unsigned int *);};
class Rva002E071E {public:int rva002E0BC0(int);};
class Rva003EF5FB {
 char unknown00[0x18];
 int id18;
 char unknown1C[0x10];
 bool enabled2C;
public:
 unsigned char test(int);
};
unsigned char Rva003EF5FB::test(int id)
{
 unsigned char result;
 if(!enabled2C) result=false;
 else if(id18!=-1 && id!=-1)
  result=(unsigned char)reinterpret_cast<Rva002E071E *>(reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(id18,0))->rva002E0BC0(id);
 else result=true;
 return result;
}
