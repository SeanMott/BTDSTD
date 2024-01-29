#pragma once

//Bytes The Dust implementation of our own time related functions and stuff

#include <BTDSTD/Types.hpp>

namespace BTD::Chrono
{
    //defines a struct of System Date Data
    struct SysDateData
    {
        uint16 year;
        uint16 month;
        uint16 dayOfWeek;
        uint16 day;
        uint16 hour;
        uint16 minute;
        uint16 second;
        uint16 milliseconds;
    };

	//gets time localized to the User System's time zone
	void GetLocalTime(SysDateData* data);
}