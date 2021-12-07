SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")

add_executable(zybo-chess.elf main.c board.c minimax.c)
target_link_libraries(zybo-chess.elf ${330_LIBS})
set_target_properties(zybo-chess.elf PROPERTIES LINKER_LANGUAGE CXX)
