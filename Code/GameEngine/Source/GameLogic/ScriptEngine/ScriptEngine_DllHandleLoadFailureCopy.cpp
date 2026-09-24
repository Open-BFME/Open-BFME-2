// cl: /O1 /DNDEBUG /MD /EHsc
// DllHandle::LoadFailure copy constructor. The thrown type is named by
// catchable-type RTTI at 0x00D11F4C; retail 0x0020426C copies std::exception
// and installs the same LoadFailure vtable as the verified default ctor.

class __declspec(dllimport) exception
{
public:
    exception(const exception &other);
    virtual ~exception();
private:
    const char *m_what;
    int m_doFree;
};

class DllHandle
{
public:
    class LoadFailure : public exception
    {
    public:
        LoadFailure(const LoadFailure &other);
    };
};

DllHandle::LoadFailure::LoadFailure(const LoadFailure &other)
    : exception(other)
{
    *(unsigned int *)this = 0x00BD3B54;
}
