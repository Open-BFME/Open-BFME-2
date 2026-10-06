// cl: /MD
//
// ?rva0049AE5E@Rva0049AE5E@@QAEXXZ @ 0x0049AE5E 70B
// Checks three ObjectIDs at +0x3E8 +0x3EC +0x3F0 via rowed
// GameLogic::findObjectByID; clears byte at +0x3CA if all three miss.
// Evidence: TheGameLogic extern use; caller 0x0049AED7; unlocks 0x0049AEA4.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
class Object
{
public:
	void *rva0028C197() const;
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class Rva0049ADB7Target
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04(int v);
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
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
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
	virtual bool v41();
};
class Rva0049AE5E
{
public:
	void rva0049AE5E();
	void rva0049ADB7();
private:
	unsigned char m_pad0[8];
	Object *m_obj8;
	unsigned char m_pad0b[0x3CA - 12];
	unsigned char m_flag3CA;
	unsigned char m_pad1[0x3E8 - 0x3CB];
	ObjectID m_id3E8;
	ObjectID m_id3EC;
	ObjectID m_id3F0;
};
void Rva0049AE5E::rva0049AE5E()
{
	GameLogic *logic = TheGameLogic;
	if (logic->findObjectByID(m_id3E8) != 0)
		return;
	if (logic->findObjectByID(m_id3EC) != 0)
		return;
	if (logic->findObjectByID(m_id3F0) != 0)
		return;
	m_flag3CA = 0;
}
// ?rva0049ADB7@Rva0049AE5E@@QAEXXZ, retail 0x0049ADB7, 80 bytes. Same-class
// sibling of rva0049AE5E (identical +0x3CA/+0x3E8/+0x3EC/+0x3F0 clears, same
// // cl: /O1 /MD): if m_id3EC is set, fetch Object at +8 via rowed
// Object::rva0028C197 and, when its vtable slot 0xA4 check passes, invoke
// slot 0x10 with 1; then clear the three IDs and the flag. Evidence: offset
// reuse from Rva0049AE5ECheck plus rowed callee 0x0028C197.
void Rva0049AE5E::rva0049ADB7()
{
	if (m_id3EC != INVALID_OBJECT_ID)
	{
		Rva0049ADB7Target *t = (Rva0049ADB7Target *)m_obj8->rva0028C197();
		if (t != 0 && t->v41())
			t->v04(1);
	}
	m_id3E8 = INVALID_OBJECT_ID;
	m_id3EC = INVALID_OBJECT_ID;
	m_id3F0 = INVALID_OBJECT_ID;
	m_flag3CA = 0;
}
