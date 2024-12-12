#ifndef NOVELLAIMAGE_H
#define NOVELLAIMAGE_H

#include <QWidget>
#include <QLabel>
#include <QPainter>


/*
 * Перечисление типов выравнивания изображения
 */
enum EAlignment
{
    Center,
    LeftBottom,
    RightBottom
};



/*
 * Класс изображения.
 * Наследование от QWidget необходимо для использования события отрисовки QWidget::paintEvent()
 * Основные возможности:
 * - Чтение изображения из файла;
 * - Отрисовка изображения в качестве виджета.
 */
class NovellaImage : public QWidget
{
private:
    /*
     * _pixmap - переменная для хранения изображения.
     * _alignment - переменная для хранения типа выравнивания изображения.
     */
    QPixmap _pixmap;
    EAlignment _alignment;

public:
    /*
     * Конструктор класса.
     * Аргумент 1: imagePath - полное имя файла с изображением (включая путь к файлу);
     * Аргумент 2: alignment - тип выравнивания изображения;
     * Аргумент 3: parent - родительский виджет для NovellaImage (необходимо, так как класс наследуется от QWidget).
     */
    NovellaImage(QString imagePath, EAlignment alignment = EAlignment::Center, QWidget *parent = nullptr);

    /*
     * Метод-сеттер для переменной _alignment.
     */
    void setAlignment(EAlignment alignment);

protected:
    /*
     * Метод, реализующий отрисовку изображения
     */
    void paintEvent(QPaintEvent *event);
};

#endif // NOVELLAIMAGE_H
