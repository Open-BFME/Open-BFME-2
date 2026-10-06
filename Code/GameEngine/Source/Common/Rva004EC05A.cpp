// cl: /DNDEBUG /MD
// ?rva004EC05A@Rva004EC05A@@QAEXPAVSubsystemInterface@@@Z @ 0x004EC05A 8 bytes.
// Adjust-and-forward: this+0x38 -> SubsystemInterfaceList::addSubsystem.
// Evidence: retail add ecx 0x38 plus jmp to rowed 0x0047A69C addSubsystem; caller 0x003A0D4C.

class SubsystemInterface;

class SubsystemInterfaceList
{
public:
	void addSubsystem(SubsystemInterface *sys);
};

class Rva004EC05A
{
public:
	void rva004EC05A(SubsystemInterface *sys);
};

void Rva004EC05A::rva004EC05A(SubsystemInterface *sys)
{
	((SubsystemInterfaceList *)((char *)this + 0x38))->addSubsystem(sys);
}
