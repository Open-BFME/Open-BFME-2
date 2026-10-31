// cl: /O2 /DNDEBUG /MD /EHsc
// Native 6EDBD0..6EDF11 RET0; following15CC bytes are padding.
// AptCharacter callback: resolves a depth/CIH/name argument then swaps the
// two17-bit signed depths and relinks the parent's display list. Actual
// query/unlink/insert providers and parent+48/instance+4C layout are shared
// with AptCharacterByteCounts.cpp and AptDisplayList.cpp. Original callback
// name is not asserted. Preserve native's unusual count/CIH guard polarity.
// The sprite() assert break is __asm int 3 (the owner AptCharacter units'
// spelling): the __debugbreak intrinsic plus barriers left the body 0.99.
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
extern AptValue *gpUndefinedValue;
class BfmeQuery1279 {public:void bfmeQuery1279(int,int,void **,void **);void rva006F6FB0(int,AptCIH *);};
struct SwapSprite {char pad[0x24];BfmeQuery1279 *list;};
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
class Rva006CFCD0
{
public:
	bool isSpriteInstBase() const;
};
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
static __forceinline SwapSprite *sprite(AptCIH *aptCIH) {
 if(!((Rva006CFCD0 *)aptCIH)->isSpriteInstBase()) {
  g_bfmeAptAssertAtE17734("isSpriteInstBase()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0x7d);
  if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
 }
 return aptCIH->instance;
}
class BfmeNestedBE;
BfmeNestedBE *bfmeUnlinkNestedBE(BfmeNestedBE *);
AptValue *Rva006EDBD0SwapDepths(AptValue *self,int count) {
 if(count!=1 && ((BfmeAptValue006DCD20 *)self)->isCIH(false))return gpUndefinedValue;
 AptCIH *cih=(AptCIH*)((BfmeAptValue006DCD20*)self)->rva006DCF60(false);
 BfmeAptValue006DCD20 *arg=g_aptDateInterpreter.stack.At(0);
 AptCIH *other=0;void *previous=0;
 if(arg->isCIH(false))other=(AptCIH *)arg->rva006DCF60(false);
 else if((unsigned char)arg->isString()) {
  EAStringC name;
  ((AptValue*)arg)->toString(name);
  sprite(cih->parent)->list->bfmeQuery1279(0,(int)&name,&previous,(void **)&other);
 } else if((unsigned char)arg->isInteger()) {
  ((SwapSprite*)cih->parent->rva006CFF40())->list->bfmeQuery1279(arg->toInteger(),0,&previous,(void **)&other);
 }
 if(other && ((AptValue*)other)->getIsDefined()) {
  int depth=((AptCIH*)((BfmeAptValue006DCD20*)other)->rva006DCF60(false))->depth;
  ((AptCIH*)((BfmeAptValue006DCD20*)other)->rva006DCF60(false))->depth=cih->depth;
  cih->depth=depth;
  sprite(cih->parent);bfmeUnlinkNestedBE((BfmeNestedBE*)other);
  sprite(cih->parent);bfmeUnlinkNestedBE((BfmeNestedBE*)cih);
  sprite(cih->parent)->list->rva006F6FB0(cih->depth,cih);
  sprite(cih->parent)->list->rva006F6FB0(other->depth,other);
  cih->changed();other->changed();
 } else if((unsigned char)arg->isInteger()) {
  sprite(cih->parent);bfmeUnlinkNestedBE((BfmeNestedBE*)cih);
  sprite(cih->parent)->list->rva006F6FB0(arg->toInteger(),cih);
  cih->changed();
 }
 return gpUndefinedValue;
}
