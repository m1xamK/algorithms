if(EXISTS "C:/Users/Kastoms/Desktop/mp_ddz/out/build/x64-Debug/LinkedList/tests/LinkedList_tests[1]_tests.cmake")
  include("C:/Users/Kastoms/Desktop/mp_ddz/out/build/x64-Debug/LinkedList/tests/LinkedList_tests[1]_tests.cmake")
else()
  add_test(LinkedList_tests_NOT_BUILT LinkedList_tests_NOT_BUILT)
endif()
