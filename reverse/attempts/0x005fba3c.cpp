// ?ShowBanner@Impl@DynamicAutoResolvePlayerPanelMovieClip@StrategicHUD@@QAEXHPBVImage@@@Z
// partial score=0.995 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

class Image;
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00577C23AptCall(Rva00222A8BTarget *,void *,const char *,const char *,int *,bool *);

class Rva00524306 {
public:
    void rva00524306(const StringBase<char> &);
    void rva00524725(const AsciiString &,const Image *);
private:
    void *m_start,*m_finish,*m_end;
};

namespace StrategicHUD {
class DynamicAutoResolvePlayerPanelMovieClip { public: class Impl; };
}
class StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl {
public:
    void ShowBanner(int slot,const Image *image);
    void HideBanner(int slot);
private:
    void *m_owner;
    int m_level;
    AsciiString m_name;
    char m_pad0C[0x18-0x0C];
    Rva00524306 m_images;
    char m_pad24[0x3C-0x24];
    struct Banner { const Image *image; bool visible; char pad[3]; } m_banners[2];
};
void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::ShowBanner(int slot,const Image *image)
{
    Banner *banner=&m_banners[slot];
    if(image!=banner->image){
        AsciiString key;
        key.format("_level%u.%s_Banner%d",m_level,m_name.str(),slot);
        if(image) m_images.rva00524725(key,image);
        else m_images.rva00524306(*(const StringBase<char> *)&key);
        banner->image=image;
    }
    if(!banner->visible){
        bool visible=true;
        Rva00577C23AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,(void *)m_level,m_name.str(),"SetBannerVisibility",&slot,&visible);
        banner->visible=true;
    }
}
void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::HideBanner(int slot)
{
    Banner *banner=&m_banners[slot];
    if(!banner->visible) return;
    bool visible=false;
    Rva00577C23AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,(void *)m_level,m_name.str(),"SetBannerVisibility",&slot,&visible);
    banner->visible=false;
}
class Rva005FBB9E {
public: void rva005FBB9E(int slot);
private: char m_pad[4]; StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl *m_member;
};
void Rva005FBB9E::rva005FBB9E(int slot) { m_member->HideBanner(slot); }
