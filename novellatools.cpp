#include "novellatools.h"

QString NovellaTools::GetTextFromFile(QString fileName)
{
    // Получение ссылки на файл и его открытие
    // Вывод ошибки если открытие не удалось
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen())
    {
        qDebug() << "NovellaDialogBox::GetStyleStringFromFile::The file" << file.fileName() << " could not be opened";
    }

    // Чтение содержимого файла и запись в строковую переменную
    QString text = file.readAll();

    //Закрытие файла и возвращение прочитанного текста
    file.close();
    return text;
}



void NovellaTools::ClearLayout(QLayout *layout)
{
    // Завершение работы метода если переданный в метод указатель на контейнер не существует
    if (layout == nullptr) return;

    // Создание переменной для хранения текущего элемента из контейнера
    QLayoutItem *item;

    // Перебор всех элементов контейнера
    while((item = layout->takeAt(0))) {

        // Если текущий элемент является другим контейнером (вложенным), производится его очистка с помощью текущего метода ClearLayout
        if (item->layout()) {
            ClearLayout(item->layout());
        }

        // Если текущий элемент является виджетом, производится его удаление (удаление виджета)
        if (item->widget()) {
            delete item->widget();
        }

        // После удаления виджета удаляется также и элемент из контейнера
        delete item;
    }
}
