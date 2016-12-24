cmake_minimum_required(VERSION 2.6)
PROJECT (tmy_server)

# set(CMAKE_CURRENT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
# set(COMMON_DIR ../common)
# INCLUDE_DIRECTORIES($(COMMON_DIR))

SET(CMAKE_CXX_FLAGS  "-std=c++11")

# find mysql 

if( WIN32 )
	find_path( MYSQL_INCLUDE_DIR
		NAMES "mysql.h"
		PATHS "$ENV{PROGRAMFILES}/MySQL/*/include"
			  "$ENV{PROGRAMFILES(x86)}/MySQL/*/include"
			  "$ENV{SYSTEMDRIVE}/MySQL/*/include" )
	
	find_library( MYSQL_LIBRARY
		NAMES "mysqlclient" "mysqlclient_r"
		PATHS "$ENV{PROGRAMFILES}/MySQL/*/lib"
			  "$ENV{PROGRAMFILES(x86)}/MySQL/*/lib"
			  "$ENV{SYSTEMDRIVE}/MySQL/*/lib" )
else()
	find_path( MYSQL_INCLUDE_DIR
		NAMES "mysql.h"
		PATHS "/usr/include/mysql"
			  "/usr/local/include/mysql"
			  "/usr/mysql/include/mysql" )
	
	find_library( MYSQL_LIBRARY
		NAMES "mysqlclient" "mysqlclient_r"
		PATHS "/lib/mysql"
			  "/lib64/mysql"
			  "/usr/lib/mysql"
			  "/usr/lib64/mysql"
			  "/usr/local/lib/mysql"
			  "/usr/local/lib64/mysql"
			  "/usr/mysql/lib/mysql"
			  "/usr/mysql/lib64/mysql" )
endif()



if( MYSQL_INCLUDE_DIR AND EXISTS "${MYSQL_INCLUDE_DIRS}/mysql_version.h" )
	file( STRINGS "${MYSQL_INCLUDE_DIRS}/mysql_version.h"
		MYSQL_VERSION_H REGEX "^#define[ \t]+MYSQL_SERVER_VERSION[ \t]+\"[^\"]+\".*$" )
	string( REGEX REPLACE
		"^.*MYSQL_SERVER_VERSION[ \t]+\"([^\"]+)\".*$" "\\1" MYSQL_VERSION_STRING
		"${MYSQL_VERSION_H}" )
endif()

# handle the QUIETLY and REQUIRED arguments and set MYSQL_FOUND to TRUE if
# all listed variables are TRUE
include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( MYSQL DEFAULT_MSG
	REQUIRED_VARS	MYSQL_LIBRARY MYSQL_INCLUDE_DIR
	VERSION_VAR		MYSQL_VERSION_STRING )

set( MYSQL_INCLUDE_DIRS ${MYSQL_INCLUDE_DIR} )
set( MYSQL_LIBRARIES ${MYSQL_LIBRARY} )

mark_as_advanced( MYSQL_INCLUDE_DIR MYSQL_LIBRARY )

#####

add_library(tmy_server logger.cpp)
add_executable(tmy_server1 server.cpp)
target_link_libraries(tmy_server1  MYSQL_LIBRARIES)