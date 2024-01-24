#include "s21_test_string.h"

void run_suite(Suite *suite) {
  SRunner *sr = srunner_create(suite);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);  // CK_MINIMAL CK_NORMAL CK_VERBOSE

  srunner_free(sr);
}

void run_tests() {
  Suite *suites_core[] = {
	suite_s21_memchr(),      // 0
	suite_s21_memcmp(),      // 1
	suite_s21_memcpy(),      // 2
	suite_s21_memset(),      // 3
	suite_s21_strncat(),     // 4
	suite_s21_strchr(),      // 5
	suite_s21_strncmp(),     // 6
	suite_s21_strncpy(),     // 7
	suite_s21_strcspn(),     // 8
	suite_s21_strerror(),    // 9
	suite_s21_strlen(),      // 10
	suite_s21_strpbrk(),     // 11
	suite_s21_strrchr(),     // 12
	suite_s21_strstr(),      // 13
	suite_s21_strtok(),      // 14
 	suite_s21_sprintf(),     // 15
	suite_s21_sscanf(),      // 16
	suite_s21_to_lower(),    // 17
	suite_s21_to_upper(),    // 18
	suite_s21_trim(),        // 19
	suite_s21_insert(),      // 20  
	NULL};

  for (Suite **cur = suites_core; *cur != NULL; cur++) {
    printf("\n==================================\n");
    run_suite(*cur);
    printf("\n==================================\n");
  }
}

int main() {
  run_tests();
  return 0;
}
