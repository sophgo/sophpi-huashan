#----------------------------------------------------------------
# Generated CMake target import file for configuration "RELEASE".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "flatbuffers::flatbuffers" for configuration "RELEASE"
set_property(TARGET flatbuffers::flatbuffers APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(flatbuffers::flatbuffers PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libflatbuffers.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS flatbuffers::flatbuffers )
list(APPEND _IMPORT_CHECK_FILES_FOR_flatbuffers::flatbuffers "${_IMPORT_PREFIX}/lib/libflatbuffers.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
