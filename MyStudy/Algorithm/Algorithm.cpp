#include "CommonInclude.h"


HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos = { 0, 0 };

void ShowConsoleCursor(bool showFlag)
{

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


int main()
{
    ShowConsoleCursor(false);
    const int WAIT_TICK = 1000 / 30; // 여기서 1000은 1000 mSec 즉 1초를 뜻한다.
    int lastTick = 0;
    while (true)
    {   
#pragma region 프레임관리
        int currentTick = (int)clock();

        // 만약에 경과한 시간이 1/30초보다 작다면
        if (currentTick - lastTick < WAIT_TICK) 
            continue;
        lastTick = currentTick;
#pragma endregion
        // FPS 프레임 (60프레임 OK 30프레임 이하로 NO)

        // 입력

        // 로직 (네트워크 통신을 하면서 로직을 주고 받는다)
        
        // 렌더링
        SetConsoleCursorPosition(out, pos);
        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 25; j++)
            {
                std::wcout << "●";
            }
            std::cout<<std::endl;
        }
    }
    return 0;
}