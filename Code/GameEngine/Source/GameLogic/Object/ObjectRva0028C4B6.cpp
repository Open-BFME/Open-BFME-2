// cl: /DNDEBUG /MD /EHsc
// ?rva0028C4B6@Object@@QAEXXZ @0x0028C4B6 55B
// Object provider-gated global flag set: prov = rva0028C197(); if prov and slot60 and slot23 then call slot24 and set holder+0x28.
// Evidence: rowed rva0028C197 plus virtual slots 0xF0 0x5C 0x60 and VA 0x00E01CFC+0x28; callers 0x0028DF48 0x0028E01F 0x0028E0F9 0x0028E151;
// neighbours ObjectRva0028C264 and ObjectRva0028C4ED give TU and flags.
extern struct BfmeWorldRV *g_bfmeWorldRV;

class Rva0028C4B6Provider
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual bool slot23();
	virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28();
	virtual void slot29(); virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40();
	virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48();
	virtual void slot49(); virtual void slot50(); virtual void slot51(); virtual void slot52();
	virtual void slot53(); virtual void slot54(); virtual void slot55(); virtual void slot56();
	virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual bool slot60();
};

struct BfmeHolder0028C4B6
{
	unsigned char m_pad[0x28];
	unsigned char m_28; // +0x28
};

#define BfmeHolder0028C4B6Ptr (*(BfmeHolder0028C4B6 **)&g_bfmeWorldRV)

class Object
{
public:
	void *rva0028C197() const;
	void rva0028C4B6();
};

void Object::rva0028C4B6()
{
	Rva0028C4B6Provider *prov = (Rva0028C4B6Provider *)rva0028C197();
	if (prov == 0)
		return;
	if (!prov->slot60())
		return;
	if (!prov->slot23())
		return;
	prov->slot24();
	BfmeHolder0028C4B6Ptr->m_28 = 1;
}
