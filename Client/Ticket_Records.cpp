#include "Visual_interface.h"

#include <conio.h> // 用于键盘输入

void ticket_records(std::vector<std::string> &records, int *num, const std::string &input = "")
{
    int rows = records.size();
    int list_height = 190;

    cleardevice();
    settextcolor(RGB(0, 0, 0));
    settextstyle(50, 0, _T("微软雅黑"));
    outtextxy(500, 50, _T("Ticket Records"));

    settextstyle(35, 0, _T("微软雅黑"));
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

    // 显示输入框和当前输入内容
    std::string print_id = " Enter the order ID: " + (input.empty() ? std::to_string(*num) : input);
    outtextxy(150, 650, print_id.c_str());

    // 绘制光标
    int text_width = textwidth(print_id.c_str());
    line(150 + text_width, 650, 150 + text_width, 650 + textheight(print_id.c_str()));

    // 绘制按钮
    setlinecolor(BLACK);
    fillroundrect(600, 640, 800, 700, 60, 250);
    settextstyle(30, 0, _T("微软雅黑"));
    outtextxy(630, 655, "Refund Ticket");
    outtextxy(1100, 650, _T("<-Return"));

    // 显示输入提示
    settextstyle(20, 0, _T("微软雅黑"));
    outtextxy(150, 690, "Press Enter to confirm, Backspace to delete");
}

void Ticket_Records(std::vector<std::string> &records)
{
    int num = 1;
    std::string input_str = ""; // 存储用户输入的字符串
    bool is_editing = false;    // 标记用户是否正在编辑

    while (true)
    {
        BeginBatchDraw();
        cleardevice();
        // 刷新界面
        ticket_records(records, &num, input_str);

        // 处理用户输入
        if (_kbhit())
        {
            int key = _getch();

            // 处理数字输入
            if (key >= '0' && key <= '9')
            {
                input_str += static_cast<char>(key);
                is_editing = true;
            }
            // 处理退格键
            else if (key == 8)
            { // 8 是 Backspace 的 ASCII 码
                if (!input_str.empty())
                {
                    input_str.pop_back();
                }
            }
            // 处理回车键
            else if (key == 13)
            { // 13 是 Enter 的 ASCII 码
                if (!input_str.empty())
                {
                    try
                    {
                        num = std::stoi(input_str);
                    }
                    catch (const std::exception &e)
                    {
                        // 处理无效输入
                        MessageBox(NULL, _T("Invalid input! Please enter a valid number."),
                                   _T("Error"), MB_OK | MB_ICONERROR);
                    }
                }
                input_str.clear();
                is_editing = false;
            }
            // 处理 ESC 键取消编辑
            else if (key == 27)
            { // 27 是 ESC 的 ASCII 码
                input_str.clear();
                is_editing = false;
            }
        }

        // 处理鼠标点击
        if (MouseHit())
        {
            ExMessage mouse_msg;
            getmessage(&mouse_msg, EX_MOUSE);

            if (mouse_msg.message == WM_LBUTTONDOWN)
            {
                // 检查是否点击了"Refund Ticket"按钮
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
                // 检查是否点击了"Return"按钮
                else if (mouse_msg.x >= 1100 && mouse_msg.x <= 1250 &&
                         mouse_msg.y >= 600 && mouse_msg.y <= 700)
                {
                    std::cout << "12321321321" << std::endl;
                    pos_global = static_cast<int>(Scene::Home_Sc);
                    judgment_err_ = false;
                    EndBatchDraw();
                    return;
                }
                // 检查是否点击了输入区域
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
        // 短暂延迟，避免CPU占用过高
        Sleep(50);
    }
    EndBatchDraw();
}