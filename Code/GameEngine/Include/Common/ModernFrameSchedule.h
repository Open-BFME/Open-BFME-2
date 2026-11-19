#ifndef BFME2_MODERN_FRAME_SCHEDULE_H
#define BFME2_MODERN_FRAME_SCHEDULE_H

#if !defined(BFME2_MODERN)
#error ModernFrameSchedule belongs only to the explicit modern variant
#endif

#include <assert.h>

// Counter ticks are supplied by the caller (QueryPerformanceCounter in game).
// Keep the original client update frequency independent of presentation rate.
// The caller may limit catch-up work per presentation, but debt is never lost.
class ModernFrameSchedule
{
public:
    ModernFrameSchedule(__int64 frequency, int updateRate, int renderRate)
        : m_frequency(frequency), m_updateRate(updateRate), m_renderRate(renderRate)
    {
        assert(frequency > 0 && updateRate > 0 && renderRate >= 0);
        reset(0);
    }

    // Call on startup and on pause/resume or load transitions. Time spent
    // paused must not turn into a burst of game updates when resuming.
    void reset(__int64 now)
    {
        m_previous = now;
        m_updateCredit = 0;
        m_renderPhase = 0;
        m_renderReady = true;
        m_visualStart = now;
        m_visualPeriod = 0;
    }

    void advance(__int64 now)
    {
        if (now < m_previous)
        {
            reset(now);
            return;
        }
        const __int64 elapsed = now - m_previous;
        m_previous = now;
        m_updateCredit += elapsed * m_updateRate;
        if (m_renderRate != 0)
        {
            const __int64 credit = m_renderPhase + elapsed * m_renderRate;
            if (credit >= m_frequency) m_renderReady = true;
            m_renderPhase = credit % m_frequency;
        }
    }

    bool takeUpdate()
    {
        if (m_updateCredit < m_frequency) return false;
        m_updateCredit -= m_frequency;
        return true;
    }

    float interpolation() const
    {
        // A caller yielding during catch-up must never extrapolate past the
        // latest complete state. Interpolate previous/current snapshots only.
        if (m_updateCredit >= m_frequency) return 1.0f;
        return (float)((double)m_updateCredit / (double)m_frequency);
    }

    bool renderDue() const { return m_renderRate == 0 || m_renderReady; }
    // The engine retains its original update pacing; visual time follows that
    // actual boundary rather than this scheduler's unused update-credit path.
    void markVisualUpdate(__int64 now, __int64 period)
    {
        m_visualStart = now;
        m_visualPeriod = period > 0 ? period : 1;
    }
    float visualInterpolation(__int64 now) const
    {
        if (!m_visualPeriod) return 1.0f;
        if (now <= m_visualStart) return 0.0f;
        if (now - m_visualStart >= m_visualPeriod) return 1.0f;
        return (float)((double)(now - m_visualStart) / (double)m_visualPeriod);
    }
    void presented() { m_renderReady = false; }

    void setRenderRate(int rate)
    {
        assert(rate >= 0);
        m_renderRate = rate;
        m_renderPhase = 0;
        m_renderReady = true;
    }

private:
    __int64 m_frequency;
    __int64 m_previous;
    __int64 m_updateCredit;
    __int64 m_renderPhase;
    __int64 m_visualStart;
    __int64 m_visualPeriod;
    int m_updateRate;
    int m_renderRate;
    bool m_renderReady;
};

#endif
