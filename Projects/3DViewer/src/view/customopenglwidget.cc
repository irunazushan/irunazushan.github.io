#include "customopenglwidget.h"

CustomOpenGLWidget::CustomOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent) {
  InitializeModel(&object);
}

CustomOpenGLWidget::~CustomOpenGLWidget() {}

void CustomOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void CustomOpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }
void CustomOpenGLWidget::resizeEvent(QResizeEvent *event) {
  QOpenGLWidget::resizeEvent(event);
}

void CustomOpenGLWidget::resetTransformationValues() {
  object_scale_ = 100;
  object_translate_ = {0, 0, 0};
  object_rotation_ = {0, 0, 0};
  max_vertex_ = 0;
}

void CustomOpenGLWidget::setObjectScale(const double &value) {
  object_scale_ = value;
}

void CustomOpenGLWidget::setObjectTranslateX(const double &value) {
  object_translate_.x = value;
}

void CustomOpenGLWidget::setObjectTranslateY(const double &value) {
  object_translate_.y = value;
}

void CustomOpenGLWidget::setObjectTranslateZ(const double &value) {
  object_translate_.z = value;
}

void CustomOpenGLWidget::setObjectRotationX(const double &value) {
  object_rotation_.x = value;
}

void CustomOpenGLWidget::setObjectRotationY(const double &value) {
  object_rotation_.y = value;
}

void CustomOpenGLWidget::setObjectRotationZ(const double &value) {
  object_rotation_.z = value;
}

void CustomOpenGLWidget::setVertexColor(const float &red, const float &green,
                                        const float &blue) {
  vertex_color_.red = red;
  vertex_color_.green = green;
  vertex_color_.blue = blue;
}

void CustomOpenGLWidget::setEdgeColor(const float &red, const float &green,
                                      const float &blue) {
  edge_color_.red = red;
  edge_color_.green = green;
  edge_color_.blue = blue;
}

void CustomOpenGLWidget::setBackgroundColor(const float &red,
                                            const float &green,
                                            const float &blue) {
  background_color_.red = red;
  background_color_.green = green;
  background_color_.blue = blue;
}

void CustomOpenGLWidget::setEdgesType(const int &value) { edges_type_ = value; }

void CustomOpenGLWidget::setEdgesThickness(const int &value) {
  edges_thickness_ = value;
}

void CustomOpenGLWidget::setVerticesSize(const int &value) {
  vertices_size_ = value;
}

void CustomOpenGLWidget::setVertexDisplayType(const int &value) {
  vertex_display_type_ = value;
}

void CustomOpenGLWidget::setProjectionType(const int &value) {
  projection_type_ = value;
}

Color CustomOpenGLWidget::getVertexColor() { return vertex_color_; }

Color CustomOpenGLWidget::getEdgeColor() { return edge_color_; }

Color CustomOpenGLWidget::getBackgroundColor() { return background_color_; }

int CustomOpenGLWidget::getVerticesSize() { return vertices_size_; }

int CustomOpenGLWidget::getEdgesThickness() { return edges_thickness_; }

int CustomOpenGLWidget::getProjectionType() { return projection_type_; }

int CustomOpenGLWidget::getVertexDisplayType() { return vertex_display_type_; }

int CustomOpenGLWidget::getEdgesType() { return edges_type_; }

double CustomOpenGLWidget::getObjectScale() { return object_scale_; }

Vertex CustomOpenGLWidget::getObjectTranslate() { return object_translate_; }

Vertex CustomOpenGLWidget::getObjectRotation() { return object_rotation_; }

void CustomOpenGLWidget::mousePressEvent(QMouseEvent *event) {
  last_mouse_position_ = event->pos();
}

void CustomOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
  int dx = event->position().x() - last_mouse_position_.x();
  int dy = event->position().y() - last_mouse_position_.y();

  if (event->buttons() & Qt::LeftButton) {
    x_camera_rotation_ += dy;
    y_camera_rotation_ += dx;
  }

  last_mouse_position_ = event->pos();
  update();
}

void CustomOpenGLWidget::paintGL() {
  glClearColor(background_color_.red, background_color_.green,
               background_color_.blue, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glVertexPointer(3, GL_DOUBLE, 0, object.vertices);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (max_vertex_ == 0) {
    max_vertex_ = getMaxVertex();
  }

  if (projection_type_ == 0) {
    glFrustum(-max_vertex_, max_vertex_, -max_vertex_, max_vertex_, max_vertex_,
              max_vertex_ * 1000.0f);
    glTranslatef(0.0f, 0.0f, -2 * max_vertex_);
    glRotatef(x_camera_rotation_, 1.0f, 0.0f, 0.0f);
    glRotatef(y_camera_rotation_, 0.0f, 1.0f, 0.0f);
  } else {
    glOrtho(-max_vertex_, max_vertex_, -max_vertex_, max_vertex_, -max_vertex_,
            1000.0f * max_vertex_);
    glTranslatef(0.0f, -max_vertex_ / 2, 0.0f);
  }

  glEnableClientState(GL_VERTEX_ARRAY);

  if (vertex_display_type_ != 0) {
    paintVertex();
  }
  paintEdges();

  glDisableClientState(GL_VERTEX_ARRAY);
}

float CustomOpenGLWidget::getMaxVertex() {
  float max_vertex = 0.0f;
  for (size_t i = 0; i < object.num_vertices; ++i) {
    max_vertex =
        std::max(max_vertex, static_cast<float>(fabs(object.vertices[i].x)));
    max_vertex =
        std::max(max_vertex, static_cast<float>(fabs(object.vertices[i].y)));
    max_vertex =
        std::max(max_vertex, static_cast<float>(fabs(object.vertices[i].z)));
  }
  return max_vertex;
}

void CustomOpenGLWidget::paintVertex() {
  if (vertex_display_type_ == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(vertices_size_);
  glColor3f(vertex_color_.red, vertex_color_.green, vertex_color_.blue);
  glDrawArrays(GL_POINTS, 0, object.num_vertices);
  if (vertex_display_type_ == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void CustomOpenGLWidget::paintEdges() {
  glLineWidth(edges_thickness_);
  glColor3f(edge_color_.red, edge_color_.green, edge_color_.blue);
  if (edges_type_ == 0) {
    paintSolidEdges();
  } else {
    paintDashedEdges();
  }
}

void CustomOpenGLWidget::paintSolidEdges() {
  glBegin(GL_LINES);
  for (size_t i = 0; i < object.num_edges; i += 2) {
    int index1 = object.edges[i];
    int index2 = object.edges[i + 1];

    Vertex vertex1 = object.vertices[index1];
    Vertex vertex2 = object.vertices[index2];
    glVertex3d(vertex1.x, vertex1.y, vertex1.z);
    glVertex3d(vertex2.x, vertex2.y, vertex2.z);
  }
  glEnd();
}

void CustomOpenGLWidget::paintDashedEdges() {
  const float kDashLength = 0.1f;
  const float kGapLength = 0.1f;

  glBegin(GL_LINES);
  for (size_t i = 0; i < object.num_edges; i += 2) {
    int index1 = object.edges[i];
    int index2 = object.edges[i + 1];

    Vertex v1 = object.vertices[index1];
    Vertex v2 = object.vertices[index2];

    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    float dz = v2.z - v1.z;
    float length = sqrtf(dx * dx + dy * dy + dz * dz);
    dx /= length;
    dy /= length;
    dz /= length;

    float currentLength = 0.0f;
    while (currentLength < length) {
      float nextDashEnd = currentLength + kDashLength;
      if (nextDashEnd > length) nextDashEnd = length;

      glVertex3d(v1.x + dx * currentLength, v1.y + dy * currentLength,
                 v1.z + dz * currentLength);
      glVertex3d(v1.x + dx * nextDashEnd, v1.y + dy * nextDashEnd,
                 v1.z + dz * nextDashEnd);

      currentLength = nextDashEnd + kGapLength;
    }
  }
  glEnd();
}
