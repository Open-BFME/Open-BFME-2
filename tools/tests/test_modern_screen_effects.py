"""Native execution of the actual crossfade update and pre-render bodies."""
import os

import pytest
from test_modern_camera import function_body, run_native_harness
import build


@pytest.mark.skipif(os.name != "nt", reason="native Windows effect harness")
def test_motion_blur_fixed_update_handles_missing_filter_and_completion(tmp_path):
    source = build.ROOT / "Code/GameEngineDevice/Source/W3DDevice/GameClient/ScreenMotionBlurFilterPostRender.cpp"
    body = function_body(source, "bool modernAdvanceMotionBlurEndPan()")
    run_native_harness(tmp_path, r'''
struct W3DFilterInterface {};
struct ScreenMotionBlurFilter { int m_maxCount; };
W3DFilterInterface *W3DFilters[10]={0};
bool modernAdvanceMotionBlurEndPan()
''' + body + r'''
int main() {
 if(!modernAdvanceMotionBlurEndPan()) return 1;
 ScreenMotionBlurFilter filter={3};
 W3DFilters[2]=reinterpret_cast<W3DFilterInterface *>(&filter);
 if(!modernAdvanceMotionBlurEndPan() || filter.m_maxCount!=2) return 2;
 if(modernAdvanceMotionBlurEndPan() || filter.m_maxCount!=1) return 3;
 return 0;
}
''', [], [])


@pytest.mark.skipif(os.name != "nt", reason="native Windows effect harness")
def test_motion_blur_end_pan_does_not_decay_on_extra_presentations(tmp_path):
    source = build.ROOT / "Code/GameEngineDevice/Source/W3DDevice/GameClient/ScreenMotionBlurFilterPostRender.cpp"
    body = function_body(source, "else if (mode == FM_VIEW_MB_END_PAN_ALPHA)")
    run_native_harness(tmp_path, r'''
#include "Common/ModernRenderPhase.h"
#include <math.h>
#include <stdio.h>
typedef float Real;
__declspec(thread) ModernRenderPhase g_modernRenderPhase=MODERN_RENDER_LEGACY;
struct Point { float x,y; };
struct Filter {
 Point m_priorDelta;
 int m_maxCount;
 bool m_decrement;
 bool endPan();
};
bool Filter::endPan() {
 Point center={0,0};
 bool pan=false, continueEffect=true;
''' + body + r'''
 return continueEffect;
}
int main() {
 Filter filter={{1,0},60,false};
 for(int tick=0;tick<30;++tick) {
  --filter.m_maxCount;
  for(int p=0;p<4;++p) {
   ModernRenderScope present(MODERN_RENDER_PRESENT);
   filter.endPan();
  }
 }
 if(filter.m_maxCount!=30) {
  printf("end-pan count %d, expected 30\n",filter.m_maxCount);
  return 1;
 }
 filter.endPan();
 return filter.m_maxCount==29 ? 0 : 2;
}
''', ["BFME2_MODERN=1"], [build.ROOT / "Code/GameEngine/Include"])


@pytest.mark.skipif(os.name != "nt", reason="native Windows effect harness")
def test_bw_update_finishes_both_directions_and_clears_filter(tmp_path):
    source = build.ROOT / "Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerScreenBWFilterSet.cpp"
    body = function_body(source, "void modernAdvanceBW()")
    run_native_harness(tmp_path, r'''
typedef int Int;
typedef float Real;
const int FM_NULL_MODE=0, FT_NULL_FILTER=0;
struct View {
 int clears;
 void setViewFilterMode(int) { ++clears; }
 void setViewFilter(int) { ++clears; }
} view={0};
View *TheTacticalView=&view;
struct ScreenBWFilter {
 static int m_curFadeFrame,m_fadeFrames,m_fadeDirection;
 static float m_curFadeValue;
};
int ScreenBWFilter::m_curFadeFrame=0;
int ScreenBWFilter::m_fadeFrames=4;
int ScreenBWFilter::m_fadeDirection=1;
float ScreenBWFilter::m_curFadeValue=0;
void modernAdvanceBW()
''' + body + r'''
int main() {
 for(int n=1; n<4; ++n) {
  modernAdvanceBW();
  if(ScreenBWFilter::m_curFadeValue != n*0.25f) return 1;
 }
 modernAdvanceBW();
 if(ScreenBWFilter::m_curFadeValue!=1 || ScreenBWFilter::m_curFadeFrame!=0 ||
    ScreenBWFilter::m_fadeDirection!=0 || view.clears!=0) return 2;
 ScreenBWFilter::m_fadeDirection=-1;
 for(int n=1; n<4; ++n) {
  modernAdvanceBW();
  if(ScreenBWFilter::m_curFadeValue != 1-n*0.25f) return 3;
 }
 modernAdvanceBW();
 if(ScreenBWFilter::m_curFadeValue!=0 || ScreenBWFilter::m_curFadeFrame!=0 ||
    ScreenBWFilter::m_fadeDirection!=0 || view.clears!=2) return 4;
 modernAdvanceBW();
 return view.clears==2 ? 0 : 5;
}
''')


@pytest.mark.skipif(os.name != "nt", reason="native Windows effect harness")
@pytest.mark.parametrize("owner,filename", [
    ("ScreenBWFilter", "W3DShaderManagerScreenBWFilterSet.cpp"),
    ("Rva000FC34FFilter", "ScreenFilterRva000FC63DSet.cpp"),
])
def test_bw_presentations_do_not_advance_fade(tmp_path, owner, filename):
    source = build.ROOT / "Code/GameEngineDevice/Source/W3DDevice/GameClient" / filename
    body = function_body(source, "Int " + owner + "::set(FilterModes mode)")
    # Execute the actual state portion; GPU material/shader setup is outside this test.
    body = body[:body.index("VertexMaterialClass *vmat")] + "return 1; } return 0; }"
    run_native_harness(tmp_path, r'''
#include "Common/ModernRenderPhase.h"
#include <stdio.h>
typedef int Int;
typedef float Real;
typedef int FilterModes;
const int FM_NULL_MODE=0, FT_NULL_FILTER=0;
__declspec(thread) ModernRenderPhase g_modernRenderPhase=MODERN_RENDER_LEGACY;
struct View { void setViewFilterMode(int) {} void setViewFilter(int) {} } view;
View *TheTacticalView=&view;
struct ScreenBWFilter {
 static int m_curFadeFrame,m_fadeFrames,m_fadeDirection;
 static float m_curFadeValue;
 Int set(FilterModes);
};
struct Rva000FC34FFilter { Int set(FilterModes); };
int ScreenBWFilter::m_curFadeFrame=0;
int ScreenBWFilter::m_fadeFrames=300;
int ScreenBWFilter::m_fadeDirection=1;
float ScreenBWFilter::m_curFadeValue=0;
// Isolate the set()->update ownership boundary. The update body has its own test.
void modernAdvanceBW() { ++ScreenBWFilter::m_curFadeFrame; }
Int ''' + owner + r'''::set(FilterModes mode)
''' + body + r'''
int main() {
 ''' + owner + r''' filter;
 for(int tick=0; tick<30; ++tick) {
  modernAdvanceBW();
  for(int p=0; p<4; ++p) {
   ModernRenderScope render(MODERN_RENDER_PRESENT);
   filter.set(1);
  }
 }
 if(ScreenBWFilter::m_curFadeFrame != 30) {
  printf("BW fade advanced %d instead of 30\n",ScreenBWFilter::m_curFadeFrame);
  return 1;
 }
 filter.set(1);
 return ScreenBWFilter::m_curFadeFrame==31 ? 0 : 2;
}
''', ["BFME2_MODERN=1"], [build.ROOT / "Code/GameEngine/Include"])


@pytest.mark.skipif(os.name != "nt", reason="native Windows effect harness")
@pytest.mark.parametrize("presentations", [0, 1, 4, 8])
@pytest.mark.parametrize("direction", [-1, 1])
def test_crossfade_time_follows_updates_not_presentations(tmp_path, presentations, direction):
    source = build.ROOT / "Code/GameEngineDevice/Source/W3DDevice/GameClient/ScreenCrossFadeFilterUpdateFadeLevel.cpp"
    update = function_body(source, "bool ScreenCrossFadeFilter::updateFadeLevel()")
    render = function_body(source, "Bool ScreenCrossFadeFilter::preRender(")
    run_native_harness(tmp_path, r'''
#include "Common/ModernRenderPhase.h"
#include <stdio.h>
typedef bool Bool;
typedef int CustomScenePassModes;
const int SCENE_PASS_ALPHA_MASK = 1;
__declspec(thread) ModernRenderPhase g_modernRenderPhase = MODERN_RENDER_LEGACY;
static bool modernCrossFadeContinue = true;
struct TacticalView { void setViewFilterMode(int) {} void setViewFilter(int) {} } view;
void *TheTacticalView = &view;
float g_Va00BBB8D8 = 1.f;
struct W3DShaderManager { static void startRenderToTexture() {} };
struct ScreenCrossFadeFilter {
 static int m_fadeDirection, m_curFadeFrame, m_fadeFrames;
 static float m_curFadeValue;
 static bool m_skipRender;
 bool updateFadeLevel();
 Bool preRender(Bool &, CustomScenePassModes &);
};
int ScreenCrossFadeFilter::m_fadeDirection = DIRECTION;
int ScreenCrossFadeFilter::m_curFadeFrame = 0;
int ScreenCrossFadeFilter::m_fadeFrames = 300;
float ScreenCrossFadeFilter::m_curFadeValue = 0;
bool ScreenCrossFadeFilter::m_skipRender = false;
bool ScreenCrossFadeFilter::updateFadeLevel()
''' + update + r'''
Bool ScreenCrossFadeFilter::preRender(Bool &skipRender, CustomScenePassModes &scenePassMode)
''' + render + r'''
int main() {
 ScreenCrossFadeFilter filter;
 bool skip = false;
 int mode = 0;
 for(int tick = 0; tick < 30; ++tick) {
  {
   ModernRenderScope fixed(MODERN_RENDER_UPDATE);
   modernCrossFadeContinue = filter.updateFadeLevel();
  }
  for(int p = 0; p < PRESENTATIONS; ++p) {
   ModernRenderScope render(MODERN_RENDER_PRESENT);
   filter.preRender(skip, mode);
  }
 }
 if(filter.m_curFadeFrame != 30) {
  printf("fade advanced %d ticks instead of 30\n", filter.m_curFadeFrame);
  return 1;
 }
 // Legacy callers still own one update for each combined draw.
 filter.preRender(skip, mode);
 return filter.m_curFadeFrame == 31 ? 0 : 2;
}
''', ["BFME2_MODERN=1", "PRESENTATIONS=" + str(presentations), "DIRECTION=" + str(direction)],
       [build.ROOT / "Code/GameEngine/Include"])
