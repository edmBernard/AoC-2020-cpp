
#**************************************************************************************************
# Set variable ************************************************************************************
SET(SAMPLES
  day9
)

foreach (SAMPLE ${SAMPLES})
  add_executable("aoc-${SAMPLE}" ${CMAKE_CURRENT_SOURCE_DIR}/${SAMPLE}.cpp)
  set_property(TARGET "aoc-${SAMPLE}" PROPERTY CXX_STANDARD 20)
endforeach(SAMPLE)
