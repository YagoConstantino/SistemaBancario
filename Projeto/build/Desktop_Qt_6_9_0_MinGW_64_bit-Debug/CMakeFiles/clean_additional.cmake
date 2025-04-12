# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Projeto_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Projeto_autogen.dir\\ParseCache.txt"
  "Projeto_autogen"
  )
endif()
