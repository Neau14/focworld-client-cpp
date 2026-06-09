# Install script for directory: C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/focworld_tcg")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/Debug/ixwebsocket.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/Release/ixwebsocket.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/MinSizeRel/ixwebsocket.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/RelWithDebInfo/ixwebsocket.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ixwebsocket" TYPE FILE FILES
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXBase64.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXBench.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXCancellationRequest.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXConnectionState.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXDNSLookup.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXExponentialBackoff.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXGetFreePort.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXGzipCodec.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXHttp.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXHttpClient.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXHttpServer.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXNetSystem.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXProgressCallback.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXSelectInterrupt.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXSelectInterruptFactory.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXSelectInterruptPipe.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXSelectInterruptEvent.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXSetThreadName.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXSocket.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXSocketConnect.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXSocketFactory.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXSocketServer.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXSocketTLSOptions.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXStrCaseCompare.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXUdpSocket.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXUniquePtr.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXUrlParser.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXUuid.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXUtf8Validator.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXUserAgent.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocket.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketCloseConstants.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketCloseInfo.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketErrorInfo.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketHandshake.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketHandshakeKeyGen.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketHttpHeaders.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketInitResult.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketMessage.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketMessageType.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketOpenInfo.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketPerMessageDeflate.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketPerMessageDeflateCodec.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketPerMessageDeflateOptions.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketProxyServer.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketSendData.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketSendInfo.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketServer.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketTransport.h"
    "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-src/ixwebsocket/IXWebSocketVersion.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket" TYPE FILE FILES "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/ixwebsocket-config.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/ixwebsocket.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket/ixwebsocket-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket/ixwebsocket-targets.cmake"
         "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/CMakeFiles/Export/dbc99e06a99e696141dafd40631f8060/ixwebsocket-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket/ixwebsocket-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket/ixwebsocket-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket" TYPE FILE FILES "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/CMakeFiles/Export/dbc99e06a99e696141dafd40631f8060/ixwebsocket-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket" TYPE FILE FILES "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/CMakeFiles/Export/dbc99e06a99e696141dafd40631f8060/ixwebsocket-targets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket" TYPE FILE FILES "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/CMakeFiles/Export/dbc99e06a99e696141dafd40631f8060/ixwebsocket-targets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket" TYPE FILE FILES "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/CMakeFiles/Export/dbc99e06a99e696141dafd40631f8060/ixwebsocket-targets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket" TYPE FILE FILES "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/CMakeFiles/Export/dbc99e06a99e696141dafd40631f8060/ixwebsocket-targets-release.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/spdlog-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/ws/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/antoi/Desktop/FOCWorld/focworld-client-cpp/build/_deps/ixwebsocket-build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
