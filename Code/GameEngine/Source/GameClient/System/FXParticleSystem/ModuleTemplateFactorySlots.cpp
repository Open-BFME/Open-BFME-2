// cl: /DNDEBUG /MD /EHsc
//
// Slot 2 of sixteen particle-module template vtables (0x00C1BE20 and its
// neighbours): each is a factory that allocates the module and constructs it
// from (the owner passed in, this template), under an EH frame that frees the
// block if the constructor throws. Product and template classes are
// address-named (or keep the names the ledger already gives three of the
// constructors); the module sizes come from the allocations.

class Rva003AD6DFTemplate;

class Rva003ACD71Module
{
public:
	Rva003ACD71Module(void *owner, Rva003AD6DFTemplate *moduleTemplate);
private:
	char m_unmodelled[0x1C];
};

class Rva003AD6DFTemplate
{
public:
	Rva003ACD71Module *rva003AD6DF(void *owner);		// vtable 0x00C1BE20#2
};

Rva003ACD71Module *Rva003AD6DFTemplate::rva003AD6DF(void *owner)
{
	return new Rva003ACD71Module(owner, this);
}

class Rva003AD71BTemplate;

class Rva003ACDA0Module
{
public:
	Rva003ACDA0Module(void *owner, Rva003AD71BTemplate *moduleTemplate);
private:
	char m_unmodelled[0x1C];
};

class Rva003AD71BTemplate
{
public:
	Rva003ACDA0Module *rva003AD71B(void *owner);		// vtable 0x00C1BE40#2
};

Rva003ACDA0Module *Rva003AD71BTemplate::rva003AD71B(void *owner)
{
	return new Rva003ACDA0Module(owner, this);
}

class Rva003AD757Template;

class Rva003ACDCFModule
{
public:
	Rva003ACDCFModule(void *owner, Rva003AD757Template *moduleTemplate);
private:
	char m_unmodelled[0x1C];
};

class Rva003AD757Template
{
public:
	Rva003ACDCFModule *rva003AD757(void *owner);		// vtable 0x00C1BE60#2
};

Rva003ACDCFModule *Rva003AD757Template::rva003AD757(void *owner)
{
	return new Rva003ACDCFModule(owner, this);
}

class Rva003AD793Template;

class Rva003ACDFEModule
{
public:
	Rva003ACDFEModule(void *owner, Rva003AD793Template *moduleTemplate);
private:
	char m_unmodelled[0x1C];
};

class Rva003AD793Template
{
public:
	Rva003ACDFEModule *rva003AD793(void *owner);		// vtable 0x00C1BE80#2
};

Rva003ACDFEModule *Rva003AD793Template::rva003AD793(void *owner)
{
	return new Rva003ACDFEModule(owner, this);
}

class V3HostRva005E7420;

class Rva005E7420Object
{
public:
	Rva005E7420Object(void *owner, V3HostRva005E7420 *moduleTemplate);
private:
	char m_unmodelled[0x5C];
};

class V3HostRva005E7420
{
public:
	Rva005E7420Object *rva003AD7CF(void *owner);		// vtable 0x00C1C270#2
};

Rva005E7420Object *V3HostRva005E7420::rva003AD7CF(void *owner)
{
	return new Rva005E7420Object(owner, this);
}

class Rva003AD80BTemplate;

class Rva003ACE5CModule
{
public:
	Rva003ACE5CModule(void *owner, Rva003AD80BTemplate *moduleTemplate);
private:
	char m_unmodelled[0x8E4];
};

class Rva003AD80BTemplate
{
public:
	Rva003ACE5CModule *rva003AD80B(void *owner);		// vtable 0x00C1BEA0#2
};

Rva003ACE5CModule *Rva003AD80BTemplate::rva003AD80B(void *owner)
{
	return new Rva003ACE5CModule(owner, this);
}

class V3HostRva005E76E0;

class Rva005E76E0Object
{
public:
	Rva005E76E0Object(void *owner, V3HostRva005E76E0 *moduleTemplate);
private:
	char m_unmodelled[0x2C];
};

class V3HostRva005E76E0
{
public:
	Rva005E76E0Object *rva003AD84A(void *owner);		// vtable 0x00C1C294#2
};

Rva005E76E0Object *V3HostRva005E76E0::rva003AD84A(void *owner)
{
	return new Rva005E76E0Object(owner, this);
}

class Rva003AD886Template;

class Rva003ACEFCModule
{
public:
	Rva003ACEFCModule(void *owner, Rva003AD886Template *moduleTemplate);
private:
	char m_unmodelled[0xA0];
};

class Rva003AD886Template
{
public:
	Rva003ACEFCModule *rva003AD886(void *owner);		// vtable 0x00C1BF20#2
};

Rva003ACEFCModule *Rva003AD886Template::rva003AD886(void *owner)
{
	return new Rva003ACEFCModule(owner, this);
}

class Rva003AD8C5Template;

class Rva003ACF32Module
{
public:
	Rva003ACF32Module(void *owner, Rva003AD8C5Template *moduleTemplate);
private:
	char m_unmodelled[0xAC];
};

class Rva003AD8C5Template
{
public:
	Rva003ACF32Module *rva003AD8C5(void *owner);		// vtable 0x00C1BF40#2
};

Rva003ACF32Module *Rva003AD8C5Template::rva003AD8C5(void *owner)
{
	return new Rva003ACF32Module(owner, this);
}

class Rva003AD904Template;

class Rva003ACFCFModule
{
public:
	Rva003ACFCFModule(void *owner, Rva003AD904Template *moduleTemplate);
private:
	char m_unmodelled[0x40];
};

class Rva003AD904Template
{
public:
	Rva003ACFCFModule *rva003AD904(void *owner);		// vtable 0x00C1BF60#2
};

Rva003ACFCFModule *Rva003AD904Template::rva003AD904(void *owner)
{
	return new Rva003ACFCFModule(owner, this);
}

class Rva003AD940Template;

class Rva003AD005Module
{
public:
	Rva003AD005Module(void *owner, Rva003AD940Template *moduleTemplate);
private:
	char m_unmodelled[0x84];
};

class Rva003AD940Template
{
public:
	Rva003AD005Module *rva003AD940(void *owner);		// vtable 0x00C1BF84#2
};

Rva003AD005Module *Rva003AD940Template::rva003AD940(void *owner)
{
	return new Rva003AD005Module(owner, this);
}

class Rva003AD97FTemplate;

class Rva003AD094Module
{
public:
	Rva003AD094Module(void *owner, Rva003AD97FTemplate *moduleTemplate);
private:
	char m_unmodelled[0x64];
};

class Rva003AD97FTemplate
{
public:
	Rva003AD094Module *rva003AD97F(void *owner);		// vtable 0x00C1BFB8#2
};

Rva003AD094Module *Rva003AD97FTemplate::rva003AD97F(void *owner)
{
	return new Rva003AD094Module(owner, this);
}

class Rva003AD9BBTemplate;

class Rva003AD0CAModule
{
public:
	Rva003AD0CAModule(void *owner, Rva003AD9BBTemplate *moduleTemplate);
private:
	char m_unmodelled[0x40];
};

class Rva003AD9BBTemplate
{
public:
	Rva003AD0CAModule *rva003AD9BB(void *owner);		// vtable 0x00C1C2F4#2
};

Rva003AD0CAModule *Rva003AD9BBTemplate::rva003AD9BB(void *owner)
{
	return new Rva003AD0CAModule(owner, this);
}

class Rva003AD9F7Template;

class Rva003AD100Module
{
public:
	Rva003AD100Module(void *owner, Rva003AD9F7Template *moduleTemplate);
private:
	char m_unmodelled[0xB4];
};

class Rva003AD9F7Template
{
public:
	Rva003AD100Module *rva003AD9F7(void *owner);		// vtable 0x00C1BFD8#2
};

Rva003AD100Module *Rva003AD9F7Template::rva003AD9F7(void *owner)
{
	return new Rva003AD100Module(owner, this);
}

class V3HostRva005E7AD0;

class Rva005E7AD0Object
{
public:
	Rva005E7AD0Object(void *owner, V3HostRva005E7AD0 *moduleTemplate);
private:
	char m_unmodelled[0x44];
};

class V3HostRva005E7AD0
{
public:
	Rva005E7AD0Object *rva003ADA36(void *owner);		// vtable 0x00C1C314#2
};

Rva005E7AD0Object *V3HostRva005E7AD0::rva003ADA36(void *owner)
{
	return new Rva005E7AD0Object(owner, this);
}

class Rva003ADBD0Template;

class Rva003AD38BModule
{
public:
	Rva003AD38BModule(void *owner, Rva003ADBD0Template *moduleTemplate);
private:
	char m_unmodelled[0xA8];
};

class Rva003ADBD0Template
{
public:
	Rva003AD38BModule *rva003ADBD0(void *owner);		// vtable 0x00C1C154#2
};

Rva003AD38BModule *Rva003ADBD0Template::rva003ADBD0(void *owner)
{
	return new Rva003AD38BModule(owner, this);
}

// Eleven more of the same factories whose constructors cannot throw: retail
// builds them with no EH frame, which the throw() specification reproduces.

class Rva003ADA72Template;

class Rva003AD16CModule
{
public:
	Rva003AD16CModule(void *owner, Rva003ADA72Template *moduleTemplate) throw();
private:
	char m_unmodelled[0x40];
};

class Rva003ADA72Template
{
public:
	Rva003AD16CModule *rva003ADA72(void *owner);		// vtable 0x00C1BFFC#2
};

Rva003AD16CModule *Rva003ADA72Template::rva003ADA72(void *owner)
{
	return new Rva003AD16CModule(owner, this);
}

class Rva003ADA95Template;

class Rva003AD19BModule
{
public:
	Rva003AD19BModule(void *owner, Rva003ADA95Template *moduleTemplate) throw();
private:
	char m_unmodelled[0x28];
};

class Rva003ADA95Template
{
public:
	Rva003AD19BModule *rva003ADA95(void *owner);		// vtable 0x00C1C020#2
};

Rva003AD19BModule *Rva003ADA95Template::rva003ADA95(void *owner)
{
	return new Rva003AD19BModule(owner, this);
}

class Rva003ADAB8Template;

class Rva003AD1CAModule
{
public:
	Rva003AD1CAModule(void *owner, Rva003ADAB8Template *moduleTemplate) throw();
private:
	char m_unmodelled[0x28];
};

class Rva003ADAB8Template
{
public:
	Rva003AD1CAModule *rva003ADAB8(void *owner);		// vtable 0x00C1C034#2
};

Rva003AD1CAModule *Rva003ADAB8Template::rva003ADAB8(void *owner)
{
	return new Rva003AD1CAModule(owner, this);
}

class Rva003ADADBTemplate;

class Rva003AD1F9Module
{
public:
	Rva003AD1F9Module(void *owner, Rva003ADADBTemplate *moduleTemplate) throw();
private:
	char m_unmodelled[0x34];
};

class Rva003ADADBTemplate
{
public:
	Rva003AD1F9Module *rva003ADADB(void *owner);		// vtable 0x00C1C058#2
};

Rva003AD1F9Module *Rva003ADADBTemplate::rva003ADADB(void *owner)
{
	return new Rva003AD1F9Module(owner, this);
}

class Rva003ADAFETemplate;

class Rva003AD228Module
{
public:
	Rva003AD228Module(void *owner, Rva003ADAFETemplate *moduleTemplate) throw();
private:
	char m_unmodelled[0x34];
};

class Rva003ADAFETemplate
{
public:
	Rva003AD228Module *rva003ADAFE(void *owner);		// vtable 0x00C1C07C#2
};

Rva003AD228Module *Rva003ADAFETemplate::rva003ADAFE(void *owner)
{
	return new Rva003AD228Module(owner, this);
}

class Rva003ADB21Template;

class Rva003AD278Module
{
public:
	Rva003AD278Module(void *owner, Rva003ADB21Template *moduleTemplate) throw();
private:
	char m_unmodelled[0x24];
};

class Rva003ADB21Template
{
public:
	Rva003AD278Module *rva003ADB21(void *owner);		// vtable 0x00C1C0A0#2
};

Rva003AD278Module *Rva003ADB21Template::rva003ADB21(void *owner)
{
	return new Rva003AD278Module(owner, this);
}

class Rva003ADB44Template;

class Rva003AD2B3Module
{
public:
	Rva003AD2B3Module(void *owner, Rva003ADB44Template *moduleTemplate) throw();
private:
	char m_unmodelled[0x3C];
};

class Rva003ADB44Template
{
public:
	Rva003AD2B3Module *rva003ADB44(void *owner);		// vtable 0x00C1C0C4#2
};

Rva003AD2B3Module *Rva003ADB44Template::rva003ADB44(void *owner)
{
	return new Rva003AD2B3Module(owner, this);
}

class Rva003ADB67Template;

class Rva003AD2E9Module
{
public:
	Rva003AD2E9Module(void *owner, Rva003ADB67Template *moduleTemplate) throw();
private:
	char m_unmodelled[0x30];
};

class Rva003ADB67Template
{
public:
	Rva003AD2E9Module *rva003ADB67(void *owner);		// vtable 0x00C1C0E8#2
};

Rva003AD2E9Module *Rva003ADB67Template::rva003ADB67(void *owner)
{
	return new Rva003AD2E9Module(owner, this);
}

class Rva003ADB8ATemplate;

class Rva003AD31FModule
{
public:
	Rva003AD31FModule(void *owner, Rva003ADB8ATemplate *moduleTemplate) throw();
private:
	char m_unmodelled[0x28];
};

class Rva003ADB8ATemplate
{
public:
	Rva003AD31FModule *rva003ADB8A(void *owner);		// vtable 0x00C1C10C#2
};

Rva003AD31FModule *Rva003ADB8ATemplate::rva003ADB8A(void *owner)
{
	return new Rva003AD31FModule(owner, this);
}

class Rva003ADBADTemplate;

class Rva003AD355Module
{
public:
	Rva003AD355Module(void *owner, Rva003ADBADTemplate *moduleTemplate) throw();
private:
	char m_unmodelled[0x3C];
};

class Rva003ADBADTemplate
{
public:
	Rva003AD355Module *rva003ADBAD(void *owner);		// vtable 0x00C1C130#2
};

Rva003AD355Module *Rva003ADBADTemplate::rva003ADBAD(void *owner)
{
	return new Rva003AD355Module(owner, this);
}

class Rva003ADC0FTemplate;

class Rva003AD3C1Module
{
public:
	Rva003AD3C1Module(void *owner, Rva003ADC0FTemplate *moduleTemplate) throw();
private:
	char m_unmodelled[0x4C];
};

class Rva003ADC0FTemplate
{
public:
	Rva003AD3C1Module *rva003ADC0F(void *owner);		// vtable 0x00C1C178#2
};

Rva003AD3C1Module *Rva003ADC0FTemplate::rva003ADC0F(void *owner)
{
	return new Rva003AD3C1Module(owner, this);
}
