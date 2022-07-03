function (create_type type_name)

	set(PROJECT_NAME ${type_name})	

	include(CheckIPOSupported)
	check_ipo_supported(RESULT supported OUTPUT error)
	
	if( supported )
		message(STATUS "${PROJECT_NAME} => IPO / LTO enabled")
		set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
	else()
		message(STATUS "${PROJECT_NAME} => IPO / LTO not supported: <${error}>")
	endif()
	
	include_directories(../../GViewCore/include)
	
	add_library(${PROJECT_NAME} SHARED)
	
	if (MSVC)
	    add_definitions(-DBUILD_FOR_WINDOWS)
	    add_compile_options(-W3)
	elseif (APPLE)
	    add_definitions(-DBUILD_FOR_OSX)
	    if (DEBUG_BUILD)
        	add_compile_options(-g)
	        add_compile_options(-W)
	    endif()
	elseif (UNIX)
	    add_definitions(-DBUILD_FOR_UNIX)
	    if (DEBUG_BUILD)
	        add_compile_options(-g)
	        add_compile_options(-W)
	    endif()
	endif()
	
	include_directories(include)
	
	add_subdirectory(src)

	file(GLOB_RECURSE PROJECT_HEADERS include/*.hpp)
	target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_HEADERS})

	add_dependencies(${PROJECT_NAME} GViewCore)
	add_dependencies(${PROJECT_NAME} AppCUI)
	
	target_link_libraries(${PROJECT_NAME} PRIVATE GViewCore)
	target_link_libraries(${PROJECT_NAME} PRIVATE AppCUI)
	
	set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "lib")
	set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".tpl")
	
	set_target_properties(${PROJECT_NAME} PROPERTIES
				    FOLDER "Types"
                    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Types"
                    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Types"
		            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Types"
			        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Types")
	
	get_target_property(F ${PROJECT_NAME} FOLDER)
	get_target_property(RODD ${PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY_DEBUG)
	get_target_property(RODR ${PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY_RELEASE)
	get_target_property(AOD ${PROJECT_NAME} ARCHIVE_OUTPUT_DIRECTORY)
	get_target_property(LOD ${PROJECT_NAME} LIBRARY_OUTPUT_DIRECTORY)
	
	message(STATUS "${PROJECT_NAME} => FOLDER = ${F}")
	message(STATUS "${PROJECT_NAME} => RUNTIME_OUTPUT_DIRECTORY_DEBUG = ${RODD}")
	message(STATUS "${PROJECT_NAME} => RUNTIME_OUTPUT_DIRECTORY_RELEASE = ${RODR}")
	message(STATUS "${PROJECT_NAME} => ARCHIVE_OUTPUT_DIRECTORY = ${AOD}")
	message(STATUS "${PROJECT_NAME} => LIBRARY_OUTPUT_DIRECTORY = ${LOD}")
endfunction()

