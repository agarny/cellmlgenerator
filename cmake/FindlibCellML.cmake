find_path(LIBCELLML_INCLUDE_DIR libcellml/version.h
    HINTS $ENV{LIBCELLML}/include
)

if(    EXISTS ${LIBCELLML_INCLUDE_DIR}/libcellml/version.h
   AND EXISTS ${LIBCELLML_INCLUDE_DIR}/libcellml/module/libcellml
   AND EXISTS ${LIBCELLML_INCLUDE_DIR}/../lib/libcellml${CMAKE_SHARED_LIBRARY_SUFFIX})
    set(LIBCELLML_FOUND YES)

    set(LIBCELLML_MODULE_DIR ${LIBCELLML_INCLUDE_DIR}/libcellml/module)
    set(LIBCELLML_LIBRARY ${LIBCELLML_INCLUDE_DIR}/../lib/libcellml${CMAKE_SHARED_LIBRARY_SUFFIX})
else()
    set(LIBCELLML_FOUND NO)
endif()
