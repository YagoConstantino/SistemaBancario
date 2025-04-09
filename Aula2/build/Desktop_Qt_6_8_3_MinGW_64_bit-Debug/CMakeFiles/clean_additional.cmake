# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Aula2_autogen"
  "CMakeFiles\\Aula2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Aula2_autogen.dir\\ParseCache.txt"
  )
endif()
