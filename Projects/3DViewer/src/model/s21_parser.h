#ifndef C8_3DVIEWER_V1_SRC_MODEL_S21_PARSER_H_
#define C8_3DVIEWER_V1_SRC_MODEL_S21_PARSER_H_

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_NO_ERROR 0
#define S21_ERROR 1

typedef struct {
  double x;
  double y;
  double z;
} Vertex;

typedef struct {
  Vertex *vertices;
  size_t num_vertices;

  int *edges;
  size_t num_edges;
} ObjModel;

void AddVertex(ObjModel *model, Vertex vertex);
void AddEdge(ObjModel *model, int v1, int v2);
void FreeModel(ObjModel *model);
void InitializeModel(ObjModel *model);
int HandleFileToObjModel(const char *filename, ObjModel *model);

#endif  // C8_3DVIEWER_V1_SRC_MODEL_S21_PARSER_H_
