
#**************************************************************************************************
# Set variable ************************************************************************************
SET(SAMPLES
  day4
)

foreach (SAMPLE ${SAMPLES})
  add_executable("aoc-${SAMPLE}" ${CMAKE_CURRENT_SOURCE_DIR}/${SAMPLE}.cpp)
endforeach(SAMPLE)
