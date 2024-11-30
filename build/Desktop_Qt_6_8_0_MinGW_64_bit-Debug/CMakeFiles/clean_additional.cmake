# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Novella_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Novella_autogen.dir\\ParseCache.txt"
  "Novella_autogen"
  )
endif()
