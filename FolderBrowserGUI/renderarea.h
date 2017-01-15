
#ifndef RENDER_AREA_H
#define RENDER_AREA_H

#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QPixmap>

#include <foldertree.h>

class RenderArea : public QWidget
{
    Q_OBJECT

public:

    RenderArea(QWidget *parent = 0);

    QColor randColor(uint seed = 1);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

public slots:
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event); 
    void onTreeBuilt(fb::FolderTree* folder_tree);

private:

    void drawFolderTree(QPainter& painter, const fb::Folder* root, double start_angle, double end_angle, int level = 1);
    void drawSegment(QPainter& painter, double start_angle, double end_angle, double radius, double length);

    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    QPixmap pixmap;
    double scale;
    int last_x;
    int last_y;
    int diff_x;
    int diff_y;
    int last_diff_x;
    int last_diff_y;

    const fb::Folder* folder_root;
    int level_radius;
};

#endif
