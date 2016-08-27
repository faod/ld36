#.rst:
# FindSTP
# --------
#
# Find STP includes and libraries (https://github.com/edoren/STP).
#
# Output
# ------

# This script defines the following variables:
# * STP_INCLUDE_DIR:      the path where STP headers are located
# * STP_FOUND:            true if LibSTP is found
# * STP_LIBRARY:          the name of the library to link
# * STP_LIBRARIES
# * STP_LIBRARY_RELEASE:  the name of the release library
# * STP_LIBRARY_DEBUG:    the name of the debug library
#
# Hints
# -----
#
# A user may set ``STP_ROOT`` to a LibSTP installation root to tell this
# module where to look.
if(NOT STP_ROOT)
  set(STP_ROOT "")
endif()

# Find include files
find_path(STP_INCLUDE_DIR NAMES "STP/TMXLoader.hpp" PATHS ${STP_ROOT} PATH_SUFFIXES "include")

# Find libraries
find_library(STP_LIBRARY_RELEASE NAMES "STP"    PATHS ${STP_ROOT}  PATH_SUFFIXES "lib" "lib64")
find_library(STP_LIBRARY_DEBUG   NAMES "STP-d"  PATHS ${STP_ROOT}  PATH_SUFFIXES "lib" "lib64")

MARK_AS_ADVANCED(STP_LIBRARY_RELEASE STP_LIBRARY_DEBUG)

if(STP_LIBRARY_RELEASE OR STP_LIBRARY_DEBUG)
  # both found
  if(STP_LIBRARY_RELEASE AND STP_LIBRARY_DEBUG)
    set(STP_LIBRARY optimized ${STP_LIBRARY_RELEASE} debug ${STP_LIBRARY_DEBUG})
  # release not debug
  elseif(STP_LIBRARY_RELEASE)
    set(STP_LIBRARY ${STP_LIBRARY_RELEASE})
    set(STP_LIBRARY_DEBUG ${STP_LIBRARY_RELEASE})
  # debug not release
  else()
    set(STP_LIBRARY ${STP_LIBRARY_DEBUG})
    set(STP_LIBRARY_RELEASE ${STP_LIBRARY_DEBUG})
  endif()
endif()

set(STP_LIBRARIES "${STP_LIBRARY}")

# Additional modules
include(FindPackageHandleStandardArgs)

# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(STP DEFAULT_MSG STP_INCLUDE_DIR STP_LIBRARIES)
