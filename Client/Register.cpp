#define _CRT_SECURE_NO_WARNINGS 1
#include "Visual_interface.h"

void Register()
{
    // 清屏并设置文字样式
    cleardevice();
    setbkcolor(WHITE);
    cleardevice();
    settextcolor(BLACK);
    settextstyle(30, 0, _T("微软雅黑"));

    // 在窗口顶部居中显示 “Login”
    outtextxy((getwidth() - textwidth(_T("Register"))) / 2, 60, _T("Register"));

    // 设置账号/密码标签的字体
    settextstyle(24, 0, _T("微软雅黑"));
    // 账号标签
    outtextxy(200, 180, _T("Name:"));
    // 密码标签
    outtextxy(200, 240, _T("Password:"));

    // 用来存储账号和密码的数组
    TCHAR username[64] = {0};
    char _username[64] = {0};
    TCHAR password[64] = {0};
    char _password[64] = {0};
    int ulen = 0, plen = 0;

    // 输入状态：0 表示正在输入账号；1 表示正在输入密码
    int inputStage = 0;

    // 账号/密码输入框的起始坐标
    const int inputX = 350, inputY_account = 180, inputY_password = 240;
    const int maxLen = 50; // 最多输入字符数

    // 先把光标定位到账号输入框
    int curX = inputX, curY = inputY_account;
    // 为了动态刷新输入内容，需要先画一个“空白区域”来遮盖光标位置／旧文字
    auto clearInputLine = [&](int y)
    {
        // 假设一行能够显示最多 maxLen 个字符，每个字符宽度大约 14 像素，往右清 14*maxLen 的区域
        // 也可以根据实际字体大小调整
        setfillcolor(WHITE);
        bar(inputX, y, inputX + 14 * maxLen, y + textheight(_T("W")));
    };

    // 绘制初始状态：账号一行显示光标，密码行先空白
    clearInputLine(inputY_account);
    clearInputLine(inputY_password);
    // 光标可以用一个下划线表示（简单粗暴）
    outtextxy(curX, curY, _T("_"));

    // 主循环：等待用户输入
    while (true)
    {
        int ch = _getch(); // 从 <conio.h> 读取一个键

        // 如果是功能键（0 或 0xE0 前缀），再读一次得到实际码；简单做法：跳过
        if (ch == 0 || ch == 0xE0)
        {
            _getch();
            continue;
        }

        // ESC：重置到账号输入阶段，清空两个缓冲区
        if (ch == 27) // ASCII 27 = ESC
        {
            ulen = plen = 0;
            username[0] = '\0';
            _username[0] = '\0';
            password[0] = '\0';
            _password[0] = '\0';
            inputStage = 0;
            // 清空两行输入区域并把光标移回账号行
            clearInputLine(inputY_account);
            clearInputLine(inputY_password);
            curX = inputX;
            curY = inputY_account;
            outtextxy(curX, curY, _T("_"));
            continue;
        }

        // 回车：如果当前是账号输入，切换到密码输入；如果密码输入完成，则退出循环
        if (ch == '\r')
        {
            if (inputStage == 0)
            {
                // 用户按下回车确认了账号，切换到密码输入
                inputStage = 1;
                // 清除账号行最后的下划线光标
                clearInputLine(inputY_account);
                outtextxy(inputX, inputY_account, username);

                // 准备密码行：画一个下划线光标
                curX = inputX;
                curY = inputY_password;
                outtextxy(curX, curY, _T("_"));
            }
            else
            {
                // 密码输入阶段，按下 Enter，就认为账号和密码都输入完毕，跳出循环
                // 最后把密码行的下划线清掉，并把掩码“*”留在屏幕上
                clearInputLine(inputY_password);
                // 用掩码重绘 password
                for (int i = 0; i < plen; ++i)
                {
                    outtextxy(inputX + i * 14, inputY_password, _T("*"));
                }
                break;
            }
            continue;
        }

        // Backspace：删除当前阶段最后一个字符
        if (ch == 8) // ASCII 8 = Backspace
        {
            if (inputStage == 0)
            {
                if (ulen > 0)
                {
                    ulen--;
                    username[ulen] = '\0';
                    _username[ulen] = '\0';
                    // 重绘账号行：先清除整行，再写入新的 username，再写下划线光标
                    clearInputLine(inputY_account);
                    outtextxy(inputX, inputY_account, username);
                    curX = inputX + ulen * 14;
                    curY = inputY_account;
                    outtextxy(curX, curY, _T("_"));
                }
            }
            else
            {
                if (plen > 0)
                {
                    plen--;
                    password[plen] = '\0';
                    _password[plen] = '\0';
                    // 重绘密码行：先清空整行，再重新画 plen 个 '*'，再画光标
                    clearInputLine(inputY_password);
                    for (int i = 0; i < plen; ++i)
                    {
                        outtextxy(inputX + i * 14, inputY_password, _T("*"));
                    }
                    curX = inputX + plen * 14;
                    curY = inputY_password;
                    outtextxy(curX, curY, _T("_"));
                }
            }
            continue;
        }

        // 其它可打印字符：把它加入到用户名或密码缓存中
        if (ch >= 32 && ch <= 126) // ASCII 可见字符范围
        {
            if (inputStage == 0)
            {
                if (ulen < maxLen - 1)
                {
                    username[ulen] = (char)ch;
                    _username[ulen++] = (char)ch;
                    username[ulen] = '\0';
                    _username[ulen] = '\0';
                    // 重绘账号行：清空 + 重绘 + 光标
                    clearInputLine(inputY_account);
                    outtextxy(inputX, inputY_account, username);
                    curX = inputX + (ulen * 14);
                    curY = inputY_account;
                    outtextxy(curX, curY, _T("_"));
                }
            }
            else
            {
                if (plen < maxLen - 1)
                {
                    password[plen] = (char)ch;
                    _password[plen++] = (char)ch;
                    _password[plen] = '\0';
                    password[plen] = '\0';
                    // 重绘密码行：清空 + 重绘掩码 + 光标
                    clearInputLine(inputY_password);
                    for (int i = 0; i < plen; ++i)
                    {
                        outtextxy(inputX + i * 14, inputY_password, _T("*"));
                    }
                    curX = inputX + plen * 14;
                    curY = inputY_password;
                    outtextxy(curX, curY, _T("_"));
                }
            }
            continue;
        }

        // 其余键全部忽略
    }

    printf("Entered username: %s\n", _username);
    printf("Entered password: %s\n", _password);
    std::string username_(_username);
    std::string userpasswd(_password);
    std::string userid = "";
    Register_Wait();
    bool result = register_request(username_, userpasswd, &userid, sock_global);
    if (result)
    {
        id_global = userid;
        name_global = username_;
        passwd_global = userpasswd;
        pos_global = static_cast<int>(Scene::Start_Sc);
        Register_Success(name_global, id_global, passwd_global);
        return;
        // TODO
    }
    else
    {
        Register_Fail();
        pos_global = static_cast<int>(Scene::Start_Sc);
        return;
    }
}