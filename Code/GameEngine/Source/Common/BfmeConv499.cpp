// cl: /O1 /MD /EHsc /DNDEBUG
// Existing EF966..EF981 27B owner initialized one owned texture word.
// Native6B3F3 constructs that frame object, passes its returned address to
// counted-holder assignment, then conditionally releases it under EH2.
// BFME1 f989 BaseHeightMapRva006CB080 supplies the owning-handle constructor
// relationship; the original class name and unused argument type are unknown.
// Keep an address-derived owner and a neutral one-word mip argument. Native
// ignores that argument; the shared132D89 loader receives exscorch01.tga.
// This replaces the old ordinary-method spelling, without a second name or
// new pin at EF966. Its full27B body and literal remain identical.
class BfmeThingBNH;
void bfmeDoBNH(BfmeThingBNH *,void *,int,int);
class TextureClass;
template<class T>class RefCountPtr{public:T*Referent;};
class Rva0006B3F3ScorchTexture:public RefCountPtr<TextureClass>{public:Rva0006B3F3ScorchTexture(int mipCount);};
Rva0006B3F3ScorchTexture::Rva0006B3F3ScorchTexture(int mipCount){bfmeDoBNH((BfmeThingBNH*)this,(char*)"exscorch01.tga",0,0);}
