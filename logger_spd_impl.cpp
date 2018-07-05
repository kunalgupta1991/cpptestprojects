#include <iostream>
#include"logger_spd.cpp"

namespace mylogger
{
	kunallogger::kunallogger()
	{
		
		std::cout << "my logger created";
	}
	filelogger::filelogger(string logname, string filename)
	{
		_logger = mylog::basic_logger_st(logname,filename);
	}
}