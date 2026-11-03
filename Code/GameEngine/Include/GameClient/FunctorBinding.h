// Target facts: FunctorBinding is a nonvirtual 0x10-byte payload with no base or vftable; the by-value argument at RVA 0x00518756 is passed to 0x0057BC63 and removed by RET 0x10. Its ledger parameter spellings use struct (UFunctorBinding@@). Field names describe the proven roles.
// RVA 0x005185BA copies four dwords to wrapper +0x08; 0x00514EA0 invokes [wrapper+0x10] with ECX = [wrapper+0x08] + [wrapper+0x14], proving payload target +0, unmodelled word +4, and the {code, adjustment} member pointer +8/+0x0C. Stores at 0x00512240/43/46 leave +4 untouched; 0x00518B62/67/6F constructs the same payload for the int callback 0x0051890E, and 0x00442150/58/5B for the Rva0043E0C5 callback 0x0043E6C9.
// The tables belong to the enclosing 0x18-byte wrapper (allocation 0x0057BC64), not this payload: constructor 0x005185C6 stores VA 0x00C6FAA0 (slots RVA 0x005FAA31 and 0x00514EA0); its deleting destructor calls 0x004E84A4, which restores base table VA 0x00BC6F20. There is no rowed FunctorBinding constructor, destructor, copy, assignment or accessor.
#pragma once

#ifndef BFME2_FUNCTORBINDING_H
#define BFME2_FUNCTORBINDING_H

class __multiple_inheritance FunctorTarget;

struct FunctorBinding
{
	typedef void (FunctorTarget::*Method)();

	FunctorBinding(Method callback, FunctorTarget *object) : m_target(object), m_method(callback) {}
	template <class Target, class Argument>
	FunctorBinding(void (Target::*callback)(Argument), Target *object)
		: m_target(reinterpret_cast<FunctorTarget *>(object)), m_method(reinterpret_cast<Method>(callback)) {}

	FunctorTarget *m_target;
	unsigned int m_04;
	Method m_method;
};

#endif
