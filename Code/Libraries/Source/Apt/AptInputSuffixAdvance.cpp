// cl: /O2 /G6 /DNDEBUG /MD
// Semantic guide: BFME1 f98983a7d game/Libraries/Source/Apt/AptInput.cpp,
// bfmeParseSuffix1285 and bfmeAdvance1285. Target parser6F97F0 uses the
// owned EAStringC emptiness/buffer/size getters and native isdigit/atoi thunks.
// Native advance6FA340 replaces donor fixed512 table with count8/capacityA/
// pointerC and current6C; CIH name8, state code via6E1F00 and event6FA100.
// Static parser remains in the callers' TU for MSVC's register convention.
extern "C" int __cdecl isdigit(int);
extern "C" int __cdecl atoi(const char*);
class EAStringC {void *data;public:bool IsEmpty()const;const char *rva00620090()const;unsigned int rva006D3750()const;};
class AptCIH {public:virtual void AddRef();virtual void Release();char unknown04[4];EAStringC name;void rva006E1F00(int);};
class Rva006FB860 {public:char unknown00[8];unsigned short count,capacity;AptCIH **entries;char unknown10[0x5C];AptCIH *current;void rva006FA100(AptCIH*,int);void rva006FA340();};
static __declspec(noinline) bool rva006F97F0Parse(EAStringC *value,int *first,int *second)
{
 if(value->IsEmpty())return false;
 const char *base=value->rva00620090();
 const char *cursor=base+value->rva006D3750()-1;
 if(!isdigit(*cursor))return false;
 while(isdigit(*cursor))--cursor;
 if(second)*second=atoi(cursor+1);
 if(*cursor--!='_')return false;
 if(!isdigit(*cursor))return false;
 while(isdigit(*cursor))--cursor;
 if(first)*first=atoi(cursor+1);
 return true;
}
void Rva006FB860::rva006FA340()
{
 int first,second;
 if(current && rva006F97F0Parse(&current->name,&first,&second))return;
 if(current) {current->rva006E1F00(1);rva006FA100(current,2);}
 if(current)current->Release();
 current=0;
 int seen=0;
 for(int i=0;i<capacity;++i) {
  if(seen==count)break;
  AptCIH *item=entries[i];
  if(item) {
   if(!item->name.IsEmpty() && rva006F97F0Parse(&entries[i]->name,&first,&second)) {
    current=entries[i];current->AddRef();break;
   }
   ++seen;
  }
 }
 if(current){current->rva006E1F00(2);rva006FA100(current,1);}
}
