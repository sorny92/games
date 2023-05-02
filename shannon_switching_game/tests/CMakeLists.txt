function(create_test test_file_name)
    add_executable(${test_file_name}_tests test_${test_file_name}.cpp)
    target_link_libraries(${test_file_name}_tests ${test_file_name})
    add_test(${test_file_name} ${test_file_name}_tests)
endfunction()

create_test(graph)
create_test(edge)
create_test(game)

