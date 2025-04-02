# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TesteYago_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TesteYago_autogen.dir\\ParseCache.txt"
  "TesteYago_autogen"
  )
endif()
