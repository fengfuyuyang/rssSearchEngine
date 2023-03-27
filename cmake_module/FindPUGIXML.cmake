set(PUGIXML_VERSION v1.13)
set(PUGIXML_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/pugixml-${PUGIXML_VERSION}/build)

find_path(PUGIXML_INCLUDE_DIR NAMES pugixml.hpp HINTS ${PUGIXML_ROOT_DIR}/include)
find_library(PUGIXML_LIBRARY NAMES pugixml HINTS ${PUGIXML_ROOT_DIR}/lib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PUGIXML DEFAULT_MSG PUGIXML_LIBRARY PUGIXML_INCLUDE_DIR)

if(PUGIXML_FOUND)
    set(PUGIXML_LIBRARIES ${PUGIXML_LIBRARY})
    set(PUGIXML_INCLUDE_DIRS ${PUGIXML_INCLUDE_DIR})
endif()

mark_as_advanced(PUGIXML_INCLUDE_DIR PUGIXML_LIBRARY)
