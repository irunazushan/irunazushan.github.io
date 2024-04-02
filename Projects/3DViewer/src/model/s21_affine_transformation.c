#include "s21_affine_transformation.h"

void MoveX(ObjModel *object, const double value) {
  for (size_t i = 0; i < object->num_vertices; ++i) {
    object->vertices[i].x += value;
  }
}

void MoveY(ObjModel *object, const double value) {
  for (size_t i = 0; i < object->num_vertices; ++i) {
    object->vertices[i].y += value;
  }
}

void MoveZ(ObjModel *object, const double value) {
  for (size_t i = 0; i < object->num_vertices; ++i) {
    object->vertices[i].z += value;
  }
}

void RotateX(ObjModel *object, const double angle) {
  double radians = angle * CONST_PI / 180.0;
  for (size_t i = 0; i < object->num_vertices; ++i) {
    double y = object->vertices[i].y;
    double z = object->vertices[i].z;
    object->vertices[i].y = y * cos(radians) - z * sin(radians);
    object->vertices[i].z = y * sin(radians) + z * cos(radians);
  }
}

void RotateY(ObjModel *object, const double angle) {
  double radians = angle * CONST_PI / 180.0;
  for (size_t i = 0; i < object->num_vertices; ++i) {
    double x = object->vertices[i].x;
    double z = object->vertices[i].z;
    object->vertices[i].x = x * cos(radians) + z * sin(radians);
    object->vertices[i].z = -x * sin(radians) + z * cos(radians);
  }
}

void RotateZ(ObjModel *object, const double angle) {
  double radians = angle * CONST_PI / 180.0;
  for (size_t i = 0; i < object->num_vertices; ++i) {
    double x = object->vertices[i].x;
    double y = object->vertices[i].y;
    object->vertices[i].x = x * cos(radians) - y * sin(radians);
    object->vertices[i].y = x * sin(radians) + y * cos(radians);
  }
}

void Scale(double scale_matrix[4][4], const double scale) {
  scale_matrix[0][0] = scale;
  scale_matrix[1][1] = scale;
  scale_matrix[2][2] = scale;
}

void ResetMatrix(double matrix[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j) {
        matrix[i][j] = 1;
      } else {
        matrix[i][j] = 0;
      }
    }
  }
}

void ApplyTransformation(Vertex *v, double m[4][4]) {
  double temp_vector[4] = {0};
  temp_vector[0] = v->x;
  temp_vector[1] = v->y;
  temp_vector[2] = v->z;
  temp_vector[3] = 1;
  v->x = m[0][0] * temp_vector[0] + m[0][1] * temp_vector[1] +
         m[0][2] * temp_vector[2] + m[0][3] * temp_vector[3];
  v->y = m[1][0] * temp_vector[0] + m[1][1] * temp_vector[1] +
         m[1][2] * temp_vector[2] + m[1][3] * temp_vector[3];
  v->z = m[2][0] * temp_vector[0] + m[2][1] * temp_vector[1] +
         m[2][2] * temp_vector[2] + m[2][3] * temp_vector[3];
}

void SetOffset(double offset_matrix[4][4], const double x, const double y,
               const double z) {
  ResetMatrix(offset_matrix);
  offset_matrix[0][3] = x;
  offset_matrix[1][3] = y;
  offset_matrix[2][3] = z;
}
