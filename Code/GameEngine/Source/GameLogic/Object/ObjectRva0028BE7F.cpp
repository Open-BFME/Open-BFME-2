// cl: /DNDEBUG /MD /EHsc
// ?rva0028BE7F@Object@@QAEPAXPAUArg1_004DEA70@@PBUCoord3DBase@@@Z, retail 0x0028BE7F, 20 bytes.
// Object +0x240 tail-forwarding wrapper over rowed Rva004DEA70::rva004DEA70.
// Evidence: neighbours ObjectFindSpecialPowerCompletionDie/ObjectGetSingleLogicalBonePosition;
// retail mov ecx,[ecx+0x240] test je xor ret plus jmp to rowed 0x004DEA70; caller 0x002CCFF0 passes Object this plus two ptr args.
struct Coord3DBase
{
	float x;
	float y;
	float z;
};
struct Arg1_004DEA70
{
	char m_pad[0x74];
	int m_74;
};
class Rva004DEA70
{
public:
	void *rva004DEA70(Arg1_004DEA70 *a1, const Coord3DBase *a2);
};
class Object
{
	char m_pad0[0x240];
	Rva004DEA70 *m_sub240;
public:
	void *rva0028BE7F(Arg1_004DEA70 *a1, const Coord3DBase *a2);
};
void *Object::rva0028BE7F(Arg1_004DEA70 *a1, const Coord3DBase *a2)
{
	Rva004DEA70 *sub = m_sub240;
	if (sub != 0)
		return sub->rva004DEA70(a1, a2);
	return 0;
}
