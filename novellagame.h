#pragma once
#ifndef NOVELLAGAME_H
#define NOVELLAGAME_H

#include "mainwindow.h"
#include "novellascene.h"

#include <QFontDatabase>
#include <QCursor>
#include <QPixmap>


/*
 * Статический класс, реализующий инструменты для работы с игрой
 */
static class NovellaGame
{
public:
    // Полное имя файла базового шрифта
    static QString pathFontBase;
    // Полное имя файла базового курсора
    static QString pathCursorBase;
    // Полное имя файла курсора при наведении на кнопку
    static QString pathCursorButton;
    // Полное имя файла стиля для текста имени
    static QString pathStyleTextName;
    // Полное имя файла стиля для текста диалога
    static QString pathStyleTextSpeak;
    // Полное имя файла стиля для рамки имени
    static QString pathStyleBorderName;
    // Полное имя файла стиля для рамки диалога
    static QString pathStyleBorderSpeak;
    // Полное имя файла стиля для кнопки
    static QString pathStyleButton;

    // базовый курсор
    static QCursor cursorBase;
    // курсор при наведении на кнопку
    static QCursor cursorButton;
    // главное окно
    static MainWindow *mainWindow;
    // главный виджет, занимающий все главное окно
    static QWidget *mainWidget;
    // главный контейнер сетки, занимающий весь mainWidget
    static QGridLayout *mainLayout;
    // первая сцена, которая будет запускаться в начале игры
    static NovellaScene *firstScene;

    /*
     * Метод инициализации игры.
     * Инициализируются курсоры, шрифт, виджеты, контейнеры и т.д. (все что будет использоваться в игре).
     * Аргумент 1: window - главное окно.
     */
    static void InitializeGame(MainWindow *window);

    /*
     * Метод инициализации сцен.
     * Инициализируются все сцены, которые могут отображаться в игре.
     */
    static void InitializeScenes();

    /*
     * Метод открытия главного меню.
     * Реализует отображение главного меню.
     */
    static void OpenMainMenu();

    /*
     * Метод открытия меню конца игры.
     * Реализует отображение меню конца игры.
     */
    static void OpenEndMenu();

    /*
     * Метод реализующий запуск начальной сцены.
     */
    static void StartGame();

    /*
     * Метод закрытия программы.
     */
    static void ExitGame();

}novellagame;

#endif // NOVELLAGAME_H
