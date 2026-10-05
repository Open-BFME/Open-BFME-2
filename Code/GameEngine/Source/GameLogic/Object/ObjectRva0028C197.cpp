// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva0028C197@Object@@QBEPAXXZ @0x0028C197 18B
// Object null-checked tail forward through the +0x250 interface (same offset
// Object_isAbleToAttack.cpp and Weapon_getRemainingAmmo.cpp document) to its
// vtable slot 0x7c. Retail shape is mov ecx+0x250 plus test plus jne plus
// xor-ret plus indirect jmp. 40-plus callers including 0x0028C4B6. Landing
// unblocks 70. Identity beyond the Object owner is unproven so the name
// stays address-derived. Flags from the same-page Object sibling
// Object_bfmeRefreshPartitionCells.cpp; if (p == 0) selects the retail jne.

// Interface returned by slot 31 of the +0x250 provider; 0x0028C173 calls
// its slot 96 (+0x180) with a zero argument.
class Rva0028C173Iface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83();
	virtual void s84(); virtual void s85(); virtual void s86(); virtual void s87();
	virtual void s88(); virtual void s89(); virtual void s90(); virtual void s91();
	virtual void s92(); virtual void s93(); virtual void s94(); virtual void s95();
	virtual int slot96(int arg);
};

class Rva0028C197Provider
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual Rva0028C173Iface *slot31();
};

class BfmeObjectModule
{
public:
	virtual void slot0();

private:
	unsigned int m_data[2];
};

class BehaviorModuleInterface37
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36();
	virtual void *slot37();
};

class BehaviorModule37 : public BfmeObjectModule, public BehaviorModuleInterface37
{
};

class Object
{
	char m_pad[0x244];
	BehaviorModule37 **m_modules244;
	char m_pad248[0x250 - 0x248];
	Rva0028C197Provider *m_provider250;

public:
	int rva0028C173() const;
	void *rva0028C197() const;
	void *rva0028C1A9() const;
};

// ?rva0028C173@Object@@QBEHXZ @0x0028C173 36B. Same +0x250 provider: asks
// its slot 31 for the interface (inline, unlike 0x0028C197) and returns that
// interface's slot 96 answer for argument 0; a missing provider or interface
// answers 1 (xor eax,eax / inc eax, so an int, not a bool).
int Object::rva0028C173() const
{
	Rva0028C197Provider *provider = m_provider250;
	if (provider)
	{
		Rva0028C173Iface *iface = provider->slot31();
		if (iface)
			return iface->slot96(0);
	}
	return 1;
}

void *Object::rva0028C197() const
{
	Rva0028C197Provider *provider = m_provider250;
	if (provider == 0)
		return 0;
	return provider->slot31();
}

void *Object::rva0028C1A9() const
{
	for (BehaviorModule37 **m = m_modules244; *m; ++m)
	{
		void *p = (*m)->slot37();
		if (p)
			return p;
	}
	return 0;
}
