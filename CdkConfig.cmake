# - Try to find CDK
# Once done this will define
#  CDK_FOUND - System has CDK
#  CDK_INCLUDE_DIRS - The CDK include directories
#  CDK_LIBRARIES - The libraries needed to use CDK
#  CDK_DEFINITIONS - Compiler switches required for using CDK

find_package(PkgConfig)
pkg_check_modules(PC_CDK QUIET cdk)
set(CDK_DEFINITIONS ${PC_CDK_CFLAGS_OTHER})

find_path(CDK_INCLUDE_DIR cdk/cdk.h
          HINTS ${PC_CDK_INCLUDEDIR} ${PC_CDK_INCLUDE_DIRS}
          PATH_SUFFIXES CDK )

find_library(CDK_LIBRARY NAMES cdk
             HINTS ${PC_CDK_LIBDIR} ${PC_CDK_LIBRARY_DIRS} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CDK_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CDK  DEFAULT_MSG
                                  CDK_LIBRARY CDK_INCLUDE_DIR)

mark_as_advanced(CDK_INCLUDE_DIR CDK_LIBRARY )

set(CDK_LIBRARIES ${CDK_LIBRARY} )
set(CDK_INCLUDE_DIRS ${CDK_INCLUDE_DIR} )
