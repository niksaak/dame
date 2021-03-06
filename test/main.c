#include <stdlib.h>
#include <check.h>

Suite* mk_draw_suite(void);
Suite* mk_entity_suite(void);
Suite* mk_error_suite(void);
Suite* mk_module_suite(void);
Suite* mk_particle_suite(void);

int main(void)
{
  int nf;
  SRunner* r = srunner_create(mk_draw_suite());
  srunner_add_suite(r, mk_particle_suite());
  srunner_add_suite(r, mk_module_suite());
  srunner_add_suite(r, mk_entity_suite());
  srunner_add_suite(r, mk_error_suite());

  srunner_run_all(r, CK_ENV);
  nf = srunner_ntests_failed(r);
  srunner_free(r);

  return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

