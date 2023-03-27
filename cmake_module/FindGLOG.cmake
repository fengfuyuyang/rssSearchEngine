set(GLOG_VERSION v0.6.0)
set(GLOG_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glog-${GLOG_VERSION}/build)

find_path(GLOG_INCLUDE_DIR NAMES glog/logging.h HINTS ${GLOG_ROOT_DIR}/include)
find_library(GLOG_LIBRARY NAMES glog HINTS ${GLOG_ROOT_DIR}/lib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLOG DEFAULT_MSG GLOG_LIBRARY GLOG_INCLUDE_DIR)

if(GLOG_FOUND)
    set(GLOG_LIBRARIES ${GLOG_LIBRARY})
    set(GLOG_INCLUDE_DIRS ${GLOG_INCLUDE_DIR})
endif()

mark_as_advanced(GLOG_INCLUDE_DIR GLOG_LIBRARY)
