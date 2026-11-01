// cl: /DNDEBUG /MD /EHsc
// ?addKey@Rva00504F09FunctionCurve@@QAEXMMPBM0@Z, retail 0x00504F09, 307B.
// BFME2 counterpart of the BFME1 key accumulator (donor
// reference/open-bfme-1/game/GameEngine/Source/Common/Rva0006AB90FunctionCurveAddKey.cpp,
// same "Function curve time must be increasing" check, same tangent flags).
// BFME2 differences read off the target: SSE arithmetic, and the curve set
// at 0x00504EAD takes the two tangents as floats (fld/fstp), not as bits.
typedef int Int;

#include "../../../Include/Common/INI/FieldParse.h"

struct Rva00504EADCurvePoint { float time,value;unsigned char reserved[8]; };

class Rva00504EADCurve
{
public:
	bool set(float time, float value, float inTangent, float outTangent);
 int size() const { return m_end - m_begin; }
 unsigned char m_reserved[8];
 Rva00504EADCurvePoint *m_begin,*m_end;
 unsigned char m_reserved10[8];
 void *m_lastNode;
};

class Rva00504F09FunctionCurve
{
public:
	void addKey(float time, float value, const float *inTangent, const float *outTangent);
 void finish();

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

// Finish: BFME1 donor2f243e26d final-key emission; target174B/WB12CC580
// proves zero literal and float-tangent ABI. WB repeats missing-out-tangent
// handling in both size branches; retaining that shape closes EBX epilogue.
void Rva00504F09FunctionCurve::finish()
{
	if (m_firstKey)
		throw INIException(3, "Function curve does not have any keyframes");

	if (!m_curve->size()) {
		if (!m_haveInTangent)
			m_inTangent.value = m_haveOutTangent ? m_outTangent.value : 0.0f;
	if (!m_haveOutTangent)
		m_outTangent.bits = m_inTangent.bits;

	} else {
		Rva00504EADCurvePoint *previous = m_curve->m_end - 1;
		if (!m_haveInTangent)
			m_inTangent.value = (m_lastValue - previous->value) / (m_lastTime - previous->time);

	if (!m_haveOutTangent)
		m_outTangent.bits = m_inTangent.bits;

	}

	m_curve->set(m_lastTime, m_lastValue, m_inTangent.value, m_outTangent.value);
}

// ?set@Rva00504EADCurve@@QAE_NMMMM@Z, retail 0x00504EAD (92B). The ledger
// pin's `QAEX` spelling was a call-site guess: retail leaves the insertion
// result's byte in AL (`mov al,[eax+4]` before `ret 0x10`), so the owner is
// the bool form and every view that calls it must say so.
// Target facts: the locals shape continues the BFME1 donor's
// (Rva0006AB10SetLocals, reference/open-bfme-1 .../Rva0006AB10CurveSet.cpp):
// one struct is the whole 0x24 frame -- a 16-byte {m_time, m_value} key
// first (key at -0x24), then the 12-byte {value, inTangent, outTangent}
// record it is built from (at -0x14). The stores run values-then-key and a
// 12-byte copy carries the record into the key. The tree at this+8 then
// inserts the key: 0x00504E6D takes the key pointer and writes its 8-byte
// {node, inserted} result through a hidden pointer (the row's by-value
// `QAE?AURva00504E6DResult@@PBX@Z` view). this+0xC (the tree cursor) is
// copied to this+0x18 before the result byte returns.
// The member order (key, values) is a structural inference: the donor
// declares {result, values, point}, retail's frame order is key, values.
struct Rva00504EADKeyVector
{
	float m_value;
	float m_inTangent;
	float m_outTangent;
};

struct Rva00504EADKey
{
	float m_time;
	Rva00504EADKeyVector m_value;
};

struct Rva00504EADSetLocals
{
	Rva00504EADKey m_key;
	Rva00504EADKeyVector m_values;

	Rva00504EADSetLocals(float time, float value, float inTangent, float outTangent)
	{
		m_values.m_value = value;
		m_values.m_inTangent = inTangent;
		m_values.m_outTangent = outTangent;
		m_key.m_time = time;
		m_key.m_value = m_values;
	}
};

struct Rva00504E6DResult
{
	Rva00504E6DResult(void *node, bool inserted)
		: m_node(node), m_inserted(inserted) {}
	void *m_node;
	bool m_inserted;
};

class Rva00504DF8
{
public:
	Rva00504E6DResult rva00504E6D(const void *value);
};

bool Rva00504EADCurve::set(float time, float value, float inTangent, float outTangent)
{
	Rva00504EADSetLocals locals(time, value, inTangent, outTangent);
	bool inserted = ((Rva00504DF8 *)&m_begin)->rva00504E6D(&locals.m_key).m_inserted;
	m_lastNode = m_end;
	return inserted;
}
