pkg_check_modules(ASSIMP QUIET assimp>=3.0)
if(ASSIMP_FOUND)
  option(BUILD_ASSIMP_PLUGIN "Building ASSIMPPlugin" ON)
else()
  option(BUILD_ASSIMP_PLUGIN "Building ASSIMPPlugin" OFF)
endif()

if(NOT BUILD_ASSIMP_PLUGIN)
  return()
endif()

set(ASSIMP_DIR ${ASSIMP_DIR} CACHE PATH "set the top directory of the ASSIMP")
if(UNIX)
  if(NOT ASSIMP_DIR)
    pkg_check_modules(ASSIMP REQUIRED assimp>=3.0)
  endif()
elseif(MSVC)
  if(NOT ASSIMP_DIR)
    message(FATAL_ERROR "Please specify the directory of the ASSIMP to ASSIMP_DIR.")
  endif()
endif()

if(NOT ASSIMP_FOUND )
  if(UNIX)
    set(ASSIMP_LIBRARIES assimp)
  elseif(MSVC)
    if( MSVC12 )
      set(MSVC_PREFIX "vc120")
    elseif( MSVC14 )
      set(MSVC_PREFIX "vc140")
    else()
      set(MSVC_PREFIX "vc150")
    endif()
      set(ASSIMP_LIBRARIES "assimp-${MSVC_PREFIX}-mt")
  endif()
    set(ASSIMP_INCLUDE_DIRS ${ASSIMP_DIR}/include)
    set(ASSIMP_LIBRARY_DIRS ${ASSIMP_DIR}/lib)
endif()

set(target CnoidAssimpPlugin)

include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})

set(sources
  AssimpPlugin.cpp
  AssimpSceneLoader.cpp
)

set(headers )

make_gettext_mofiles(${target} mofiles) 
add_cnoid_plugin(${target} SHARED ${sources} ${headers} ${mofiles})
target_link_libraries(${target} CnoidBase ${ASSIMP_LIBRARIES})
apply_common_setting_for_plugin(${target} "${headers}")

if(MSVC)
  if(INSTALL_RUNTIME_DEPENDENCIES)
    install(PROGRAMS  ${ASSIMP_DIR}/bin/${ASSIMP_LIBRARIES}.dll DESTINATION bin
      CONFIGURATIONS Release Debug)
  endif()
endif()