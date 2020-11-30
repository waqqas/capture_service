cmake_minimum_required(VERSION 3.12)

project("CaptureService" VERSION "0.1.0")

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(macros.cmake)

set(ICON_NAME appicon.icns)

set_source_files_properties(${ICON_NAME} PROPERTIES 
MACOSX_PACKAGE_LOCATION Resources
)

set(SOURCES main.cpp Info.plist.in license.txt ${ICON_NAME} app.plist)
add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES})

ADD_OSX_FRAMEWORK(${PROJECT_NAME} Foundation )
ADD_OSX_FRAMEWORK(${PROJECT_NAME} CoreGraphics )

# app.plist

configure_file(app.plist.in app.plist)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/app.plist PROPERTIES 
MACOSX_PACKAGE_LOCATION Resources
)


# app icon

file(COPY ${ICON_NAME} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set_source_files_properties(license.txt PROPERTIES 
MACOSX_PACKAGE_LOCATION Resources
)


set_target_properties(${PROJECT_NAME} PROPERTIES
MACOSX_BUNDLE ON
MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in
)

set(Boost_USE_RELEASE_LIBS ON)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS system date_time)
target_include_directories(${PROJECT_NAME} PUBLIC "${Boost_INCLUDE_DIRS}")
target_link_libraries(${PROJECT_NAME} Boost::system Boost::date_time)
add_dependencies(${PROJECT_NAME} Boost::system Boost::date_time)


install(TARGETS ${PROJECT_NAME} 
  RUNTIME DESTINATION bin
  BUNDLE DESTINATION bin
  RESOURCE DESTINATION bin
)
