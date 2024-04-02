#ifndef C8_3DVIEWER_V1_SRC_MODEL_S21_AFFINE_TRANSFORMATION_H_
#define C8_3DVIEWER_V1_SRC_MODEL_S21_AFFINE_TRANSFORMATION_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_parser.h"

#define CONST_PI 3.14159265358979323846

void MoveX(ObjModel *object, const double value);
void MoveY(ObjModel *object, const double value);
void MoveZ(ObjModel *object, const double value);

void RotateX(ObjModel *object, const double angle);
void RotateY(ObjModel *object, const double angle);
void RotateZ(ObjModel *object, const double angle);

void Scale(double scale_matrix[4][4], const double scale);

void ApplyTransformation(Vertex *v, double m[4][4]);
void SetOffset(double offset_matrix[4][4], const double x, const double y,
               const double z);
void ResetMatrix(double matrix[4][4]);

#endif  // C8_3DVIEWER_V1_SRC_MODEL_S21_AFFINE_TRANSFORMATION_H_
