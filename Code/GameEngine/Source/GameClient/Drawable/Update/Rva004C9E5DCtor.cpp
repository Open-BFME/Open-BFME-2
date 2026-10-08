// Retail 0x004C9E5D..0x004C9E94; RET8 and return-this. Caller 0x004CA53C.
// The 168-byte animation key has ID0 / reference4 / frame8 / two 76-byte masks
// at +0xC and +0x58 / byte +0xA4. The default reference constructor is inline:
// it zeroes +4 and preserves the native ID store before mask initialization.
// Rva004C9E94 independently proves these offsets; the mask ctor is rowed.
// cl: /O1 /G7 /arch:SSE /EHsc /MD
class Rva0042526Member { public: Rva0042526Member(); unsigned int words[19]; };
// ?AnimationSoundNullRef::AnimationSoundNullRef present-unmatched
struct AnimationSoundNullRef { void*owner; __forceinline AnimationSoundNullRef():owner(0){} };
class Rva004C9E5D { public: Rva004C9E5D(const int*,float); int id; AnimationSoundNullRef sound; float frame; Rva0042526Member required,prohibited; unsigned char conditional; };
Rva004C9E5D::Rva004C9E5D(const int*p,float f):id(*p),sound(),frame(f),required(),prohibited(),conditional(0){}
