// ?rva000E6406@Rva000E6406SwayView@@QAEXABUBreezeInfo@@@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Donor structural guide: BFME 1 575ba2b04 W3DShrubBufferUpdateSway.cpp.
// Target provenance: the full retail __FILE__ names W3DVegetationBufferBase.cpp.
// The existing shrub frame-update caller passes the same leading sway subobject.
// Enclosing-class identity remains unproven, so the method and view retain RVA names.
// Native table offsets and the omitted per-shrub randomization are target facts.
// A named float wrap period keeps its SSE load outside the final offset loop.
// Vegetation sway update, retail 0x000E6406 (398 bytes, ret 4): when the breeze version changed, rebuilds the
// 100-entry sway offset table and the ten sway types' steps and factors from the breeze (Open-BFME-1 twin:
// W3DShrubBufferUpdateSway.cpp, 0x0071C0E0, which also re-rolls every shrub's sway type; the BFME2 body does not);
// then advances the ten sway offsets by their steps, wrapping at 100. BFME2 layout read from retail: sway
// offsets +0x90 (12 bytes each), current version +0x540, offsets +0x544, steps +0x56C, factors +0x594 and the
// breeze period scale +0x5BC; the random calls pass the native vegetation-base literal at lines 0x1B5 and 0x1BA.
typedef int Int;
typedef short Short;
typedef float Real;

struct BreezeInfo
{
	Real m_direction;
	Real m_directionVecX;
	Real m_directionVecY;
	Real m_intensity;
	Real m_lean;
	Real m_randomness;
	Short m_breezePeriod;
	Short m_breezeVersion;
};

extern Real Cos(Real);
extern Real Sin(Real);
extern Real GetGameClientRandomValueReal(Real, Real, char *, Int);

class Rva000E6406SwayView
{
public:
	void rva000E6406(const BreezeInfo &info);

private:
	char m_pad00[0x90];
	Real m_swayOffsets[100 * 3];
	Int m_curSwayVersion;
	Real m_curSwayOffset[10];
	Real m_curSwayStep[10];
	Real m_curSwayFactor[10];
	Real m_swayRate;
};

static const float swayWrapPeriod=100.0f;
void Rva000E6406SwayView::rva000E6406(const BreezeInfo &info)
{
	Int i;
	if (info.m_breezeVersion != m_curSwayVersion) {
		for (i = 0; i < 100; i++) {
			Real factor = Cos((Real)i * 0.06220976f);
			Real angle = info.m_lean + (info.m_intensity * factor);
			Real S = Sin(angle);
			Real C = Cos(angle);
			m_swayOffsets[i * 3] = info.m_directionVecX * S;
			m_swayOffsets[i * 3 + 1] = info.m_directionVecY * S;
			m_swayOffsets[i * 3 + 2] = C - 1.0f;
		}

		Real delta = info.m_randomness * 0.5f;
		Real high = 1.0f + delta;
		Real low = 1.0f - delta;
		for (i = 0; i < 10; i++) {
			m_curSwayStep[i] = swayWrapPeriod / ((Real)info.m_breezePeriod * m_swayRate);
			m_curSwayStep[i] *= GetGameClientRandomValueReal(low, high,
				"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DVegetationBufferBase.cpp", 0x1b5);
			if (m_curSwayStep[i] < 0.0f)
				m_curSwayStep[i] = 0.0f;
			m_curSwayOffset[i] = 0;
			m_curSwayFactor[i] = GetGameClientRandomValueReal(low, high,
				"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DVegetationBufferBase.cpp", 0x1ba);
		}
		m_curSwayVersion = info.m_breezeVersion;
	}

	for (i = 0; i < 10; i++) {
		m_curSwayOffset[i] += m_curSwayStep[i];
		if (m_curSwayOffset[i] > swayWrapPeriod)
			m_curSwayOffset[i] -= swayWrapPeriod;
	}
}
