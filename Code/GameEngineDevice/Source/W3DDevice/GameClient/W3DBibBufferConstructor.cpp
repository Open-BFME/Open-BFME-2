// cl: /O1 /DNDEBUG /MD /EHsc
class TextureClass { public: virtual void slot00(); unsigned short refCount, pad06; void Release_Ref(); };
template<class T> class RefCountPtr { public:
 RefCountPtr():Ptr(0) {}
 ~RefCountPtr() { if (Ptr) Ptr->Release_Ref(); }
 RefCountPtr const &operator=(RefCountPtr const &other);
 T *Ptr;
};
class BFME2ParticleTextureHandle { public:
 TextureClass *Ptr;
 ~BFME2ParticleTextureHandle() { if(Ptr) Ptr->Release_Ref(); }
};
extern BFME2ParticleTextureHandle __cdecl BFME2LoadParticleTexture(const char *,int,int);
class ShroudFilter { public: char pad[12]; int u,v; };
class ShroudTexture { public: ShroudFilter *getFilter(); };
struct TBib { TBib(); float corners[4][3]; bool highlight; int color; unsigned objectID, drawableID; bool unused; };
// ZH W3DBibBuffer.cpp (BF1 donor 575ba2b04) supplies the constructor purpose,
// texture names and clamp operations. BFME2 parent allocation at 0x6CC5C calls
// this body for its +385C bib owner and allocates 109D0 bytes. Native +10/+14
// are counted holders, unlike ZH raw pointers; the native array helper calls
// the already-owned 22B TBib constructor 1000 times with stride 68. The added
// two dwords at +20 are opaque: this constructor does not initialize them.
// All factory/assignment/filter/buffer/release callees are existing owners.
class W3DBibBuffer { public: W3DBibBuffer();
protected: void allocateBibBuffers();
 void *vertex; int vertexSize; void *index; int indexSize;
 RefCountPtr<TextureClass> bibTexture,highlight;
 int vertices,indices; char pad20[8]; TBib bibs[1000];
 int count; bool sorted; char pad109CD; bool initialized;
};
W3DBibBuffer::W3DBibBuffer() {
 initialized=false;
 vertex=0; index=0; vertices=0; indices=0;
 count=0; sorted=true;
 indexSize=384; vertexSize=256;
 allocateBibBuffers();
 bibTexture=(const RefCountPtr<TextureClass> &)BFME2LoadParticleTexture("TBBib.tga",0,0);
 highlight=(const RefCountPtr<TextureClass> &)BFME2LoadParticleTexture("TBRedBib.tga",0,0);
 ((ShroudTexture *)&bibTexture)->getFilter()->u=1;
 ((ShroudTexture *)&bibTexture)->getFilter()->v=1;
 ((ShroudTexture *)&highlight)->getFilter()->u=1;
 ((ShroudTexture *)&highlight)->getFilter()->v=1;
 initialized=true;
}
