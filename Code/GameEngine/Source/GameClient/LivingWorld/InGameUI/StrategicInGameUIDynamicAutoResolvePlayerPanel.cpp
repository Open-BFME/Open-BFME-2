// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// Native005EAF19..005EB071,344B,RET20. WB015E4C90 names
// StrategicInGameUI::DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip.
// The existing OnPlayerPanelLoaded caller5EB0CB allocates40B and forwards
// Impl/side/index/unsigned level/AsciiString reference. Current master supplies
// movie-clip ctor5FBE0D and GetPlayerData5EA575; no new callee pins are used.
// Target establishes an8B counted base (folded tableBC6F20), movie clip at8,
// owner10,side14,index18,count1C,two image pointers20/24. The base's actual
// class name remains unknown; existing Rva0007DF07 is a structural ABI view.
// Player projections are access views only: name1C,color184,template40 and
// template image20; they do not assert the complete target class layouts.
// Canonical banner-global spelling/type is reused from data_ledger009FE32C;
// no new global name, data definition or address pin is introduced.
// Signed-key map payload is retained as int storage, as in the existing
// DynamicAutoResolveDialog maps; conversion to a banner-name pointer is
// evidenced by the native node14 load plus20. Cache the end iterator once
// before lower_bound(1), preserving retail's EDI node and dead argument homes.

#include <map>

// Preserve STLport's inlined walk without emitting a competing size-profile
// wrapper. stlport_map_int_int.cpp owns the complete retail entry at 0x169ED0.
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > > &
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > >::operator++()
{
    _M_node = _Rb_global_inst::_M_increment(_M_node);
    return *this;
}
}
#include "ascii_string.h"
#include "unicode_string.h"

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
#include "../../../../Include/Common/Rva0007DF07.h"
class Rva005FBBEE {public:Rva005FBBEE(unsigned,const AsciiString&);virtual ~Rva005FBBEE();private:void *impl;};
class Rva005FBBFC {public:void setPlayerName(const UnicodeString&);};
class Rva005FBB68 {public:void setPlayerColor(int);void rva005FBB55(float);};
class Image;
class ImageCollection {public:const Image *findImageByName(const AsciiString&);};
extern ImageCollection *TheMappedImageCollection;
class Rva005FB83E {public:void rva005FB83E(const Image*);};
class Rva005FBB96 {public:void rva005FBB96(int,const Image*);};
class BannerUI {public:const AsciiString&GetBannerIconImageName(const AsciiString&);};
extern BannerUI *TheBannerUI;
#include "../../../../../Libraries/Include/Lib/RGBColor.h"
struct PlayerView {char pad00[0x1c];UnicodeString name;char pad20[0x184-0x20];RGBColor color;};
struct PlayerTemplateView {char pad00[0x20];AsciiString image;};
struct PlayerFullView {char pad00[0x40];PlayerTemplateView *playerTemplate;};
struct MapEntryView { _STL::map<int,int> values;char pad[0x34-sizeof(_STL::map<int,int>)];};
struct MapsView {MapEntryView *first;};
struct PlayerDataView {PlayerView *player;int mapIndex;float a,remaining;};
namespace StrategicInGameUI {
class DynamicAutoResolveDialog {public:class Impl;};
class DynamicAutoResolveDialog::Impl {public:class PlayerPanelMovieClip;char pad00[0x10];MapsView *maps;int pad14;float total;};
class DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip: public Rva0007DF07,public Rva005FBBEE {
public:PlayerPanelMovieClip(Impl*,int,int,unsigned,const AsciiString&);virtual ~PlayerPanelMovieClip();int GetPlayerData();
private:Impl *owner;int side,index,count;const Image *banners[2];
};
DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip::PlayerPanelMovieClip(Impl *impl,int s,int i,unsigned level,const AsciiString &name):Rva005FBBEE(level,name),owner(impl),side(s),index(i) {
 count=0;for(const Image **p=banners;p!=banners+2;++p)*p=0;
 PlayerDataView *data=(PlayerDataView*)GetPlayerData();
 ((Rva005FBBFC*)static_cast<Rva005FBBEE*>(this))->setPlayerName(data->player->name);
 ((Rva005FBB68*)static_cast<Rva005FBBEE*>(this))->setPlayerColor(data->player->color.getAsInt()|0xff000000);
 PlayerTemplateView *pt=((PlayerFullView*)data->player)->playerTemplate;
 ((Rva005FB83E*)static_cast<Rva005FBBEE*>(this))->rva005FB83E(TheMappedImageCollection->findImageByName(pt->image));
 ((Rva005FBB68*)static_cast<Rva005FBBEE*>(this))->rva005FBB55(data->remaining/owner->total*100.0f);
 MapEntryView *entry=owner->maps->first+data->mapIndex;
 _STL::map<int,int>::iterator end=entry->values.end();
 for(_STL::map<int,int>::iterator it=entry->values.lower_bound(1);count<2 && it!=end;++it) {
  const AsciiString &bannerName=*(const AsciiString*)(it->second+0x20);
  banners[count]=TheMappedImageCollection->findImageByName(TheBannerUI->GetBannerIconImageName(bannerName));
  ((Rva005FBB96*)static_cast<Rva005FBBEE*>(this))->rva005FBB96(count,banners[count]);
  ++count;
 }
}
}
