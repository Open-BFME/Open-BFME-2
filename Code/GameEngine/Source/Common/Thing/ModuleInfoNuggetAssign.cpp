// cl: /O1
//
// ??4Nugget@ModuleInfo@@QAEAAU01@ABU01@@Z @0x002CEFCD 57B.
// ModuleInfo::Nugget copy assignment. Layout is the BFME1 donor
// (Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp Rva0013E5D0Nugget:
// two AsciiStrings then ModuleData pointer then Int then two Bools for
// 0x14-byte records); ZH adds a third Bool which retail does not copy.
// Identity is pin-proven: per-element callee of the rowed 5-arg
// _STL::__copy_ptrs worker at 0x002CF0BE (ModuleInfoNuggetCopyPtrs.cpp).

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	char *m_data;
};

class ModuleData
{
};

class ModuleInfo
{
public:
	struct Nugget
	{
		Nugget &operator=(const Nugget &other);

		AsciiString m_first;
		AsciiString m_moduleTag;
		const ModuleData *m_data;
		int m_interfaceMask;
		unsigned char m_copiedFromDefault;
		unsigned char m_inheritable;
	};
};

ModuleInfo::Nugget &ModuleInfo::Nugget::operator=(const Nugget &other)
{
	m_first = other.m_first;
	m_moduleTag = other.m_moduleTag;
	m_data = other.m_data;
	m_interfaceMask = other.m_interfaceMask;
	m_copiedFromDefault = other.m_copiedFromDefault;
	m_inheritable = other.m_inheritable;
	return *this;
}
