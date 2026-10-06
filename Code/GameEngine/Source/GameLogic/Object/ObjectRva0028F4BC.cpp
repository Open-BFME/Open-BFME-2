// cl: /DNDEBUG /MD
//
// ?rva0028F4BC@Object@@QAEPAVRva00373EC6@@XZ @0x0028F4BC 51B:
// List search over Rva00373EC6 pointers at +0x4B4..+0x4B8, returning the first
// whose rowed ?rva00373EC6@Rva00373EC6@@QBE_NXZ predicate is true, else null.
// Class proven by caller at 0x00290FF0 via same-this Object call (mov ecx,edi
// with getControllingPlayer plus this). Flags from neighbour Object file.
class Rva00373EC6
{
public:
	bool rva00373EC6() const;
};

class Object
{
public:
	Rva00373EC6 *rva0028F4BC();
private:
	char m_pad0[0x4B4];
	Rva00373EC6 **m_begin; // +0x4B4
	Rva00373EC6 **m_end; // +0x4B8
};

Rva00373EC6 *Object::rva0028F4BC()
{
	for (Rva00373EC6 **it = m_begin; it != m_end; ++it) {
		Rva00373EC6 *obj = *it;
		if (obj != 0 && obj->rva00373EC6())
			return obj;
	}
	return 0;
}
