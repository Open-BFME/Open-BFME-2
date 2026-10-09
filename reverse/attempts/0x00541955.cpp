// ?rva00541955@Rva00541579@@QAE?AVRva00540D94@@M@Z
// partial score=0.75 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ob0
struct Rva00540E9DSrc { int a,b,c; };
class Rva00540D94 {
public:
    Rva00540D94(const Rva00540D94 &);
    int mode;
    Rva00540E9DSrc position;
    float scalar10,scalar14;
};
Rva00540D94::Rva00540D94(const Rva00540D94 &other)
{
    int *dst=(int *)this;
    const int *src=(const int *)&other;
    for(int i=0;i<6;++i) dst[i]=src[i];
}
Rva00540D94 Rva00540DCAGet(float,Rva00540D94 *,int,Rva00540D94 *,int,Rva00540D94 *,int,Rva00540D94 *,int);
extern "C" __declspec(dllimport) double __cdecl floor(double);
struct BfmePod28 { int key; Rva00540D94 frame; };
class Rva00541579 {
public:
    bool rva00541579(int);
    Rva00540D94 rva00541955(float);
private:
    char listener00[16];
    BfmePod28 *begin10,*end14,*capacity18;
    int hint1C;
};
Rva00540D94 Rva00541579::rva00541955(float frame)
{
    if(frame<0.f) return begin10[0].frame;
    rva00541579((int)floor(frame));
    if((unsigned)hint1C>=(unsigned)(end14-begin10-1)) return begin10[hint1C].frame;
    BfmePod28 *current=begin10+hint1C;
    int nextKey=current[1].key;
    if(current->key==nextKey) return current->frame;
    frame=(frame-current->key)/(nextKey-current->key);
    BfmePod28 *previous=hint1C>0 ? begin10+hint1C-1 : current;
    BfmePod28 *after=(unsigned)(hint1C+2)<(unsigned)(end14-begin10) ? begin10+hint1C+2 : current+1;
    return Rva00540DCAGet(frame,&previous->frame,previous->key,&current->frame,current->key,&current[1].frame,nextKey,&after->frame,after->key);
}
