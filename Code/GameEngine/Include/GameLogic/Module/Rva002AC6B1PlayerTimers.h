// Rva002AC6B1PlayerTimers: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002AC6B1PLAYERTIMERS_H
#define CANONICAL_RVA002AC6B1PLAYERTIMERS_H

class SpecialPowerTemplate;

class Rva002AC6B1PlayerTimers
{
public:
	unsigned int getOrStart(const SpecialPowerTemplate *tmpl);
	void resetOrStart(const SpecialPowerTemplate *specialPowerTemplate);
	void rva002AC75C(const SpecialPowerTemplate *temp, unsigned int frame);
};

#endif // CANONICAL_RVA002AC6B1PLAYERTIMERS_H
