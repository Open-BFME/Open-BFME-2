// cl: /DNDEBUG /MD
// ?rva0026417F@AIUpdateInterface@@QAEHH@Z
// 0x0026417F 59B: AIUpdateInterface score helper between slot139 0x0026412B and free 0x00264237. Reads owner at this+8 and template byte +0x109 bits 0x40 and 0x02 plus 10x Object::rva0028CE7B. Evidence: this+8 is m_object as in AIUpdateInterfacePrivateCommands slot bodies and Rva00263910Goal +8 model. Callee rowed-or-pinned 0x0028CE7B. Callers in 0x0026CF11 0x002EBE54 0x002EC0A2.
class ThingTemplate
{
public:
	unsigned char m_pad[0x109];
	unsigned char m_b109; // +0x109
};

class Object
{
public:
	signed char rva0028CE7B() const;
	unsigned char m_pad[4];
	ThingTemplate *m_template; // +4
};

class AIUpdateInterface
{
public:
	int rva0026417F(int arg);
	unsigned char m_pad[8];
	Object *m_object; // +8
};

int AIUpdateInterface::rva0026417F(int arg)
{
	(void)arg;
	Object *obj = m_object;
	int v = 0;
	if ((obj->m_template->m_b109 & 0x40) != 0)
		v = 100;
	v += 10 * obj->rva0028CE7B();
	if ((obj->m_template->m_b109 & 2) != 0)
		v += 5;
	return v;
}
