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

    GameClientRandomVariable();

    void setRange(float low, float high, DistributionType type = UNIFORM);
    float getValue() const;
    float getMinimumValue() const;
    float getMaximumValue() const;
    DistributionType getDistributionType() const { return m_type; }

protected:
    DistributionType m_type;
    float m_low, m_high;

    friend bool operator==(const GameClientRandomVariable &a, const GameClientRandomVariable &b);
};

float GameClientRandomVariable::getMinimumValue() const
{
    return m_low;
}

float GameClientRandomVariable::getMaximumValue() const
{
    return m_high;
}

GameClientRandomVariable::GameClientRandomVariable()
{
    m_type = CONSTANT;
    m_low = 0.0f;
    m_high = 0.0f;
}

// The distribution type is stored last: retail loads it into eax before either
// bound reaches memory and writes it after both.
void GameClientRandomVariable::setRange(float low, float high, DistributionType type)
{
    m_low = low;
    m_high = high;
    m_type = type;
}

bool operator==(const GameClientRandomVariable &a, const GameClientRandomVariable &b)
{
    return a.m_type == b.m_type && a.m_low == b.m_low && a.m_high == b.m_high;
}

bool operator!=(const GameClientRandomVariable &a, const GameClientRandomVariable &b)
{
    return !(a == b);
}
