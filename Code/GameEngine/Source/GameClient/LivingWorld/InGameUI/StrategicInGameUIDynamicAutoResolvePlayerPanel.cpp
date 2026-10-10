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
#include "ascii_string.h"
#include "unicode_string.h"
class Rva0007DF07 {public:__forceinline Rva0007DF07():zero(0){} virtual ~Rva0007DF07(){} private:void *zero;};
class Rva005FBBEE {public:Rva005FBBEE(unsigned,const AsciiString&);virtual ~Rva005FBBEE();private:void *impl;};
class Rva005FBBFC {public:void rva005FBBFC(const UnicodeString&);};
class Rva005FBB68 {public:void rva005FBB4D(int);void rva005FBB55(float);};
class Image;
class ImageCollection {public:const Image *findImageByName(const AsciiString&);};
extern ImageCollection *TheMappedImageCollection;
class Rva005FB83E {public:void rva005FB83E(const Image*);};
class Rva005FBB9E {public:void rva005FBB96(int,int);};
class BannerUI {public:const AsciiString&GetBannerIconImageName(const AsciiString&);};
extern BannerUI *g_00DFE32C;
class RGBColor {public:int getAsInt()const;float r,g,b;};
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
DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip::PlayerPanelMovieClip(Impl *o,int s,int i,unsigned level,const AsciiString &name):Rva005FBBEE(level,name),owner(o),side(s),index(i) {
 count=0;for(const Image **p=banners;p!=banners+2;++p)*p=0;
 PlayerDataView *data=(PlayerDataView*)GetPlayerData();
 ((Rva005FBBFC*)static_cast<Rva005FBBEE*>(this))->rva005FBBFC(data->player->name);
 ((Rva005FBB68*)static_cast<Rva005FBBEE*>(this))->rva005FBB4D(data->player->color.getAsInt()|0xff000000);
 PlayerTemplateView *pt=((PlayerFullView*)data->player)->playerTemplate;
 ((Rva005FB83E*)static_cast<Rva005FBBEE*>(this))->rva005FB83E(TheMappedImageCollection->findImageByName(pt->image));
 ((Rva005FBB68*)static_cast<Rva005FBBEE*>(this))->rva005FBB55(data->remaining/owner->total*100.0f);
 MapEntryView *entry=owner->maps->first+data->mapIndex;
 _STL::map<int,int>::iterator end=entry->values.end();
 for(_STL::map<int,int>::iterator it=entry->values.lower_bound(1);count<2 && it!=end;++it) {
  const AsciiString &bannerName=*(const AsciiString*)(it->second+0x20);
  banners[count]=TheMappedImageCollection->findImageByName(g_00DFE32C->GetBannerIconImageName(bannerName));
  ((Rva005FBB9E*)static_cast<Rva005FBBEE*>(this))->rva005FBB96(count,(int)banners[count]);
  ++count;
 }
}
}
