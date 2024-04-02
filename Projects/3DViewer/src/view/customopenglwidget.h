#ifndef CUSTOMOPENGLWIDGET_H
#define CUSTOMOPENGLWIDGET_H

extern "C" {
#include <s21_parser.h>
}

#include <QKeyEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <cmath>

struct Color {
  float red, green, blue;
};

class CustomOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  CustomOpenGLWidget(QWidget *parent = nullptr);
  ~CustomOpenGLWidget();

 public:
  ObjModel object;

 public:
  void resetTransformationValues();

  void setEdgesType(const int &value);
  void setEdgesThickness(const int &value);
  void setVerticesSize(const int &value);
  void setVertexDisplayType(const int &value);
  void setProjectionType(const int &value);
  void setVertexColor(const float &red, const float &green, const float &blue);
  void setEdgeColor(const float &red, const float &green, const float &blue);
  void setBackgroundColor(const float &red, const float &green,
                          const float &blue);
  void setObjectScale(const double &value);
  void setObjectTranslateX(const double &value);
  void setObjectTranslateY(const double &value);
  void setObjectTranslateZ(const double &value);
  void setObjectRotationX(const double &value);
  void setObjectRotationY(const double &value);
  void setObjectRotationZ(const double &value);

  Color getVertexColor();
  Color getEdgeColor();
  Color getBackgroundColor();
  float getMaxVertex();
  int getVerticesSize();
  int getEdgesThickness();
  int getProjectionType();
  int getVertexDisplayType();
  int getEdgesType();
  double getObjectScale();
  Vertex getObjectTranslate();
  Vertex getObjectRotation();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void paintGL() override;

  void resizeEvent(QResizeEvent *event) override;
  void onResized();

 private:
  void paintVertex();
  void paintEdges();
  void paintSolidEdges();
  void paintDashedEdges();

 private:
  QPoint last_mouse_position_;
  Color vertex_color_{0.0f, 0.0f, 0.0f};
  Color edge_color_{0.0f, 0.0f, 0.0f};
  Color background_color_{0.702f, 0.729f, 0.718f};

  int vertices_size_ = 1;        // размер вершин
  int edges_thickness_ = 1;      // толщина граней
  int projection_type_ = 1;      // 0 - perspective | 1 - orthographic
  int vertex_display_type_ = 0;  // 0 - none | 1 - circle | 2 - square
  int edges_type_ = 0;           // 0 - solid | 1 - dashed

  GLfloat x_camera_rotation_ = 30;
  GLfloat y_camera_rotation_ = 0;

  double object_scale_ = 100;
  Vertex object_translate_;
  Vertex object_rotation_;

  GLfloat max_vertex_ = 0;
};

#endif  // CUSTOMOPENGLWIDGET_H
