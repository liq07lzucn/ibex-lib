# see arithmetic/CMakeLists.txt for comments

list (APPEND IBEX_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Agenda.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Agenda.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Array.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_BitSet.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_BitSet.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_DirectedHyperGraph.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_DirectedHyperGraph.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_DoubleHeap.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Exception.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Exception.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Heap.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_HyperGraph.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_HyperGraph.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Id.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Id.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_IntStack.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Map.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Memory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Memory.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Random.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Random.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_SharedHeap.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_String.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_String.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_SymbolMap.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Timer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_Timer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ibex_mistral_Bitset.h
  )

list (APPEND IBEX_INCDIRS ${CMAKE_CURRENT_SOURCE_DIR})

# Propagate new values of list to parent scope
set (IBEX_SRC ${IBEX_SRC} PARENT_SCOPE)
set (IBEX_INCDIRS ${IBEX_INCDIRS} PARENT_SCOPE)
