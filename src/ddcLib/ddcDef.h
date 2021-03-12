#ifndef __ddcDef__
#define __ddcDef__

#include <stdlib.h>

//ints
typedef signed char             int8t;
typedef signed short 		int16t;
typedef signed int	        int32t;
typedef signed long long int    int64t;
typedef unsigned char           uint8t;
typedef signed short 		uint16t;
typedef signed int	        uint32t;
typedef signed long long int    uint64t;
typedef signed long long int 	sizet;



#ifndef make
	#define make(t,s) ((t*)malloc(s*sizeof(t)))
	#endif
#ifndef raze
	#define raze(t) (free(t))
	#endif



#ifndef __BYINC
	#define __BYINC 10
	#endif
#ifndef MAINF__
	#define MAINF__ int main(ddsize agsc, char** ags)
	#endif
#ifndef SET_DDARGS__
	#define SET_DDARGS__ ddArgs da = init_ddArgs(ags, agsc)
	#define SET_DDARGSV__(x) ddArgs x = init_ddArgs(ags, agsc)
	#endif
#ifndef oBLOCK
	#define oBLOCK {
	#define cBLOCK }
	#endif



#ifndef true
	#define true 1
	#endif
#ifndef false
	#define false 0
	#endif
#ifndef bool
	typedef char bool;
	#endif
#ifndef ddsize
	#define ddsize unsigned long long int
	#endif
#ifndef DNL
	#define DNL '\n'
	#endif
#ifndef NULL
	#define NULL 0
	#endif
#ifndef null
	#define null 0
	#endif
#ifndef nullptr
	#define nullptr 0x00000000
	#endif





#endif
