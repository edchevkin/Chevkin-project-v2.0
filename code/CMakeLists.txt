# CMakeList.txt: ������ CMake ��� TheGame; �������� �������� ��� � �����������,
# ������� ����� ������ ��� ����������� �������.
#
cmake_minimum_required (VERSION 3.8)

# �������� �������� � ����������� ���� ����� �������.
add_executable(DungeonMaster "game.cpp" "enemy.cpp" "hero.cpp")
target_link_libraries(DungeonMaster PUBLIC sfml-graphics sfml-window sfml-system)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fonts/)

add_executable(DM_test "DM_Test.cpp" "enemy.cpp" "hero.cpp")
target_link_libraries(DM_test PUBLIC sfml-graphics sfml-window sfml-system doctest::doctest default)
doctest_discover_tests(DM_test)