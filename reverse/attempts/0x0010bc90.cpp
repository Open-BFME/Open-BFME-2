// ?getTexture@Rva0010BC90ShadowManager@@QAEPAVW3DShadowTexture@@PBD@Z
// partial score=0.95 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
#include "ascii_string.h"
class Rva000B3F84Pair { public: Rva000B3F84Pair() {} const char *m_ptr; int m_len; };
struct WinMainTitlePair : Rva000B3F84Pair { operator AsciiString(); Rva000B3F84Pair m_secondPair; };
Rva000B3F84Pair Rva00108B93Make(const char*);
WinMainTitlePair operator+(const Rva000B3F84Pair&,const char*);
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template<class T> class RefCountPtr { public: T *m_ptr; const RefCountPtr& operator=(const RefCountPtr&); ~RefCountPtr(){if(m_ptr)m_ptr->Release_Ref();} };
class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass> {};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char*,int,int);
namespace _STL { class ios_base { protected: void _M_clear_nothrow(int); }; }
class Rva0010BC90ShadowManager;
class ShroudFilter : public _STL::ios_base { friend class Rva0010BC90ShadowManager; public: unsigned prefix[3]; int addressU,addressV; };
class ShroudTexture { public: ShroudFilter *getFilter(); };
class HAnimClass;
class HAnimManagerClass { public: HAnimClass *Get_Anim(const char*); bool Add_Anim(HAnimClass*); };
class Rva007AE680Name { public: void setName(const char*); };
class W3DShadowTexture { public: W3DShadowTexture(); char prefix[0x30]; RefCountPtr<TextureClass> texture; char tail[0xa4-0x34]; };
class Rva0010BC90ShadowManager { public: char prefix[0x24c]; HAnimManagerClass *manager; W3DShadowTexture *getTexture(const char*); };
W3DShadowTexture *Rva0010BC90ShadowManager::getTexture(const char *name)
{
    AsciiString filename=Rva00108B93Make(name)+".tga";
    W3DShadowTexture *result=reinterpret_cast<W3DShadowTexture*>(manager->Get_Anim(filename.str()));
    if (!result) {
        BFME2ParticleTextureHandle texture=BFME2LoadParticleTexture(filename.str(),0,0);
        if(!texture.m_ptr) return 0;
        reinterpret_cast<ShroudTexture*>(&texture)->getFilter()->addressU=1;
        reinterpret_cast<ShroudTexture*>(&texture)->getFilter()->addressV=1;
        reinterpret_cast<ShroudTexture*>(&texture)->getFilter()->_M_clear_nothrow(0);
        result=new W3DShadowTexture;
        reinterpret_cast<Rva007AE680Name*>(result)->setName(filename.str());
        manager->Add_Anim(reinterpret_cast<HAnimClass*>(result));
        result->texture=texture;
    }
    return result;
}
