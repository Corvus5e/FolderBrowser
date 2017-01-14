#include <renderarea.h>
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>
#include <QPen>
#include <QDebug>


RenderArea::RenderArea(QWidget *parent) :QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    level_radius = 15;
    scale = 1.0;
    diff_x = 0;
    diff_y = 0;
    last_diff_x = 0;
    last_diff_y = 0;
    folder_root = nullptr;
}

void RenderArea::paintEvent(QPaintEvent*){

    QPainter painter(this);
    //painter.setBrush(brush);

    painter.save();
    painter.scale(scale, scale);
    painter.translate(painter.window().width()/2 + diff_x, painter.window().height()/2 + diff_y);
    drawFolderTree(painter, this->folder_root, 0, 6.28);
    painter.restore();
}

void RenderArea::drawFolderTree(QPainter& painter, fb::Folder* root, double start_angle, double end_angle, int level){
    if(root != nullptr){
        double offset = start_angle;
        this->drawCircle(painter, start_angle, end_angle, level*level_radius);
        for(auto it = root->nodes().begin(); it != root->nodes().end(); ++it){
            if(root->size() > 0 && (*it)->size() > 0){
                double angle_range = (*it)->size() * (end_angle - start_angle)/root->size();
                drawFolderTree(painter, *it, offset, offset + angle_range, level + 1);
                offset += angle_range;
            }
        }
    }
}

void RenderArea::drawCircle(QPainter& painter, double start_angle, double end_angle, double radius){
    double s_angle = start_angle * 180.0/3.1415;
    double e_angle = end_angle * 180.0/3.1415;
    double radius_under = (radius - level_radius);
    QPainterPath path;
    QPainterPath path_under;

    painter.setPen(QColor(Qt::black));
    path.arcMoveTo(QRect(-radius/2, -radius/2, radius, radius), s_angle);
    path_under.arcMoveTo(QRect(-radius_under/2, -radius_under/2, radius_under, radius_under), s_angle);
    painter.drawLine(path.currentPosition(), path_under.currentPosition());

    //painter.drawEllipse(path.currentPosition(), 1, 1);

    path.arcTo(QRect(-radius/2, -radius/2, radius, radius), s_angle, e_angle-s_angle);
    path_under.arcTo(QRect(-radius_under/2, -radius_under/2, radius_under, radius_under), s_angle, e_angle-s_angle);
    painter.drawLine(path.currentPosition(), path_under.currentPosition());

    painter.setPen(QColor(Qt::red));
    //painter.drawEllipse(path.currentPosition(), 1, 1);
    painter.drawPath(path);
    path.closeSubpath();
}

void RenderArea::onTreeBuilt(fb::Folder *folder_root){
    this->folder_root = folder_root;
    this->repaint();
}

void RenderArea::wheelEvent(QWheelEvent *event){
    if(event->delta() > 0)
        scale += 0.10;
    else
        scale -= 0.10;
    this->repaint();
}

void RenderArea::mouseMoveEvent(QMouseEvent *event){
    diff_x = last_diff_x + event->x() - last_x;
    diff_y = last_diff_y + event->y() - last_y;
    this->repaint();
}

void RenderArea::mousePressEvent(QMouseEvent *event){
    last_x = event->x();
    last_y = event->y();    
 }

void RenderArea::mouseReleaseEvent(QMouseEvent*){
    last_diff_x = diff_x;
    last_diff_y = diff_y;
}

QColor RenderArea::randColor(uint seed){
    qsrand(seed);
    int r = qrand() % 155;
    int g = qrand() % 155;
    int b = qrand() % 155;
    return QColor(r, g, b);
}
