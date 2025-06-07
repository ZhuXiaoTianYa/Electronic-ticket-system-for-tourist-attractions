#define _CRT_SECURE_NO_WARNINGS 1
#include "Visual_interface.h"

void Register()
{
    // ����������������ʽ
    cleardevice();
    setbkcolor(WHITE);
    cleardevice();
    settextcolor(BLACK);
    settextstyle(30, 0, _T("΢���ź�"));

    // �ڴ��ڶ���������ʾ ��Login��
    outtextxy((getwidth() - textwidth(_T("Register"))) / 2, 60, _T("Register"));

    // �����˺�/�����ǩ������
    settextstyle(24, 0, _T("΢���ź�"));
    // �˺ű�ǩ
    outtextxy(200, 180, _T("Name:"));
    // �����ǩ
    outtextxy(200, 240, _T("Password:"));

    // �����洢�˺ź����������
    TCHAR username[64] = {0};
    char _username[64] = {0};
    TCHAR password[64] = {0};
    char _password[64] = {0};
    int ulen = 0, plen = 0;

    // ����״̬��0 ��ʾ���������˺ţ�1 ��ʾ������������
    int inputStage = 0;

    // �˺�/������������ʼ����
    const int inputX = 350, inputY_account = 180, inputY_password = 240;
    const int maxLen = 50; // ��������ַ���

    // �Ȱѹ�궨λ���˺������
    int curX = inputX, curY = inputY_account;
    // Ϊ�˶�̬ˢ���������ݣ���Ҫ�Ȼ�һ�����հ��������ڸǹ��λ�ã�������
    auto clearInputLine = [&](int y)
    {
        // ����һ���ܹ���ʾ��� maxLen ���ַ���ÿ���ַ���ȴ�Լ 14 ���أ������� 14*maxLen ������
        // Ҳ���Ը���ʵ�������С����
        setfillcolor(WHITE);
        bar(inputX, y, inputX + 14 * maxLen, y + textheight(_T("W")));
    };

    // ���Ƴ�ʼ״̬���˺�һ����ʾ��꣬�������ȿհ�
    clearInputLine(inputY_account);
    clearInputLine(inputY_password);
    // ��������һ���»��߱�ʾ���򵥴ֱ���
    outtextxy(curX, curY, _T("_"));

    // ��ѭ�����ȴ��û�����
    while (true)
    {
        int ch = _getch(); // �� <conio.h> ��ȡһ����

        // ����ǹ��ܼ���0 �� 0xE0 ǰ׺�����ٶ�һ�εõ�ʵ���룻������������
        if (ch == 0 || ch == 0xE0)
        {
            _getch();
            continue;
        }

        // ESC�����õ��˺�����׶Σ��������������
        if (ch == 27) // ASCII 27 = ESC
        {
            ulen = plen = 0;
            username[0] = '\0';
            _username[0] = '\0';
            password[0] = '\0';
            _password[0] = '\0';
            inputStage = 0;
            // ��������������򲢰ѹ���ƻ��˺���
            clearInputLine(inputY_account);
            clearInputLine(inputY_password);
            curX = inputX;
            curY = inputY_account;
            outtextxy(curX, curY, _T("_"));
            continue;
        }

        // �س��������ǰ���˺����룬�л����������룻�������������ɣ����˳�ѭ��
        if (ch == '\r')
        {
            if (inputStage == 0)
            {
                // �û����»س�ȷ�����˺ţ��л�����������
                inputStage = 1;
                // ����˺��������»��߹��
                clearInputLine(inputY_account);
                outtextxy(inputX, inputY_account, username);

                // ׼�������У���һ���»��߹��
                curX = inputX;
                curY = inputY_password;
                outtextxy(curX, curY, _T("_"));
            }
            else
            {
                // ��������׶Σ����� Enter������Ϊ�˺ź����붼������ϣ�����ѭ��
                // ���������е��»���������������롰*��������Ļ��
                clearInputLine(inputY_password);
                // �������ػ� password
                for (int i = 0; i < plen; ++i)
                {
                    outtextxy(inputX + i * 14, inputY_password, _T("*"));
                }
                break;
            }
            continue;
        }

        // Backspace��ɾ����ǰ�׶����һ���ַ�
        if (ch == 8) // ASCII 8 = Backspace
        {
            if (inputStage == 0)
            {
                if (ulen > 0)
                {
                    ulen--;
                    username[ulen] = '\0';
                    _username[ulen] = '\0';
                    // �ػ��˺��У���������У���д���µ� username����д�»��߹��
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
                    // �ػ������У���������У������»� plen �� '*'���ٻ����
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

        // �����ɴ�ӡ�ַ����������뵽�û��������뻺����
        if (ch >= 32 && ch <= 126) // ASCII �ɼ��ַ���Χ
        {
            if (inputStage == 0)
            {
                if (ulen < maxLen - 1)
                {
                    username[ulen] = (char)ch;
                    _username[ulen++] = (char)ch;
                    username[ulen] = '\0';
                    _username[ulen] = '\0';
                    // �ػ��˺��У���� + �ػ� + ���
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
                    // �ػ������У���� + �ػ����� + ���
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

        // �����ȫ������
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