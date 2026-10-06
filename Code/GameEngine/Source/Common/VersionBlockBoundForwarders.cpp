// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Version-block bound adapters for the equal-range worker at 0x00427DEA.
// Each adapter forwards its four arguments to the matching five-argument
// bound in VersionBlockBounds.cpp with a trailing zero flag the bound
// never reads. Frameless retail shape needs plain /O1 (no /Oy-); /Oy-
// forces an ebp frame. Both adapters are called only from the worker.
// Semantic class membership is unproven so both ride the TU-local
// VersionBlockParser scope; opaque behavior.

class VersionBlockParser
{
public:
	static const void *lowerBound(const void *first, const void *last, const char *const *key, const void *match, int flags);
	static const void *upperBound(const void *first, const void *last, const char *const *key, const void *match, int flags);
	static const void *forwardLowerBound(const void *first, const void *last, const char *const *key, const void *match);
	static const void *forwardUpperBound(const void *first, const void *last, const char *const *key, const void *match);
};

// ?forwardLowerBound@VersionBlockParser@@SAPBXPBX0PBQBD0@Z
const void *VersionBlockParser::forwardLowerBound(const void *first, const void *last, const char *const *key, const void *match)
{
	return VersionBlockParser::lowerBound(first, last, key, match, 0);
}

const void *VersionBlockParser::forwardUpperBound(const void *first, const void *last, const char *const *key, const void *match)
{
	return VersionBlockParser::upperBound(first, last, key, match, 0);
}
