// ?Rva006D5160Concat@@YA?AVEAStringC@@PBDABV1@@Z
// partial score=0.9121057118 date=2026-10-09
// cl: /O2 /DNDEBUG /MD /EHsc
// Native 006D5160..006D5291: concatenates a C string followed by EAStringC.
// WB17749C0 supplies algorithm guide. Native proves hidden return storage,
// copy constructor branches, the 8B header, and post-copy hash reset.
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" void *__cdecl memcpy(void*,const void*,unsigned int);
#pragma intrinsic(strlen,memcpy)
class EAStringC {
public:
 class StringDataC {public:unsigned short refs,size,maxSize,hash;};
 StringDataC *data;
 EAStringC(unsigned int);
 EAStringC(const char *s):data(0){Assign(s);}
 EAStringC(const EAStringC&);
 static void FreeData(StringDataC*);
 ~EAStringC(){FreeData(data);}
 void Assign(const char*);
 void SetSize(int);
 const char *buffer()const{return (const char*)data+8;}
 char *buffer(){return (char*)data+8;}
};
EAStringC Rva006D5160Concat(const char *left,const EAStringC &right){
 int rightSize=right.data->size;
 if(!rightSize)return EAStringC(left);
 unsigned int leftSize=strlen(left);
 if(!leftSize)return EAStringC(right);
 int fullSize=leftSize+rightSize;
 EAStringC result(fullSize);
 char *out=result.buffer();
 memcpy(out,left,leftSize);
 out+=leftSize;
 memcpy(out,right.buffer(),rightSize);
 out[rightSize]=0;
 result.SetSize(fullSize);result.data->hash=0;
 return EAStringC(result);
}
