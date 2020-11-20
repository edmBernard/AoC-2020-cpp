
#**************************************************************************************************
# Set variable ************************************************************************************
SET(SAMPLES
  day1_part1
  day1_part2
)

foreach (SAMPLE ${SAMPLES})
  add_executable("aoc-${SAMPLE}" ${CMAKE_CURRENT_SOURCE_DIR}/${SAMPLE}.cpp)
  target_compile_options("aoc-${SAMPLE}" PRIVATE -O3)
  target_link_libraries("aoc-${SAMPLE}" PRIVATE -pthread)
endforeach(SAMPLE)
