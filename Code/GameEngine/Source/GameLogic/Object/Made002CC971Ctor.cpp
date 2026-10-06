// cl: /DNDEBUG /MD
//
// ??0Made002CC971@@QAE@XZ retail 0x0050ABF7 18B base plus vtable.
// Evidence: pin ??0Made002CC971@@QAE@XZ; rowed base Rva00507823 0x0050775B;
// vtable 0x00864B00; caller parseSlaveAttackNugget 0x002CC996 news 0x128.
class Rva00507823
{
public:
	virtual ~Rva00507823();
	Rva00507823();
private:
	char m_pad04[0x128 - 4];
};

class Made002CC971 : public Rva00507823
{
public:
	Made002CC971();
};

Made002CC971::Made002CC971()
{
}
