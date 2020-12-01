# capture_service
Mac OS screen capture agent

# dependencies
- boost (1.74)

# build
- mkdir build
- cd build
- cmake ..
- make

# generate installer
Make sure that Qt Installer framework is installed and binarycreator is available in path

- make install
- make installer

# output
Service generate a screen capture every 10 seconds in /tmp directory