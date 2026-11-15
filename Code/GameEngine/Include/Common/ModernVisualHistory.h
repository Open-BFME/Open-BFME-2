#ifndef BFME2_MODERN_VISUAL_HISTORY_H
#define BFME2_MODERN_VISUAL_HISTORY_H

#if !defined(BFME2_MODERN)
#error ModernVisualHistory belongs only to the explicit modern variant
#endif

// Owned by the visual object's lifetime, never by its address in a global map.
// The caller supplies a monotonically increasing client-update serial and
// resets on recreation/load. Teleports explicitly break continuity. Capture
// the settled pose even on stationary updates, so old movement cannot repeat.
// Value::Lerp must interpolate the visual value without touching game state.
template<class Value> class ModernVisualHistory
{
public:
    ModernVisualHistory() : m_valid(false), m_serial(0) {}
    void reset() { m_valid = false; }

    void capture(const Value &value, unsigned int serial, bool continuous)
    {
        if (!m_valid || !continuous ||
            (serial != m_serial && serial - m_serial != 1))
        {
            m_previous = value;
        }
        else if (serial != m_serial)
        {
            m_previous = m_current;
        }
        m_current = value;
        m_serial = serial;
        m_valid = true;
    }

    bool sample(float alpha, Value &out) const
    {
        if (!m_valid) return false;
        // Treat NaN like the latest state, never feed it into matrix math.
        if (!(alpha < 1.0f)) out = m_current;
        else if (alpha <= 0.0f) out = m_previous;
        else Value::Lerp(m_previous, m_current, alpha, out);
        return true;
    }

private:
    Value m_previous;
    Value m_current;
    bool m_valid;
    unsigned int m_serial;
};

// This scope borrows a live render object; it must not outlive or delete it.
// Use the object's setter both ways so camera frusta and model hierarchy
// caches are invalidated after application AND restoration. Do not use this
// on the simulation object or across a game update. Set_Transform must not throw.
template<class Target, class Value> class ModernVisualTransformScope
{
public:
    ModernVisualTransformScope(Target &target,
                               const ModernVisualHistory<Value> &history,
                               float alpha)
        : m_target(target), m_active(false)
    {
        Value visual;
        if (history.sample(alpha, visual))
        {
            m_original = target.Get_Transform();
            target.Set_Transform(visual);
            m_active = true;
        }
    }
    ~ModernVisualTransformScope()
    {
        if (m_active) m_target.Set_Transform(m_original);
    }
private:
    ModernVisualTransformScope(const ModernVisualTransformScope &);
    ModernVisualTransformScope &operator=(const ModernVisualTransformScope &);
    Target &m_target;
    Value m_original;
    bool m_active;
};

#endif
