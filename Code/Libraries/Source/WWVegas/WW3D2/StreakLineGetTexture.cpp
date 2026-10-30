// cl: /arch:SSE /G7 /EHsc /MD /DNDEBUG
// Donor: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d
// game/Libraries/Source/WWVegas/WW3D2/streak.cpp and the ZH streak.cpp.
// StreakLineClass::Get_Texture forwards to its line renderer.
// BFME2 0x00741750 returns an owning handle through a caller buffer. The
// renderer occupies +0x100, as the matched Reset_Line and Set_Texture prove.
// Native RET 4 at 0x0074176E completes the 33-byte body before INT3 padding.
// The owned renderer getter is 0x00191210; use its existing handle declaration.
// This prefix view is pointer-only; no allocation or complete size is asserted.
class TextureClass;
class ParticleBufferClass {
public:
 class TextureHandleClass {
 public:
  TextureClass *Ptr;
  TextureHandleClass();
  TextureHandleClass(const TextureHandleClass &);
  ~TextureHandleClass();
 };
};
class BFMELineRendererTexture {
 TextureClass *Texture;
public:
 ParticleBufferClass::TextureHandleClass Get_Texture() const;
};
class StreakLineClass {
 char beforeLineRenderer[0x100];
 BFMELineRendererTexture LineRenderer;
public:
 ParticleBufferClass::TextureHandleClass Get_Texture();
};
ParticleBufferClass::TextureHandleClass StreakLineClass::Get_Texture() {
 return ((BFMELineRendererTexture *)&LineRenderer)->Get_Texture();
}
