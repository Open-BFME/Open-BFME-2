// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00357B3D@ScriptEngine@@QAE_NHW4ObjectID@@_N@Z, retail 0x00357B3D 69B leaf.
// Evidence: next to ScriptEngine 0x00357AF8 same flags; playerVectors[20] at
// +0x1A3A8 from ScriptEngine_dtor; vector<ObjectID>::erase rowed 0x0025BF5D;
// caller 0x003E4455 pushes index id 1 with ScriptEngine singleton.
// _STL::vector<ObjectID> minimal view: begin/end inline (as retail inlines
// them), erase declared only so the call reaches the retail copy in
// Code/GameEngine/Source/Common/Rva004D6BF0Erase.cpp instead of emitting a
// wrong COMDAT here.
namespace _STL {
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector {
public:
	T *m_start;
	T *m_finish;
	T *m_end;
	T *begin() { return m_start; }
	T *end() { return m_finish; }
	T *erase(T *pos);
};
}

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class ScriptEngine
{
public:
	bool rva00357B3D(int index, ObjectID id, bool remove);

private:
	char m_pad[0x1A3A8];
	_STL::vector<ObjectID> m_vec1A3A8[20]; // +0x1A3A8
};

bool ScriptEngine::rva00357B3D(int index, ObjectID id, bool remove)
{
	if (index < 0 || index >= 20)
		return false;
	_STL::vector<ObjectID> &vec = m_vec1A3A8[index];
	for (ObjectID *it = vec.begin(); it != vec.end(); ++it)
	{
		if (*it == id)
		{
			if (remove)
				vec.erase(it);
			return true;
		}
	}
	return false;
}
