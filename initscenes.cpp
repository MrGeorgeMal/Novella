#include "novellagame.h"

void NovellaGame::InitializeScenes()
{
    // Инициализация всех сцен
    NovellaScene *s1 = new NovellaScene(mainLayout);
    NovellaScene *s2 = new NovellaScene(mainLayout);

    // Задание сцены 1
    s1->SetBackground(":/res/images/background/bg1.jpg");
    s1->SetFirstCharacter(":/res/images/character/chrMain.png");
    s1->SetSecondCharacter(":/res/images/character/chrMain.png");
    s1->Say("Имя", "Текст");
    s1->AddChoice("Далее", s2);
    s1->AddChoice();

    // Задание сцены 2
    s2->SetBackground(":/res/images/background/bg1.jpg");
    s2->SetSecondCharacter(":/res/images/character/chr1.png");
    s2->Say("Имя", "ЭТО ДРУГАЯ СЦЕНА");
    s2->AddChoice();

    // Установка начальной сцены
    firstScene = s1;
}
