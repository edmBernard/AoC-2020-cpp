
#**************************************************************************************************
# Set variable ************************************************************************************
SET(SAMPLES
  day3
)

foreach (SAMPLE ${SAMPLES})
  add_executable("aoc-${SAMPLE}" ${CMAKE_CURRENT_SOURCE_DIR}/${SAMPLE}.cpp)
  set_property(TARGET "aoc-${SAMPLE}" PROPERTY CXX_STANDARD 20)
  target_compile_options("aoc-${SAMPLE}" PRIVATE -O3)
  target_link_libraries("aoc-${SAMPLE}" PRIVATE -pthread)
endforeach(SAMPLE)
