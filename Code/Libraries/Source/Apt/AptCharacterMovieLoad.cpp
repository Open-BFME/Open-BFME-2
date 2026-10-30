// cl: /O2 /DNDEBUG /MD /EHsc
// The loadMovie/unloadMovie callbacks moved out of AptCharacterByteCounts.cpp:
// both call AptLinker::Load (0x006D1F80, matched in AptLoad.cpp) and stay apart
// from the byte-count and display callbacks.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class AptCIH;
class EAStringC;
class Rva006DBB30SarDwordField
{
public:
	int get() const;
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
};

class AptCIH
{
public:
    unsigned char prefix[0x4c];
    void *member4C;
    char unknown50[8];
    signed int depth:17;
    unsigned int unknownDepth17:15;
    void rva006E1DD0(void *);
    void *rva006E1170() const;
};

class EAStringC
{
public:
    class StringDataC
    {
    public:
        unsigned short m_uRefCount;
        unsigned short m_uSize;
        unsigned short m_uMaxSize;
        unsigned short m_uHash;
    };
private:
    StringDataC *data;
public:
    EAStringC();
    EAStringC(const char *);
    EAStringC(const EAStringC &);
    EAStringC &clear();
    EAStringC &operator=(const EAStringC&);
    ~EAStringC();
    EAStringC &Rva006D4F00Append(const EAStringC &other);
    const char *rva00620090() const;
    int GetAt(int) const;
    unsigned int rva006D3750() const;
    int rva006D54B0(int,int);
};
extern EAStringC::StringDataC g_eaEmptyStringData;
// Native callers invoke this 16-byte constructor at 0x006D2F90, folded with
// clear; it roots the string at the empty singleton (RVA 0x009DC020 / VA
// 0x00DDC020) and takes one reference. Keep the native call boundary.
__declspec(noinline) inline EAStringC::EAStringC()
{
    data = &g_eaEmptyStringData;
    ++data->m_uRefCount;
}

class AptBasePtrStack {public:AptValue *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;void loadVariables(AptValue *,AptValue *,const EAStringC *);};
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;

// Native C590..C669: Ghidra-unlisted callback after the rowed release worker.
// Asserts nParams == 0 (AptCharacter.cpp 0x320, retail text), reads the
// receiver's URL through the rowed rva006ffce0 name worker and asks the Apt
// linker (rowed AptLinker::Load) to load an empty movie over that target:
// the unloadMovie shape. Callback name remains address-derived.
class AptLinker {public:void Load(const EAStringC &a,EAStringC b);};
extern AptLinker *g_bfmeAptLinkerAtE176F8;
void rva006ffce0(AptValue *,EAStringC &);
void __debugbreak();
#pragma intrinsic(__debugbreak)
AptValue *Rva006EC590UnloadMovie(AptValue *self,int nParams){
 if(!(nParams==0)){
  g_bfmeAptAssertAtE17734("nParams == 0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",0x320);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 AptCIH *cih=self->c_cih(false);
 EAStringC url;
 rva006ffce0((AptValue *)cih,url);
 g_bfmeAptLinkerAtE176F8->Load(EAStringC(""),url);
 return gpUndefinedValue;
}

// Native C3E0..C589: Ghidra-unlisted callback before unloadMovie. Asserts
// nParams == 1 (AptCharacter.cpp 0x2ED, retail text) and converts stack
// argument 0 to a URL. An empty URL, or one ending in ".swf" by retail's
// character tests (the upper-case alternatives re-test the last character,
// as native), is loaded: a copy with the four-character extension removed
// (rowed rva006D54B0) is the movie, the receiver's name from the rowed
// rva006ffce0 is the target, and both go to the rowed AptLinker::Load: the
// loadMovie shape. Callback name remains address-derived.
AptValue *Rva006EC3E0LoadMovie(AptValue *self,int nParams){
 AptValue *aptValue=g_aptDateInterpreter.stack.At(0);
 if(!(nParams==1)){
  g_bfmeAptAssertAtE17734("nParams == 1","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",0x2ED);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 EAStringC url;
 aptValue->toString(url);
 int length=url.rva006D3750();
 if(length==0 ||
  ((url.GetAt(length-1)=='f' || url.GetAt(length-1)=='F') &&
   (url.GetAt(length-2)=='w' || url.GetAt(length-1)=='W') &&
   (url.GetAt(length-3)=='s' || url.GetAt(length-1)=='S') &&
   url.GetAt(length-4)=='.')){
  EAStringC movie;
  movie=url;
  if(length>=4)
   movie.rva006D54B0(length-4,4);
  rva006ffce0((AptValue *)self->c_cih(false),url);
  g_bfmeAptLinkerAtE176F8->Load(movie,url);
 }
 return gpUndefinedValue;
}
