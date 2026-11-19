"""Execute camera policy bodies with the game's native compiler in a small harness.

These tests isolate input policy; they do not establish rendering or ABI correctness.
"""
import os
from pathlib import Path
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def function_body(source, signature):
    text = source.read_text(encoding="utf-8")
    start = text.index("{", text.index(signature))
    depth = 1
    end = start + 1
    while depth:
        depth += (text[end] == "{") - (text[end] == "}")
        end += 1
    return text[start:end]


def run_native_harness(tmp_path, text, defines=(), includes=()):
    harness = tmp_path / "camera.cpp"
    harness.write_text(text, encoding="utf-8")
    root = build.vc71_root()
    executable = tmp_path / "camera.exe"
    command = [str(root / "Vc7/bin/cl.exe"), "/nologo", "/MT", "/EHsc",
               *["/D" + define for define in defines],
               *["/I" + str(path) for path in includes], str(harness),
               "/Fe" + str(executable), "/Fo" + str(tmp_path / "camera.obj")]
    compiled = subprocess.run(command, cwd=tmp_path, env=build.compiler_environment(root),
                              capture_output=True, text=True)
    assert compiled.returncode == 0, compiled.stdout + compiled.stderr
    environment = dict(os.environ)
    environment.pop("BFME2_MODERN_HORPLUS", None)
    environment.pop("BFME2_MODERN_ZOOM", None)
    tested = subprocess.run([str(executable)], capture_output=True, text=True, env=environment)
    assert tested.returncode == 0, tested.stdout + tested.stderr


@pytest.mark.skipif(os.name != "nt", reason="native Windows camera harness")
def test_horplus_preserves_vertical_scene_extent(tmp_path):
    source = build.ROOT / "Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetCameraTransformBfme.cpp"
    body = function_body(source, "static float modernHorizontalFov(float fov, float aspect)")
    run_native_harness(tmp_path, r'''
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static float modernHorizontalFov(float fov, float aspect)
''' + body + r'''
int main() {
    const float aspects[] = {4.0f/3.0f, 16.0f/9.0f, 21.0f/9.0f, 32.0f/9.0f};
    const float fields[] = {0.5f, 0.87266463f, 1.5f};
    for (int f = 0; f < 3; ++f) {
        const float original = fields[f];
        const double originalVerticalExtent = tan(original * 0.5) / aspects[0];
        float previous = 0;
        for (int a = 0; a < 4; ++a) {
            float corrected = modernHorizontalFov(original, aspects[a]);
            double verticalExtent = tan(corrected * 0.5) / aspects[a];
            if (fabs(verticalExtent - originalVerticalExtent) > 0.000001) {
                printf("vertical scene extent changed at aspect %.6f\n", aspects[a]);
                return 1;
            }
            if (a == 0 && corrected != original) return 2;
            if (a > 0 && corrected <= previous) return 3;
            if (corrected >= 3.14159265f) return 4;
            previous = corrected;
        }
        if (modernHorizontalFov(original, 0) != original) return 5;
        if (modernHorizontalFov(original, -1) != original) return 6;
    }
    _putenv("BFME2_MODERN_HORPLUS=0");
    if (modernHorizontalFov(0.87266463f, 32.f/9.f) != 0.87266463f) return 7;
    _putenv("BFME2_MODERN_HORPLUS=1");
    if (modernHorizontalFov(0.87266463f, 32.f/9.f) <= 0.87266463f) return 8;
    return 0;
}
''')


@pytest.mark.skipif(os.name != "nt", reason="native Windows camera harness")
def test_panorama_slice_keeps_explicit_horizontal_fov(tmp_path):
    source = build.ROOT / "Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetCameraTransformBfme.cpp"
    helper = function_body(source, "static float modernHorizontalFov(float fov, float aspect)")
    text = source.read_text(encoding="utf-8")
    start = text.index(" float worldFov=")
    projection = text[start:text.index("#else", start)]
    run_native_harness(tmp_path, r'''
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static float modernHorizontalFov(float fov, float aspect)
''' + helper + r'''
struct Camera {
    float aspect, horizontal;
    float Get_Aspect_Ratio() const { return aspect; }
    void Set_View_Plane(float h, float) { horizontal = h; }
};
struct Globals { bool field0EA6; float field0EA8; } globals;
Globals *TheWritableGlobalData = &globals;
void project(Camera *camera, float fov) {
''' + projection + r'''
}
int main() {
    Camera camera;
    const float aspects[] = {4.f/3.f, 16.f/9.f, 21.f/9.f, 32.f/9.f};
    for (int i = 0; i < 4; ++i) {
        camera.aspect = aspects[i];
        globals.field0EA6 = true;
        globals.field0EA8 = 1.f;
        project(&camera, 0.87266463f);
        if (camera.horizontal != 1.f) {
            printf("panorama slice FOV changed: %.9f\n", camera.horizontal);
            return 1;
        }
        globals.field0EA6 = false;
        project(&camera, 0.87266463f);
        if (fabs(camera.horizontal - modernHorizontalFov(0.87266463f, aspects[i])) > 0.000001)
            return 2;
    }
    return 0;
}
''')


@pytest.mark.skipif(os.name != "nt", reason="native Windows camera harness")
@pytest.mark.parametrize("modern", [False, True])
@pytest.mark.parametrize("map_maximum", [300, 500])
@pytest.mark.parametrize("zoom_enabled", [False, True])
def test_camera_height_limit_and_script_locks(tmp_path, modern, map_maximum, zoom_enabled):
    source = build.ROOT / "Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraModFinalZoomBfme.cpp"
    body = function_body(source, "void W3DView::setHeightAboveGround(Real z)")
    program = r'''
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef float Real;
struct GameClientCameraLocks { bool m_lockC0; } client = { false };
void *TheGameClient = &client;
struct Limits {
    float getMinimum() const { return 120.0f; }
    float getMaximum() const { return MAP_MAXIMUM; }
};
struct W3DView {
    bool m_zoomLimited, m_heightLocked, m_cameraMovementMode;
    bool m_doingRotateCamera, m_doingPitchCamera, m_doingZoomCamera;
    bool m_CameraArrivedAtWaypointOnPathFlag, m_doingScriptedCameraLock;
    bool m_cameraConstraintValid;
    float m_heightTravelled, m_heightAboveGround;
    Limits m_cameraLimits;
    int redraws;
    void setCameraTransform() { ++redraws; }
    void setHeightAboveGround(Real z);
};
void W3DView::setHeightAboveGround(Real z)
''' + body + r'''
int main() {
    _putenv("BFME2_MODERN_ZOOM=''' + ("1" if zoom_enabled else "0") + r'''");
    W3DView view = {0};
    view.m_zoomLimited = true;
    view.setHeightAboveGround(2000.0f);
    const float expected = ''' + str(map_maximum * (2 if modern and zoom_enabled else 1)) + r'''.0f;
    if (view.m_heightAboveGround != expected) {
        printf("maximum: got %.1f, expected %.1f\n", view.m_heightAboveGround, expected);
        return 1;
    }
    view.setHeightAboveGround(0.0f);
    if (view.m_heightAboveGround != 120.0f) return 2;
    view.m_doingScriptedCameraLock = true;
    view.setHeightAboveGround(250.0f);
    if (view.m_heightAboveGround != 120.0f || view.redraws != 2) return 3;
    view.m_doingScriptedCameraLock = false;
    client.m_lockC0 = true;
    view.setHeightAboveGround(250.0f);
    if (view.m_heightAboveGround != 120.0f || view.redraws != 2) return 4;
    client.m_lockC0 = false;
    bool *locks[] = { &view.m_heightLocked, &view.m_cameraMovementMode,
        &view.m_doingRotateCamera, &view.m_doingPitchCamera,
        &view.m_doingZoomCamera, &view.m_CameraArrivedAtWaypointOnPathFlag };
    for (int i = 0; i < 6; ++i) {
        *locks[i] = true;
        view.setHeightAboveGround(250.0f);
        if (view.m_heightAboveGround != 120.0f || view.redraws != 2) return 6 + i;
        *locks[i] = false;
    }
    view.m_zoomLimited = false;
    view.setHeightAboveGround(900.0f);
    if (view.m_heightAboveGround != 900.0f) return 5;
    return 0;
}
'''
    defines = ["MAP_MAXIMUM=" + str(map_maximum) + ".0f"]
    if modern:
        defines.append("BFME2_MODERN=1")
    run_native_harness(tmp_path, program, defines)
