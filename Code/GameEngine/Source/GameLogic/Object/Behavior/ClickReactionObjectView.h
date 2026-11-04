// Shared private Object/AI view for the ClickReactionBehavior donors.
// The reaction body establishes model flags at +0x10C and AI at +0x258;
// the update body uses the same AI pointer and virtual slot 110.
#pragma once

class Drawable;

class AIUpdateInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s0A(); virtual void s0B(); virtual void s0C(); virtual void s0D(); virtual void s0E();
	virtual void s0F(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
	virtual void s19(); virtual void s1A(); virtual void s1B(); virtual void s1C(); virtual void s1D();
	virtual void s1E(); virtual void s1F(); virtual void s20(); virtual void s21(); virtual void s22();
	virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s2A(); virtual void s2B(); virtual void s2C();
	virtual void s2D(); virtual void s2E(); virtual void s2F(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
	virtual void s37(); virtual void s38(); virtual void s39(); virtual void s3A(); virtual void s3B();
	virtual void s3C(); virtual void s3D(); virtual void s3E(); virtual void s3F(); virtual void s40();
	virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45();
	virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49(); virtual void s4A();
	virtual void s4B(); virtual void s4C(); virtual void s4D(); virtual void s4E(); virtual void s4F();
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
	virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s5A(); virtual void s5B(); virtual void s5C(); virtual void s5D(); virtual void s5E();
	virtual void s5F(); virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68();
	virtual void s69(); virtual void s6A(); virtual void s6B(); virtual void s6C(); virtual void s6D();
	virtual bool isIdle(); // slot 110 (+0x1B8)
};

static __forceinline bool testWordBit(const unsigned int *words, unsigned int bit)
{
	return (words[bit >> 5] >> (bit & 0x1f)) & 1;
}

class Rva0028B7AELeaGetter
{
public:
	void *get() const; // 0x0028B7AE
};

#include "../../../../Include/GameClient/Drawable.h"

class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}

	unsigned int m_words[19];
};

class Object
{
public:
	Drawable *getDrawable() const; // Thing::getDrawable 0x005508E2
	void rva0028AE6D();
	bool testCondition(unsigned int bit) const
	{
		return testWordBit(m_modelConditionFlags.m_words, bit);
	}
	__forceinline void setModelConditionState(unsigned int bit)
	{
		if (m_modelConditionFlags.test(bit) == 0)
		{
			m_modelConditionFlags.set(bit);
			rva0028AE6D();
		}
	}

	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
};
