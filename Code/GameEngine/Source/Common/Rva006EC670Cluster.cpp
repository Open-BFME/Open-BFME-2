// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Address-derived recovery of 0x006EC670 (116B), an Apt argument handler.
// Retail fetches interpreter-stack values At(0), At(1) and, when the int
// argument is >= 3, At(2); converts At(1) through the rowed
// BfmeAptValue::toInteger (0x006DD360) and adds 0x4000; then calls the
// interpreter method 0x007092F0 with (checkedCast, 0, checkedCast, At(0),
// size, At(2)) and returns the undefined singleton at 0x00E18078. The check
// cast 0x006DCF60 and At 0x006FE580 are rowed; 0x007092F0 is the rowed
// duplicate-movie-clip helper AptActionInterpreter::rva007092F0 (private,
// so this handler is its friend here). Identity of the handler is not proven.
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

// g_aptDateInterpreter: interpreter global at VA 0x00E182E0; the stack
// sub-object is at offset 0 (matched references already place it there).
extern AptActionInterpreter g_aptDateInterpreter;
// g_aptUndefinedAtE18078: the undefined-value singleton at VA 0x00E18078.
extern AptValue *gpUndefinedValue;

BfmeAptValue006DCD20 *rva006ec670(BfmeAptValue006DCD20 *pValue, int nParams)
{
	BfmeAptValue006DCD20 *p0 = g_aptDateInterpreter.stack.At(0);
	BfmeAptValue006DCD20 *p1 = g_aptDateInterpreter.stack.At(1);
	BfmeAptValue006DCD20 *p2 = (nParams >= 3) ? g_aptDateInterpreter.stack.At(2) : 0;
	int size = p1->toInteger() + 0x4000;
	g_aptDateInterpreter.rva007092F0((AptCIH *)pValue->rva006DCF60(false), 0,
		(AptValue *)pValue->rva006DCF60(false), (AptValue *)p0, size, (AptValue *)p2);
	return (*(BfmeAptValue006DCD20 * *)&gpUndefinedValue);
}
