// cl: /Ireference/shims/bfme2_ascii /GX-
// ?buildDozer@AIDozerManager@@QAEXPAVObject@@@Z, retail 0x00599564, 162 bytes.
// Unlock lane; prev Rva00599534EraseFirst /O1 GX- SSE2; callers 0x00599EAC.
// Evidence: pin-only callees 0x002A8AB1 0x0028BC58; rowed 0x00327C1B 0x002D06CA;
// TheEmptyString; g_009FF000; TheSkirmishAIManager; virtual slots +0x44 +0x54 +0x8 +0x20.
#include "ascii_string.h"

class Object;
class Rva002A8F24;
class Rva002A8AB1Record;
class ProductionEntry;
class ThingTemplate;
class ThingFactory;
class SuffixObj;

class Object
{
public:
	void *rva0028BC58(int val);
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *p);
};

struct Rva002A8AB1Record
{
	char m_pad[0x16c];
	int m_16c; // +0x16c
};

class ProductionEntry
{
public:
	bool getProductionObject() const;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &s);
};

class SuffixObj
{
public:
	virtual void *v00();
	virtual void *v01();
	virtual void *v02(); // +0x8
	virtual void *v03();
	virtual void *v04();
	virtual void *v05();
	virtual void *v06();
	virtual void *v07();
	virtual void *v08(void *a1, int a2, void *a3, int a4, int a5, const AsciiString *a6, int a7); // +0x20
	virtual void *v09();
	virtual void *v0a();
	virtual void *v0b();
	virtual void *v0c();
	virtual void *v0d();
	virtual void *v0e();
	virtual void *v0f();
	virtual void *v10();
	virtual int v11(); // +0x44
	virtual void *v12();
	virtual void *v13();
	virtual void *v14();
	virtual ProductionEntry *v15(); // +0x54
};

extern Rva002A8F24 *TheSkirmishAIManager;
class ThingFactory;
extern ThingFactory *TheThingFactory;

class AIDozerManager
{
public:
	void buildDozer(Object *obj);
private:
	char m_pad00[8];
	AsciiString m_str; // +0x08
	void *m_0c; // +0x0c
	unsigned char m_10; // +0x10
};

void AIDozerManager::buildDozer(Object *obj)
{
	int zero = 0;
	Rva002A8AB1Record *rec = TheSkirmishAIManager->rva002A8AB1(m_0c);
	if (m_10 != zero || rec->m_16c > zero) {
		SuffixObj *suffixObj = (SuffixObj *)obj->rva0028BC58(zero);
		if (suffixObj != (SuffixObj *)zero) {
			if (suffixObj->v11() == 1) {
				ProductionEntry *productionEntry = suffixObj->v15();
				if (!productionEntry->getProductionObject())
					goto docall;
				ProductionEntry *d = suffixObj->v15();
				void *e = *(void **)((char *)d + 8);
				if ((((unsigned char *)e)[0x113] & 4) != 0)
					goto docall;
			}
			if (suffixObj->v11() != zero)
				goto done;
docall:
			void *r = suffixObj->v02();
			void *thingTemplate = (void *)reinterpret_cast<ThingFactory *>(TheThingFactory)->findTemplate(m_str);
			suffixObj->v08(thingTemplate, -1, r, -1, zero, &AsciiString::TheEmptyString, zero);
		}
	}
done:;
}
