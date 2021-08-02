set( target chapter02 )

set( chapter02_SOURCES
	main.cpp
	diffuse_reflection.cpp
	adsReflection.cpp 
	adsTwoSide.cpp )

	
include_directories( 
	${CMAKE_MAIN_DIRECTORY}/ingredients
	${CMAKE_MAIN_DIRECTORY}/include )

link_directories(${CMAKE_MAIN_DIRECTORY}/lib)

add_executable( ${target} ${chapter02_SOURCES} )

target_compile_definitions(${target}
		PRIVATE
		GLFW_INCLUDE_NONE
		)

target_link_libraries( ${target}
		PRIVATE
		ingredients
		glfw3
		${OPENGL_gl_LIBRARY}
		)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
