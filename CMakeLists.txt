cmake_minimum_required(VERSION 3.12)

project(sima)

add_executable(sima WIN32
	"src/sim/computer.cpp"
	"src/sim/assembly/instruction.cpp"
	"src/sim/assembly/operand.cpp"
	"src/sim/assembly/program.cpp"
	"src/ui/application.cpp"
	"src/ui/memory_window.cpp"
	"src/ui/proc_window.cpp"
	"src/ui/window.cpp"
	"src/main.cpp"
)

target_precompile_headers(sima PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h)
target_compile_definitions(sima PRIVATE UNICODE)
