// Target evidence: FoundationAIUpdate obtains the new owner's
// Rva002A8AB1Record and calls its +0x2C6A3D forwarder; that 17-byte body
// tail-jumps here with the record in ECX and Object* on the stack. The paired
// old-owner forwarder at 0x002C6A4E tail-jumps to the removal path at
// 0x004EC8F4, whose matching template tests remove from the +0x140 and +0x38
// subobjects. This body's target tests use ThingTemplate bytes +0x108,
// +0x10F and +0x120 and Object ID +0x74. The record subobject identities at
// +0x38 and +0x140 are inferred from those call targets. The method name is
// kept address-derived; the more specific add-on-ownership interpretation is
// supported by the new-owner call path but remains an inference.

typedef unsigned int ObjectID;

class ThingTemplate
{
public:
	char m_pad00[0x108];
	unsigned int m_flags108;
	unsigned char m_pad10C[3];
	unsigned char m_flag10F;
	unsigned char m_pad110[0x10];
	unsigned char m_flag120;
};

class Object
{
public:
	ThingTemplate *getThingTemplate() const { return m_thingTemplate; }
	ObjectID getID() const { return m_id; }

private:
	void *m_vtable;
	ThingTemplate *m_thingTemplate;
	char m_pad08[0x74 - 0x08];
	ObjectID m_id;
};

class FXNugget;
class FXList
{
public:
	void addFXNugget(FXNugget *nugget);
};

class Rva00598149
{
public:
	void rva00598431(int objectID);
};

class AIDozerManager
{
public:
	void rva00599825(int objectID);
};

class Rva002A8AB1Record
{
public:
	void rva004EC30E(Object *object);
	void rva002C6A3D(Object *object);
private:
	char m_pad00[0x168];
	unsigned char m_168;
};

void Rva002A8AB1Record::rva004EC30E(Object *object)
{
	if ((object->getThingTemplate()->m_flag120 & 0x04) != 0)
		((FXList *)((char *)this + 0x140))->addFXNugget(
			(FXNugget *)object->getID());

	if ((object->getThingTemplate()->m_flag10F & 0x80) != 0)
		((Rva00598149 *)((char *)this + 0x38))->rva00598431(
			object->getID());

	unsigned int flags = object->getThingTemplate()->m_flags108;
	if ((flags & 0x4000) != 0 && (flags & 0x02) != 0)
		((AIDozerManager *)((char *)this + 0x140))->rva00599825(
			object->getID());
}
// ?rva002C6A3D@Rva002A8AB1Record@@QAEXPAVObject@@@Z @0x002C6A3D 17B
// Leaf forwarder called by FoundationAIUpdate::rva00455B67 at 0x00455BC1 with
// the new owner's record. Tests byte +0x168; when zero tail-jumps to rowed
// Rva002A8AB1Record::rva004EC30E with the same Object*. Same class and
// signature as the callee; pin proves the name.
void Rva002A8AB1Record::rva002C6A3D(Object *object)
{
	if (m_168 != 0)
		return;
	rva004EC30E(object);
}
