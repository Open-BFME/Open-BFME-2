"""Native checks for fixed-update/presentation ownership and exception restoration."""
import os

import pytest

from test_modern_camera import run_native_harness, function_body
import build


@pytest.mark.skipif(os.name != "nt", reason="native Windows renderer harness")
def test_background_renderer_does_not_inherit_main_thread_phase(tmp_path):
    source = build.ROOT / "Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp"
    definition = next(line for line in source.read_text().splitlines()
                      if "g_modernRenderPhase = MODERN_RENDER_LEGACY;" in line)
    run_native_harness(tmp_path, r'''
#include "Common/ModernRenderPhase.h"
extern "C" {
__declspec(dllimport) void *__stdcall CreateThread(void *, unsigned long, unsigned long (__stdcall *)(void *), void *, unsigned long, unsigned long *);
__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
__declspec(dllimport) int __stdcall GetExitCodeThread(void *, unsigned long *);
__declspec(dllimport) int __stdcall CloseHandle(void *);
}
#pragma comment(lib,"kernel32.lib")
''' + definition + r'''
unsigned long __stdcall worker(void *) {
 if(g_modernRenderPhase != MODERN_RENDER_LEGACY) return 1;
 {
  ModernRenderScope render(MODERN_RENDER_PRESENT);
  if(modernUpdatesScene() || !modernPresentsScene()) return 2;
 }
 return g_modernRenderPhase == MODERN_RENDER_LEGACY ? 0 : 3;
}
int main() {
 ModernRenderScope update(MODERN_RENDER_UPDATE);
 void *thread=CreateThread(0,0,worker,0,0,0);
 if(!thread) return 4;
 if(WaitForSingleObject(thread,5000)!=0) return 5;
 unsigned long result=99;
 if(!GetExitCodeThread(thread,&result)) return 6;
 CloseHandle(thread);
 if(result) return 7;
 return g_modernRenderPhase == MODERN_RENDER_UPDATE ? 0 : 8;
}
''', ["BFME2_MODERN=1"], [build.ROOT / "Code/GameEngine/Include"])


@pytest.mark.skipif(os.name != "nt", reason="native Windows renderer harness")
def test_engine_presentation_deadlines_and_phase(tmp_path):
    source = build.ROOT / "Code/GameEngine/Source/Common/GameEngineExecuteRva0022D290.cpp"
    body = function_body(source, "static void modernDrawIfDue(ModernFrameSchedule &clock)")
    run_native_harness(tmp_path, r'''
#include "Common/ModernFrameSchedule.h"
#include "Common/ModernRenderPhase.h"
__declspec(thread) ModernRenderPhase g_modernRenderPhase = MODERN_RENDER_LEGACY;
struct LARGE_INTEGER { __int64 QuadPart; } counter;
__declspec(thread) float g_modernVisualAlpha=1.0f;
void QueryPerformanceCounter(LARGE_INTEGER *out) { *out = counter; }
int presents = 0, badPhase = 0;
bool failNext = false, reported = false;
void modernPresentFrame() {
    if (g_modernRenderPhase != MODERN_RENDER_PRESENT) ++badPhase;
    if (failNext) { failNext = false; throw 42; }
    ++presents;
}
#define REPORT_CRASH(reason) (reported = true)
static void modernDrawIfDue(ModernFrameSchedule &clock)
''' + body + r'''
int main() {
    const int rates[] = {30, 60, 120, 144, 0};
    for (int r = 0; r < 5; ++r) {
        ModernFrameSchedule clock(1000, 30, rates[r]);
        presents = 0;
        for (int ms = 0; ms <= 10000; ++ms) {
            counter.QuadPart = ms;
            modernDrawIfDue(clock);
            if (g_modernRenderPhase != MODERN_RENDER_LEGACY) return 1;
        }
        if (presents != (rates[r] ? rates[r]*10+1 : 10001)) return 2;
    }
    ModernFrameSchedule clock(1000, 30, 0);
    failNext = true;
    modernDrawIfDue(clock);
    if (!reported || g_modernRenderPhase != MODERN_RENDER_LEGACY) return 3;
    return badPhase ? 4 : 0;
}
''', ["BFME2_MODERN=1"], [build.ROOT / "Code/GameEngine/Include"])


@pytest.mark.skipif(os.name != "nt", reason="native Windows renderer harness")
def test_render_phase_scopes_restore_after_nested_calls_and_exceptions(tmp_path):
    run_native_harness(tmp_path, r'''
#include "Common/ModernRenderPhase.h"
__declspec(thread) ModernRenderPhase g_modernRenderPhase = MODERN_RENDER_LEGACY;
int main() {
    if (!modernUpdatesScene() || !modernPresentsScene()) return 1;
    try {
        ModernRenderScope fixed(MODERN_RENDER_UPDATE);
        if (!modernUpdatesScene() || modernPresentsScene()) return 2;
        {
            ModernRenderScope render(MODERN_RENDER_PRESENT);
            if (modernUpdatesScene() || !modernPresentsScene()) return 3;
        }
        if (!modernUpdatesScene() || modernPresentsScene()) return 4;
        throw 42;
    } catch (int) {}
    if (g_modernRenderPhase != MODERN_RENDER_LEGACY) return 5;
    // More presentations must not cause extra simulation-owned scene work.
    int updates = 0, presents = 0;
    for (int frame = 0; frame < 30; ++frame) {
        {
            ModernRenderScope fixed(MODERN_RENDER_UPDATE);
            if (modernUpdatesScene()) ++updates;
            if (modernPresentsScene()) ++presents;
        }
        for (int extra = 0; extra < 4; ++extra) {
            ModernRenderScope render(MODERN_RENDER_PRESENT);
            if (modernUpdatesScene()) ++updates;
            if (modernPresentsScene()) ++presents;
        }
    }
    return updates == 30 && presents == 120 ? 0 : 6;
}
''', ["BFME2_MODERN=1"], [build.ROOT / "Code/GameEngine/Include"])
