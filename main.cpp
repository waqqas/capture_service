#include <sstream>
#include <boost/format.hpp>
#include <boost/process.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <iostream>

namespace bp = boost::process;
namespace pt = boost::posix_time;

bool _continue = true;

void handle_sigint(int sig)
{
    _continue = false;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, handle_sigint);

    while (_continue)
    {
        std::ostringstream command;

        pt::ptime now = pt::second_clock::local_time();

        command << boost::format(R"DEM(screencapture -x -D1 -t jpg "/tmp/cpp-%s.jpg")DEM") % pt::to_iso_string(now);

        std::cout << command.str() << std::endl;

        bp::system(command.str());

        sleep(10);
    }

    return 0;
}