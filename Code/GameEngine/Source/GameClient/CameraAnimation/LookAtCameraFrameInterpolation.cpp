// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Native 540DCA..540E82184B and WB A9D800 establish the frame-channel wrapper.
// The24-byte frame has mode0, a12-byte coordinate at4 and scalar channels10/14.
// Constructing the result evaluates mode, scalar14, scalar10 and coordinates
// in native order. The existing providers retain their established ABI views;
// source frame and helper names are unknown. No reference donor was available.
struct Rva00540E9DSrc { int a,b,c; };
class Rva00540D94 {
public:
    Rva00540D94(const Rva00540E9DSrc &,float,float,int);
    int mode;
    Rva00540E9DSrc position;
    float scalar10,scalar14;
};
class CameraAnimationFrameData {
public:
    float doInterpolate(float,float *,int,float *,int,float *,int,float *,int);
    int mode;
};
class Rva005C71ADView {
public:
    void *rva005C71AD(void *,float,void *,void *,void *,void *,void *,void *,void *,void *);
    int mode;
};
Rva00540D94 Rva00540DCAGet(float t,Rva00540D94 *a,int ta,Rva00540D94 *b,int tb,Rva00540D94 *c,int tc,Rva00540D94 *d,int td)
{
    Rva00540E9DSrc position;
    return Rva00540D94(
        *(Rva00540E9DSrc *)((Rva005C71ADView *)b)->rva005C71AD(&position,t,&a->position,(void *)ta,&b->position,(void *)tb,&c->position,(void *)tc,&d->position,(void *)td),
        ((CameraAnimationFrameData *)b)->doInterpolate(t,&a->scalar10,ta,&b->scalar10,tb,&c->scalar10,tc,&d->scalar10,td),
        ((CameraAnimationFrameData *)b)->doInterpolate(t,&a->scalar14,ta,&b->scalar14,tb,&c->scalar14,tc,&d->scalar14,td),
        b->mode);
}

