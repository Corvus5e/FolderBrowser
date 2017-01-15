#include <renderarea.h>
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>
#include <QPen>
#include <QTime>
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

void RenderArea::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //painter.setBrush(brush);    
    QPen pen(Qt::black);
    pen.setWidth(0.1);
    painter.setPen(pen);
    painter.save();
    painter.scale(scale, scale);
    painter.translate(painter.window().width()/2 + diff_x, painter.window().height()/2 + diff_y);
    drawFolderTree(painter, this->folder_root, 0, 6.28);
    painter.restore();
}

void RenderArea::drawFolderTree(QPainter& painter, const fb::Folder* root, double start_angle, double end_angle, int level){
    if(root != nullptr){
        double offset = start_angle;
        painter.setBrush(this->randColor(level * end_angle  * QTime::currentTime().msec()));
        if(level == 1){
            painter.drawEllipse(QPoint(0,0), level_radius - 2, level_radius - 2);
        }
        else{
            this->drawSegment(painter, start_angle, end_angle, level*level_radius, level_radius);
        }
        for(auto it = root->cnodes().cbegin(); it != root->cnodes().cend(); ++it){
            if(root->size() > 0 && (*it)->size() > 0){
                double angle_range = (*it)->size() * (end_angle - start_angle)/root->size();
                drawFolderTree(painter, *it, offset, offset + angle_range, level + 1);
                offset += angle_range;
            }
        }
    }
}

void RenderArea::drawSegment(QPainter& painter, double start_angle, double end_angle, double radius, double length){
    double s_angle = start_angle * 180.0/3.1415;
    double e_angle = end_angle * 180.0/3.1415;    
    QPainterPath path;
    QPainterPath hpath;

    double outer_radius = radius + length;
    path.arcMoveTo(QRect(-radius/2, -radius/2, radius, radius), s_angle);
    path.arcTo(QRect(-radius/2, -radius/2, radius, radius), s_angle, e_angle-s_angle);
    hpath.arcMoveTo(QRect(-outer_radius/2, -outer_radius/2, outer_radius, outer_radius), e_angle);
    path.lineTo(hpath.currentPosition());
    path.arcTo(QRect(-outer_radius/2, -outer_radius/2, outer_radius, outer_radius), e_angle, -(e_angle-s_angle));
    hpath.arcMoveTo(QRect(-radius/2, -radius/2, radius, radius), s_angle);
    path.lineTo(hpath.currentPosition());
    path.closeSubpath();
    painter.drawPath(path);
}

void RenderArea::onTreeBuilt(fb::FolderTree *folder_tree){
    this->folder_root = folder_tree->getRootFolder();
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
    int r = qrand() % 255;
    int g = qrand() % 255;
    int b = qrand() % 255;
    return QColor(r, g, b);
}
