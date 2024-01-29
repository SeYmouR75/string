#include "s21_test_string.h"

#define ACTUAL(x, y) s21_strstr(x, y)
#define EXPECTED(x, y) strstr(x, y)
#define SUITE_LABEL "suite_s21_strstr"
#define SUITE_NAME *suite_s21_strstr()
#define HAYSTACK strings_strstr
#define NEEDLE needle_strstr
#define TEST_SIZE 31  // 1-30

char HAYSTACK[][256] = {
    "These are the GNU core utilities.  This package is the union of",
    "the GNU fileutils, sh-utils, and textutils packages.",
    "",
    "Most of these programs have significant advantages over their Unix",
    "arbitrary limits.",
    "",
    "The programs that can be built with this package are:",
    "",
    "  [ arch b2sum base32 base64 basename basenc cat chcon chgrp chmod chown",
    "  chroot cksum comm coreutils cp csplit cut date dd df dir dircolors "
    "dirname",
    "  du echo env expand expr factor false fmt fold groups head hostid "
    "hostname",
    "  id install join kill link ln logname ls md5sum mkdir mkfifo mknod "
    "mktemp",
    "  mv nice nl nohup nproc numfmt od paste pathchk pinky pr printenv printf "
    "ptx",
    "  pwd readlink realpath rm rmdir runcon seq sha1sum sha224sum sha256sum",
    "  sha384sum sha512sum shred shuf sleep sort split stat stdbuf stty sum "
    "sync",
    "  tac tail tee test timeout touch tr true truncate tsort tty uname "
    "unexpand",
    "  uniq unlink uptime users vdir wc who whoami yes",
    "",
    "See the file NEWS for a list of major changes in the current release.",
    "",
    "If you obtained this file as part of a \"git clone\", then see the",
    "README-hacking file.  If this file came to you as part of a tar archive,",
    "then see the file INSTALL for general compilation and installation",
    "instructions, or README-install for system and coreutils specific "
    "instructions.",
    " part of",
    "Like the rest of the GNU system, these programs mostly conform to",
    "POSIX, with BSD and other extensions.  For closer conformance, or",
    "conformance to a particular POSIX version, set the POSIXLY_CORRECT",
    "and the _POSIX2_VERSION environment variables, as described in",
    "the documentation under \"Standards conformance\"."};

char NEEDLE[][20] = {"part of", ".", " ", "a", "README-hacking file.", ""};

START_TEST(test) {
  char *actual_result;
  char *expected_result;
  for (int i = 0; i < 6; i++) {
    actual_result = ACTUAL(HAYSTACK[_i], NEEDLE[i]);
    expected_result = EXPECTED(HAYSTACK[_i], NEEDLE[i]);

    // printf("\n str1:%s | str2:%s | res_exp:%s | res_act:%s \n", HAYSTACK[_i],
    // NEEDLE[i], expected_result, actual_result);     //  print for debug

    ck_assert_pstr_eq(actual_result, expected_result);
  }
}
END_TEST

Suite SUITE_NAME {
  Suite *suite = suite_create(SUITE_LABEL);

  TCase *tcase = tcase_create("case");
  tcase_add_loop_test(tcase, test, 0, TEST_SIZE);
  suite_add_tcase(suite, tcase);

  return suite;
}
