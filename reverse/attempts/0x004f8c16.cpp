// ?inplaceMergeRva004F8C16@@YAXPAURva004F8C16Element@@000PAHURva004F8C16Cmp@@@Z
// partial score=0.99 date=2026-10-05
// cl: /O1 /MD /EHsc
// Ghidra[4F8C16,4F8C99),131B. STLport4.5.3 inplace_merge_aux semantic
// guide; native first/middle/last pointers imply4B elements, two unused
// dispatchpointer arguments and a byvalue empty comparator are present.
// Original element and comparator names remain unknown. Native51B
// buffer initialization4F77AD and independently matched33B destruction
// 4F77E0 prove the12B temporary layout: count4 and buffer8.
struct Rva004F8C16Element {char bytes[4];};
struct Rva004F8C16Cmp {};
class Rva004F60AA {
public:
 Rva004F60AA(char*,char*);
 ~Rva004F60AA();
 int originalLength,length;
 Rva004F8C16Element *buffer;
};
void mergeWithoutRva004F8C16(Rva004F8C16Element*,Rva004F8C16Element*,Rva004F8C16Element*,int,int,Rva004F8C16Cmp);
void mergeAdaptiveRva004F8C16(Rva004F8C16Element*,Rva004F8C16Element*,Rva004F8C16Element*,int,int,Rva004F8C16Element*,int,Rva004F8C16Cmp);
void inplaceMergeRva004F8C16(Rva004F8C16Element *first,Rva004F8C16Element *middle,Rva004F8C16Element *last,Rva004F8C16Element*,int*,Rva004F8C16Cmp comp)
{
 int len1=middle-first,len2=last-middle;
 Rva004F60AA tmp((char*)first,(char*)last);
 if (tmp.buffer==0)
  mergeWithoutRva004F8C16(first,middle,last,len1,len2,comp);
 else
  mergeAdaptiveRva004F8C16(first,middle,last,len1,len2,tmp.buffer,tmp.length,comp);
}
