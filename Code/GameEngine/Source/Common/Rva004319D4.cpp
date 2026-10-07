// cl: /MD
// ?Rva004319D4Get@@YAHXZ @0x004319D4 30B: free function returning TheMouse+0x4F24 and +0x4F30 both nonzero. Evidence: unlock lane unblocks 0x00431E5A; extern TheMouse ?TheMouse@@3PAVMouse@@A used by 2 TUs; caller 0x00431E5A tests al; prev Rva00431978 next Rva00431A4D same dir same flags.
class Mouse
{
public:
	char m_pad0[0x4F24];
	void *m_4F24;
	char m_pad1[0x4F30 - 0x4F24 - 4];
	void *m_4F30;
};

extern Mouse *TheMouse;

int Rva004319D4Get()
{
	if (TheMouse->m_4F24 != 0 && TheMouse->m_4F30 != 0)
		return 1;
	return 0;
}

// Complete retail 4318A8..4318C6 is the complementary no-button predicate.
// TheMouse and these same two pointer fields are independently used by
// the rowed FormationTranslator first-button check at 431955.
// Native code does not consume ECX or arguments and returns integer 0/1.
int Rva004318A8Get()
{
 if (TheMouse->m_4F24 == 0 && TheMouse->m_4F30 == 0)
  return 1;
 return 0;
}
