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
class EAStringC
{
public:
	class StringDataC { public: unsigned short m_uRefCount; unsigned short m_uSize; unsigned short m_uMaxSize; unsigned short m_uHash; };
	EAStringC();
	EAStringC(const char *);
	EAStringC(const EAStringC &);
	static void FreeData(StringDataC *);
	EAStringC &clear();
	EAStringC &operator=(const EAStringC&);
	~EAStringC();
	int GetAt(int) const;
	bool IsEmpty() const;
	unsigned int rva006D3750() const;
	bool IsEqualTo(const EAStringC*) const;
	bool rva006D30D0(const EAStringC*) const;
	bool rva006D3510(const char*) const;
	EAStringC &MakeLower();
	EAStringC &Rva006D4F00Append(const EAStringC &other);
	const char *rva00620090() const;
	int rva006D54B0(int,int);
private:
	StringDataC *data; // +0x00
};
// AptValue::getVtblIndex (donor identity, pinned at 0x006DBB30) is rowed as
// Rva006DBB30SarDwordField::get; the loops below call it by the ledger's name.
class Rva006DBB30SarDwordField
{
public:
	int get() const;
};

class AptCIH;
class AptValue
{
public:
	AptCIH *c_cih(bool bUndefinedOK);
	bool isCIH(bool bUndefinedOK) const;
	bool isUndefined() const;
	bool getIsDefined() const;
	float toFloat() const;
	int toInteger() const;
	void toString(EAStringC &) const;
	virtual void AddRef();
	virtual void Release();
};
class AptNativeHash;
struct SwapSprite;
class AptCIH
{
public:
    virtual void slot0();
    virtual void changed();
    virtual void slot2();
    virtual AptNativeHash *slot3();
    char unknown04[8];
    float matrix[6];
    char unknown24[0x44-0x24];
    float *properties;
    AptCIH *parent;
    SwapSprite *instance;
    char unknown50[8];
    signed int depth:17;
    unsigned int unknownDepth17:15;
    int unknown5c;
    void *rva006CFF40() const;
    void jumpToFrame(int);
    bool rva006CFCD0() const;
    bool IsSpriteInst(bool) const;
    bool IsAnimationInst(bool) const;
    void factorySetProperty(int,float,bool);
    void factoryEnsureProperties();
    void rva006E1DD0(void *);
    void *rva006E1170() const;
    void SetEventHandler(int);
    void RemoveEventHandler(int);
    int rva006E1F90(int);
};
class BfmeAptValue006DCD20 : public AptValue
{
public:
	BfmeAptValue006DCD20(int);
	BfmeAptValue006DCD20 *rva006DCF60(bool undefOK);
	BfmeAptValue006DCD20 *checkedString();
	bool isCIH(bool bUndefinedOK) const;
	bool isUndefined() const;
	int isCharacterInst() const;
	int isInteger() const;
	int isString() const;
	int rva006E02B0() const;
	int rva006E03A0() const;
	void *rva006E0F40() const;
	int toInteger() const;
	virtual ~BfmeAptValue006DCD20();
	unsigned int m_flags; // +0x04
};
class AptBasePtrStack
{
public:
	BfmeAptValue006DCD20 *At(int);
private:
	char bytes[12]; // +0x00
};
struct AptActionInterpreter
{
private:
	friend BfmeAptValue006DCD20 *rva006ec670(BfmeAptValue006DCD20 *pValue, int nParams);
public:
	bool setVariable(AptValue*,AptValue*,const EAStringC*,AptValue*,int,int,int);
	AptValue *getVariable(AptValue*,AptValue*,const EAStringC*,int,int,int);
	void loadVariables(AptValue *,AptValue *,const EAStringC *);
private:
	void rva007092F0(AptCIH *context, AptValue *with, AptValue *source, AptValue *target, int depth, AptValue *init);
public:
	AptBasePtrStack stack; // +0x00
};
extern AptActionInterpreter g_aptDateInterpreter;
struct BindingDefinition {char unknown00[0x34]; const char *defaultText;};
class Rva006EBFF0
{
public:
    void rva006EBFF0(AptValue*parent);
    void rva006EBE60(AptValue*parent);
    char unknown00[0xC];
    BindingDefinition *definition;
    char unknown10[8];
    EAStringC text;
    EAStringC variable;
    char unknown20[0x6C-0x20];
    unsigned int flags;
};
class AptString:public AptValue
{
public:
    static AptString *Create();
    __forceinline EAStringC &value()
    {
        return *(EAStringC*)((char*)this+8);
    }
};
void Rva006EBFF0::rva006EBE60(AptValue *parent)
{
 if(variable.IsEmpty())return;
 if(variable.rva00620090()[0]=='$'){text=variable;return;}
 while(parent && !(!parent->isUndefined() && (((const Rva006DBB30SarDwordField *)parent)->get()==13||((const Rva006DBB30SarDwordField *)parent)->get()==18)) && ((AptCIH *)parent)->parent){parent=(AptValue *)((AptCIH *)parent)->parent;}
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
 while(parent && !(!parent->isUndefined() && (((const Rva006DBB30SarDwordField *)parent)->get()==13||((const Rva006DBB30SarDwordField *)parent)->get()==18)) && ((AptCIH *)parent)->parent){parent=(AptValue *)((AptCIH *)parent)->parent;}
 AptValue *value=g_aptDateInterpreter.getVariable(parent,0,&variable,1,1,0);
 if(!value){g_bfmeAptAssertAtE17734("pValue != NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",351);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
 if(value->isUndefined()){
  if(definition->defaultText){EAStringC tmp(definition->defaultText);result=tmp;}
  else {EAStringC tmp("");result=tmp;}
 }else value->toString(result);
 if(text.rva006D30D0(&result)){text=result;flags=(flags&~1u)|2u;}
}
