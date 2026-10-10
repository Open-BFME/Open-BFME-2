// cl: /O2 /MD
// ?rva006E2560@AptCIH@@QAEXH@Z @0x006E2560 224B (includes jump table)
// Chain from 0x006CFCD0: AptCIH type-dispatch counter plus sprite tail.
// Evidence: pMCInfo assert line 0x931 via AptCIH.cpp string; type via rowed
// get 0x006DBB30 minus 0x0C with 7-way jump table; button case 0x0E calls rowed
// 0x006E1090 then rowed 0x006F7AF0; tail calls rowed isSpriteInstBase 0x006CFCD0
// twice with 0x7D AptCIH.h assert then rowed 0x006F7AF0 via +0x4C/+0x24.
// Caller 0x006F7B03. Prev/next Apt TUs use /O2 /MD.
// Retail table at RVA 0x006E2624 maps kinds 0x0C..0x12 to counter offsets
// 0x18, 0x04, 0x08, 0x10, 0x0C, 0x14, 0x00 respectively. These offsets
// are target evidence; the counters' semantic names remain unknown.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006DBB30SarDwordField
{
public:
	int get() const;
};

class Rva006CFCD0
{
public:
	bool isSpriteInstBase() const;
};

class Rva006F7AC0List
{
public:
	void rva006F7AF0(int arg);
};

struct AptMCInfo
{
	int m00;
	int m04;
	int m08;
	int m0c;
	int m10;
	int m14;
	int m18;
};

struct AptButtonPayload
{
	char m_pad[0x1c];
	Rva006F7AC0List *m_list;
};

struct AptTailBlock
{
	char m_pad[0x24];
	Rva006F7AC0List *m_list;
};


class EAStringC;
class AptValue {public:AptValue *findChild(const EAStringC *,AptValue *);};
class AptCIH;
class EAStringC { public: const char *rva00620090() const; unsigned short *data; };
struct AptFileRecord { int unknown0; int size; EAStringC name; };
struct AptFileSlot { AptFileRecord *file; };
struct AptAnimData { char pad[0x34]; AptFileSlot fileSlot; };
class AptCharacterInst { public: virtual void slot0(); virtual ~AptCharacterInst(); virtual void slot8(); };
class AptNativeHash { public: void ClearData(); };
class BfmeAptValue006DCD20 {
public:
 bool isUndefined() const;
 int rva006CBEE0(bool) const;
 int isScriptFunction() const;
 BfmeAptValue006DCD20 *rva006DCEE0();
 void setGCRootCount(unsigned int);
};
class Rva006DBB60ShrNAndField {public:int get() const;};
class Rva006E0DE0 {public:int rva006E0DE0(AptValue *);char data[8];};
class AptAnimationPoolData {public:void removeFromBIL(AptCIH *);};
class Rva006E3FF0Owner {public:void rva006E44F0(AptCIH *);};
class Rva006CD650 {public:void *rva006CD650();};
class AptDisplayList {public:void clear(bool);};
class Rva008981E0Value {public:int aptHasAll();};
class Rva006DBDB0DwordOrSetter {public:void apply();};
class AptValueVector {public:void ReleaseValues();void rva006E6C00(AptValue *);};
class CullableClass;
class CullSystemClass {protected:CullableClass *Get_First_Collected_Object_Internal();friend class AptCIH;};
class AptBasePtrStack {public:void rva006FE920();};
struct AptActionInterpreter {void callFunction(AptValue *,AptValue *,int);};
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValueVector *g_releaseVectorAtE17710;
extern AptValueVector *g_aptOptionalValueVector;
extern unsigned char g_00E18348;
extern AptValue *gpUndefinedValue;
class Rva006E34D0 {
public:
 AptCIH **array;int count;
 Rva006E0DE0 s8;
 char gap10[8];
 Rva006E0DE0 s18,s20,s28;
 char gap30[0x30];
 AptValue *v60,*v64;
};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
static __forceinline AptFileSlot *fileSlot(void *p) { AptFileSlot *slot=(AptFileSlot *)((char *)p+0x34); return slot; }
EAStringC *Rva0070B4F0GetString(int);
AptCIH *_AptGetAnimationAtLevel(int);
void Rva006CC110Log(int,const char *,...);
void Rva006CD200SetFlag();

class AptCIH
{
public:
	virtual void vtableSlot0();
	virtual void vtableSlot1();
	virtual void vtableSlot2();
	virtual AptNativeHash *nativeHash();
	virtual void vtableSlot4();
	virtual void vtableSlot5();
	virtual void clearNative(int);
	void *rva006E1090() const;
	void rva006E2560(int arg);
	void rva006E2690(int arg);
	bool queueClipEvents(int,int,int);
	AptValue *findChild(const EAStringC *,AptValue *);

private:
	unsigned char m_pad4[4];
	EAStringC name;
	unsigned char m_pad0c[0x38];
	void *m_44;
	AptCIH *m_parent;
	AptCharacterInst *m_4C;
	unsigned char m_pad2[12];
	int m_code;
};

void AptCIH::rva006E2560(int pMCInfoArg)
{
	AptMCInfo *pMCInfo = (AptMCInfo *)pMCInfoArg;
	if (pMCInfo == 0)
	{
		g_bfmeAptAssertAtE17734("pMCInfo", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x931);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	int kind = ((const Rva006DBB30SarDwordField *)this)->get();
	switch (kind - 0x0c)
	{
	case 0:
		pMCInfo->m18++;
		break;
	case 1:
		pMCInfo->m04++;
		break;
	case 2:
		pMCInfo->m08++;
		{
			void *btn = rva006E1090();
			Rva006F7AC0List **ppList = (Rva006F7AC0List **)((char *)btn + 0x1c);
			(*ppList)->rva006F7AF0(pMCInfoArg);
		}
		break;
	case 3:
		pMCInfo->m10++;
		break;
	case 4:
		pMCInfo->m0c++;
		break;
	case 5:
		pMCInfo->m14++;
		break;
	case 6:
		pMCInfo->m00++;
		break;
	default:
		break;
	}
	if (((const Rva006CFCD0 *)this)->isSpriteInstBase())
	{
		if (!((const Rva006CFCD0 *)this)->isSpriteInstBase())
		{
			g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7d);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		((AptTailBlock *)m_4C)->m_list->rva006F7AF0(pMCInfoArg);
	}
}

// Native6E2690..6E29F3 RET4 is867B. WB17949D0 ClearCIH in AptCIH.cpp
// supplies the teardown guide; retail independently establishes flags5C and
// character4C (WB has50). Sparse sets and globals use existing target owners.
// Original member identity remains address-derived; WB name is provenance.
void AptCIH::rva006E2690(int arg)
{
    if ((m_code & 0xC0000)==0x40000 || ((BfmeAptValue006DCD20 *)this)->isUndefined()) return;
    g_bfmeAptPtrAtE176D0->s8.rva006E0DE0((AptValue *)this);
    g_bfmeAptPtrAtE176D0->s28.rva006E0DE0((AptValue *)this);
    if (g_bfmeAptPtrAtE176D0->v60==(AptValue *)this)g_bfmeAptPtrAtE176D0->v60=gpUndefinedValue;
    if (g_bfmeAptPtrAtE176D0->v64==(AptValue *)this)g_bfmeAptPtrAtE176D0->v64=gpUndefinedValue;
    g_bfmeAptPtrAtE176D0->s18.rva006E0DE0((AptValue *)this);
    g_bfmeAptPtrAtE176D0->s20.rva006E0DE0((AptValue *)this);
    ((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->removeFromBIL(this);
    for(int i=0;i<g_bfmeAptPtrAtE176D0->count;++i) {
        if (g_bfmeAptPtrAtE176D0->array[i]==this) {
            g_bfmeAptPtrAtE176D0->array[i]->vtableSlot1();
            g_bfmeAptPtrAtE176D0->array[i]=g_bfmeAptPtrAtE176D0->array[g_bfmeAptPtrAtE176D0->count-1];
            --g_bfmeAptPtrAtE176D0->count;
        }
    }
    if (((Rva006DBB30SarDwordField *)this)->get()==0x12 && !((BfmeAptValue006DCD20 *)this)->isUndefined())
        ((Rva006E3FF0Owner *)g_bfmeAptPtrAtE176D0)->rva006E44F0(this);
    if (m_4C) {
        if ((unsigned char)arg==1 && ((Rva006DBB30SarDwordField *)this)->get()==0xD && !((BfmeAptValue006DCD20 *)this)->isUndefined()) {
            queueClipEvents(4,0,0);
            AptValue *child=((AptValue *)this)->findChild(Rva0070B4F0GetString(0x75),0);
            if (child && (unsigned char)((Rva006DBB60ShrNAndField *)child)->get() && (unsigned char)((BfmeAptValue006DCD20 *)child)->isScriptFunction()) {
                BfmeAptValue006DCD20 *fn=((BfmeAptValue006DCD20 *)child)->rva006DCEE0();
                g_aptDateInterpreter.callFunction((AptValue *)this,(AptValue *)fn,0);
                ((AptBasePtrStack *)&g_aptDateInterpreter)->rva006FE920();
            }
        }
        if (!g_00E18348 && (m_code&0xFFFF)>0 && (unsigned char)((BfmeAptValue006DCD20 *)this)->rva006CBEE0(false) && this!=_AptGetAnimationAtLevel(0)) {
            if (g_aptOptionalValueVector && !((Rva008981E0Value *)g_aptOptionalValueVector)->aptHasAll()) {
                ((AptDisplayList *)((char *)((Rva006CD650 *)this)->rva006CD650()+0x24))->clear(true);
                nativeHash()->ClearData();
                if (((CullSystemClass *)g_releaseVectorAtE17710)->Get_First_Collected_Object_Internal()) g_releaseVectorAtE17710->ReleaseValues();
                if ((m_code&0xFFFF)>0) {
                    m_code&=~0x10000;
                    clearNative(0);
                    AptFileRecord *record=fileSlot(((Rva006CD650 *)this)->rva006CD650())->file;
                    int size=record->size;
                    AptFileRecord *fileName=fileSlot(((Rva006CD650 *)this)->rva006CD650())->file;
                    Rva006CC110Log(3,"WARNING :: ANIMATION[name = %s  file = %s.swf  size = %d bytes] HAS %d EXTERNAL FUNCTION REFERENCES, THEREFORE IT WILL NOT BE REMOVED FROM MEMORY UNTIL THEY ARE REMOVED\n",name.rva00620090(),fileName->name.rva00620090(),size,m_code&0xFFFF);
                    Rva006CC110Log(3,"           REFER TO BUG253 ON COREFORGE FOR MORE INFORMATION [http://coreforge.eac.ad.ea.com/tracker/index.php?func=detail&aid=253&group_id=41&atid=247].  EVALUATION OF YOUR SWF FILES IS HIGHLY RECOMMENDED\n");
                    ((Rva006DBDB0DwordOrSetter *)this)->apply();
                    g_aptOptionalValueVector->rva006E6C00((AptValue *)this);
                    m_code=(m_code&~0x80000)|0x40000;
                    Rva006CD200SetFlag();
                    return;
                }
            } else {
                AptFileRecord *record=fileSlot(((Rva006CD650 *)this)->rva006CD650())->file;
                int size=record->size;
                    AptFileRecord *fileName=fileSlot(((Rva006CD650 *)this)->rva006CD650())->file;
                Rva006CC110Log(3,"WARNING :: ANIMATION[name = %s  file = %s.swf  size = %d bytes] HAS %d EXTERNAL FUNCTION REFERENCES.  THERE IS NO SPACE IS LEFT TO KEEP TRACK THEREFOR IT WILL BE REMOVED FROM MEMORY\n",name.rva00620090(),fileName->name.rva00620090(),size,m_code&0xFFFF);
                Rva006CC110Log(3,"           REFER TO BUG253 ON COREFORGE FOR MORE INFORMATION [http://coreforge.eac.ad.ea.com/tracker/index.php?func=detail&aid=253&group_id=41&atid=247].  EVALUATION OF YOUR SWF FILES IS HIGHLY RECOMMENDED\n");
                m_code=(m_code&~0x40000)|0x80000;
            }
        }
        ((BfmeAptValue006DCD20 *)this)->setGCRootCount(0);
        m_4C->slot0();m_4C->slot8();delete m_4C;m_4C=0;
    }
    m_code&=~0x10000;
    clearNative(0);
}
