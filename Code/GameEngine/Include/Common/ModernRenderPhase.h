#ifndef BFME2_MODERN_RENDER_PHASE_H
#define BFME2_MODERN_RENDER_PHASE_H

#if !defined(BFME2_MODERN)
#error ModernRenderPhase belongs only to the explicit modern variant
#endif

// Legacy callers (loading screens and movie playback) retain their combined
// update/draw pass. The main loop can own fixed updates and presentation apart.
enum ModernRenderPhase
{
    MODERN_RENDER_LEGACY,
    MODERN_RENDER_UPDATE,
    MODERN_RENDER_PRESENT
};

// Loading-screen workers retain their own combined update/draw phase even
// while the main thread is inside a fixed update or extra presentation.
extern __declspec(thread) ModernRenderPhase g_modernRenderPhase;
extern __declspec(thread) float g_modernVisualAlpha;
void modernPresentFrame();
// Set after each fixed update; the next Apt draw consumes it. Apt marks its
// custom-rendered component windows only on a frame after an update, so the
// per-frame "hide what was not drawn" pass belongs to that frame alone.
extern bool g_modernAptFreshUpdate;
// Clears the push-button clocks drawn since the last update (W3DPushButton).
void modernClearPushButtonClocks();
// Unit model interpolation (W3DModelDrawDoDrawModule.cpp): prune and advance at
// each update; apply the blend for a presentation and restore it afterwards.
void modernBeginModelUpdate();
void modernApplyModelInterpolation(float alpha);
void modernRestoreModelInterpolation();
// The active radial menu (Rva005C6CCC.cpp): registered on update, dropped by
// its destructor, re-laid out at presentation under the interpolated camera.
void modernRadialSeen(void *radial);
void modernRadialGone(void *radial);
void modernRefreshRadial();
// Opt-in pacing trace (BFME2_MODERN_TRACE=1): one CSV line per event with a
// microsecond timestamp, written to modern_trace.csv in the working directory.
void modernTrace(char kind, double a, double b, double c, double d);
void modernAdvanceViewEffects();
void modernAdvanceCrossFade();
void modernAdvanceBW();
bool modernAdvanceMotionBlurEndPan();

inline bool modernUpdatesScene() { return g_modernRenderPhase != MODERN_RENDER_PRESENT; }
inline bool modernPresentsScene() { return g_modernRenderPhase != MODERN_RENDER_UPDATE; }

class ModernRenderScope
{
public:
    explicit ModernRenderScope(ModernRenderPhase phase) : m_previous(g_modernRenderPhase)
    {
        g_modernRenderPhase = phase;
    }
    ~ModernRenderScope() { g_modernRenderPhase = m_previous; }
private:
    ModernRenderScope(const ModernRenderScope &);
    ModernRenderScope &operator=(const ModernRenderScope &);
    ModernRenderPhase m_previous;
};

#endif
