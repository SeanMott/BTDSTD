//Windows implementation of the Chrono header in Bytes The Dust

#include <BTDSTD/IO/Chrono.hpp>

#define LEAN_AND_MEAN
#include <Windows.h>

//gets the local system time, set to the User's time zone
void BTD::Chrono::GetLocalTime(SysDateData* data)
{
	//gets the time and other junk
	SYSTEMTIME st;
	GetLocalTime(&st);

	//copies into data
	memcpy(data, &st, sizeof(st));
}