set(TARGET_NAME ${PROJECT_NAME})

if(APPLE)
    # create bundle on apple compiles
    add_executable(${TARGET_NAME} MACOSX_BUNDLE )

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(${TARGET_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable(${TARGET_NAME} WIN32 ${TARGET_NAME}.exe.manifest)
endif()

target_sources(
  ${TARGET_NAME}
  PRIVATE
  app.cpp
  cli_controller.cpp
  cli_view.cpp
  app.h
  cli_controller.h
  cli_view.h
)
# Statically link with mingw
# if(MINGW)
#   target_link_libraries (${TARGET_NAME} PRIVATE -static gcc stdc++ winpthread -dynamic)
# endif()
target_link_libraries(${TARGET_NAME} PRIVATE pascha-lib)
