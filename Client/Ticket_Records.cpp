#include "Visual_interface.h"

#include <conio.h> // ���ڼ�������

void ticket_records(std::vector<std::string> &records, int *num, const std::string &input = "")
{
    int rows = records.size();
    int list_height = 190;

    cleardevice();
    settextcolor(RGB(0, 0, 0));
    settextstyle(50, 0, _T("΢���ź�"));
    outtextxy(500, 50, _T("Ticket Records"));

    settextstyle(35, 0, _T("΢���ź�"));
    std::string list_title = "| RID |        Area_Name        | Option | Num |             Time             |";
    RECT d = {240, 130, 1150, 170};
    drawtext(list_title.c_str(), &d, DT_LEFT);
    settextcolor(BROWN);

    for (int i = 0; i < rows; i++)
    {
        RECT r = {240, list_height, 1150, list_height + 50};
        drawtext(records[i].c_str(), &r, DT_LEFT);
        list_height += 50;
    }

    settextcolor(BLACK);

    // ��ʾ�����͵�ǰ��������
    std::string print_id = " Enter the order ID: " + (input.empty() ? std::to_string(*num) : input);
    outtextxy(150, 650, print_id.c_str());

    // ���ƹ��
    int text_width = textwidth(print_id.c_str());
    line(150 + text_width, 650, 150 + text_width, 650 + textheight(print_id.c_str()));

    // ���ư�ť
    setlinecolor(BLACK);
    fillroundrect(600, 640, 800, 700, 60, 250);
    settextstyle(30, 0, _T("΢���ź�"));
    outtextxy(630, 655, "Refund Ticket");
    outtextxy(1100, 650, _T("<-Return"));

    // ��ʾ������ʾ
    settextstyle(20, 0, _T("΢���ź�"));
    outtextxy(150, 690, "Press Enter to confirm, Backspace to delete");
}

void Ticket_Records(std::vector<std::string> &records)
{
    int num = 1;
    std::string input_str = ""; // �洢�û�������ַ���
    bool is_editing = false;    // ����û��Ƿ����ڱ༭

    while (true)
    {
        BeginBatchDraw();
        cleardevice();
        // ˢ�½���
        ticket_records(records, &num, input_str);

        // �����û�����
        if (_kbhit())
        {
            int key = _getch();

            // ������������
            if (key >= '0' && key <= '9')
            {
                input_str += static_cast<char>(key);
                is_editing = true;
            }
            // �����˸��
            else if (key == 8)
            { // 8 �� Backspace �� ASCII ��
                if (!input_str.empty())
                {
                    input_str.pop_back();
                }
            }
            // ����س���
            else if (key == 13)
            { // 13 �� Enter �� ASCII ��
                if (!input_str.empty())
                {
                    try
                    {
                        num = std::stoi(input_str);
                    }
                    catch (const std::exception &e)
                    {
                        // ������Ч����
                        MessageBox(NULL, _T("Invalid input! Please enter a valid number."),
                                   _T("Error"), MB_OK | MB_ICONERROR);
                    }
                }
                input_str.clear();
                is_editing = false;
            }
            // ���� ESC ��ȡ���༭
            else if (key == 27)
            { // 27 �� ESC �� ASCII ��
                input_str.clear();
                is_editing = false;
            }
        }

        // ���������
        if (MouseHit())
        {
            ExMessage mouse_msg;
            getmessage(&mouse_msg, EX_MOUSE);

            if (mouse_msg.message == WM_LBUTTONDOWN)
            {
                // ����Ƿ�����"Refund Ticket"��ť
                if (mouse_msg.x >= 600 && mouse_msg.x <= 800 &&
                    mouse_msg.y >= 640 && mouse_msg.y <= 700)
                {
                    if (!input_str.empty())
                    {
                        try
                        {
                            num = std::stoi(input_str);
                        }
                        catch (const std::exception &e)
                        {
                            MessageBox(NULL, _T("Invalid input! Please enter a valid number."),
                                       _T("Error"), MB_OK | MB_ICONERROR);
                            continue;
                        }
                    }
                    areas_aid;
                    for (int i = 0; i < records.size(); i++)
                    {
                        if (records[i].find(input_str) != std::string::npos)
                        {
                            if (records[i].find("Beijing") != std::string::npos)
                            {
                                areas_aid = BEIJING;
                                break;
                            }
                            else if (records[i].find("Guangdong") != std::string::npos)
                            {
                                areas_aid = GUANGDONG;
                                break;
                            }
                            else if (records[i].find("Shanghai") != std::string::npos)
                            {
                                areas_aid = SHANGHAI;
                                break;
                            }
                        }
                    }
                    pos_global = static_cast<int>(Scene::Ticket_Refund_Wait_Sc);
                    EndBatchDraw();
                    Ticket_Refund_Wait();
                    bool result = tickets_request(id_global, areas_aid, "Refund", "1", sock_global);
                    if (result)
                    {
                        pos_global = static_cast<int>(Scene::Ticket_Refund_Success_Sc);
                    }
                    else
                    {
                        pos_global = static_cast<int>(Scene::Ticket_Refund_Fail_Sc);
                    }
                    judgment_err_ = false;
                    return;
                }
                // ����Ƿ�����"Return"��ť
                else if (mouse_msg.x >= 1100 && mouse_msg.x <= 1250 &&
                         mouse_msg.y >= 600 && mouse_msg.y <= 700)
                {
                    std::cout << "12321321321" << std::endl;
                    pos_global = static_cast<int>(Scene::Home_Sc);
                    judgment_err_ = false;
                    EndBatchDraw();
                    return;
                }
                // ����Ƿ�������������
                else if (mouse_msg.x >= 150 && mouse_msg.x <= 500 &&
                         mouse_msg.y >= 640 && mouse_msg.y <= 680)
                {
                    is_editing = true;
                    input_str = std::to_string(num);
                }
                else
                {
                    judgment_err_ = true;
                }
            }
        }
        FlushBatchDraw();
        // �����ӳ٣�����CPUռ�ù���
        Sleep(50);
    }
    EndBatchDraw();
}