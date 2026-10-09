// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x006EBE60/386 and 0x006EBFF0/377: Apt text-binding workers.
// 006EBE60 resolves or creates the bound value; 006EBFF0 refreshes text.
// Identity: WorldBuilder 0x017812A0 source path/line 351, target assertion,
// and native string/interpreter calls. Original method name is unknown.
// Layout comes from retail accesses: definition +0C/defaultText +34,
// text +18, variable +1C, flags +6C, and the parent chain +48.
// The WB parent offset +4C is not carried over. Existing typed providers and
// the data-ledger interpreter owner supply every external reference.
// Named C-string temporaries preserve the two native EH states. The assert
// trap remains inline int3, matching adjacent Apt runtime assertion paths.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class EAStringC {
public:
 void *data;
 EAStringC(){clear();}
 EAStringC(const char*);
 ~EAStringC();
 EAStringC &clear();
 EAStringC &operator=(const EAStringC&);
 bool IsEmpty()const;
 const char*rva00620090()const;
 bool rva006D30D0(const EAStringC*)const;
};
class AptValue {
public:
 bool isUndefined()const;
 int getVtblIndex()const;
 void toString(EAStringC&)const;
 char unknown00[0x48];
 AptValue *parent;
};
struct AptActionInterpreter {
 bool setVariable(AptValue*,AptValue*,const EAStringC*,AptValue*,int,int,int);
 AptValue *getVariable(AptValue*,AptValue*,const EAStringC*,int,int,int);
};
extern AptActionInterpreter g_aptDateInterpreter;
struct BindingDefinition {char unknown00[0x34]; const char *defaultText;};
class Rva006EBFF0 {
public:
 void rva006EBFF0(AptValue*parent);
 void rva006EBE60(AptValue*parent);
 char unknown00[0xC]; BindingDefinition *definition;
 char unknown10[8]; EAStringC text; EAStringC variable;
 char unknown20[0x6C-0x20]; unsigned int flags;
};
class AptString:public AptValue {
public: static AptString *Create();
 EAStringC &value(){return *(EAStringC*)((char*)this+8);}
};
void Rva006EBFF0::rva006EBE60(AptValue *parent)
{
 if(variable.IsEmpty())return;
 if(variable.rva00620090()[0]=='$'){text=variable;return;}
 while(parent && !(!parent->isUndefined() && (parent->getVtblIndex()==13||parent->getVtblIndex()==18)) && parent->parent){parent=parent->parent;}
 AptValue *value=g_aptDateInterpreter.getVariable(parent,0,&variable,1,1,0);
 if(value->isUndefined()){
  AptString *created=AptString::Create();
  if(definition->defaultText){EAStringC tmp(definition->defaultText);created->value()=tmp;}
  else {EAStringC tmp("");created->value()=tmp;}
  text=created->value();
  g_aptDateInterpreter.setVariable(parent,0,&variable,created,1,1,0);
 }else value->toString(text);
}
void Rva006EBFF0::rva006EBFF0(AptValue *parent)
{
 if(variable.IsEmpty()||variable.rva00620090()[0]=='$')return;
 EAStringC result;
 while(parent && !(!parent->isUndefined() && (parent->getVtblIndex()==13||parent->getVtblIndex()==18)) && parent->parent){parent=parent->parent;}
 AptValue *value=g_aptDateInterpreter.getVariable(parent,0,&variable,1,1,0);
 if(!value){g_bfmeAptAssertAtE17734("pValue != NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",351);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
 if(value->isUndefined()){
  if(definition->defaultText){EAStringC tmp(definition->defaultText);result=tmp;}
  else {EAStringC tmp("");result=tmp;}
 }else value->toString(result);
 if(text.rva006D30D0(&result)){text=result;flags=(flags&~1u)|2u;}
}
