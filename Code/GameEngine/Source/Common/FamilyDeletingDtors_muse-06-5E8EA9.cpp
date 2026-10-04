// cl: /O1 /MD
// ??_GRva005E8EA1@@QAEPAXI@Z @0x005E8EA9 28B: scalar deleting dtor calls the rowed ??1 at 0x005E8EA1 plus rowed operator delete 0x0002FD60.
class Rva005E8EA1 {
public:
	~Rva005E8EA1();
};

void Rva005E8EA1_Delete(Rva005E8EA1 *p) { delete p; }

// Native 005E8F50..005E8F6A clears the pointer at this+0 before deletion.
// The direct destructor call proves the pointee uses the existing
// Rva005E8EA1 lifetime; the owning class's original name is unknown.
class Rva005E8F50 {
public:
	void clear();
private:
	Rva005E8EA1 *value;
};

void Rva005E8F50::clear()
{
	Rva005E8EA1 *old = value;
	value = 0;
	delete old;
}
