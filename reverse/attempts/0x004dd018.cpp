// ?rva004DD018@Emotion@@QAE_NHHPAURva004DD018Arg@@@Z
// partial score=0.89 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHs /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva004DD018@Emotion@@QAE_NHHPAURva004DD018Arg@@@Z @ 0x004DD018 (494B).
// Chain from just-landed Object::rva0028C149: Emotion predicate over entry
// delays, map expiry, attribute 4/5 via the pool and AI state 0x2D.
// Evidence: same Emotion/Entry/maps family as banked 0x004DD2C0;
// callees rowed testStatus 0x0004E536, rva0028AFBB, map find/erase,
// rva0028C197, rva0028C149, getCurrentStateID 0x00262FC3,
// TheGameLogic 0x009FE78C, g_Va007C26F0; callers at 0x004B10E3, 0x004B14B0,
// 0x004B1572, 0x004B1ABE, 0x004B1B69 pass (int,int,ptr) with ret 0xC.

#include <map>
#include "ascii_string.h"

struct Gen_lt_00940b40 : public _STL::less<unsigned short> {};

enum ObjectStatusTypes
{
	STATUS_46 = 0x46
};

class Object;
class AttributeModifierPoolUpdate;
class AIUpdateInterface;
class Player;

class GameLogic
{
public:
	char m_pad00[0x40];
	int m_frame;
};

extern GameLogic *TheGameLogic;
extern float g_Va007C26F0;

class AttributeModifierPoolUpdate
{
public:
	bool rva00403382(int attribute, float *value, int arg);
};

class AIUpdateInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
	virtual void v88(); virtual void v89(); virtual void v90();
	virtual bool v91();
	virtual void v92(); virtual void v93(); virtual void v94(); virtual void v95();
	virtual void v96(); virtual void v97(); virtual void v98(); virtual void v99();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103();
	virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107();
	virtual void v108(); virtual void v109();
	virtual bool v110();
	int getCurrentStateID() const;
};

class Rva0028C197Provider
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual Object *v68();
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	bool rva0028AFBB() const;
	void *rva0028C197() const;
	bool rva0028C149(int attribute, float *value, int arg);
};

struct Rva004DD018Inner
{
	char m_pad00[0x5D8];
	unsigned short m_5D8;
};

struct Rva004DD018Arg
{
	char m_pad00[0x04];
	Rva004DD018Inner *m_04;
	char m_pad08[0x74 - 0x08];
	int m_74;
};

class EmotionEntry
{
public:
	char m_pad00[0x04];
	int m_04;
	unsigned char m_08;
	unsigned char m_09;
	char m_pad0A[0x10 - 0x0A];
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	unsigned char m_2C;
	unsigned char m_2D;
	char m_pad2E[0x38 - 0x2E];
	const void *m_fx38;
	AsciiString m_str3C;
	int m_40;
	unsigned char m_flag44;
	char m_pad45[3];
	int m_48;
	int m_4C;
};

class Emotion
{
public:
	bool rva004DD018(int a, int b, Rva004DD018Arg *arg);
private:
	Object *m_object;
	EmotionEntry *m_entry;
	int m_id08;
	unsigned short m_key0C;
	char m_pad0E[2];
	int m_frame10;
	_STL::map<int, int> m_map14x;
	_STL::map<unsigned short, int, Gen_lt_00940b40> m_map20x;
	int m_2C;
	int m_start30;
};

// ?rva004DD018@Emotion@@QAE_NHHPAURva004DD018Arg@@@Z present-unmatched
bool Emotion::rva004DD018(int a, int b, Rva004DD018Arg *arg)
{
	Object *obj = m_object;
	if (obj->testStatus(STATUS_46))
		return false;
	if (m_entry->m_08 || m_entry->m_09)
	{
		AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)obj + 0x258);
		if (!ai)
			return false;
		if (!ai->v110())
		{
			if (m_entry->m_09)
				return false;
		}
		else if (ai->v91())
		{
			if (m_entry->m_09)
				return false;
		}
		else
		{
			if (m_entry->m_08)
				return false;
			goto check2c;
		}
	}
check2c:
	if (!m_entry->m_2C)
	{
		if (m_entry->m_2D)
		{
			if (!obj->rva0028AFBB())
				return false;
			if (m_entry->m_2D)
				return true;
			return false;
		}
	}
	else
	{
		if (!obj->rva0028AFBB())
			return false;
		if (!m_entry->m_2D)
			return false;
	}
	if (m_entry->m_1C * a + m_entry->m_20 >= 0)
		return false;
	if (m_entry->m_24 * b + m_entry->m_28 >= 0)
		return false;
	int frame = TheGameLogic->m_frame;
	if (frame < m_frame10)
		return false;
	b = frame;
	if (!arg)
		goto attr;
	{
		int key = arg->m_74;
		_STL::map<int, int>::iterator it = m_map14x.find(key);
		if (it._M_node != m_map14x.end()._M_node)
		{
			if (b < it->second)
				return false;
			m_map14x.erase(it);
		}
	}
	{
		unsigned short key = arg->m_04->m_5D8;
		_STL::map<unsigned short, int, Gen_lt_00940b40>::iterator it = m_map20x.find(key);
		if (it._M_node != m_map20x.end()._M_node)
		{
			if (TheGameLogic->m_frame < it->second)
				return false;
			m_map20x.erase(it);
		}
	}
attr:
	if (m_entry->m_04 < 4 || m_entry->m_04 > 7)
		return false;
	Object *target = m_object;
	{
		void *tpl = *(void **)((char *)target + 4);
		if (*(unsigned char *)((char *)tpl + 0x115) & 0x20)
		{
			void *prov = target->rva0028C197();
			if (prov)
				target = ((Rva0028C197Provider *)prov)->v68();
		}
	}
	if (!target)
		return false;
	*(float *)&a = 0.0f;
	int attrKind = 4 + (m_entry->m_04 == 6 ? 1 : 0);
	bool ok = target->rva0028C149(attrKind, (float *)&a, 0);
	bool use = true;
	if (ok)
	{
		if (g_Va007C26F0 <= *(float *)&a)
			use = false;
		else
			use = true;
	}
	AIUpdateInterface *aai = *(AIUpdateInterface **)((char *)target + 0x258);
	if (aai)
	{
		if (aai->getCurrentStateID() == 0x2D)
			use = false;
	}
	if (!use)
		return false;
	return true;
}
