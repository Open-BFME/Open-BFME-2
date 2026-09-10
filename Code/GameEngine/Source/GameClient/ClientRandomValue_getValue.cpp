// cl: /O1 /arch:SSE2
// BFME1 GameClientRandomVariable::getValue transferred to the BFME2 layout.

typedef float Real;

extern Real GetGameClientRandomValueReal(Real low, Real high, char *file,
	int line);

class GameClientRandomVariable
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

Real GameClientRandomVariable::getValue() const
{
	switch (m_type)
	{
	case CONSTANT:
		if (m_low == m_high)
			return m_low;
		// A non-degenerate CONSTANT falls through to the uniform path.
	case UNIFORM:
		return GetGameClientRandomValueReal(
			m_low, m_high,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\Common\\RandomValue.cpp",
			394);
	default:
		return 0.0f;
	}
}
