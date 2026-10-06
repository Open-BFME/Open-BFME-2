// cl: /DNDEBUG /MD /EHsc
// ?addKey@Rva00504F09FunctionCurve@@QAEXMMPBM0@Z, retail 0x00504F09, 307B.
// BFME2 counterpart of the BFME1 key accumulator (donor
// reference/open-bfme-1/game/GameEngine/Source/Common/Rva0006AB90FunctionCurveAddKey.cpp,
// same "Function curve time must be increasing" check, same tangent flags).
// BFME2 differences read off the target: SSE arithmetic, and the curve set
// at 0x00504EAD takes the two tangents as floats (fld/fstp), not as bits.
typedef int Int;

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

class Rva00504EADCurve
{
public:
	void set(float time, float value, float inTangent, float outTangent);
};

class Rva00504F09FunctionCurve
{
public:
	void addKey(float time, float value, const float *inTangent, const float *outTangent);

private:
	Rva00504EADCurve *m_curve;
	bool m_firstKey;
	float m_lastTime;
	float m_lastValue;
	union Tangent
	{
		float value;
		Int bits;
	} m_inTangent, m_outTangent;
	bool m_haveInTangent;
	bool m_haveOutTangent;
};

void Rva00504F09FunctionCurve::addKey(float time, float value,
	const float *inTangent, const float *outTangent)
{
	if (m_firstKey) {
		m_lastTime = time;
		m_firstKey = false;
		m_lastValue = value;
		m_haveInTangent = inTangent != 0;
		if (m_haveInTangent)
			m_inTangent.bits = *(const Int *)inTangent;
		m_haveOutTangent = outTangent != 0;
		if (m_haveOutTangent)
			m_outTangent.bits = *(const Int *)outTangent;
		return;
	}

	if (time <= m_lastTime)
		throw INIException(3, "Function curve time must be increasing");

	if (!m_haveOutTangent)
		m_outTangent.value = (value - m_lastValue) / (time - m_lastTime);
	if (!m_haveInTangent)
		m_inTangent.bits = m_outTangent.bits;
	m_curve->set(m_lastTime, m_lastValue, m_inTangent.value, m_outTangent.value);
	if (!inTangent)
		m_inTangent.value = (value - m_lastValue) / (time - m_lastTime);
	else
		m_inTangent.bits = *(const Int *)inTangent;
	m_haveInTangent = true;
	m_haveOutTangent = outTangent != 0;
	if (m_haveOutTangent)
		m_outTangent.bits = *(const Int *)outTangent;
	m_lastTime = time;
	m_lastValue = value;
}
