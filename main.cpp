#include <sstream>
#include <boost/format.hpp>
#include <boost/process.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <iostream>

#include <CoreFoundation/CFURL.h>
#include <ImageIO/CGImageDestination.h>
#include <CoreGraphics/CGDirectDisplay.h>

namespace bp = boost::process;
namespace pt = boost::posix_time;

bool _continue = true;

void handle_sigint(int sig)
{
    _continue = false;
}

void doCGCapture()
{
    CGDirectDisplayID displays[256];
    uint32_t dispCount = 0;

    // get a list of all displays
    if (CGGetActiveDisplayList(256, displays, &dispCount))
    {
        printf("Error getting display list\n");
        return;
    }

    std::ostringstream filename;
    pt::ptime now = pt::second_clock::local_time();

    // iterate screens and take the screenshots
    for (int i = 0; i < dispCount; i++)
    {
        CGDirectDisplayID dispId = displays[i];

        // get the raw pixels
        CGImageRef img = CGDisplayCreateImage(dispId);

        filename << boost::format(R"DEM(/tmp/cg-%d-%s.jpg)DEM") % pt::to_iso_string(now) % i;

        // output file
        CFURLRef path =
            CFURLCreateWithFileSystemPath(NULL,
                                          __CFStringMakeConstantString(filename.str().c_str()),
                                          kCFURLPOSIXPathStyle, false);

        // file/format to save pixels to
        CGImageDestinationRef destination =
            CGImageDestinationCreateWithURL(
                path, CFSTR("public.jpeg"), 1, NULL); //[4]

        // add our captured pixels
        CGImageDestinationAddImage(destination, img, nil);

        // generate the image
        if (!CGImageDestinationFinalize(destination))
        {
            printf("Failed to finalize\n");
        }
    }
}

int main(int argc, char *argv[])
{
    signal(SIGINT, handle_sigint);

    while (_continue)
    {
        // std::ostringstream command;
        // pt::ptime now = pt::second_clock::local_time();
        // command << boost::format(R"DEM(screencapture -x -D1 -t jpg "/tmp/cpp-%s.jpg")DEM") % pt::to_iso_string(now);
        // std::cout << command.str() << std::endl;
        // bp::system(command.str());

        doCGCapture();

        sleep(10);
    }

    return 0;
}