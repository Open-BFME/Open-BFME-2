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

    GameClientRandomVariable &operator=(const GameClientRandomVariable &that);

    void setRange(float low, float high, DistributionType type = UNIFORM);
    float getValue() const;
    float getMinimumValue() const;
    float getMaximumValue() const;
    DistributionType getDistributionType() const;

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

GameClientRandomVariable::DistributionType GameClientRandomVariable::getDistributionType() const
{
    return m_type;
}

inline GameClientRandomVariable::GameClientRandomVariable()
{
    m_type = CONSTANT;
    m_low = 0.0f;
    m_high = 0.0f;
}

// 12-byte block copy; retail emits three movsd, which is what a struct
// assignment produces here rather than three member stores.
GameClientRandomVariable &GameClientRandomVariable::operator=(const GameClientRandomVariable &that)
{
    struct Raw
    {
        DistributionType type;
        float low;
        float high;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

bool operator==(const GameClientRandomVariable &a, const GameClientRandomVariable &b)
{
    return a.m_type == b.m_type && a.m_low == b.m_low && a.m_high == b.m_high;
}

bool operator!=(const GameClientRandomVariable &a, const GameClientRandomVariable &b)
{
    return !(a == b);
}

// These are header inlines that the units including the header emit as
// select-any copies, which plain definitions here collided with. The anchor
// keeps this unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeGameClientRandomVariableInlineAnchor absent-from-retail
void _bfmeGameClientRandomVariableInlineAnchor(GameClientRandomVariable *gameClientRandomVariable)
{
    gameClientRandomVariable->GameClientRandomVariable::GameClientRandomVariable();
}
#pragma inline_depth()
