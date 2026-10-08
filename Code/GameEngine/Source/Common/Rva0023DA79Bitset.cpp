// cl: /MD /GX
// ?rva0023DA79@Rva0023DA79@@QAEPAV1@HH@Z @0x0023DA79 (44B): memset-16 plus
// bit-set returning this. Retail: push esi; push 16; esi=ecx; push 0;
// push esi; call memset (0x6291AE import); ecx=[esp+24] (index); edx=0;
// eax=ecx; ecx&=31; edx=1; eax>>=5; edx<<=cl; eax=this+eax*4;
// add esp,12; [eax]|=edx; eax=esi; pop esi; ret 8. Two int args (first
// ignored beyond stack slot? second is index? actually [esp+24] after
// pushes = original second arg?); memset size const 16; no EH; imports
// resolve; address-derived.
#include <string.h>

class Rva0023DA79
{
public:
	Rva0023DA79 *rva0023DA79(int ignored, int index);
private:
	unsigned int m_bits[4];
};

// ?rva0023DA79@Rva0023DA79@@QAEPAV1@HH@Z
Rva0023DA79 *Rva0023DA79::rva0023DA79(int ignored, int index)
{
	(void)ignored;
	memset(this, 0, 16);
	m_bits[(unsigned)index >> 5] |= (1u << ((unsigned)index & 31));
	return this;
}

// BFME1 9cbfb551 OpenContain.cpp emits _Base_bitset<4>::_M_do_flip.
// Native 332E83..332E8F is a complete leaf after bounded 332E60+35:
// four consecutive 32-bit words are complemented in an unsigned loop.
// Preserve the unknown owning type with an address-derived storage view.
class Rva00332E83BitWords
{
public:
    void flip();
    unsigned int m_words[4];
};
void Rva00332E83BitWords::flip()
{
    for (unsigned int i = 0; i < 4; ++i)
        m_words[i] = ~m_words[i];
}
