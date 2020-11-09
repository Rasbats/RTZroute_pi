##---------------------------------------------------------------------------
## Author:      Rasbats aka. Mike Rossiter
## Copyright:
## License:     wxWidgets License
##---------------------------------------------------------------------------

# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(RTZroute_pi)

SET(PACKAGE_NAME RTZroute_pi)
SET(VERBOSE_NAME RTZroute)
SET(TITLE_NAME RTZroute)
SET(CPACK_PACKAGE_CONTACT "Mike Rossiter")

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "3")

SET(NAME_SUFFIX "ov50")

set (CMAKE_CXX_STANDARD 11)

#SET(CMAKE_BUILD_TYPE Debug)
SET( wxWidgets_USE_DEBUG OFF)
SET( wxWidgets_USE_UNICODE ON)
SET( wxWidgets_USE_UNIVERSAL OFF)
SET( wxWidgets_USE_STATIC OFF)

#SET(CMAKE_BUILD_TYPE Debug)
OPTION(RTZroute_USE_SVG "Use SVG graphics" ON)

INCLUDE("cmake/PluginConfigure.cmake")

IF(WIN32)
	SET(xercesc ${CMAKE_SOURCE_DIR}/src/xercesc)
	SET(xercesc "${PARENT}.lib")

	LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/xercesc)
	INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/xercesc)
	INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/xercesc/include)
	
ENDIF(WIN32)


IF(RTZroute_USE_SVG)
  ADD_DEFINITIONS(-DRTZroute_USE_SVG)
ENDIF(RTZroute_USE_SVG)

SET(SRC_RTZroute
        src/RTZroute_pi.h
        src/RTZroute_pi.cpp
        src/icons.h
        src/icons.cpp
	    src/RTZroutegui.h
	    src/RTZroutegui.cpp
	    src/RTZroutegui_impl.cpp
	    src/RTZroutegui_impl.h
		src/load-grammar-dom.cpp
		src/load-grammar-dom.h
		src/load-grammar-sax.cpp
		src/load-grammar-sax.h
	    src/NavFunc.h
	    src/NavFunc.cpp
		src/ocpn_plugin.h
		src/tinyxml.cpp
        src/tinyxmlerror.cpp
        src/tinyxmlparser.cpp
        src/tinyxml.h
		src/tinyxml2.cpp
		src/tinyxml2.h
	)


ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_RTZroute})

ADD_DEFINITIONS(-DTIXML_USE_STL)

IF(WIN32)
	FIND_LIBRARY(xerces-c_3 ${CMAKE_SOURCE_DIR}/src/xercesc)
	TARGET_LINK_LIBRARIES(${PACKAGE_NAME} xerces-c_3)
ENDIF(WIN32)

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
