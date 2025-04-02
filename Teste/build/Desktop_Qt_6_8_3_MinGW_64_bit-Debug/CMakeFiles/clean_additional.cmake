# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Teste_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Teste_autogen.dir\\ParseCache.txt"
  "Teste_autogen"
  )
endif()
