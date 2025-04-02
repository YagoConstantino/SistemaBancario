# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TesteDeNovo_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TesteDeNovo_autogen.dir\\ParseCache.txt"
  "TesteDeNovo_autogen"
  )
endif()
