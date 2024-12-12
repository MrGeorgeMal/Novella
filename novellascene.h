#pragma once
#ifndef NOVELLASCENE_H
#define NOVELLASCENE_H

#include "novellatools.h"
#include "novellaimage.h"

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QString>
#include <QPixmap>
#include <QPushButton>
#include <QFile>
#include <QLayout>



/*
 * Объявление класса NovellaGame.
 * Его нельзя подключить в качестве библиотеки, так как произойдет цикличное подключение библиотек.
 */
class NovellaGame;



/*
 * Класс сцены.
 * Основные возможности:
 * - Отображать сцену;
 * - Задавать для сцены изображение фона, изображения персонажей, текст диалога и возможные выборы (кнопки).
 */
class NovellaScene
{
private:

    /*
     * Вложенный класс кнопки.
     * Класс является вложенным, так как нет необходимости создавать кнопки напрямую от этого класса. Этот функционал имеется в NovellaScene.
     * Поэтому NovellaBattun находится в приватном поле класса NovellaScene.
     * Основные возможности:
     * - Создавать виджет кнопки;
     */
    class NovellaButton
    {
    private:
        /*
         * _text - текст кнопки;
         * _currentScene - текущая сцена, которая должна удалиться при нажатии на эту кнопку;
         * _nextScene - следующая сцена, которая должна открыться при нажатии на эту кнопку.
         */
        QString _text = "";
        NovellaScene *_currentScene = nullptr;
        NovellaScene *_nextScene = nullptr;

    public:
        /*
         * Конструктор класса.
         * Аргумент 1: currentScene - текущая сцена;
         * Аргумент 2: text - текст кнопки;
         * Аргумент 3: nextScene - следующая сцена.
         */
        NovellaButton(NovellaScene *currentScene, QString text = "Кнопка", NovellaScene *nextScene = nullptr);

        /*
         * Метод создания кнопки.
         * Возвращает созданную кнопку (виджет).
         */
        QPushButton* CreateButton();

    private:
        /*
         * Метод обработки события при нажатии на кнопку.
         */
        void NovellaButton_Clicked();
    };



    /*
     * Вложенный класс диалогового окна.
     * Основные возможности:
     * - Задавать диалоговое окно: имя говорящего персонажа, текст диалога и возможные варианты ответа (кнопки);
     * - Создавать кнопки диалога;
     * - Размещать диалоговое окно в контейнере.
     */
    class NovellaDialogBox
    {
    private:
        /*
         * _name - имя персонажа, который говорит
         * _text - текст, который говорит персонаж
         * _btns - массив кнопок NovellaButton
         * _currentScene - текущая сцена
         */
        QString _name = "";
        QString _text = "";
        QList<NovellaButton*> _btns = QList<NovellaButton*>();
        NovellaScene *_currentScene = nullptr;

    public:
        /*
         * Коснтуктор класса.
         * Аргумент 1: currentScene - текущая сцена.
         */
        NovellaDialogBox(NovellaScene *currentScene);

        /*
         * Деструктор класса. Удаляет кнопки из массива _btns.
         */
        ~NovellaDialogBox();

        /*
         * Метод для задания диалогового окна.
         * Аргумент 1: name - имя персонажа;
         * Аргумент 2: text - текст диалога.
         */
        void SetDialog(QString name, QString text);

        /*
         * Метод создания кнопки NovellaButton и добавление ее в массив _btns.
         * Аргумент 1: text - текст кнопки;
         * Аргумент 2: nextScene - следующая сцена.
         */
        void CreateNovellaButton(QString text, NovellaScene *nextScene);

        /*
         * Метод создания контейнера, в который помещается все виджеты диалогового окна.
         * Возвращает созданный контейнер диалогового окна.
         */
        QLayout* CreateLayout();
    };



private:
    /*
     * _parentLayout - главный виджет игры
     * _dialog - экзепляр объекта класса NovellaDialogBox. Диалоговое окно
     * _bgImagePath - полное имя файла с изображением заднего фона
     * _chrFirstImagePath - полное имя файла с изображением первого персонажа
     * _chrSecondImagePath - полное имя файла с изображением второго персонажа
     */
    QGridLayout *_parentLayout = nullptr;
    NovellaDialogBox *_dialog = nullptr;
    QString _bgImagePath = "";
    QString _chrFirstImagePath = "";
    QString _chrSecondImagePath = "";

public:

    /*
     * Конструктор класса.
     * Аргумент 1: parentLayout - родительский контейнер (главный контейнер).
     */
    NovellaScene(QGridLayout* parentLayout);

    /*
     * Деструктор класса. Удаляет диалоговое окно.
     */
    ~NovellaScene();

    /*
     * Метод-сеттер для задания заднего фона.
     * Аргумент 1: imagePath - полное имя файла с изображением.
     */
    void SetBackground(QString imagePath);

    /*
     * Метод-сеттер для задания изображения с первым персонажем.
     * Аргумент 1: imagePath - полное имя файла с изображением.
     */
    void SetFirstCharacter(QString imagePath);

    /*
     * Метод-сеттер для задания изображения со вторым персонажем.
     * Аргумент 1: imagePath - полное имя файла с изображением.
     */
    void SetSecondCharacter(QString imagePath);

    /*
     * Метод задания имени говорящего и текста диалога.
     */
    void Say(QString name, QString text);

    /*
     * Метод добавления кнопки выбора в диалоговое окно.
     * Аргумент 1: text - текст кнопки;
     * Аргумент 2: nextScene - следующая сцена.
     */
    void AddChoice(QString text = "Кнопка", NovellaScene *nextScene = nullptr);

    /*
     * Метод отображения сцены на экран.
     */
    void Show();
};

#endif // NOVELLASCENE_H
