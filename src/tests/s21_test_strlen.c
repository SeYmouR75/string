#include "s21_test_string.h"

#define ACTUAL(x) s21_strlen(x)
#define EXPECTED(x) strlen(x)
#define SUITE_LABEL "suite_s21_strlen"
#define SUITE_NAME *suite_s21_strlen()
#define STRINGS strings_strlen
#define TEST_SIZE 31  // 1-31

char STRINGS[][256] = {
    "These are the GNU core utilities.  This package is the union of",
    "the GNU fileutils, sh-utils, and textutils packages.",
    "\0",
    "12345\0",
    "counterparts, such as greater speed, additional options, and fewer",
    "arbitrary limits.",
    "",
    "The programs that can be built with this package are:",
    "   ",
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
    "     ",
    "See the file NEWS for a list of major changes in the current release.",
    ";;;;;;;;;;;;;;",
    "If you obtained this file as part of a \"git clone\", then see the",
    "README-hacking file.  If this file came to you as part of a tar archive,",
    "1234567890",
    "instructions, or README-install for system and coreutils specific "
    "instructions.",
    "QQQQQQQQQQQ",
    "Like the rest of the GNU system, these programs mostly conform to",
    "POSIX, with BSD and other extensions.  For closer conformance, or",
    "conformance to a particular POSIX version, set the POSIXLY_CORRECT",
    "and the _POSIX2_VERSION environment variables, as described in",
    "the documentation under \"Standards conformance\"."};

START_TEST(test) {
  char *ch = STRINGS[_i];
  ck_assert_uint_eq(ACTUAL(ch), EXPECTED(ch));
}
END_TEST

Suite SUITE_NAME {
  Suite *suite = suite_create(SUITE_LABEL);

  TCase *tcase = tcase_create("case");
  tcase_add_loop_test(tcase, test, 0, TEST_SIZE);
  suite_add_tcase(suite, tcase);

  return suite;
}
