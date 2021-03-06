include (SubDirList)
subdir_list (LP_LIB_LIST RELATIVE)

set(LP_LIB "none" CACHE STRING "Library used for linear programming")
set_property(CACHE LP_LIB PROPERTY STRINGS ${LP_LIB_LIST})

list(FIND LP_LIB_LIST ${LP_LIB} is_valid)
if (is_valid LESS 0)
  message (FATAL_ERROR "Unsupported library for interval arithmetic: ${LP_LIB}")
else ()
  message (STATUS "Library for interval arithmetic: ${LP_LIB}")
endif ()

# Absolute path of wrapper directory
set (LP_LIB_ABSPATH ${CMAKE_CURRENT_SOURCE_DIR}/${LP_LIB})

# Go into wrapper directory
add_subdirectory (${LP_LIB})

# Check that mandatory file exists and add it in IBEX_SRC
set (LP_LIB_REQUIRED_FILES ibex_LPLibWrapper.cpp ibex_LPLibWrapper.h)

set (PRE "Error with wrapper of linear programming ${LP_LIB}")
foreach (f ${LP_LIB_REQUIRED_FILES})
  if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${LP_LIB}/${f})
    message (FATAL_ERROR "${PRE}, it should have a file named ${f}")
  else ()
    list (APPEND IBEX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${LP_LIB}/${f})
  endif ()
endforeach ()

# Add directory of wrapper in list of included directory
list (APPEND IBEX_INCDIRS ${LP_LIB_ABSPATH})

# Propagate new values of list to parent scope
set (IBEX_INCDIRS ${IBEX_INCDIRS} PARENT_SCOPE)
set (IBEX_SRC ${IBEX_SRC} PARENT_SCOPE)
