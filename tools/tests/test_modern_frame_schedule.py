"""Native tests of independent fixed-update and presentation deadlines."""
import os

import pytest

from test_modern_camera import run_native_harness
import build


@pytest.mark.skipif(os.name != "nt", reason="native Windows timing harness")
def test_visual_fraction_tracks_actual_update_boundary(tmp_path):
    run_native_harness(tmp_path, r'''
#include "Common/ModernFrameSchedule.h"
int main() {
 ModernFrameSchedule clock(1000,30,144);
 clock.markVisualUpdate(100,40);
 if(clock.visualInterpolation(100)!=0) return 1;
 if(clock.visualInterpolation(110)!=.25f) return 2;
 if(clock.visualInterpolation(140)!=1) return 3;
 if(clock.visualInterpolation(1000)!=1) return 4;
 if(clock.visualInterpolation(90)!=0) return 5;
 clock.markVisualUpdate(200,20);
 if(clock.visualInterpolation(210)!=.5f) return 6;
 clock.reset(0);
 if(clock.visualInterpolation(100)!=1) return 7;
 return 0;
}
''', ["BFME2_MODERN=1"], [build.ROOT / "Code/GameEngine/Include"])


@pytest.mark.skipif(os.name != "nt", reason="native Windows timing harness")
def test_fixed_updates_do_not_follow_render_rate(tmp_path):
    run_native_harness(tmp_path, r'''
#include "Common/ModernFrameSchedule.h"
#include <stdio.h>
int main() {
    const int rates[] = {30, 60, 120, 144, 0};
    for (int r = 0; r < 5; ++r) {
        ModernFrameSchedule clock(1000000, 30, rates[r]);
        clock.reset(0);
        int updates = 0;
        int presentations = 0;
        // 1 kHz polling, ten seconds: exact rational timing, no 33 ms drift.
        for (int i = 0; i <= 10000; ++i) {
            clock.advance((__int64)i * 1000);
            while (clock.takeUpdate()) ++updates;
            if (clock.renderDue()) { ++presentations; clock.presented(); }
            if (clock.interpolation() < 0 || clock.interpolation() >= 1) return 1;
        }
        if (updates != 300) {
            printf("rate %d changed game speed: %d updates\n", rates[r], updates);
            return 2;
        }
        int wanted = rates[r] ? 10 * rates[r] + 1 : 10001;
        if (presentations != wanted) {
            printf("rate %d: %d presentations, expected %d\n", rates[r], presentations, wanted);
            return 3;
        }
    }
    return 0;
}
''', ["BFME2_MODERN=1"], [build.ROOT / "Code/GameEngine/Include"])


@pytest.mark.skipif(os.name != "nt", reason="native Windows timing harness")
def test_hitch_pause_reset_and_rate_change(tmp_path):
    run_native_harness(tmp_path, r'''
#include "Common/ModernFrameSchedule.h"
#include <stdio.h>
#include <math.h>
int main() {
    ModernFrameSchedule clock(1000, 30, 144);
    clock.reset(100);
    clock.presented();
    clock.advance(600); // A half-second hitch owes fifteen updates.
    for (int i = 0; i < 4; ++i) if (!clock.takeUpdate()) return 1;
    if (clock.interpolation() != 1) return 2;
    int remaining = 0;
    while (clock.takeUpdate()) ++remaining;
    if (remaining != 11) return 3; // Work limit must not discard game time.
    if (!clock.renderDue()) return 4;
    clock.presented();
    if (clock.renderDue()) return 5; // No burst of stale presentations.
    clock.advance(610);
    const float alpha = clock.interpolation();
    clock.setRenderRate(60);
    // MSVC 7.1 may keep a returned float in an extended x87 register.
    if (fabs(clock.interpolation() - alpha) > 0.000001 || clock.takeUpdate()) {
        printf("rate change interpolation %.17g -> %.17g\n", (double)alpha, (double)clock.interpolation());
        return 6;
    }
    clock.advance(633);
    if (clock.takeUpdate()) return 11;
    clock.advance(634);
    if (!clock.takeUpdate() || clock.takeUpdate()) return 12;
    clock.reset(10000); // Resume after pause/load: no catch-up for paused time.
    if (clock.takeUpdate() || clock.interpolation() != 0) return 7;
    clock.advance(10010);
    if (clock.takeUpdate()) return 8;
    clock.advance(9999); // Clock discontinuity resets, never underflows.
    if (clock.takeUpdate() || clock.interpolation() != 0) return 9;
    clock.setRenderRate(0);
    clock.presented();
    if (!clock.renderDue()) return 10;
    return 0;
}
''', ["BFME2_MODERN=1"], [build.ROOT / "Code/GameEngine/Include"])
