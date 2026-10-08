// ?rva001EDE9C@@YAXXZ
// partial score=0.85 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc
// ?rva001EDE9C@@YAXXZ 0x001EDE9C 59B. Free function over three globals: TheTacticalView vslot 0x1CC
// gates a call on TheGameLogic isGamePaused (0x0023CD97), then TheMouse vslot 0x58 runs on every path.
class View
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3C();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4C();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5C();
	virtual void v60();
	virtual void v64();
	virtual void v68();
	virtual void v6C();
	virtual void v70();
	virtual void v74();
	virtual void v78();
	virtual void v7C();
	virtual void v80();
	virtual void v84();
	virtual void v88();
	virtual void v8C();
	virtual void v90();
	virtual void v94();
	virtual void v98();
	virtual void v9C();
	virtual void vA0();
	virtual void vA4();
	virtual void vA8();
	virtual void vAC();
	virtual void vB0();
	virtual void vB4();
	virtual void vB8();
	virtual void vBC();
	virtual void vC0();
	virtual void vC4();
	virtual void vC8();
	virtual void vCC();
	virtual void vD0();
	virtual void vD4();
	virtual void vD8();
	virtual void vDC();
	virtual void vE0();
	virtual void vE4();
	virtual void vE8();
	virtual void vEC();
	virtual void vF0();
	virtual void vF4();
	virtual void vF8();
	virtual void vFC();
	virtual void v100();
	virtual void v104();
	virtual void v108();
	virtual void v10C();
	virtual void v110();
	virtual void v114();
	virtual void v118();
	virtual void v11C();
	virtual void v120();
	virtual void v124();
	virtual void v128();
	virtual void v12C();
	virtual void v130();
	virtual void v134();
	virtual void v138();
	virtual void v13C();
	virtual void v140();
	virtual void v144();
	virtual void v148();
	virtual void v14C();
	virtual void v150();
	virtual void v154();
	virtual void v158();
	virtual void v15C();
	virtual void v160();
	virtual void v164();
	virtual void v168();
	virtual void v16C();
	virtual void v170();
	virtual void v174();
	virtual void v178();
	virtual void v17C();
	virtual void v180();
	virtual void v184();
	virtual void v188();
	virtual void v18C();
	virtual void v190();
	virtual void v194();
	virtual void v198();
	virtual void v19C();
	virtual void v1A0();
	virtual void v1A4();
	virtual void v1A8();
	virtual void v1AC();
	virtual void v1B0();
	virtual void v1B4();
	virtual void v1B8();
	virtual void v1BC();
	virtual void v1C0();
	virtual void v1C4();
	virtual void v1C8();
	virtual bool slot1CC();
};

class GameLogic
{
public:
	unsigned char isGamePaused();
};

class Mouse
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3C();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4C();
	virtual void v50();
	virtual void v54();
	virtual void slot58();
};

extern View *TheTacticalView;
extern GameLogic *TheGameLogic;
extern Mouse *TheMouse;

void rva001EDE9C()
{
	if (TheTacticalView && TheTacticalView->slot1CC())
	{
		if (TheGameLogic->isGamePaused())
		{
			TheMouse->slot58();
			return;
		}
		TheMouse->slot58();
		return;
	}
	TheMouse->slot58();
}
