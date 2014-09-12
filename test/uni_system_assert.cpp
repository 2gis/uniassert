#define UNI_FORCE_ASSERTS
#define UNI_SYSTEM_ASSERT 1
#include <uniassert/uniassert.h>

#if !defined(UNI_ASSERT) || UNI_ASSERT != 1
#	error "UNI_SYSTEM_ASSERT is not working"
#endif