#include <check.h>

#include "../model/s21_affine_transformation.h"
#include "../model/s21_parser.h"

#define TOL 1e-1

START_TEST(s21_3d_viewer_test_1) {
  Vertex v = {10, 10, 10};
  ObjModel object = {&v, 1, NULL, 0};
  RotateZ(&object, 180);
  ck_assert_double_eq_tol(v.x, -10, TOL);
  ck_assert_double_eq_tol(v.y, -10, TOL);
  ck_assert_double_eq_tol(v.z, 10, TOL);
}
END_TEST

START_TEST(s21_3d_viewer_test_2) {
  Vertex v = {10, 10, 10};
  ObjModel object = {&v, 1, NULL, 0};
  RotateX(&object, 180);
  ck_assert_double_eq_tol(v.x, 10, TOL);
  ck_assert_double_eq_tol(v.y, -10, TOL);
  ck_assert_double_eq_tol(v.z, -10, TOL);
}
END_TEST

START_TEST(s21_3d_viewer_test_3) {
  Vertex v = {10, 10, 10};
  ObjModel object = {&v, 1, NULL, 0};
  RotateY(&object, 180);
  ck_assert_double_eq_tol(v.x, -10, TOL);
  ck_assert_double_eq_tol(v.y, 10, TOL);
  ck_assert_double_eq_tol(v.z, -10, TOL);
}
END_TEST

START_TEST(s21_3d_viewer_test_4) {
  Vertex v = {10, 10, 10};
  double scale[4][4] = {0};
  Scale(scale, 0.5);
  ApplyTransformation(&v, scale);
  ck_assert_double_eq_tol(v.x, 5, TOL);
  ck_assert_double_eq_tol(v.y, 5, TOL);
  ck_assert_double_eq_tol(v.z, 5, TOL);
}
END_TEST

START_TEST(s21_3d_viewer_test_5) {
  Vertex v = {10, 5, 100};
  double scale[4][4] = {0};
  Scale(scale, 20.4);
  ApplyTransformation(&v, scale);
  ck_assert_double_eq_tol(v.x, 204, TOL);
  ck_assert_double_eq_tol(v.y, 102, TOL);
  ck_assert_double_eq_tol(v.z, 2040, TOL);
}
END_TEST

START_TEST(s21_3d_viewer_test_6) {
  Vertex v = {10, 5, 100};
  double offsetMx[4][4] = {0};
  double x = 20, y = 30, z = 40;
  SetOffset(offsetMx, x, y, z);
  ApplyTransformation(&v, offsetMx);
  ck_assert_double_eq_tol(v.x, 10 + x, TOL);
  ck_assert_double_eq_tol(v.y, 5 + y, TOL);
  ck_assert_double_eq_tol(v.z, 100 + z, TOL);
}
END_TEST

START_TEST(s21_3d_viewer_test_7) {
  double matrix[4][4] = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  ResetMatrix(matrix);
  ck_assert_double_eq_tol(matrix[0][0], 1, TOL);
  ck_assert_double_eq_tol(matrix[0][1], 0, TOL);
  ck_assert_double_eq_tol(matrix[0][2], 0, TOL);
  ck_assert_double_eq_tol(matrix[0][3], 0, TOL);

  ck_assert_double_eq_tol(matrix[1][0], 0, TOL);
  ck_assert_double_eq_tol(matrix[1][1], 1, TOL);
  ck_assert_double_eq_tol(matrix[1][2], 0, TOL);
  ck_assert_double_eq_tol(matrix[1][3], 0, TOL);

  ck_assert_double_eq_tol(matrix[2][0], 0, TOL);
  ck_assert_double_eq_tol(matrix[2][1], 0, TOL);
  ck_assert_double_eq_tol(matrix[2][2], 1, TOL);
  ck_assert_double_eq_tol(matrix[2][3], 0, TOL);

  ck_assert_double_eq_tol(matrix[3][0], 0, TOL);
  ck_assert_double_eq_tol(matrix[3][1], 0, TOL);
  ck_assert_double_eq_tol(matrix[3][2], 0, TOL);
  ck_assert_double_eq_tol(matrix[3][3], 1, TOL);
}
END_TEST

START_TEST(s21_3d_viewer_test_8) {
  Vertex vertices[] = {{10, 5, 100}};
  ObjModel object = {vertices, 1, NULL, 0};

  double value = 20;

  MoveX(&object, value);
  ck_assert_double_eq_tol(object.vertices[0].x, 10 + value, TOL);
  ck_assert_double_eq_tol(object.vertices[0].y, 5, TOL);
  ck_assert_double_eq_tol(object.vertices[0].z, 100, TOL);
}
END_TEST

START_TEST(s21_3d_viewer_test_9) {
  Vertex vertices[] = {{10, 5, 100}};
  ObjModel object = {vertices, 1, NULL, 0};

  double value = 20;

  MoveY(&object, value);
  ck_assert_double_eq_tol(object.vertices[0].x, 10, TOL);
  ck_assert_double_eq_tol(object.vertices[0].y, 5 + value, TOL);
  ck_assert_double_eq_tol(object.vertices[0].z, 100, TOL);
}
END_TEST

START_TEST(s21_3d_viewer_test_10) {
  Vertex vertices[] = {{10, 5, 100}};
  ObjModel object = {vertices, 1, NULL, 0};

  double value = 20;

  MoveZ(&object, value);
  ck_assert_double_eq_tol(object.vertices[0].x, 10, TOL);
  ck_assert_double_eq_tol(object.vertices[0].y, 5, TOL);
  ck_assert_double_eq_tol(object.vertices[0].z, 100 + value, TOL);
}
END_TEST

START_TEST(s21_3d_viewer_test_11) {
  ObjModel model;
  int result = HandleFileToObjModel("objects/cube.obj", &model);
  ck_assert_int_eq(result, S21_NO_ERROR);
  ck_assert_int_eq(model.num_vertices, 8);
  FreeModel(&model);
}
END_TEST

START_TEST(s21_3d_viewer_test_12) {
  ObjModel model;
  int result = HandleFileToObjModel("objects/noname.obj", &model);
  ck_assert_int_eq(result, S21_ERROR);
}
END_TEST

START_TEST(s21_3d_viewer_test_13) {
  ObjModel model;
  int result;
  const char *expectedFilename = "sword.obj";
  result = HandleFileToObjModel("objects/sword.obj", &model);
  ck_assert_int_eq(result, S21_NO_ERROR);
  const char *path = "objects/sword.obj";
  const char *filename = strrchr(path, '/');
  if (filename) {
    filename++;
  }
  ck_assert_str_eq(filename, expectedFilename);
  FreeModel(&model);
}
END_TEST

/* EXECUTION */

Suite *s21_main_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("3D_VIEWER SUITE");
  tc_core = tcase_create("3D_VIEWER CORE");

  tcase_add_test(tc_core, s21_3d_viewer_test_1);   // RotateZ
  tcase_add_test(tc_core, s21_3d_viewer_test_2);   // RotateX
  tcase_add_test(tc_core, s21_3d_viewer_test_3);   // RotateY
  tcase_add_test(tc_core, s21_3d_viewer_test_4);   // Scale
  tcase_add_test(tc_core, s21_3d_viewer_test_5);   // Scale
  tcase_add_test(tc_core, s21_3d_viewer_test_6);   // Offset
  tcase_add_test(tc_core, s21_3d_viewer_test_7);   // Reset
  tcase_add_test(tc_core, s21_3d_viewer_test_8);   // MoveX
  tcase_add_test(tc_core, s21_3d_viewer_test_9);   // MoveY
  tcase_add_test(tc_core, s21_3d_viewer_test_10);  // MoveZ
  tcase_add_test(tc_core, s21_3d_viewer_test_11);  // Parser_success
  tcase_add_test(tc_core, s21_3d_viewer_test_12);  // Parser_failure
  tcase_add_test(tc_core, s21_3d_viewer_test_13);  // Parser_negative_facets

  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_main_test();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
