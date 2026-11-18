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
// Push-button clocks drawn since the last update are cleared by it (W3DPushButton).
void modernClearPushButtonClocks();
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
