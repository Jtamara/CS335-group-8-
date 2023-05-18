add_library(pokemon "")
set_target_properties(pokemon PROPERTIES LINKER_LANGUAGE CXX)

target_sources(pokemon
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/attack.hpp
		${CMAKE_CURRENT_LIST_DIR}/attack_factory.hpp
		${CMAKE_CURRENT_LIST_DIR}/pokemon.hpp
		${CMAKE_CURRENT_LIST_DIR}/pokemon_factory.hpp
		${CMAKE_CURRENT_LIST_DIR}/types.hpp
)

target_include_directories(pokemon
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)