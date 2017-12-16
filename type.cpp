#include "type.h"

uint64 MP4GetAbsTimestamp() {
	/* MP4 epoch is midnight, January 1, 1904
	* offset from midnight, January 1, 1970 is 2082844800 seconds
	* 208284480 is (((1970 - 1904) * 365) + 17) * 24 * 60 * 60
	*/
//	__timeb64 buf;
//	_ftime64_s(&buf);

//	return (uint64(buf.time) * 1000 + buf.millitm) / 1000 + 2082844800;
    
    return 0;
}

#if __linux__
unsigned long long htonll(unsigned long long host)
{
    unsigned long temp_low, temp_high;
    temp_low = htonl((long)host);
    temp_high = htonl((long)(host >> 32));

    host &= 0;
    host |= temp_low;
    host <<= 32;
    host |= temp_high;
    return host;
}
#endif