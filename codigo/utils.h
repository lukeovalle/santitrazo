// utils.h

#ifndef _UTILS__H_
#define _UTILS__H_

#define MIN(val1, val2) ( (val1) < (val2) ? (val1) : (val2) )
#define MAX(val1, val2) ( (val1) > (val2) ? (val1) : (val2) )
#define CLAMP(val, min, max)  ( MIN(max, MAX(val, min)) )

#endif
