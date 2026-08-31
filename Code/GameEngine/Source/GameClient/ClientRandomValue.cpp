// cl: /O1 /arch:SSE2

// Member layout is the Zero Hour one, unchanged in BFME 2: the distribution
// type in the first four bytes, then the two Real bounds. The comparison
// bodies read exactly [ecx], [ecx+4] and [ecx+8].
class GameClientRandomVariable
{
public:
    enum DistributionType
    {
        CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
    };

    void setRange(float low, float high, DistributionType type = UNIFORM);
    float getValue() const;
    float getMinimumValue() const { return m_low; }
    float getMaximumValue() const { return m_high; }
    DistributionType getDistributionType() const { return m_type; }

protected:
    DistributionType m_type;
    float m_low, m_high;

    friend bool operator==(const GameClientRandomVariable &a, const GameClientRandomVariable &b);
};

bool operator==(const GameClientRandomVariable &a, const GameClientRandomVariable &b)
{
    return a.m_type == b.m_type && a.m_low == b.m_low && a.m_high == b.m_high;
}

bool operator!=(const GameClientRandomVariable &a, const GameClientRandomVariable &b)
{
    return !(a == b);
}
