#include "novellagame.h"

QString NovellaGame::pathFontBase = ":/res/fonts/Caveat.ttf";
QString NovellaGame::pathCursorBase = ":/res/cursors/pointer.png";
QString NovellaGame::pathCursorButton = ":/res/cursors/link.png";
QString NovellaGame::pathStyleTextName = ":/res/styles/DialogNameTextStyle.txt";
QString NovellaGame::pathStyleTextSpeak = ":/res/styles/DialogSpeakTextStyle.txt";
QString NovellaGame::pathStyleBorderName = ":/res/styles/DialogNameBorderStyle.txt";
QString NovellaGame::pathStyleBorderSpeak = ":/res/styles/DialogSpeakBorderStyle.txt";
QString NovellaGame::pathStyleButton = ":/res/styles/DialogButtonStyle.txt";

QCursor NovellaGame::cursorBase;
QCursor NovellaGame::cursorButton;
MainWindow *NovellaGame::mainWindow;
QWidget *NovellaGame::mainWidget;
QGridLayout *NovellaGame::mainLayout;
NovellaScene *NovellaGame::firstScene;

void NovellaGame::InitializeGame(MainWindow *window)
{
    // Создание главного виджета и главного контейнера сетки
    mainWindow = window;
    mainWidget = new QWidget(window);
    mainLayout = new QGridLayout(mainWidget);

    // Применение выравниваний и отступов
    window->setCentralWidget(mainWidget);
    mainWidget->setLayout(mainLayout);
    mainWidget->setContentsMargins(0, 0, 0, 0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Инициализация курсоров
    cursorBase = QCursor(QPixmap(pathCursorBase), 0, 0);
    cursorButton = QCursor(QPixmap(pathCursorButton), 0, 0);
    window->setCursor(cursorBase);

    // Добавление шрифта в приложение
    QFontDatabase::addApplicationFont(pathFontBase);
}

void NovellaGame::OpenMainMenu()
{
    // Отчищение главного контейнера
    novellatools.ClearLayout(mainLayout);

    // Инициализация виджетов главного меню
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QLabel *text = new QLabel("Новелла");
    QPushButton *startGameBtn = new QPushButton("Играть");
    QPushButton *exitGameBtn = new QPushButton("Выход");
    NovellaImage *bgImage = new NovellaImage(":/res/images/background/bg1.jpg");

    // Применение стилей, выравниваний и отступов
    QString styleText = novellatools.GetTextFromFile(pathStyleTextSpeak);
    text->setStyleSheet(styleText);
    text->setFixedWidth(500);
    text->setAlignment(Qt::AlignCenter);

    QString styleBtn = novellatools.GetTextFromFile(pathStyleButton);
    startGameBtn->setStyleSheet(styleBtn);
    exitGameBtn->setStyleSheet(styleBtn);
    startGameBtn->setCursor(cursorButton);
    exitGameBtn->setCursor(cursorButton);

    // Привязка событий на нажатия кнопок
    startGameBtn->connect(startGameBtn, &QPushButton::clicked, [](){ StartGame(); });
    exitGameBtn->connect(exitGameBtn, &QPushButton::clicked, [](){ ExitGame(); });

    // Добавление всех виджетов и вспомогательных котейнеров в главный контейнер сетки
    verticalLayout->addWidget(text);
    verticalLayout->addWidget(startGameBtn);
    verticalLayout->addWidget(exitGameBtn);

    mainLayout->addWidget(bgImage, 0, 0);
    mainLayout->addLayout(verticalLayout, 0, 0, Qt::AlignCenter);
}

void NovellaGame::OpenEndMenu()
{
    // Отчищение главного контейнера
    novellatools.ClearLayout(mainLayout);

    // Инициализация виджетов меню конца игры
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QLabel *text = new QLabel("Игра пройдена!");
    QPushButton *openMainMenuBtn = new QPushButton("Вернуться в главное меню");
    QPushButton *startGameBtn = new QPushButton("Играть с начала");
    QPushButton *exitGameBtn = new QPushButton("Выход");
    NovellaImage *bgImage = new NovellaImage(":/res/images/background/bg1.jpg");

    // Применение стилей, выравниваний и отступов
    QString styleText = novellatools.GetTextFromFile(pathStyleTextSpeak);
    text->setStyleSheet(styleText);
    text->setFixedWidth(500);
    text->setAlignment(Qt::AlignCenter);

    QString styleBtn = novellatools.GetTextFromFile(pathStyleButton);
    openMainMenuBtn->setStyleSheet(styleBtn);
    startGameBtn->setStyleSheet(styleBtn);
    exitGameBtn->setStyleSheet(styleBtn);
    openMainMenuBtn->setCursor(cursorButton);
    startGameBtn->setCursor(cursorButton);
    exitGameBtn->setCursor(cursorButton);

    // Привязка событий на нажатия кнопок
    openMainMenuBtn->connect(openMainMenuBtn, &QPushButton::clicked, [](){ OpenMainMenu(); });
    startGameBtn->connect(startGameBtn, &QPushButton::clicked, [](){ StartGame(); });
    exitGameBtn->connect(exitGameBtn, &QPushButton::clicked, [](){ ExitGame(); });

    // Добавление всех виджетов и вспомогательных котейнеров в главный контейнер сетки
    verticalLayout->addWidget(text);
    verticalLayout->addWidget(openMainMenuBtn);
    verticalLayout->addWidget(startGameBtn);
    verticalLayout->addWidget(exitGameBtn);

    mainLayout->addWidget(bgImage, 0, 0);
    mainLayout->addLayout(verticalLayout, 0, 0, Qt::AlignCenter);
}

void NovellaGame::StartGame()
{
    // Инициализация всех сцен и запуск начальной сцены
    InitializeScenes();
    firstScene->Show();
}

void NovellaGame::ExitGame()
{
    // Закрытие игры
    mainWindow->close();
}
