#ifndef  spdlogger
#define spdlogger
#include "spdlog\spdlog.h"

//#include "spdlog\logger.h"
namespace mylog = spdlog;
using namespace std;
namespace mylogger
{
	enum class logfilelevel:int
	{
		vpgrouping = 0,
		simulation =1
	};
	enum class loglevel : int
	{
		info,
		warning,
		critical
	};
	class filelogger
	{
		shared_ptr<mylog::logger> _logger;
		//v.push_back(2);
	public:
		filelogger() = delete;
		filelogger(string loggertype, string filename);
		void log(string msg)
		{

		}

	};
	class kunallogger
	{
		map < string, unique_ptr<filelogger> >logging_map;
	public:
		kunallogger();
		void log(string str, string message)
		{
			logging_map[str]->log(message);
		}
	};
	

}
 //int main()

 //{
	//mylogger::kunallogger  k;
	//k.log("vpgroping", "bhad main jao");


	// 
	// //auto console = bihari::stdout_color_mt("console");
	// //console->info("Welcome to spdlog!");
	// //console->error("Some error message with arg{}..", 1);

	// //// Formatting examples
	// //console->warn("Easy padding in numbers like {:08d}", 12);
	// //console->critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
	// //console->info("Support for floats {:03.2f}", 1.23456);
	// //console->info("Positional args are {1} {0}..", "too", "supported");
	// //console->info("{:<30}", "left aligned");
 //}
#endif // ! spdlogger