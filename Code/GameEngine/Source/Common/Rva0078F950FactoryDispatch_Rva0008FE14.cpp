// cl: -DNDEBUG -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?selectFactory@Rva0078F830Owner@@QAEHPAURva0078F950Record@@HHH@Z
// retail 0x0008FE14, 112 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Rva0078F950FactoryDispatch.cpp
// (reference/open-bfme-1). Compiled /Os the donor body is byte-identical to
// retail once relocations are masked (unique hit on unclaimed .text). Only the
// placed body is defined here; the donor's other 10 definitions are omitted.
//
// The dispatch is a 3-way select on the context flags: bit 0x10 pairs with the
// record's kind byte tested against 0x80, bit 8 additionally consults the
// head predicate's flag byte, and neither set leaves the record untouched and
// returns 0. Each arm stores one of four factory constructors into
// record->m_factory and hands off to dispatchFactory.
// shared handler; the explicit one-byte local preserves the retail
// mov/test branch shape while the argument record selects one of the two
// already reconstructed 0x2F8-byte object factories.

class Rva007903F0VptrCtor;
class Rva00790480VptrCtor;
class Rva00793150VptrCtor;
class Rva007931B0VptrCtor;
class Rva00798510VptrCtor;
class Rva007985A0VptrCtor;
class Rva00796A60VptrCtor;
class Rva00796AF0VptrCtor;
class Rva00793D30VptrCtor;
class Rva00793E00VptrCtor;
class Rva007961D0VptrCtor;
class Rva00796260VptrCtor;
class Rva0078FCA0VptrCtor;
class Rva0078FD30VptrCtor;
class GameWindow;
class GameFont;

class DisplayString
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual int getTextLength();
};

class WinInstanceData
{
public:
	char m_gap00[0xc];
	unsigned int m_style;
	char m_gap10[0x174];
	GameFont *m_font;
	char m_gap188[0x14];
	DisplayString *m_text;
	inline int getTextLength()
	{
		if (m_text != 0)
			return m_text->getTextLength();
		return 0;
	}
};

struct Rva0078F770ListboxData
{
	short m_listLength;
	char m_gap02[8];
	unsigned char m_scrollBar;
	char m_gap0b[0x1d];
	int m_totalHeight;
	short m_insertPos;
	short m_selectPos;
	char m_gap30[4];
	int m_scrollPosition;
	char m_gap38[4];
	short m_displayHeight;
	char m_gap3e[2];
	int m_displayPos;
	short m_totalHeightShort;
	char m_gap46[6];
};

class GameWindow
{
public:
	void winSetUserData(void *data);
	int winSetOwner(GameWindow *owner);
};

void j_00002e69();
void j_000194a7();
void j_000272fa();
void j_0002d939();
void j_00047230();
class Rva007996A0VptrCtor;
class Rva00799730VptrCtor;
class Rva00790C40VptrCtor;
class Rva00790CD0VptrCtor;

Rva007903F0VptrCtor *__stdcall Rva0078F100New(void *argument);
Rva00790480VptrCtor *__stdcall Rva0078F180New(void *argument);
Rva00793150VptrCtor *__stdcall Rva0078F200New(void *argument);
Rva007931B0VptrCtor *__stdcall Rva0078F280New(void *argument);
Rva00798510VptrCtor *__stdcall Rva0078EE00New(void *argument);
Rva007985A0VptrCtor *__stdcall Rva0078EE80New(void *argument);
Rva00796A60VptrCtor *__stdcall Rva0078E8F0New(void *argument);
Rva00796AF0VptrCtor *__stdcall Rva0078E970New(void *argument);
Rva00793D30VptrCtor *__stdcall Rva0078E9F0New(void *argument);
Rva00793E00VptrCtor *__stdcall Rva0078EA70New(void *argument);
Rva007961D0VptrCtor *__stdcall Rva0078EB00New(void *argument);
Rva00796260VptrCtor *__stdcall Rva0078EB80New(void *argument);
Rva0078FCA0VptrCtor *__stdcall Rva0078EC00New(void *argument);
Rva0078FD30VptrCtor *__stdcall Rva0078EC80New(void *argument);
Rva007996A0VptrCtor *__stdcall Rva0078F300New(void *argument);
Rva00799730VptrCtor *__stdcall Rva0078F380New(void *argument);
Rva00790C40VptrCtor *__stdcall Rva0078F400New(void *argument);
Rva00790CD0VptrCtor *__stdcall Rva0078F480New(void *argument);
void *__stdcall Rva0078ED00New(void *argument);
void *__stdcall Rva0078ED80New(void *argument);
void *__stdcall Rva0078EF00New(void *argument);
void *__stdcall Rva0078EF80New(void *argument);
void *__stdcall Rva0078F000New(void *argument);
void *__stdcall Rva0078F080New(void *argument);

typedef void *(__stdcall *Rva0078F950Factory)(void *argument);

class Rva0078F830Predicate
{
public:
	unsigned char flags(void);
};

struct Rva0078F830Context
{
	char m_gap[12];
	unsigned int m_flags;
};

struct Rva0078F950Record
{
	Rva0078F830Predicate *m_head;
	signed char m_kind;
	char m_gap[15];
	short m_height;
	char m_gapAfterHeight[2];
	Rva0078F950Factory m_factory;
	char m_gap2[20];
	union
	{
		Rva0078F830Context *m_context;
		WinInstanceData *m_instanceData;
	};
};

class Rva0078F950Owner
{
public:
	void selectFactory(Rva0078F950Record *record);
	void dispatchFactory(Rva0078F950Record *record);
};

class Rva0078F8D0Owner
{
public:
	void selectFactory(Rva0078F950Record *record);
	void dispatchFactory(Rva0078F950Record *record);
};

class Rva0078F910Owner
{
public:
	void selectFactory(Rva0078F950Record *record);
	void dispatchFactory(Rva0078F950Record *record);
};

#define DECLARE_FACTORY_SELECTOR_OWNER(address) \
	class Rva##address##Owner \
	{ \
	public: \
		void selectFactory(Rva0078F950Record *record); \
		void dispatchFactory(Rva0078F950Record *record); \
	}

DECLARE_FACTORY_SELECTOR_OWNER(0078F630);
DECLARE_FACTORY_SELECTOR_OWNER(0078F670);
DECLARE_FACTORY_SELECTOR_OWNER(0078F6B0);
DECLARE_FACTORY_SELECTOR_OWNER(0078F6F0);

class Rva0078F730Owner
{
public:
	void selectFactory(Rva0078F950Record *record, int first, int second,
		int third);
	void dispatchFactory(Rva0078F950Record *record, int first, int second,
		int third);
};

struct Rva0078F770Secondary
{
	char m_gap[11];
	unsigned char m_flag;
	char m_rest[0x40];
};

class Rva0078F770Owner
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void assignDefaultGadgetLook(GameWindow *, int, int);
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual GameWindow *create(void *record);
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual int winFontHeight(GameFont *font);

	void selectFactory(Rva0078F950Record *record,
		Rva0078F770Secondary *secondary, int ignored, int value);
	GameWindow *dispatchFactory(Rva0078F950Record *record,
		Rva0078F770Secondary *secondary, int ignored, int value);
};

class Rva0078F830Owner
{
public:
	int selectFactory(Rva0078F950Record *record, int first, int second,
		int third);
	int dispatchFactory(Rva0078F950Record *record, int first, int second,
		int third);
};

int Rva0078F830Owner::selectFactory(Rva0078F950Record *record, int first,
	int second, int third)
{
	unsigned int flags = record->m_context->m_flags;

	if (flags & 0x10)
	{
		if (record->m_kind & 0x80)
			record->m_factory = (Rva0078F950Factory)Rva0078F480New;
		else
			record->m_factory = (Rva0078F950Factory)Rva0078F400New;
	}
	else if (flags & 8)
	{
		if ((record->m_kind & 0x80) && (record->m_head == 0 ||
			!(record->m_head->flags() & 0x20)))
			record->m_factory = (Rva0078F950Factory)Rva0078F380New;
		else
			record->m_factory = (Rva0078F950Factory)Rva0078F300New;
	}
	else
	{
		return 0;
	}

	return dispatchFactory(record, first, second, third);
}
