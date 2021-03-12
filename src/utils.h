#ifndef __tmf_utils_h__
#define __tmf_utils_h__

void buffer_clear(char* buffer, long length)
{
	for (int i = 0; i < length; i++)
		buffer[i] = 0;
}

#endif
