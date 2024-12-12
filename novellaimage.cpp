#include "novellaimage.h"

NovellaImage::NovellaImage(QString imagePath, EAlignment alignment, QWidget *parent): QWidget(parent)
{
    // Начальная настройка объекта при его создании
    setAlignment(alignment);
    _pixmap = QPixmap(imagePath);
    update();
}

void NovellaImage::setAlignment(EAlignment alignment)
{
    _alignment = alignment;
}

void NovellaImage::paintEvent(QPaintEvent *event)
{
    // Создание переменной для отрисовки изображения, хранящегося в _pixmap.
    // Необходимо так как изоражение может изменяться в размере, в зависимости от размера окна
    // Таким образом, painter отвечает за перерисовку изображения при изменении размера окна
    QPainter painter(this);

    // Если в _pixmap содержится изображение, то определяется место его отрисовки, которое зависит от выравнивания _alignment
    if (false == _pixmap.isNull())
    {
        QSize widgetSize = size();
        QPixmap scaledPixmap = _pixmap.scaled(widgetSize, Qt::KeepAspectRatio);
        int widthAlign = 0;
        int heightAlign = 0;

        switch (_alignment)
        {
        case EAlignment::Center:
            widthAlign = (widgetSize.width() - scaledPixmap.width()) / 2;
            heightAlign = (widgetSize.height() - scaledPixmap.height()) / 2;
            break;

        case EAlignment::LeftBottom:
            widthAlign = 0;
            heightAlign = (widgetSize.height() - scaledPixmap.height());
            break;

        case EAlignment::RightBottom:
            widthAlign = (widgetSize.width() - scaledPixmap.width());
            heightAlign = (widgetSize.height() - scaledPixmap.height());
            break;
        }

        QPoint placePoint(widthAlign, heightAlign);
        painter.drawPixmap(placePoint, scaledPixmap);
    }

    // Вызов события отрисовки. Отрисовываться будет то изображение, которое помещено в painter
    QWidget::paintEvent(event);
}
