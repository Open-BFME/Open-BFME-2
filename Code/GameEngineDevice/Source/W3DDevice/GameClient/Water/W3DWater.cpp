// cl: /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
// RenderableStandingWaterArea::createTexture: native 0x0007EDBC..0x0007EEB0,
// 244 bytes, RET4. WB 0x0073EFF0 identifies the method and W3DWater.cpp.
// Native calls and member accesses prove area+40, texture slots+50, and
// the 60/62/61 fallback order for slot zero. The matched river-water
// createTexture at 7EEBE supplies the loader's counted return lifetime.
// StringBase<char>'s canonical header owns isEmpty; the native string
// prefix read proves its shared-buffer data starts eight bytes later.
#include "string_base.h"
class Rva0030812E { public: void *rva0030812E(int index); };
enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };
class W3DRadarFormatCaps { public: bool supportTextureFormat(WW3DFormat format); };
class DX8Caps;
class DX8Wrapper {
 friend class RenderableStandingWaterArea;
protected:
 static DX8Caps *CurrentCaps;
};
class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
	int m_pad[2];
};

template <class T>
class RefCountPtr
{
public:
	const RefCountPtr &operator=(const RefCountPtr &other);
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

BFME2ParticleTextureHandle __cdecl BFME2LoadParticleTexture(const char *filename, int a, int b);


class RenderableStandingWaterArea {
public:
 void createTexture(int index);
private:
 char m_pad00[0x40];
 Rva0030812E *m_area;
 char m_unknown44[0x0c];
 BFME2ParticleTextureHandle m_textures[4];
};
void RenderableStandingWaterArea::createTexture(int index) {
 StringBase<char> *s=(StringBase<char>*)m_area->rva0030812E(index);
 if (!s->isEmpty()) {
  if (index == 0) {
   int format=0;
   if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3c)) format=0x3c;
   else if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3e)) format=0x3e;
   else if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3d)) format=0x3d;
   const char *data=*(const char *const *)s;
   m_textures[0] = BFME2LoadParticleTexture(data ? data+8 : "",1,format);
  } else {
   const char *data=*(const char *const *)s;
   m_textures[index] = BFME2LoadParticleTexture(data ? data+8 : "",0,0);
  }
 }
}
