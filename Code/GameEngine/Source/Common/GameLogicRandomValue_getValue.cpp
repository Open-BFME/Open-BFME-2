// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME1 GameLogicRandomVariable::getValue transferred to the BFME2 layout,
// mirroring the matched GameClient twin at 0x002341A1 (70 bytes). Retail
// 0x00234206 issues the same shapes: CONSTANT falls through to UNIFORM
// unless low equals high, UNIFORM calls the four-argument game-logic helper
// with the RandomValue.cpp path and line 438, and anything else reads 0.0f.

typedef float Real;

extern Real GetGameLogicRandomValueReal(Real low, Real high, char *file,
	int line);

class GameLogicRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
	};

	Real getValue() const;

private:
	DistributionType m_type;
	Real m_low;
	Real m_high;
};

Real GameLogicRandomVariable::getValue() const
{
	switch (m_type)
	{
	case CONSTANT:
		if (m_low == m_high)
			return m_low;
		// A non-degenerate CONSTANT falls through to the uniform path.
	case UNIFORM:
		return GetGameLogicRandomValueReal(
			m_low, m_high,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\Common\\RandomValue.cpp",
			438);
	default:
		return 0.0f;
	}
}
