"""Native tests of visual snapshots; these do not prove in-game interpolation."""
import os
import pytest
from test_modern_camera import run_native_harness
import build


@pytest.mark.skipif(os.name != "nt", reason="native Windows interpolation harness")
def test_camera_integration_captures_restores_and_resets(tmp_path):
    source = build.ROOT / "Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetCameraTransformBfme.cpp"
    text = source.read_text()
    assert "// Modern camera interpolation implementation" in text
    implementation = text.split("// Modern camera interpolation implementation\n", 1)[1].split("// End modern camera interpolation", 1)[0]
    run_native_harness(tmp_path, r'''
#include <string.h>
#include "Common/ModernRenderPhase.h"
#include "Common/ModernVisualHistory.h"
#include "Common/ModernCameraInterpolation.h"
__declspec(thread) ModernRenderPhase g_modernRenderPhase=MODERN_RENDER_PRESENT;
__declspec(thread) float g_modernVisualAlpha=.5f;
struct Matrix3D {
 float v[12];
 static void Lerp(const Matrix3D &a,const Matrix3D &b,float t,Matrix3D &out) {
  for(int i=0;i<12;++i)out.v[i]=a.v[i]+(b.v[i]-a.v[i])*t;
 }
};
class CameraClass {
public:
 Matrix3D modernTransform;
 void Set_Transform(const Matrix3D &m) { modernTransform=m; }
};
''' + implementation + r'''
int main() {
 int owner=1;
 CameraClass camera;
 Matrix3D a={0},b={0}; a.v[3]=10; b.v[3]=30;
 modernBeginCameraUpdate();
 modernCaptureCamera(&owner,&camera,a);
 modernBeginCameraUpdate();
 modernCaptureCamera(&owner,&camera,b);
 camera.Set_Transform(b);
 try {
  ModernCameraPresentation scope(&owner,&camera);
  if(camera.modernTransform.v[3]!=20)return 1;
  throw 1;
 }catch(int){}
 if(camera.modernTransform.v[3]!=30)return 2;
 modernBeginCameraUpdate(); // stationary camera settles, never repeats motion
 { ModernCameraPresentation scope(&owner,&camera);
   if(camera.modernTransform.v[3]!=30)return 3; }
 modernResetCamera(&owner);
 { ModernCameraPresentation scope(&owner,&camera);
   if(camera.modernTransform.v[3]!=30)return 4; }
 modernBeginCameraUpdate(); modernCaptureCamera(&owner,&camera,a);
 camera.Set_Transform(a);
 { ModernCameraPresentation scope(&owner,&camera);
   if(camera.modernTransform.v[3]!=10)return 5; }
 // Loading can rebuild the camera more than once; neither an intermediate
 // pose nor its pre-load predecessor may survive the loading scope.
 try {
  ModernCameraDiscontinuity loading(0);
  modernCaptureCamera(&owner,&camera,b);
  throw 42;
 }catch(int){}
 camera.Set_Transform(a);
 { ModernCameraPresentation scope(&owner,&camera);
   if(camera.modernTransform.v[3]!=10)return 6; }
 return 0;
}
''', ["BFME2_MODERN=1"], [build.ROOT / "Code/GameEngine/Include"])


@pytest.mark.skipif(os.name != "nt", reason="native Windows interpolation harness")
def test_visual_transform_is_restored_after_render_and_exception(tmp_path):
    run_native_harness(tmp_path, r'''
#include "Common/ModernVisualHistory.h"
struct Pose {
 float x;
 static void Lerp(const Pose &a,const Pose &b,float t,Pose &out) {
  out.x=a.x+(b.x-a.x)*t;
 }
};
struct Camera {
 Pose transform;
 int invalidations;
 const Pose &Get_Transform() const { return transform; }
 void Set_Transform(const Pose &p) { transform=p; ++invalidations; }
};
int main() {
 ModernVisualHistory<Pose> history;
 Pose previous={10}, current={30};
 Camera camera={{30},0};
 {
  ModernVisualTransformScope<Camera,Pose> empty(camera,history,.5f);
  if(camera.transform.x!=30 || camera.invalidations) return 1;
 }
 history.capture(previous,1,true);
 history.capture(current,2,true);
 try {
  ModernVisualTransformScope<Camera,Pose> outer(camera,history,.5f);
  if(camera.transform.x!=20) return 2;
  {
   ModernVisualTransformScope<Camera,Pose> inner(camera,history,.25f);
   if(camera.transform.x!=15) return 3;
  }
  if(camera.transform.x!=20) return 4;
  throw 42;
 } catch(int) {}
 if(camera.transform.x!=30 || camera.invalidations!=4) return 5;
 Pose out={0};
 history.sample(.5f,out);
 if(out.x!=20 || previous.x!=10 || current.x!=30) return 6;
 return 0;
}
''', ["BFME2_MODERN=1"], [build.ROOT / "Code/GameEngine/Include"])


@pytest.mark.skipif(os.name != "nt", reason="native Windows interpolation harness")
def test_visual_history_updates_resets_and_read_only_sampling(tmp_path):
    run_native_harness(tmp_path, r'''
#include "Common/ModernVisualHistory.h"
struct Pose {
 float x;
 static void Lerp(const Pose &a,const Pose &b,float t,Pose &out) {
  out.x=a.x+(b.x-a.x)*t;
 }
};
int main() {
 ModernVisualHistory<Pose> history;
 Pose out={-1}, first={10}, second={20}, last={30}, teleported={900};
 if(history.sample(.5f,out) || out.x!=-1) return 1;
 history.capture(first,1,true);
 if(!history.sample(.5f,out) || out.x!=10) return 2;
 history.capture(second,2,true);
 if(!history.sample(.25f,out) || out.x!=12.5f) return 3;
 // Multiple writes in one update replace its endpoint, not its predecessor.
 history.capture(last,2,true);
 if(!history.sample(.5f,out) || out.x!=20) return 4;
 for(int i=0;i<144;++i) history.sample(.5f,out);
 if(out.x!=20 || first.x!=10 || second.x!=20 || last.x!=30) return 5;
 history.sample(-1,out); if(out.x!=10) return 6;
 history.sample(2,out); if(out.x!=30) return 7;
 // Explicit discontinuities must never sweep a teleport across the map.
 history.capture(teleported,3,false);
 history.sample(0,out); if(out.x!=900) return 8;
 // A gap, rewind/load, or reset cannot reuse stale movement.
 history.capture(first,8,true);
 history.sample(0,out); if(out.x!=10) return 9;
 history.capture(second,1,true);
 history.sample(0,out); if(out.x!=20) return 10;
 history.reset();
 if(history.sample(.5f,out)) return 11;
 history.capture(last,1,true);
 history.sample(0,out); if(out.x!=30) return 12;
 // An unchanged next update settles the preceding motion, including pause.
 history.capture(last,2,true);
 history.sample(.5f,out); if(out.x!=30) return 13;
 return 0;
}
''', ["BFME2_MODERN=1"], [build.ROOT / "Code/GameEngine/Include"])
