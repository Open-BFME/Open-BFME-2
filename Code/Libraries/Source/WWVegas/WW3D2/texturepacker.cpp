// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail 0x001711A6..0x00171522 (892 B): TexturePacker::UpdateResultTexture, named
// by the WorldBuilder twin A12EB0 (texturepacker.cpp). Target evidence: the whole
// native body, its 0x144 frame and EH state map, and the rowed callees it calls.
// Carried from the WB body: make_pair insert into the area multimap, skyline[0]
// only, side<<5 written per use, an inline null-guarded validity test, a bool
// clear flag, and a D3DX RECT built member by member from the packed rectangle.
// The area multimap is a real STLport multimap<unsigned,AssetReference>: its
// in-unit template bodies let the make_pair and value_type temporaries share
// retail's frame slots (address-derived views of the same callees do not).
// The receiver keeps the ledger's address-derived spelling.
#include <functional>
// less<unsigned> is the rowed vendored body at 0x00758C50; keep it inline here.
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(const unsigned int &x, const unsigned int &y) const { return x < y; }
}
#include <map>

class TextureClass {
public:
    void Release_Ref();
    void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this)+4); }
};
class TextureInitializationView {
public:
    virtual void slot0()=0; virtual void slot1()=0;
    virtual void slot2()=0; virtual void slot3()=0;
    virtual void slot4()=0; virtual void slot5()=0;
    virtual void slot6()=0; virtual void slot7()=0;
    virtual void slot8()=0; virtual void slot9()=0;
    virtual bool Is_Initialized() const=0;
};
class AssetReference {
public:
    TextureClass *object;
    AssetReference() : object(0) {}
    AssetReference(const AssetReference &assetReference) : object(assetReference.object) { if(object) object->Add_Ref(); }
    ~AssetReference() { if(object) object->Release_Ref(); }
    bool operator<(const AssetReference &a) const { return (unsigned)object < (unsigned)a.object; }
    bool Is_Initialized() const { if(object) return reinterpret_cast<TextureInitializationView *>(object)->Is_Initialized(); return false; }
};
struct Rva00170999Data { unsigned left,top,right,bottom; };
#include "../../../../GameEngine/Include/Common/Rva00170BFF.h"
class Rva001333C6 { public: void f(); };
struct IDirect3DBaseTexture8;
class TextureBaseClass {
public:
    int rva0013275A() const;
    int rva00132784() const;
    IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva00131DFC.h"
class W3DRadarResetSurface {
public:
    void *surface;
    ~W3DRadarResetSurface();
    void clear(bool);
};
#include "../../../../GameEngine/Include/Common/CursorTextureSlot.h"
struct RECT { long left,top,right,bottom; };
extern "C" long __stdcall D3DXLoadSurfaceFromSurface(void *,void *,const RECT *,void *,void *,const RECT *,unsigned,unsigned);
extern "C" long __stdcall D3DXFilterTexture(void *,void *,unsigned,unsigned);

// The native area-tree node factory at 0x00170B70 allocates 24 bytes and
// constructs its counted value at +0x10 through 0x00170A97. The default
// template copy here inlines that construction and differs from retail.
// Bind the existing rowed factory without changing the value's ownership.
class Rva00151DAB;
class Rva00170B19
{
public:
    void *rva00170B70(const Rva00151DAB &value);
};
typedef _STL::_Rb_tree<unsigned int, _STL::pair<const unsigned int, AssetReference>,
    _STL::_Select1st<_STL::pair<const unsigned int, AssetReference> >,
    _STL::less<unsigned int>, _STL::allocator<_STL::pair<const unsigned int, AssetReference> > > AreaTree;
namespace _STL {
// This forwarding view is inline-only; it emits no standalone body.
// The real 34-byte factory remains rowed under Rva00170B19 above.
// ?_STL::AreaTree::_M_create_node absent-from-retail
template <> __declspec(dllimport) __forceinline AreaTree::_Link_type
AreaTree::_M_create_node(const AreaTree::value_type &value)
{
    return reinterpret_cast<AreaTree::_Link_type>(
        reinterpret_cast<Rva00170B19 *>(this)->rva00170B70(
            reinterpret_cast<const Rva00151DAB &>(value)));
}
}

typedef _STL::map<AssetReference,Rva00170999Data> RectangleMap;
typedef _STL::multimap<unsigned,AssetReference> AreaMap;
// The tree's destructor is the rowed /EHs body at 0x00170D7F (it resets the EH
// state before freeing the header); this /EHsc unit's copy would not.
namespace _STL { template <> _Rb_tree<unsigned int, pair<const unsigned int, AssetReference>, _Select1st<pair<const unsigned int, AssetReference> >, less<unsigned int>, allocator<pair<const unsigned int, AssetReference> > >::~_Rb_tree(); }
class Rva00171024 {
public:
    void UpdateResultTexture();
    unsigned maxSize;
    unsigned format;
    RectangleMap rectangles;
    RectangleMap::iterator current;
    AssetReference result;
    bool dirty;
    bool blackWhite;
    float inverseWidth,inverseHeight;
};

// Packs every texture into a square atlas, largest area first, on a skyline of
// 32-pixel cells, then rebuilds the result texture and copies each texture in.
void Rva00171024::UpdateResultTexture()
{
    dirty=false;
    reinterpret_cast<Rva001333C6 *>(&result)->f();
    inverseWidth=inverseHeight=1.0f;
    AreaMap byArea;
    for(RectangleMap::iterator it=rectangles.begin(); it!=rectangles.end(); ++it) {
        const TextureBaseClass *texture=reinterpret_cast<const TextureBaseClass *>(&it->first);
        unsigned area=texture->rva0013275A()*texture->rva00132784();
        byArea.insert(_STL::make_pair(area,it->first));
    }
    int side=1;
    int skyline[64];
    skyline[0]=0;
    for(AreaMap::reverse_iterator it=byArea.rbegin(); it!=byArea.rend(); ++it) {
        AssetReference texture(it->second);
        TextureBaseClass *handle=reinterpret_cast<TextureBaseClass *>(&texture);
        int width=((unsigned)handle->rva0013275A()+31u)>>5;
        int height=((unsigned)handle->rva00132784()+31u)>>5;
        for(;;) {
            int placementRow;
            for(placementRow=0; placementRow<=side-height; ++placementRow) {
                int j;
                for(j=0; j<height; ++j)
                    if(skyline[placementRow+j]+width>side) break;
                if(j==height) break;
            }
            if(placementRow>side-height) {
                if((unsigned)(side*2*32)>maxSize) return;
                for(int newSkylineRow=side; newSkylineRow<side*2; ++newSkylineRow) skyline[newSkylineRow]=0;
                side*=2;
            } else {
                int placementColumn=0;
                for(int j=0; j<height; ++j) if(skyline[placementRow+j]>placementColumn) placementColumn=skyline[placementRow+j];
                for(int j=0; j<height; ++j) skyline[placementRow+j]=placementColumn+width;
                Rva00170999Data *rect=reinterpret_cast<Rva00170BFF *>(&rectangles)->rva00171128(texture);
                rect->left=placementColumn<<5;
                rect->top=placementRow<<5;
                rect->right=rect->left+handle->rva0013275A();
                rect->bottom=rect->top+handle->rva00132784();
                break;
            }
        }
    }
    reinterpret_cast<Rva00131DFC *>(&result)->rva00131DFC((void *)(side<<5),(void *)(side<<5),(void *)format,0,1,0);
    if(!result.Is_Initialized()) return;
    inverseWidth=inverseHeight=1.0f/(side<<5);
    W3DRadarResetSurface destination=reinterpret_cast<CursorTextureSlot *>(&result)->Get_Surface_Level();
    destination.clear(blackWhite);
    for(RectangleMap::iterator it=rectangles.begin(); it!=rectangles.end(); ++it) {
        AssetReference texture(it->first);
        const Rva00170999Data &packed=it->second;
        RECT rect;
        rect.left=packed.left;
        rect.top=packed.top;
        rect.right=packed.right;
        rect.bottom=packed.bottom;
        W3DRadarResetSurface source=reinterpret_cast<CursorTextureSlot *>(&texture)->Get_Surface_Level();
        D3DXLoadSurfaceFromSurface(destination.surface,0,&rect,source.surface,0,0,1,0);
    }
    D3DXFilterTexture(reinterpret_cast<TextureBaseClass *>(&result)->Peek_D3D_Base_Texture(),0,~0u,~0u);
}
