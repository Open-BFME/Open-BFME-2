#ifndef INGAME_NOTICE_DISPLAY_VECTOR_H
#define INGAME_NOTICE_DISPLAY_VECTOR_H

#include <vector>

// Keep these accessors inline without emitting per-TU vector<void *> COMDATs.
// Both notice fragments need the same specializations before any use.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void *, allocator<void *> >::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *, allocator<void *> >::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void *, allocator<void *> >::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void *, allocator<void *> >::operator[](size_t __n)
{ return *(begin() + __n); }
}

#endif
