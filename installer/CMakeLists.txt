add_subdirectory("config")
add_subdirectory("packages")

add_custom_target(installer_installer ALL
    DEPENDS  installer.app
)

add_custom_command(
  OUTPUT ${INSTALLER_DIR}/packages/com.test.app.${PROJECT_NAME}/data/${PROJECT_NAME}.app
  COMMENT "Copying app bundle"
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}.app ${INSTALLER_DIR}/packages/com.test.app.${PROJECT_NAME}/data
)

add_custom_command(
    OUTPUT  installer.app
    DEPENDS ${INSTALLER_DIR}/packages/com.test.app.${PROJECT_NAME}/data/${PROJECT_NAME}.app
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${INSTALLER_DIR}/packages/CMakeFiles
    COMMAND binarycreator --offline-only -c ${INSTALLER_DIR}/config/config.xml -p ${INSTALLER_DIR}/packages ${CMAKE_CURRENT_BINARY_DIR}/installer
)
