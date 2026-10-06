// ?rva001E468F@Rva001E468F@@QAE_NPAVObject@@@Z
// partial score=0.93 date=2026-10-01
// cl: /MD
// ?rva001E468F@Rva001E468F@@QAE_NPAVObject@@@Z @0x001E468F 82B unlock lane Object status/kind predicate.
// Evidence: calls rowed Object::testStatus 0x0004E536 with 0x16 0x1E plus rowed Object::rva00293926 0x00293926 with 0x84; byte guards +0x108 via +4 and +0x249; caller 0x001E4742.
enum ObjectStatusTypes {
	OBJECT_STATUS_16 = 0x16,
	OBJECT_STATUS_1E = 0x1E
};
enum KindOfType {
	KINDOF_84 = 0x84
};
class Object {
public:
	bool testStatus(ObjectStatusTypes s) const;
	bool rva00293926(KindOfType k);
};
struct Rva001E468FInner {
	char m_pad[0x108];
	unsigned char m_108;
};
class Rva001E468F {
public:
	bool rva001E468F(Object *obj);
private:
	char m_pad0[4];
	Rva001E468FInner *m_04;
};

bool Rva001E468F::rva001E468F(Object *obj)
{
	if ((m_04->m_108 != 0 && (obj->testStatus(OBJECT_STATUS_16) || obj->testStatus(OBJECT_STATUS_1E))) ||
		(obj != 0 && ((unsigned char *)obj)[0x249] != 0 && obj->rva00293926(KINDOF_84)))
		return true;
	return false;
}
