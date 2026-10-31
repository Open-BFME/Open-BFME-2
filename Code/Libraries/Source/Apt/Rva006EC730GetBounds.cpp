// cl: /DNDEBUG /MD /EHsc
// Native C730..C8F1 (450B): the getBounds callback. More than one argument
// returns undefined; one argument names the target coordinate space (an
// undefined one returns undefined), otherwise the receiver's own. It builds a
// fresh object -- the inlined Rva006D6360(0x1B, 8) / Rva006D6470Owner
// construction (vtables 0x00CEA228 then 0x00CEA264) from the 0xE176F4 pool,
// freed through 0x006F12F0 on unwind -- fetches the receiver's bounds through
// the rowed rva006E1DD0, offsets them by the target's +0x1C/+0x20 position,
// and stores the four as floats under pool strings 0xAD, 0xAE, 0xB0 and 0xB1
// through the rowed AptNativeHash::Set. Callback name address-derived.
// Shape notes: the stores go through an inline member setter, so both
// argument calls are evaluated before either is pushed (retail's ebx temp and
// merged stack cleanup); the right edge is offset first as in retail.
// Private views only; the Rva006D6360 / Rva006D6470Owner bodies stay with
// their rowed out-of-line owners in Rva006D6360Ctor.cpp.
class AptCIH;
class EAStringC;
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
// Retail vtable 0x008EA228 starts with the rowed AptValue::AddRef (0x006DCAC0) and Release.
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
struct Rect {float left,top,right,bottom;};
AptValue *Rva008A4EA0MakeFloat(float);
class AptNativeHash {
public:
  int count;
  void *items;
  AptValue *proto, *prototype;
  unsigned events;
  AptNativeHash(int);
  ~AptNativeHash();
  void Set(const EAStringC *const,AptValue *const);
  static void *operator new(unsigned n);
  static void operator delete(void *p, unsigned n);
  void Set__Proto__(AptValue *value) {
    if (value)
      value->AddRef();
    if (proto)
      proto->Release();
    proto = value;
  }
};
class Rva006D2A60 {public:void *allocBlock(int);void freeBlock(void *,int);};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
void Rva006F12F0Free(void *,int);
EAStringC *Rva0070B4F0GetString(int);
class Rva006D6360 : public BfmeAptValue006DCD20
{
public:
 Rva006D6360(int type,int size) : BfmeAptValue006DCD20(type),m_hash(size) {}
 virtual ~Rva006D6360();
 AptNativeHash m_hash;
};
class Rva006D6470Owner : public Rva006D6360
{
public:
 Rva006D6470Owner(int type,int size) : Rva006D6360(type,size)
 {
  *(unsigned char *)&m_bits=0;
  m_bits&=0xFFFFFCFF;
 }
 virtual ~Rva006D6470Owner();
 static void *operator new(unsigned int n){return g_pChainBlockAllocatorF4->allocBlock(n);}
 static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
 void setMember(const EAStringC *name,AptValue *value){m_hash.Set(name,value);}
 unsigned int m_bits;
};
AptValue *__cdecl Rva006EC730GetBounds(AptValue *self,int count)
{
 if(count>1)return gpUndefinedValue;
 AptCIH *target=self->c_cih(false);
 if(count==1){
  AptValue *aptValue=g_aptDateInterpreter.stack.At(0);
  if(aptValue->isUndefined())return gpUndefinedValue;
  target=aptValue->c_cih(false);
 }
 Rva006D6470Owner *object=new Rva006D6470Owner(0x1B,8);
 Rect bounds;
 self->c_cih(false)->rva006E1DD0(&bounds);
 bounds.right-=((float *)target)[7];
 bounds.left-=((float *)target)[7];
 bounds.top-=((float *)target)[8];
 bounds.bottom-=((float *)target)[8];
 object->setMember(Rva0070B4F0GetString(0xAD),Rva008A4EA0MakeFloat(bounds.right));
 object->setMember(Rva0070B4F0GetString(0xAE),Rva008A4EA0MakeFloat(bounds.left));
 object->setMember(Rva0070B4F0GetString(0xB0),Rva008A4EA0MakeFloat(bounds.bottom));
 object->setMember(Rva0070B4F0GetString(0xB1),Rva008A4EA0MakeFloat(bounds.top));
 return (AptValue *)object;
}
