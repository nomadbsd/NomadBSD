cmake_minimum_required(VERSION 3.16)
project(nomadbsd-setup-gui LANGUAGES CXX)
set(CMAKE_INSTALL_PREFIX "/usr")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROGRAM ${CMAKE_PROJECT_NAME})
set(BACKEND "nomadbsd-setup")
set(PATH_DATA_DIR ${CMAKE_INSTALL_PREFIX}/share/nomadbsd-setup)
set(BACKEND_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/libexec)
set(PATH_BACKEND ${BACKEND_INSTALL_DIR}/${BACKEND})
set(MODULE_PATH ${BACKEND_INSTALL_DIR})
set(ROOTLABEL
    "nomadroot"
    CACHE STRING "Label of the root device")
set(POOLNAME
    "nomadbsd_zroot"
    CACHE STRING "Name of ZFS pool")
set(ASHIFT
    "12"
    CACHE STRING "ZFS ashift")
set(FILESYSTEM
    "UFS"
    CACHE STRING "File system")
set(DATALABEL
    "nomaddata"
    CACHE STRING "Label of data partition")
file(GLOB DATA_FILES "files/*")
file(GLOB BACKEND_MODULES "backend/*.pm")

set(SOURCE_FILES src/main.cpp src/password.cpp src/wizard.cpp src/password.h
                 src/backend.h src/wizard.h)

find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)
qt_standard_project_setup()

set(TS_FILES
    locale/nomadbsd-setup-gui_ru.ts
    locale/nomadbsd-setup-gui_de.ts
    locale/nomadbsd-setup-gui_cs.ts
    locale/nomadbsd-setup-gui_id.ts
    locale/nomadbsd-setup-gui_fr.ts
    locale/nomadbsd-setup-gui_es.ts
    locale/nomadbsd-setup-gui_tr.ts)

add_executable(nomadbsd-setup-gui ${SOURCE_FILES})
qt_add_translations(nomadbsd-setup-gui TS_FILES ${TS_FILES})
qt_add_resources(
  nomadbsd-setup-gui
  "images"
  PREFIX
  "/images"
  BASE
  "${PROJECT_SOURCE_DIR}/images"
  FILES
  ${PROJECT_SOURCE_DIR}/images/logo-large.png
  ${PROJECT_SOURCE_DIR}/images/logo.png)

target_include_directories(
  nomadbsd-setup-gui
  PUBLIC "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
         "${CMAKE_CURRENT_SOURCE_DIR}/src")

if((${FILESYSTEM} STREQUAL "UFS") OR (${FILESYSTEM} STREQUAL "ufs"))
  set(BACKEND_MOD "backend/nomadbsd_setup_ufs.pm")
  if(MAC)
    set(MODULE_ARCH "mac")
  else()
    set(MODULE_ARCH "pc")
  endif()
elseif((${FILESYSTEM} STREQUAL "ZFS") OR (${FILESYSTEM} STREQUAL "zfs"))
  set(BACKEND_MOD "backend/nomadbsd_setup_zfs.pm")
  set(MODULE_ARCH "zfs")
endif()

configure_file(defs.h.in defs.h @ONLY)
configure_file(backend/nomadbsd-setup.in nomadbsd-setup @ONLY)

set(LIBS Qt6::Widgets)
target_link_libraries(nomadbsd-setup-gui PRIVATE ${LIBS})

install(TARGETS nomadbsd-setup-gui DESTINATION bin)
install(PROGRAMS "${CMAKE_CURRENT_BINARY_DIR}/${BACKEND}" DESTINATION libexec)
install(FILES ${BACKEND_MODULES} DESTINATION libexec)
install(FILES ${DATA_FILES} DESTINATION ${PATH_DATA_DIR})
