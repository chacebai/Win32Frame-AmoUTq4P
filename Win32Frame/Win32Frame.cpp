// Win32Frame.cpp : Defines the entry point for the application.
//

#include "Win32Frame.h"

#include "framework.h"

#include "GridLayout.hpp"
#include "VerticalLayout.hpp"
#include "HorizontalLayout.hpp"
#include "FormLayout.hpp"
#include "ButtonControl.hpp"
#include "StaticTextControl.hpp"
#include "TabControl.hpp"
#include "PaddingLayout.hpp"
#include "TestWindow.hpp"

using namespace std;

int run();
int testGridLayout();
int testVerticalLayout();
int testHorizontalLayout();
int testFormLayout();

int WINAPI WinMain(
    _In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPSTR     lpCmdLine,
    _In_     INT       nCmdShow)
{
    SetProcessDPIAware();
    // return testGridLayout();
    // return testVerticalLayout();
    return testHorizontalLayout();
    // return testFormLayout();
}

int testGridLayout()
{
    GridLayout grid(2, 6);

    ButtonControl btnA(TEXT("好啊好啊"));
    ButtonControl btnB(TEXT("qRltFl0GtElLX6FT3PKzaqcpdH0wE1FmmrPNUxT46XsFz2A1t5h7eEFgrHoYz0VCphoUml5x4BS0LoQeuu3af04QX9GtRIBZ0AICndaGsYEHm6rrqjIS6H66ZRAk0CDs"));
    ButtonControl btnC(TEXT("mEP6iMuvXbj58zpeepiuRyTVtqTOM19bRnzi3Rs9nshDGxmkyhuLxU8QaOU4vXCGGaIS2DTK47SUf7grqtyNeVXLkZHG1c6AOcjo1oKh1F2ERkQGPAOmVm4q7KDMmnSa"));
    StaticTextControl btnD(TEXT("DFJy5ycmFDHwjcyLiRTNvlSnxbCZGU86aLsgOwJ9phDQvndVbGSyNDrIj31feUKF7el8EAqcxXxG6NXrjiBlUR25q5HlddDQ3joN1na7nRPy4ul0ErwNWo1Prv2NxPlB"));
    TabControl btnE(TEXT("qG9V22NRqKjS1Zdyu5W8CDHu4O1ZjRYB8mrhAedBrCGJ8T8IEFGTp1QHdqkzDYnxpZlm7StSMmZHrU75uNuIuZ4kSAVllGTk0hMsK3ZahW1gPN2rUUnm1qnaJvFMqldS"));
    grid.AddComponent(0, 0, 1, 1, &btnA);
    grid.AddComponent(1, 0, 1, 1, &btnB);
    grid.AddComponent(0, 1, 1, 1, &btnC);
    grid.AddComponent(1, 1, 1, 1, &btnD);
    grid.AddComponent(0, 2, 1, 2, &btnE);

    PaddingLayout padding(50, 50, 50, 50);
    padding.SetComponent(&grid);

    TestWindow wndTest(&padding);
    if (!wndTest.Create(TEXT("Test Window 好好")))
    {
        return -1;
    }
    // Window must created before CreateTabPage
    btnE.CreateTabPage(TEXT("AAA 好好"));
    btnE.CreateTabPage(TEXT("BBB 好好"));
    btnE.CreateTabPage(TEXT("CCC 好好"));
    btnE.CreateTabPage(TEXT("DDD 好好"));
    btnE.CreateTabPage(TEXT("EEE 好好"));
    btnE.CreateTabPage(TEXT("FFF 好好"));
    btnE.CreateTabPage(TEXT("GGG 好好"));
    btnE.CreateTabPage(TEXT("HHH 好好"));
    btnE.CreateTabPage(TEXT("III 好好"));
    btnE.CreateTabPage(TEXT("JJJ 好好"));
    btnE.CreateTabPage(TEXT("KKK 好好"));
    wndTest.Show(SW_SHOWNORMAL);
    return run();
}

int testVerticalLayout()
{
    VerticalLayout vert;

    ButtonControl btnA(TEXT("好啊好啊"));
    btnA.SetMinSize(512, btnA.GetHeight());
    btnA.SetMaxSize(1024, btnA.GetHeight());
    ButtonControl btnB(TEXT("r7vPtoebJ1DrXSgch9v8AEfyBsrQhPAMtmEu6s9RjA9dpe27hM30HN54fQW6JlmozfLsPAvt8vIF1X3bSzAyIPCI4LLQz6NAzfUmOWGJ6lxWiMl9QaZHT4amkWMCXILX"));
    btnB.SetMinSize(512, btnB.GetHeight());
    btnB.SetMaxSize(1024, btnB.GetHeight());
    ButtonControl btnC(TEXT("UoxavhwClBjYMCtivycaeMh7VOpaPFBLKQi8xj1QPKHuV9V6Tqi9LU94Fq7KKhr5HizHzrRiutn4YTAEJ7MFeRh6bNZ17DgvQqJ4lIYcBob3fbQEXqVnixSOtLP2bvWb"));
    btnC.SetMinSize(512, btnC.GetHeight());
    btnC.SetMaxSize(1024, btnC.GetHeight());
    StaticTextControl btnD(TEXT("81VawGNqi3e4GjSuuXcjfolv4i8scx5mbKGswptJOSvQlHIMV083lmc8iutKQLPQ2pO3tZsIRjUff2ybSI37H0mh4AFNAlBwQ04IGAwAmnCoFGlrn5DScisHoPjUrMcB"));
    btnD.SetMinSize(512, btnD.GetHeight());
    btnD.SetMaxSize(1024, btnD.GetHeight());
    TabControl btnE(TEXT("mHmkP9GRsnBMRnRIH16mZeMJag3DzmaAdZmTo1B5MLwMOfGYmoroMIeeTRO05Pe7M5UatFvWPjyqiEGkf3FnmxPToixvf0WRgTiTZeL7goAJ2LWQ0NqRqtvMUmdGdCYW"));
    vert.AddComponent(10, &btnA);
    vert.AddComponent(10, &btnB);
    vert.AddComponent(10, &btnC);
    vert.AddComponent(10, &btnD);
    vert.AddComponent(10, &btnE);

    PaddingLayout padding(50, 50, 50, 50);
    padding.SetComponent(&vert);

    TestWindow wndTest(&padding);
    if (!wndTest.Create(TEXT("Test Window 好好")))
    {
        return -1;
    }
    // Window must created before CreateTabPage
    btnE.CreateTabPage(TEXT("AAA 好好"));
    btnE.CreateTabPage(TEXT("BBB 好好"));
    btnE.CreateTabPage(TEXT("CCC 好好"));
    btnE.CreateTabPage(TEXT("DDD 好好"));
    btnE.CreateTabPage(TEXT("EEE 好好"));
    btnE.CreateTabPage(TEXT("FFF 好好"));
    btnE.CreateTabPage(TEXT("GGG 好好"));
    btnE.CreateTabPage(TEXT("HHH 好好"));
    btnE.CreateTabPage(TEXT("III 好好"));
    btnE.CreateTabPage(TEXT("JJJ 好好"));
    btnE.CreateTabPage(TEXT("KKK 好好"));
    wndTest.Show(SW_SHOWNORMAL);
    return run();
}

int testHorizontalLayout()
{
    HorizontalLayout hori;

    ButtonControl btnA(TEXT("好啊好啊"));
    btnA.SetMinSize(btnA.GetWidth(), 30);
    btnA.SetMaxSize(btnA.GetWidth(), 30);
    ButtonControl btnB(TEXT("dxXFee0q8gWQ2tEtscIYnDXyIRBDxkz3uZwTSkgjkXru4h60HIJT7OvBM1rGEd3o5h3tgnGmcoofQ2GIXO7GVWQpKswD7o6we1fmHfvOaGOU82iGTfvpmzafQdKTHogC"));
    ButtonControl btnC(TEXT("QNek66GCDsq9VKFcV4r0QGmraUGc6nkhllDv4zNcmsBTzEqnc7JC3WMG2WjYL0uSAIDa5mvWReLKmkA3PwKQhLz2PAV6YnoQP4jNU1pzR1839OptYqUMs9f3B1O6WE8g"));
    StaticTextControl btnD(TEXT("x0IW53gevIZ0VJQLBFqsRolCs1aTk3kfRy7Wo8YuuHRzgigAjnf21viCMwEzPZnI2JzYa631MVkBWdA0xiIcSSZEjG0P7wThD6tzKDd7UpzSmlMMRfOpGTb3Y1bBjg7c"));
    btnD.SetMinSize(btnD.GetWidth(), 20);
    btnD.SetMaxSize(btnD.GetWidth(), 20);
    TabControl btnE(TEXT("hpIh4unyJHGsvWY1S7qPEaREQ0T9VPF6XWwaWxg7GY93z3cwFh57jQgtZ3732uoEQ5CHmvDX4deBgmrDIcWzNVZ6SS0yZXpn3w2POQkpZzcqmvJQLvb7XFHLm04N7jau"));
    btnE.SetMinSize(0, 256);
    btnE.SetMaxSize(INT_MAX, 1024);

    
    VerticalLayout vert;
    ButtonControl btnA2(TEXT("好啊好啊"));
    ButtonControl btnA3(TEXT("好啊好啊"));
    btnA2.SetMinSize(0, 30);
    btnA2.SetMaxSize(INT_MAX, 30);
    btnA3.SetMinSize(0, 30);
    btnA3.SetMaxSize(INT_MAX, 30);
    vert.AddComponent(30, &btnA2);
    vert.AddComponent(40, &btnA3);
    hori.AddComponent(10, &vert);
    hori.AddComponent(10, &btnA);
    hori.AddComponent(10, &btnB);
    hori.AddComponent(10, &btnC);
    hori.AddComponent(10, &btnD);
    hori.AddComponent(10, &btnE);

    PaddingLayout padding(50, 50, 50, 50);
    padding.SetComponent(&hori);

    TestWindow wndTest(&hori);
    if (!wndTest.Create(TEXT("Test Window 好好")))
    {
        return -1;
    }
    // Window must created before CreateTabPage
    btnE.CreateTabPage(TEXT("AAA 好好"));
    btnE.CreateTabPage(TEXT("BBB 好好"));
    btnE.CreateTabPage(TEXT("CCC 好好"));
    btnE.CreateTabPage(TEXT("DDD 好好"));
    btnE.CreateTabPage(TEXT("EEE 好好"));
    btnE.CreateTabPage(TEXT("FFF 好好"));
    btnE.CreateTabPage(TEXT("GGG 好好"));
    btnE.CreateTabPage(TEXT("HHH 好好"));
    btnE.CreateTabPage(TEXT("III 好好"));
    btnE.CreateTabPage(TEXT("JJJ 好好"));
    btnE.CreateTabPage(TEXT("KKK 好好"));
    wndTest.Show(SW_SHOWNORMAL);
    return run();
}

int testFormLayout()
{
    FormLayout form(50);

    ButtonControl btnA(TEXT("好啊好啊"));
    ButtonControl btnB(TEXT("oiCLbetZHMxGGjTa3jlrl0KBdfm4caUeAZUNUtDsk634dKgwogehEkchWXamnox2QIcLIbqFA2yR8ptEEyettqLCbTUPLLPlOydejhJ7dE7Ak8a3hTm1oKTdmYmTW0P3"));
    ButtonControl btnC(TEXT("qEipKJmP0KkNg8O06hKICDtac0CxYCMmQmm1dyC7jZ7I0l7Gdvf9dbY0ek5Y5avastAC9b2vBaWFfec9xGSLQtHFDKWUdjJmM3Vx9l04FipVM4bC4oPHYByYSErcJEfW"));
    StaticTextControl staA(TEXT("WiPeYc7eLdCV5sRYbu4jaxBlZE5fX3HlVqnYy3W4QV1yqUJ2LfsnC6uBYJ4wiKMahbTFwaAWBQkLZHEw4Z750DEC62w4psWIGNNTsEdTPdqtCLnigJtrMpELI47A3Cdn"));
    StaticTextControl staB(TEXT("Aq17mZSuDOpUGOPbHDIPzUt2VyOoBBtGR2YEiCI8vF4SyVqKZqclYlMLJGtia0WUt7S6MjVUfUeXdkVo7oTFbD3M9Fj1cpv76M9RM2cq8gYJnxRWI2z2TxgAzjicE3nw"));
    StaticTextControl staC(TEXT("LwiqpG9EFiccYJSgEpxhKCwxKtAGbqwindAh5HjK3wtpRombiRm15HFn5K3brCa4D9s2qdfDzyYWycAdUqeVcDXOUMck5dS0R7YbUN6230Ykymuca4INPchD7zsPxDLf"));


    form.AddRow(&staA, &btnA);
    form.AddRow(&staB, &btnB);
    form.AddRow(&staC, &btnC);

    PaddingLayout padding(50, 50, 50, 50);
    padding.SetComponent(&form);

    TestWindow wndTest(&padding);
    if (!wndTest.Create(TEXT("Test Window 好好")))
    {
        return -1;
    }
    wndTest.Show(SW_SHOWNORMAL);
    return run();
}

int run()
{
    ACCEL accelTable[] = {
        { FVIRTKEY | FCONTROL, 'C', IDM_COPY },   // Ctrl + C for Copy
        { FVIRTKEY | FCONTROL, 'V', IDM_PASTE },  // Ctrl + V for Paste
        { FVIRTKEY | FCONTROL, 'X', IDM_CUT },    // Ctrl + X for 
        { FVIRTKEY | FCONTROL, 'A', IDM_ABOUT },  // Ctrl + A for About
        { FVIRTKEY | FCONTROL, 'E', IDM_EXIT },   // Ctrl + E for Exit
        { 0, VK_ESCAPE, IDM_EXIT },
        // Add more accelerators as needed
    };

    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1212133));
    HACCEL hAccelTable = CreateAcceleratorTable(accelTable, sizeof(accelTable) / sizeof(ACCEL));

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}





