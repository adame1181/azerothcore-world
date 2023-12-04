# tests/CMakeLists.txt

# Nastavenie názvu testovacieho projektu
set(TEST_PROJECT_NAME VehicleTests)

# Zbieranie zdrojových súborov pre testy
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp")

# Vytvorenie testovacieho projektu
add_executable(${TEST_PROJECT_NAME} ${TEST_SOURCES})

# Priradenie závislostí pre testy
target_link_libraries(${TEST_PROJECT_NAME} PRIVATE gtest gtest_main game)

# Pridanie konfigurácie spustenia testov
add_test(NAME ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME})
