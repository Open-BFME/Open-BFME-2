// cl: /DNDEBUG /MD /EHsc
// Native ED580..ED769 (490B): the attachMovie callback. It reads the linkage
// id (stack argument 0), the new instance name (1), the depth (2) and, with
// four or more arguments, the init object (3); resolves the id against the
// receiver through the rowed rva006ED490 lookup (logging "Trying to
// attachMovie: '%s' could not be found." and returning undefined when it
// fails); then submits the found character under the new name through the
// pinned AptDisplayList submit 0x006F8B70 at depth + 0x4000 on the
// receiver's sprite instance (AptCIH.h 0x7D isSpriteInstBase assert) and
// ticks new instances on the Apt root (rowed _tickNewInsts). The new
// instance is returned; when none appears it logs both names and fires the
// AptCharacter.cpp 0x2CE "attachMovie Failed" assert, returning undefined.
// Retail text throughout; callback name address-derived.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
void __cdecl Rva006CC110Log(int level, const char *fmt, ...);

class AptCIH;
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
class Rva006CFCD0
{
public:
	bool isSpriteInstBase() const;
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
class AptAnimationPoolData {public:void _tickNewInsts();};
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
class Rva006ED490X;
class Rva006ED490Obj;
int rva006ED490(Rva006ED490X *x, Rva006ED490Obj *obj, char flag);
class BfmeSubmitter1283
{
public:
	void *bfmeSubmit1283(AptCIH *a1, int a2, int a3, int a4, int a5, int a6, int a7, float *a8, int a9, int a10, int a11, int a12);
};

struct Rva006ED580Inst { char m_pad[0x24]; BfmeSubmitter1283 m_displayList; };
struct Rva006ED580CIH
{
	char m_pad[0x4C];
	Rva006ED580Inst *m_inst;
	Rva006ED580Inst *spriteInst()
	{
		if (!((const Rva006CFCD0 *)this)->isSpriteInstBase()) {
			g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
		return m_inst;
	}
};

AptValue *__cdecl attachMovie(AptValue *self, int count)
{
	AptValue *idValue = g_aptDateInterpreter.stack.At(0);
	AptValue *nameValue = g_aptDateInterpreter.stack.At(1);
	AptValue *depthValue = g_aptDateInterpreter.stack.At(2);
	AptValue *initObject = count >= 4 ? g_aptDateInterpreter.stack.At(3) : 0;
	EAStringC id;
	idValue->toString(id);
	int found = rva006ED490((Rva006ED490X *)self->c_cih(false), (Rva006ED490Obj *)&id, 1);
	if (!found) {
		Rva006CC110Log(4, "Trying to attachMovie: '%s' could not be found.\n", id.rva00620090());
	} else {
		EAStringC name;
		nameValue->toString(name);
		Rva006ED580CIH *parent = (Rva006ED580CIH *)self->c_cih(false);
		void *created = parent->spriteInst()->m_displayList.bfmeSubmit1283(0,
			((BfmeAptValue006DCD20 *)depthValue)->toInteger() + 0x4000, found, (int)&name,
			(int)parent, 1, -1, 0, 0, 0, 0, (int)initObject);
		((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->_tickNewInsts();
		if (created)
			return (AptValue *)created;
		Rva006CC110Log(4, "MovieClip instance not found after Attach Movie\n");
		Rva006CC110Log(4, "Attaching: Item '%s' as '%s'.\n", id.rva00620090(), name.rva00620090());
		g_bfmeAptAssertAtE17734("false && \"attachMovie Failed see TTL for more info.\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp", 0x2CE);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	return gpUndefinedValue;
}
