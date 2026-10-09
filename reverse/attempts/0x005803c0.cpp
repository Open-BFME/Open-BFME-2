// ?compareRva005803C0@Rva000795C1Record@@QBE_NPAX0@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Native005803C0..0058062B RET8 and existing Rva000795C1Record sort callers establish the 16B receiver and two pointer ABI.
// Target direct GameInfo::getMap call proves that family; metric08/09/21 and tag5C remain opaque.
// ZH LobbyUtils GameSortStruct supplies the general name/metric sorting purpose, not the target key mapping.
// Target keys1/2/4/8/16 and direction bit10000, second-key and stable pointer fallback come from the native body.
// Helper109 declaration follows independently verified SN5 work; provider is not yet published locally.
// Best616B reproduces all instruction forms but places shared SETL tail after the cases rather than inside case4 (native619).
#include "ascii_string.h"
#include "unicode_string.h"
#include <string.h>
#include <wchar.h>
class GameInfo {
public:
 virtual void v00();virtual void v01();virtual void v02();virtual void v03();
 virtual void v04();virtual void v05();virtual void v06();virtual void v07();
 virtual int metric08();virtual int metric09();
 virtual void v10();virtual void v11();virtual void v12();virtual void v13();
 virtual void v14();virtual void v15();virtual void v16();virtual void v17();
 virtual void v18();virtual void v19();virtual void v20();virtual int metric21();
 virtual UnicodeString gameName();
 AsciiString getMap() const;
 unsigned tag()const{return word5C;}
 char pad04[0x5C-4];unsigned word5C;
};
class Rva005801F6Probe;
class Rva005801F6 {public:void rva005801F6(Rva005801F6Probe*,Rva005801F6Probe*);};
class Rva00580316 {
public: char pad00[12];int primarySort,secondarySort,word14,statusSort;
};
class Rva000795C1Record {
 const Rva00580316 *key;
 int *first,*last,*end;
public:
 Rva000795C1Record(const Rva000795C1Record &);

 bool compareRva005803C0(void *,void *) const;
};
bool Rva000795C1Record::compareRva005803C0(void *lhs,void *rhs) const {
 GameInfo *a=(GameInfo*)lhs,*b=(GameInfo*)rhs;
 int diff09=a->metric09()-b->metric09();
 int diff08=a->metric08()-b->metric08();
 int names=_wcsicmp((const wchar_t*)a->gameName().str(),(const wchar_t*)b->gameName().str());
 int diff21=a->metric21()-b->metric21();
 int maps=a->tag()==b->tag()?_strcmpi(a->getMap().str(),b->getMap().str()):0;
 reinterpret_cast<Rva005801F6 *>(const_cast<Rva000795C1Record *>(this))->rva005801F6(reinterpret_cast<Rva005801F6Probe *>(a),reinterpret_cast<Rva005801F6Probe *>(b));
 int mode=key->primarySort;
 for(int pass=0;pass<2;++pass,mode=key->secondarySort) {
  bool descending=(mode&0x10000)==0x10000;
  switch(mode&~0x10000) {
   case 16:for(int *it=first;it!=last;++it){int value=*it;if(value)return value>0;}break;
   case 8:if(diff21)return descending?diff21>0:diff21<0;break;
   case 4:if(diff09)return descending?diff09>0:diff09<0;
          if(diff08)return diff08<0;break;
   case 2:if(maps)return descending?maps>0:maps<0;break;
   case 1:if(names)return descending?names>0:names<0;break;
  }
 }
 if(names)return names<0;
 if(diff09)return diff09<0;
 if(maps)return maps<0;
 if(diff21)return diff21<0;
 return a<b;
}
