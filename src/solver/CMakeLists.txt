# see arithmetic/CMakeLists.txt for comments

list (APPEND IBEX_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_DefaultSolver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_DefaultSolver.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Solver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Solver.h
  )

list (APPEND IBEX_INCDIRS ${CMAKE_CURRENT_SOURCE_DIR})

# Propagate new values of list to parent scope
set (IBEX_SRC ${IBEX_SRC} PARENT_SCOPE)
set (IBEX_INCDIRS ${IBEX_INCDIRS} PARENT_SCOPE)
