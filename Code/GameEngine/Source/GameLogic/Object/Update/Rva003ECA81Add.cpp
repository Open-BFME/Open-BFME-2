// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva003ECA81@Rva003ECA4BElement@@QAEPAV1@PBV1@@Z, retail 0x003ECA81 (50 bytes).
// Target evidence: element-wise add of two 0x44-byte float records (the element
// whose ctor/clear are rowed at 0x003ECA4B/0x003ECA69); called by
// ThreatFinder::getThreatForPlayer, which ignores the result.
// Codegen finding: retail returns this in eax (the copy of ecx and the esi loop
// counter exist because this stays live to the epilogue); peeling element 0
// reproduces the push 0x10 / pop count idiom and the dst-src delta loop.
class Rva003ECA4BElement
{
public:
	Rva003ECA4BElement *rva003ECA81(const Rva003ECA4BElement *other);
	Rva003ECA4BElement *rva003ECAB3(float scale);
	Rva003ECA4BElement *rva003ECBD6(float divisor);

private:
	float m_values[17];
};

Rva003ECA4BElement *Rva003ECA4BElement::rva003ECA81(const Rva003ECA4BElement *other)
{
	m_values[0] += other->m_values[0];
	for (int i = 1; i < 17; ++i)
		m_values[i] += other->m_values[i];
	return this;
}

// Native 0x003ECAB3..0x003ECAE0 scales the same 17-float record and returns
// its receiver. The adjacent add/clear/xfer bodies establish the 0x44-byte
// record; the original class and method names remain unknown.
// The loop reloads scale before the element. The volatile access preserves
// that order without claiming that the original parameter was volatile.
Rva003ECA4BElement *Rva003ECA4BElement::rva003ECAB3(float scale)
{
	m_values[0] *= scale;
	int count = 16;
	float *p = &m_values[1];
	do {
		*p = *reinterpret_cast<const volatile float *>(&scale) * *p;
		++p;
	} while (--count != 0);
	return this;
}

// ?rva003ECBD6@Rva003ECA4BElement@@QAEPAV1@M@Z, retail 0x003ECBD6 (34 bytes):
// divide the record by scaling it with 1/divisor through the rowed
// rva003ECAB3 above; returns this.
Rva003ECA4BElement *Rva003ECA4BElement::rva003ECBD6(float divisor)
{
	rva003ECAB3(1.0f / divisor);
	return this;
}
