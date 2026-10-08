// cl: /O1 /arch:SSE /G7 /MD /EHsc
// Reference: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DBibBuffer.cpp and
// its Zero Hour W3DBibBuffer.h declaration.
// Native D402E..D4078 RET0. ZH's named W3DBibBuffer cleanup and existing
// freeBibBuffers row identify the owner. Target-specific owning texture
// members supply EH cleanup absent from ZH's raw-pointer member view.
// The verified 28-byte wrapper at 665DB calls this destructor, tests flag bit
// zero, conditionally frees storage, and returns the original pointer.
// Prefix padding preserves only the evidenced +10/+14 ownership offsets;
// the remaining bib-array fields are unused by these bodies.
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
// ?W3DBibBufferDeleteAnchor absent-from-retail
// Ordinary delete forces MSVC to emit the native nonvirtual deleting wrapper.
void W3DBibBufferDeleteAnchor(W3DBibBuffer *p) { delete p; }
