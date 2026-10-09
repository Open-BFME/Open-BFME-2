// ?ShowBanner@Impl@DynamicAutoResolvePlayerPanelMovieClip@StrategicHUD@@QAEXHPBVImage@@@Z
// partial score=0.98 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
class Image;
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
int __cdecl Rva00577C23AptCall(Rva00222A8BTarget *, void *, const char *, const char *, int *, bool *);
class Rva00524306 {
public:
 void rva00524306(const StringBase<char> &);
 void rva00524725(const AsciiString &, const Image *);
private: char storage[12];
};
namespace StrategicHUD {
class DynamicAutoResolvePlayerPanelMovieClip { public: class Impl; };
class DynamicAutoResolvePlayerPanelMovieClip::Impl {
public: void ShowBanner(int bannerSlot, const Image *image);
private:
 char pad00[4]; unsigned int level; StringBase<char> name;
 char pad0c[0x18-0x0c]; Rva00524306 images;
 char pad24[0x3c-0x24];
 struct Banner { const Image *image; bool visible; char pad05[3]; } banners[2];
};
void DynamicAutoResolvePlayerPanelMovieClip::Impl::ShowBanner(int bannerSlot,const Image *image) {
 Banner &banner=banners[bannerSlot];
 if(image!=banner.image) {
  AsciiString key;
  key.format("_level%u.%s_Banner%d", level, name.str(), bannerSlot);
  if(image) images.rva00524725(key,image);
  else images.rva00524306(*(const StringBase<char> *)&key);
  banner.image=image;
 }
 if(!banner.visible) {
  bool show=true;
  Rva00577C23AptCall(TheRva00222A8BTarget,(void *)level,name.str(),"SetBannerVisibility",&bannerSlot,&show);
  banner.visible=true;
 }
}
}
