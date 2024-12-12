#include "novellascene.h"
#include "novellagame.h"

NovellaScene::NovellaButton::NovellaButton(NovellaScene *currentScene, QString text, NovellaScene *nextScene)
{
    _text = text;
    _nextScene = nextScene;
    _currentScene = currentScene;
}

QPushButton* NovellaScene::NovellaButton::CreateButton()
{
    // Создание объекта обычной кнопки.
    QPushButton *btn = new QPushButton(_text);

    // Применение стилей к кнопке.
    QString style = novellatools.GetTextFromFile(novellagame.pathStyleButton);
    btn->setStyleSheet(style);
    btn->setCursor(novellagame.cursorButton);

    // Привязка события при нажатии на кнопку.
    btn->connect(btn, &QPushButton::clicked, [this](){ this->NovellaButton_Clicked(); });

    // Возвращение созданной кнопки.
    return btn;
}

void NovellaScene::NovellaButton::NovellaButton_Clicked()
{
    // Если следующая сцена существует, то производится переход к следующей сцене.
    // Текущая сцена удаляется сразу после перехода на следующую.
    // Если следующей сцены не существует, то открывается меню конца игры.
    if (_nextScene != nullptr)
    {
        _nextScene->Show();
        delete _currentScene;
    }
    else
    {
        novellagame.OpenEndMenu();
    }
}



NovellaScene::NovellaDialogBox::NovellaDialogBox(NovellaScene *currentScene)
{
    _currentScene = currentScene;
}

NovellaScene::NovellaDialogBox::~NovellaDialogBox()
{
    // В цикле удаляются все кнопки из массива _btns
    for (int i = 0; i < _btns.size(); i++)
    {
        delete _btns.takeAt(i);
    }
}

void NovellaScene::NovellaDialogBox::SetDialog(QString name, QString text)
{
    // Задается имя и текст диалога
    _name = name;
    _text = text;
}

void NovellaScene::NovellaDialogBox::CreateNovellaButton(QString text, NovellaScene *nextScene)
{
    // Создается новая кнопка и помещается в массив _btns
    _btns.push_back(new NovellaButton(_currentScene, text, nextScene));
}

QLayout* NovellaScene::NovellaDialogBox::CreateLayout()
{
    // Создание двух контейнеров.
    // hLayout - вертикальный контейнер для кнопок.
    // gridLayout - контейнер сетки. Является главным для диалогового окна.
    QHBoxLayout *hLayout = new QHBoxLayout();
    QGridLayout *gridLayout = new QGridLayout();

    // Создание виджетов для имени персонажа и текста диалога.
    // textNameLabel - виджет, отображающий текст имени.
    // textSpeakLabel - виджет, отображаюзий текст диалога.
    // borderNameLabel - виджет, отображающий рамку для имени.
    // borderSpeakLabel - виджет, отображающий рамку для текста диалога.
    QLabel *textNameLabel = new QLabel(_name);
    QLabel *textSpeakLabel = new QLabel(_text);
    QLabel *borderNameLabel = new QLabel(_name);
    QLabel *borderSpeakLabel = new QLabel(_text);

    // Задание стилей для виджетов
    QString styleTextNameLabel = novellatools.GetTextFromFile(novellagame.pathStyleTextName);
    QString styleTextSpeakLabel = novellatools.GetTextFromFile(novellagame.pathStyleTextSpeak);
    QString styleBorderNameLabel = novellatools.GetTextFromFile(novellagame.pathStyleBorderName);
    QString styleBorderSpeakLabel = novellatools.GetTextFromFile(novellagame.pathStyleBorderSpeak);
    textNameLabel->setStyleSheet(styleTextNameLabel);
    textSpeakLabel->setStyleSheet(styleTextSpeakLabel);
    borderNameLabel->setStyleSheet(styleTextNameLabel + styleBorderNameLabel);
    borderSpeakLabel->setStyleSheet(styleTextSpeakLabel + styleBorderSpeakLabel);

    // Настройка отступов для виджетов
    // Отступ текста для имени и текста диалога
    textNameLabel->setMargin(10);
    textSpeakLabel->setMargin(15);
    // Отсуп между кнопками и диалогом
    hLayout->setContentsMargins(0, 20, 0, 0);
    // Отступ между кнопками
    hLayout->setSpacing(20);
    // Отступ диалогового окна от краев экрана
    gridLayout->setContentsMargins(300, 0, 300, 100);
    // Отступ между виджетами сетки
    gridLayout->setSpacing(0);

    // Создание виджетов кнопок и размещение их в контейнер hLayout
    for (int i = 0; i < _btns.size(); i++)
    {
        hLayout->addWidget(_btns[i]->CreateButton(), i);
        hLayout->setStretch(i, 1); // Задание равномерного растягивания кнопок (чтобы все кнопки занимали одинаковое колиство места)
    }

    // Добавление виджетов для имени и текста диалога в контейнер gridLayout
    // Если имя - пустая строка, то добавляются только виджеты для текста диалога
    // Иначе добавляются все виджеты
    if (textNameLabel->text() == "")
    {
        gridLayout->addWidget(borderSpeakLabel, 1, 0, 1, 2);
        gridLayout->addWidget(textSpeakLabel, 1, 0, Qt::AlignLeft);
    }
    else
    {
        gridLayout->addWidget(borderNameLabel, 0, 0, 1, 1, Qt::AlignLeft);
        gridLayout->addWidget(borderSpeakLabel, 1, 0, 1, 2);
        gridLayout->addWidget(textNameLabel, 0, 0, Qt::AlignLeft);
        gridLayout->addWidget(textSpeakLabel, 1, 0, Qt::AlignLeft);
    }

    // Добавление контейнера с кнопками в главный контейнер gridLayout
    gridLayout->addLayout(hLayout, 2, 0);

    // Возвращение главного контейнера диалогового окна gridLayout
    return gridLayout;
}



NovellaScene::NovellaScene(QGridLayout* parentLayout)
{
    _parentLayout = parentLayout;
    // Создание эксземпляра диалогового окна
    _dialog = new NovellaDialogBox(this);
}

NovellaScene::~NovellaScene()
{
    // Удаление диалогового окна
    delete _dialog;
}

void NovellaScene::SetBackground(QString imagePath)
{
    _bgImagePath = imagePath;
}

void NovellaScene::SetFirstCharacter(QString imagePath)
{
    _chrFirstImagePath = imagePath;
}

void NovellaScene::SetSecondCharacter(QString imagePath)
{
    _chrSecondImagePath = imagePath;
}

void NovellaScene::Say(QString name, QString text)
{
    _dialog->SetDialog(name, text);
}

void NovellaScene::AddChoice(QString text, NovellaScene *nextScene)
{
    _dialog->CreateNovellaButton(text, nextScene);
}

void NovellaScene::Show()
{
    // Полное очищение главного родительского контейнера
    novellatools.ClearLayout(_parentLayout);

    // Создание виджетов с изображениями
    NovellaImage *_bgImage = new NovellaImage(_bgImagePath);
    NovellaImage *_chrFirstImage = new NovellaImage(_chrFirstImagePath, EAlignment::LeftBottom);
    NovellaImage *_chrSecondImage = new NovellaImage(_chrSecondImagePath, EAlignment::RightBottom);

    // Добавление всех виджетов в главный родительский контейнер
    _parentLayout->addWidget(_bgImage, 0, 0);
    _parentLayout->addWidget(_chrFirstImage, 0, 0);
    _parentLayout->addWidget(_chrSecondImage, 0, 0);
    _parentLayout->addLayout(_dialog->CreateLayout(), 0, 0, Qt::AlignBottom);

    // На всякий случай контейнер обновляется
    _parentLayout->update();
}
