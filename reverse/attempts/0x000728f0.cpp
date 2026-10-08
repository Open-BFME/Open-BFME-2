// ?ReAcquireResources@W3DShroud@@QAEEXZ
// partial score=0.9 date=2026-10-08
// cl: /O1 /G7 /MD /EHsc /DNDEBUG
// BFME1 W3DShroudBfme.cpp@34f59164 guide; BFME2 native728F0..72988.
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
struct BFMEDX8DeviceLock { BFMEDX8DeviceLock(){BFME_DX8_Thread_Lock();} ~BFMEDX8DeviceLock(){BFME_DX8_Thread_Assert();} };
class BfmeResetResource;
struct BfmeResetTextureRef { BfmeResetResource *pointer; void clear(); };
class Rva00131DFC { public: void rva00131DFC(void*,void*,void*,void*,int,int); };
struct IDirect3DBaseTexture8;
class TextureBaseClass { public: IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const; };
class ShroudFilter { public: int minFilter,magFilter,mipFilter,uAddress,vAddress; __declspec(noinline) void setMipMapping(int); };
class ShroudTexture { public: ShroudFilter *getFilter(); };
class W3DShroud { public:
 unsigned char ReAcquireResources();
 int width,height,maxWidth,maxHeight;float cellWidth,cellHeight;void *shroudData;
 BfmeResetTextureRef texture;int textureWidth,textureHeight,filter;float originX,originY;
 unsigned char drawFog,clearTexture;
};
unsigned char W3DShroud::ReAcquireResources()
{
 if (!textureWidth) return 1;
 bool success;
 {
 BFMEDX8DeviceLock lock;
 success=true;
 ((Rva00131DFC *)&texture)->rva00131DFC((void*)textureWidth,(void*)textureHeight,(void*)0x1A,(void*)1,1,0);
 if (!((TextureBaseClass *)&texture)->Peek_D3D_Base_Texture()) {
  texture.clear();textureWidth=0;textureHeight=0;success=0;
 } else {
  ((ShroudTexture *)&texture)->getFilter()->uAddress=1;
  ((ShroudTexture *)&texture)->getFilter()->vAddress=1;
  ((ShroudTexture *)&texture)->getFilter()->setMipMapping(0);
  clearTexture=1;
 }
 }
 return success;
}
void ShroudFilter::setMipMapping(int value) { mipFilter=value; }
