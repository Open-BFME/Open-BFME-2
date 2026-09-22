// cl: /O1 /GX /DNDEBUG /MD
//
// The <Something>Nugget field callbacks of the INI `Weapon` block: BFME2's
// WeaponTemplate FieldParse table at 0x00800B48 pairs each nugget keyword with
// one of these (INI*, WeaponTemplate*) __cdecl bodies. Same job as BFME1's
// WeaponNuggetParse.cpp, rebuilt for BFME2's shape: new the nugget, run its
// out-of-line ctor, point it at the weapon (+0x104), run its four-argument
// field parser, then hand it to the weapon through one out-of-line member
// (0x002CBA59). Four of them also raise a flag byte on the weapon afterwards.
//
// Only the entry points are named, from their keywords, in BFME1's
// parse<Keyword> spelling. The nugget classes, their ctors and field parsers
// keep BFME1's address-derived Made/q4Notify names (keyed on each entry's BFME2
// RVA), and the append member is rva002CBA59: none of them is identified.

class INI;

class WeaponTemplate
{
public:
	void rva002CBA59(void *nugget);

	char m_gap0[0x114];
	bool m_flag114;		// +0x114
	char m_gap115[0x157 - 0x115];
	bool m_flag157;		// +0x157
};

struct WeaponNuggetHead
{
	char m_gap0[0x104];
	WeaponTemplate *m_owner;	// +0x104
};

// "DamageNugget": 0x002CC5E1, news 0x1A4, ctor 0x00507C2D, field parser 0x005088F0
class Made002CC5E1 : public WeaponNuggetHead
{
public:
	Made002CC5E1();
private:
	char m_tail[0x1A4 - 0x108];
};
void q4Notify002CC5E1(void *ini, Made002CC5E1 *m, int c, int d);

// ?parseDamageNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseDamageNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CC5E1 *m = new Made002CC5E1;
	m->m_owner = weapon;
	q4Notify002CC5E1(ini, m, 0, 0);
	weapon->rva002CBA59(m);
	weapon->m_flag114 = true;
}

// "DamageFieldNugget": 0x002CC774, news 0x134, ctor 0x00509522, field parser 0x00509379
class Made002CC774 : public WeaponNuggetHead
{
public:
	Made002CC774();
private:
	char m_tail[0x134 - 0x108];
};
void q4Notify002CC774(void *ini, Made002CC774 *m, int c, int d);

// ?parseDamageFieldNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseDamageFieldNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CC774 *m = new Made002CC774;
	m->m_owner = weapon;
	q4Notify002CC774(ini, m, 0, 0);
	weapon->rva002CBA59(m);
	weapon->m_flag114 = true;
}

// "WeaponOCLNugget": 0x002CC7DE, news 0x130, ctor 0x0050968B, field parser 0x005095AE
class Made002CC7DE : public WeaponNuggetHead
{
public:
	Made002CC7DE();
private:
	char m_tail[0x130 - 0x108];
};
void q4Notify002CC7DE(void *ini, Made002CC7DE *m, int c, int d);

// ?parseWeaponOCLNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseWeaponOCLNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CC7DE *m = new Made002CC7DE;
	m->m_owner = weapon;
	q4Notify002CC7DE(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "ProjectileNugget": 0x002CC841, news 0x154, ctor 0x00509CC3, field parser 0x00509780
class Made002CC841 : public WeaponNuggetHead
{
public:
	Made002CC841();
private:
	char m_tail[0x154 - 0x108];
};
void q4Notify002CC841(void *ini, Made002CC841 *m, int c, int d);

// ?parseProjectileNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseProjectileNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CC841 *m = new Made002CC841;
	m->m_owner = weapon;
	q4Notify002CC841(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "MetaImpactNugget": 0x002CC8A4, news 0x164, ctor 0x0050A39B, field parser 0x00509DAB
class Made002CC8A4 : public WeaponNuggetHead
{
public:
	Made002CC8A4();
private:
	char m_tail[0x164 - 0x108];
};
void q4Notify002CC8A4(void *ini, Made002CC8A4 *m, int c, int d);

// ?parseMetaImpactNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseMetaImpactNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CC8A4 *m = new Made002CC8A4;
	m->m_owner = weapon;
	q4Notify002CC8A4(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "HordeAttackNugget": 0x002CCBCA, news 0x130, ctor 0x0050B8B3, field parser 0x0050B6F8
class Made002CCBCA : public WeaponNuggetHead
{
public:
	Made002CCBCA();
private:
	char m_tail[0x130 - 0x108];
};
void q4Notify002CCBCA(void *ini, Made002CCBCA *m, int c, int d);

// ?parseHordeAttackNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseHordeAttackNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CCBCA *m = new Made002CCBCA;
	m->m_owner = weapon;
	q4Notify002CCBCA(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "SpawnAndFadeNugget": 0x002CCC2D, news 0x13C, ctor 0x0050BB0E, field parser 0x0050B8DB
class Made002CCC2D : public WeaponNuggetHead
{
public:
	Made002CCC2D();
private:
	char m_tail[0x13C - 0x108];
};
void q4Notify002CCC2D(void *ini, Made002CCC2D *m, int c, int d);

// ?parseSpawnAndFadeNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseSpawnAndFadeNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CCC2D *m = new Made002CCC2D;
	m->m_owner = weapon;
	q4Notify002CCC2D(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "GrabNugget": 0x002CC907, news 0x140, ctor 0x0050AA97, field parser 0x0050A7E5
class Made002CC907 : public WeaponNuggetHead
{
public:
	Made002CC907();
private:
	char m_tail[0x140 - 0x108];
};
void q4Notify002CC907(void *ini, Made002CC907 *m, int c, int d);

// ?parseGrabNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseGrabNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CC907 *m = new Made002CC907;
	m->m_owner = weapon;
	q4Notify002CC907(ini, m, 0, 0);
	weapon->rva002CBA59(m);
	weapon->m_flag157 = true;
}

// "AttributeModifierNugget": 0x002CC64B, news 0x140, ctor 0x00508BE5, field parser 0x0050893A
class Made002CC64B : public WeaponNuggetHead
{
public:
	Made002CC64B();
private:
	char m_tail[0x140 - 0x108];
};
void q4Notify002CC64B(void *ini, Made002CC64B *m, int c, int d);

// ?parseAttributeModifierNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseAttributeModifierNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CC64B *m = new Made002CC64B;
	m->m_owner = weapon;
	q4Notify002CC64B(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "SpecialModelConditionNugget": 0x002CC6AE, news 0x138, ctor 0x00508E11, field parser 0x00508D2F
class Made002CC6AE : public WeaponNuggetHead
{
public:
	Made002CC6AE();
private:
	char m_tail[0x138 - 0x108];
};
void q4Notify002CC6AE(void *ini, Made002CC6AE *m, int c, int d);

// ?parseSpecialModelConditionNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseSpecialModelConditionNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CC6AE *m = new Made002CC6AE;
	m->m_owner = weapon;
	q4Notify002CC6AE(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "ParalyzeNugget": 0x002CC711, news 0x138, ctor 0x00508F51, field parser 0x00508EBF
class Made002CC711 : public WeaponNuggetHead
{
public:
	Made002CC711();
private:
	char m_tail[0x138 - 0x108];
};
void q4Notify002CC711(void *ini, Made002CC711 *m, int c, int d);

// ?parseParalyzeNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseParalyzeNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CC711 *m = new Made002CC711;
	m->m_owner = weapon;
	q4Notify002CC711(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "LuaEventNugget": 0x002CCC90, news 0x134, ctor 0x0050BD45, field parser 0x0050BBEB
class Made002CCC90 : public WeaponNuggetHead
{
public:
	Made002CCC90();
private:
	char m_tail[0x134 - 0x108];
};
void q4Notify002CCC90(void *ini, Made002CCC90 *m, int c, int d);

// ?parseLuaEventNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseLuaEventNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CCC90 *m = new Made002CCC90;
	m->m_owner = weapon;
	q4Notify002CCC90(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "FireLogicNugget": 0x002CCCF3, news 0x1B4, ctor 0x0050BF8F, field parser 0x0050BDED
class Made002CCCF3 : public WeaponNuggetHead
{
public:
	Made002CCCF3();
private:
	char m_tail[0x1B4 - 0x108];
};
void q4Notify002CCCF3(void *ini, Made002CCCF3 *m, int c, int d);

// ?parseFireLogicNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseFireLogicNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CCCF3 *m = new Made002CCCF3;
	m->m_owner = weapon;
	q4Notify002CCCF3(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "SlaveAttackNugget": 0x002CC971, news 0x128, ctor 0x0050ABF7, field parser 0x0050AAEA
class Made002CC971 : public WeaponNuggetHead
{
public:
	Made002CC971();
private:
	char m_tail[0x128 - 0x108];
};
void q4Notify002CC971(void *ini, Made002CC971 *m, int c, int d);

// ?parseSlaveAttackNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseSlaveAttackNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CC971 *m = new Made002CC971;
	m->m_owner = weapon;
	q4Notify002CC971(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "DamageContainedNugget": 0x002CC9D4, news 0x168, ctor 0x0050AEAB, field parser 0x0050ADB9
class Made002CC9D4 : public WeaponNuggetHead
{
public:
	Made002CC9D4();
private:
	char m_tail[0x168 - 0x108];
};
void q4Notify002CC9D4(void *ini, Made002CC9D4 *m, int c, int d);

// ?parseDamageContainedNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseDamageContainedNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CC9D4 *m = new Made002CC9D4;
	m->m_owner = weapon;
	q4Notify002CC9D4(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "DOTNugget": 0x002CCA37, news 0x1AC, ctor 0x0050B1FC, field parser 0x0050B13A
class Made002CCA37 : public WeaponNuggetHead
{
public:
	Made002CCA37();
private:
	char m_tail[0x1AC - 0x108];
};
void q4Notify002CCA37(void *ini, Made002CCA37 *m, int c, int d);

// ?parseDOTNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseDOTNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CCA37 *m = new Made002CCA37;
	m->m_owner = weapon;
	q4Notify002CCA37(ini, m, 0, 0);
	weapon->rva002CBA59(m);
	weapon->m_flag114 = true;
}

// "OpenGateNugget": 0x002CCAA1, news 0x12C, ctor 0x0050B374, field parser 0x0050B23B
class Made002CCAA1 : public WeaponNuggetHead
{
public:
	Made002CCAA1();
private:
	char m_tail[0x12C - 0x108];
};
void q4Notify002CCAA1(void *ini, Made002CCAA1 *m, int c, int d);

// ?parseOpenGateNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseOpenGateNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CCAA1 *m = new Made002CCAA1;
	m->m_owner = weapon;
	q4Notify002CCAA1(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "EmotionWeaponNugget": 0x002CCB04, news 0x134, ctor 0x0050B59B, field parser 0x0050B42C
class Made002CCB04 : public WeaponNuggetHead
{
public:
	Made002CCB04();
private:
	char m_tail[0x134 - 0x108];
};
void q4Notify002CCB04(void *ini, Made002CCB04 *m, int c, int d);

// ?parseEmotionWeaponNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseEmotionWeaponNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CCB04 *m = new Made002CCB04;
	m->m_owner = weapon;
	q4Notify002CCB04(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}

// "StealMoneyNugget": 0x002CCB67, news 0x12C, ctor 0x0050B6B4, field parser 0x0050B5F6
class Made002CCB67 : public WeaponNuggetHead
{
public:
	Made002CCB67();
private:
	char m_tail[0x12C - 0x108];
};
void q4Notify002CCB67(void *ini, Made002CCB67 *m, int c, int d);

// ?parseStealMoneyNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z
void parseStealMoneyNugget(INI *ini, WeaponTemplate *weapon)
{
	Made002CCB67 *m = new Made002CCB67;
	m->m_owner = weapon;
	q4Notify002CCB67(ini, m, 0, 0);
	weapon->rva002CBA59(m);
}
