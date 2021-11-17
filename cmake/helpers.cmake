cmake_minimum_required(VERSION 3.7.0 FATAL_ERROR)

function(_clio_install_component_headers component)
  install(
    DIRECTORY "${clio_source_dir}/include/${component}"
    DESTINATION ${clio_header_installation_dir}
    FILES_MATCHING PATTERN "*.hpp"
  )
endfunction()

function(_clio_install_library_file component)
  install(
    TARGETS "clio_${component}"
    DESTINATION ${clio_lib_installation_dir}
  )
endfunction()

# Usage: clio_register_component(component [HEADER_ONLY])
function(clio_register_component component)
  set(options HEADER_ONLY)
  cmake_parse_arguments(opt ${options} "" "" ${ARGV})

  add_custom_target(${component})
  if(NOT opt_HEADER_ONLY)
    add_library("clio_${component}")
    add_dependencies(${component} "clio_${component}")
    _clio_install_library_file(${component})
  endif()
  _clio_install_component_headers(${component})
  list(APPEND clio_component_list ${component})
  set(clio_component_list ${clio_component_list} PARENT_SCOPE)
endfunction()

# Usage: clio_process_components()
function(clio_process_components)
  foreach(component ${clio_component_list})
    set(clio_current_component "clio_${component}")
    add_subdirectory("${clio_source_dir}/clio/lib/${component}")
  endforeach()
endfunction()

# Usage: clio_install_impl_headers(files...)
function(clio_install_headers)
  foreach(header ${ARGV})
    file(RELATIVE_PATH dst_dir "${clio_source_dir}/clio" "${CMAKE_CURRENT_LIST_DIR}")
    install(FILES ${header} DESTINATION "${clio_header_installation_dir}/${dst_dir}")
  endforeach()
endfunction()

# Usage: clio_add_component_sources(sources...)
function(clio_add_component_sources)
  if(NOT DEFINED clio_current_component)
    message(FATAL_ERROR "infrastructure error: no component traversed at the moment")
  endif()
  target_sources(${clio_current_component} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/${ARGV}")
endfunction()
