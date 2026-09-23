// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/GameEngine/Source/Common

class Rva0020E150Value
{
public:
	float positiveRatio() const;

private:
	unsigned char m_padding[8];
	float m_numerator;
	unsigned char m_paddingC[4];
	float m_denominator;
};

float Rva0020E150Value::positiveRatio() const
{
	if (m_denominator > 0.0f) {
		return m_numerator / m_denominator;
	}
	return 0.0f;
}
