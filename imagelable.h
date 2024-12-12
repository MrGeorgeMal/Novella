#ifndef IMAGELABLE_H
#define IMAGELABLE_H

class ImageLabel : public QWidget
{
    Q_OBJECT

public:
    explicit ImageLabel(QWidget *parent = 0);
    const QPixmap* pixmap() const;

public slots:
    void setPixmap(const QPixmap&);

protected:
    void resizeEvent(QResizeEvent *);

private slots:
    void resizeImage();

private:
    QLabel *label;
};

#endif // IMAGELABLE_H
