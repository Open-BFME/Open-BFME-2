// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Native5EFF60..5EFF68 complete8B: wrapper forwards count through field4
// to canonical StrategicHUD::RegionDetailsArmiesMovieClip::Impl::SetIconSlotCount.
// stlport
#include "RegionDetailsArmiesClipImplView.h"
class Rva005EFF60 {public:void rva005EFF60(int);private:char unknown00[4];StrategicHUD::RegionDetailsArmiesMovieClip::Impl *impl;};
void Rva005EFF60::rva005EFF60(int count){impl->SetIconSlotCount(count);}
