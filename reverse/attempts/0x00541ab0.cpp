// ?rva00541AB0@Rva005418CB@@QAE?AVRva00540E9D@@M@Z
// partial score=0.870761 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ob1
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct Region2D{Region2D(const Region2D&)throw();float lower[2],upper[2];};
struct Rva00540E9DSrc{int a,b,c;};
class Rva00540E9D {
public:
    __forceinline Rva00540E9D(const Rva00540E9D &other){((Region2D*)this)->Region2D::Region2D(*(const Region2D*)&other);}
    int mode;
    Rva00540E9DSrc position;
};
class Rva005C71ADView;
Rva00540E9D rva00540EBD(float,void*,void*,Rva005C71ADView*,void*,void*,void*,void*,void*);
extern "C" __declspec(dllimport) double __cdecl floor(double);
struct CameraKey20 { int key; Rva00540E9D frame; };
class Rva005418CB {
public:
 bool rva00541641(int);
    
    Rva00540E9D rva00541AB0(float);
private:
    char listener00[16];
    CameraKey20 *begin10,*end14,*capacity18;
    int hint1C;
};
Rva00540E9D Rva005418CB::rva00541AB0(float frame)
{
    if(frame<0.f) return begin10[0].frame;
    rva00541641((int)floor(frame));
    if((unsigned)hint1C>=(unsigned)(*(CameraKey20 *volatile*)&end14-*(CameraKey20 *volatile*)&begin10-1)) return begin10[hint1C].frame;
    CameraKey20 *current=begin10+hint1C;
    int nextKey=current[1].key;
    if(current->key==nextKey) return current->frame;
    frame=(frame-current->key)/(nextKey-current->key);
    CameraKey20 *previous=hint1C>0 ? begin10+hint1C-1 : current;
    _ReadWriteBarrier();CameraKey20 *after=(unsigned)(hint1C+2)<(unsigned)(*(CameraKey20 *volatile*)&end14-*(CameraKey20 *volatile*)&begin10) ? begin10+hint1C+2 : current+1;
    return rva00540EBD(frame,&previous->frame,(void*)previous->key,(Rva005C71ADView*)&current->frame,(void*)current->key,&current[1].frame,(void*)nextKey,&after->frame,(void*)after->key);
}
