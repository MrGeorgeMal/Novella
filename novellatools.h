#pragma once
#ifndef NOVELLATOOLS_H
#define NOVELLATOOLS_H

#include <QLayout>
#include <QWidget>
#include <QString>
#include <QFile>
#include <QDebug>


/*
 * Статический класс, реализующий инструменты (статические методы) для удобства работы
 */
static class NovellaTools
{
public:
    /*
     * Статический метод чтения текста из файла.
     * Возвращает строку.
     * Аргумент 1: fileName - полное название файла (включая путь к нему)
    */
    static QString GetTextFromFile(QString fileName);

    /*
     * Статический метод очищения контейнера от содержимого (также очищаются все контейнеры внутри передаваемого контейнера).
     * Аргумент 1: layout - контейнер, который должен быть очищен
    */
    static void ClearLayout(QLayout *layout);

} novellatools;

#endif // NOVELLATOOLS_H
