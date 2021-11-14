cmake_minimum_required(VERSION 3.7.0 FATAL_ERROR)

# Usage: clio_install_public_header_dirs(dirs...)
function(clio_install_public_header_dirs)
  install(
    DIRECTORY ${ARGV}
    DESTINATION "include/clio"  
    FILES_MATCHING PATTERN "*.hpp"
  )
endfunction()

# Usage: clio_install_impl_headers(files...)
macro(clio_install_impl_headers)
  foreach(header ${ARGV})
    file(RELATIVE_PATH dst_dir "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_LIST_DIR}")
    install(FILES ${header} DESTINATION "include/clio/${dst_dir}")
  endforeach()
endmacro()

# Usage: clio_build_components(names...)
macro(clio_build_components)
  foreach(component ${ARGV})
    add_library(${component} INTERFACE)
  endforeach() 
  foreach(component ${ARGV})
    set(clio_current_component ${component})
    add_subdirectory(${component})
  endforeach()
endmacro()
