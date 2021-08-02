set(target chapter01)

set( chapter01_SOURCES
	main.cpp
	chapter_01.cpp
	load_shader.cpp )

include_directories( ingredients include)
link_directories(lib)

add_executable( ${target} ${chapter01_SOURCES} )

target_compile_definitions(${target}
		PRIVATE
		${DEFAULT_COMPILE_DEFINITIONS}
		GLFW_INCLUDE_NONE
		)

target_link_libraries( ${target}
        PRIVATE
        ingredients
        ${OPENGL_gl_LIBRARY}
		glfw3
		)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
