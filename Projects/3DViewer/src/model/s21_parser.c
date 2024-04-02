#include "s21_parser.h"

void InitializeModel(ObjModel *model) {
  model->vertices = NULL;
  model->num_vertices = 0;
  model->edges = NULL;
  model->num_edges = 0;
}

void FreeModel(ObjModel *model) {
  if (model->vertices != NULL) {
    free(model->vertices);
    model->vertices = NULL;
  }
  if (model->edges != NULL) {
    free(model->edges);
    model->edges = NULL;
  }
  model->num_vertices = 0;
  model->num_edges = 0;
}

void AddVertex(ObjModel *model, Vertex vertex) {
  model->vertices = (Vertex *)realloc(
      model->vertices, (model->num_vertices + 1) * sizeof(Vertex));
  model->vertices[model->num_vertices++] = vertex;
}

void AddEdge(ObjModel *model, int v1, int v2) {
  model->edges =
      (int *)realloc(model->edges, (model->num_edges + 2) * sizeof(int));
  model->edges[model->num_edges++] = v1;
  model->edges[model->num_edges++] = v2;
}

int HandleFileToObjModel(const char *filename, ObjModel *model) {
  setlocale(LC_NUMERIC, "C");
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return S21_ERROR;
  }

  InitializeModel(model);

  char line[128];
  while (fgets(line, sizeof(line), file)) {
    if (strncmp(line, "v ", 2) == 0) {
      Vertex vertex;
      sscanf(line, "v %lf %lf %lf", &vertex.x, &vertex.y, &vertex.z);
      AddVertex(model, vertex);
    } else if (strncmp(line, "f ", 2) == 0) {
      int vertex_indices[4];
      char *token = strtok(line + 2, " ");
      int index = 0;
      while (token != NULL && index < 4) {
        int vertexIndex;
        sscanf(token, "%d", &vertexIndex);
        if (vertexIndex < 0) {
          vertexIndex = model->num_vertices + vertexIndex + 1;
        }
        vertex_indices[index++] =
            vertexIndex - 1;  // Adjust for 0-based indexing
        token = strtok(NULL, " ");
      }
      for (int i = 1; i < index - 1; i++) {
        AddEdge(model, vertex_indices[0], vertex_indices[i]);
        AddEdge(model, vertex_indices[i], vertex_indices[i + 1]);
      }
    }
  }

  fclose(file);
  return S21_NO_ERROR;
}
