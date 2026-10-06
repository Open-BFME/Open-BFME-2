// cl: /MD
// ?append@Rva0056654FOwner@@QAEXABVRva004E18A2@@@Z @0x0056654F 8B: tail-jump.
// Adds 0x78 then jumps to the rowed vector<Rva004E18A2>::push_back 0x005663A8
// (the record whose virtual dtor is rowed at 0x004E18A2). Caller is the
// LivingWorld ParseAudioEventBlock proc 0x004E18F8. Sibling of
// Rva00566527Thunk.cpp; owner name address-derived.
//
// The same LivingWorld owner's other append thunks (callers are the event
// parse procs at 0x004E141D / 0x004E17EB / 0x004E1BFC / 0x004E1C7B):
//   0x00566537  8B  +0x2C -> push_back<Rva0052BDE6> 0x005662CC
//   0x0056653F  8B  +0x38 -> push_back<Rva0052BE33> 0x00566303
//   0x00566547  8B  +0x54 -> push_back<Rva003A6F70> 0x0056633A
//   0x0056656A 11B  +0xA8 -> push_back<Rva0052BEF0> 0x00566417
class Rva004E18A2
{
public:
	virtual ~Rva004E18A2();
private:
	char m_pad[0xC];
};

class Rva0052BDE6 { char m_pad[0xC]; };
class Rva0052BE33 { char m_pad[0x10]; };
class Rva003A6F70 { char m_pad[0x20]; };
class Rva0052BEF0 { char m_pad[0xC]; };

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <class T> class vector<T, allocator<T> >
{
public:
	void push_back(const T &x);
private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
template <> class vector<Rva004E18A2, allocator<Rva004E18A2> >
{
public:
	void push_back(const Rva004E18A2 &x);
private:
	Rva004E18A2 *m_start;
	Rva004E18A2 *m_finish;
	Rva004E18A2 *m_endOfStorage;
};
}

class Rva0056654FOwner
{
public:
	void append(const Rva004E18A2 &record);
private:
	char m_pad[0x78];
	_STL::vector<Rva004E18A2, _STL::allocator<Rva004E18A2> > m_audioEvents;
};

void Rva0056654FOwner::append(const Rva004E18A2 &record)
{
	m_audioEvents.push_back(record);
}

class Rva00566537Owner
{
public:
	void append(const Rva0052BDE6 &record);
private:
	char m_pad[0x2C];
	_STL::vector<Rva0052BDE6, _STL::allocator<Rva0052BDE6> > m_records;
};

void Rva00566537Owner::append(const Rva0052BDE6 &record)
{
	m_records.push_back(record);
}

class Rva0056653FOwner
{
public:
	void append(const Rva0052BE33 &record);
private:
	char m_pad[0x38];
	_STL::vector<Rva0052BE33, _STL::allocator<Rva0052BE33> > m_records;
};

void Rva0056653FOwner::append(const Rva0052BE33 &record)
{
	m_records.push_back(record);
}

class Rva00566547Owner
{
public:
	void append(const Rva003A6F70 &record);
private:
	char m_pad[0x54];
	_STL::vector<Rva003A6F70, _STL::allocator<Rva003A6F70> > m_records;
};

void Rva00566547Owner::append(const Rva003A6F70 &record)
{
	m_records.push_back(record);
}

class Rva0056656AOwner
{
public:
	void append(const Rva0052BEF0 &record);
private:
	char m_pad[0xA8];
	_STL::vector<Rva0052BEF0, _STL::allocator<Rva0052BEF0> > m_records;
};

void Rva0056656AOwner::append(const Rva0052BEF0 &record)
{
	m_records.push_back(record);
}
