// ??1W3DBibBuffer@@QAE@XZ
// partial score=1.0 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD /EHsc
// Native D402E..D4078 RET0. ZH's named W3DBibBuffer cleanup and existing
// freeBibBuffers row identify the owner. Target-specific owning texture
// members supply EH cleanup absent from ZH's raw-pointer member view.
class TextureBaseClass {public: void Release_Ref();};
struct Rva000D402ETextureHolder {
 TextureBaseClass *texture;
 ~Rva000D402ETextureHolder() {if (texture) texture->Release_Ref();}
};
class W3DBibBuffer {
public: ~W3DBibBuffer();
protected: void freeBibBuffers();
private:
 char unknown00[0x10];
 Rva000D402ETextureHolder texture10, texture14;
};
W3DBibBuffer::~W3DBibBuffer() { freeBibBuffers(); }
// ?Rva000D402EDelete absent-from-retail
void Rva000D402EDelete(W3DBibBuffer *p) { delete p; }
