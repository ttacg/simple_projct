#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>
#include <random>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

void sleepMs(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void typeText(const string& text, int delay = 35) {
    for (unsigned char c : text) {
        cout << c << flush;
        sleepMs(delay);
    }
}

void statusLine(const string& tag, const string& text, int dots = 5, int delay = 220) {
    cout << "[" << tag << "] " << text;
    for (int i = 0; i < dots; i++) {
        cout << "." << flush;
        sleepMs(delay);
    }
    cout << " [OK]\n";
}

void progressBar(const string& tag, const string& text, int width = 24) {
    cout << "[" << tag << "] " << text << "\n";
    cout << "       [";
    for (int i = 0; i < width; i++) {
        cout << "#" << flush;
        sleepMs(70);
    }
    cout << "] 100%\n";
}

void drawAnimation() {
    const vector<string> frames = {
        "<    >",
        "<=   >",
        "<==  >",
        "<=== >",
        "<====>",
        "< ===>",
        "<  ==>",
        "<   =>"
    };

    cout << "[DRAW] 电子签筒正在摇动 ";
    for (int i = 0; i < 18; i++) {
        cout << "\r[DRAW] 电子签筒正在摇动 " << frames[i % frames.size()] << flush;
        sleepMs(120);
    }
    cout << "\r[DRAW] 电子签筒完成抽取 <====> [OK]\n";
}

int getTodayNumber() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    return (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday;
}

unsigned int simpleHash(const string& s) {
    unsigned int h = 2166136261u;
    for (unsigned char c : s) {
        h ^= c;
        h *= 16777619u;
    }
    return h;
}

int randomIndex(mt19937& rng, int size) {
    return uniform_int_distribution<int>(0, size - 1)(rng);
}

int main() {
    setupConsole();

    string name, birthday;

    cout << "请输入你的姓名：";
    getline(cin, name);

    cout << "请输入生日，例如 2005-08-16：";
    getline(cin, birthday);

    unsigned int seed = simpleHash(name + birthday + to_string(getTodayNumber()));
    mt19937 rng(seed);

    vector<string> fortunes = {
        "你的精神状态像刚刚重启的服务器：风扇很响，但核心还算稳定。",
        "命运正在后台编译，警告很多，但暂时没有致命错误。",
        "你以为你在选择人生，其实人生正在读取默认配置。",
        "今日不宜深夜思考未来，因为未来服务器当前响应超时。",
        "你的灵魂像一个 while(true)：表面稳定，实际很难退出。",
        "宇宙日志显示：你今天会遇到一个小问题，但它只是伪装成 bug 的提示。",
        "你的人生当前处于 beta 版本，偶尔闪退属于正常现象。",
        "不要害怕 bug，bug 只是命运给你的彩蛋，只是有点难拆。",
        "你的未来像模板报错，看不太懂，但一定很高级。",
        "今天适合保持低功耗模式，等待命运缓存刷新。"
    };

    vector<string> good = {
        "喝水并重启大脑",
        "写两行能运行的代码",
        "整理桌面和下载文件夹",
        "看一点没用但好玩的东西",
        "打开 VS Code 假装很忙",
        "早点睡，但允许失败一次",
        "给变量起一个正常名字",
        "把计划拆成一个小任务"
    };

    vector<string> bad = {
        "重装环境",
        "删除 C 盘",
        "深夜研究就业形势",
        "立下过于宏大的计划",
        "相信玄学超过相信报错信息",
        "没有备份就乱改配置",
        "反复追问人生的意义",
        "同时打开三个 AI 让它们互相解释"
    };

    vector<string> items = {
        "一杯带气泡的水",
        "冰可乐",
        "绿色终端窗口",
        "一个能运行的 exe",
        "没有报错的 main 函数",
        "祖传 U 盘",
        "一份没崩的配置文件",
        "一只安静的鼠标"
    };

    vector<string> signs = {
        "上上签：权限已提升",
        "上签：缓存命中",
        "中签：系统稳定运行",
        "下签：网络轻微波动",
        "小凶：配置文件有点叛逆",
        "大凶但还能抢救：请勿手滑",
        "抽象签：命运返回了未知类型",
        "赛博观音沉默签：答案在日志里"
    };

    system("cls");

    typeText("[BOOT] Cyber Fate Terminal v1.0\n", 25);
    typeText("[BOOT] 正在载入今日命运协议...\n\n", 25);

    statusLine("LINK", "正在连接赛博命运服务器");
    statusLine("SCAN", "正在解析出生参数");
    statusLine("AUTH", "正在校验灵魂访问权限");
    progressBar("SYNC", "正在同步今日宇宙噪声");
    drawAnimation();

    cout << "\n";
    typeText("[SIGN] 叮！一支电子签从数据流里弹了出来。\n\n", 35);

    int luck = uniform_int_distribution<int>(0, 100)(rng);

    string fortune = fortunes[randomIndex(rng, fortunes.size())];
    string todayGood = good[randomIndex(rng, good.size())];
    string todayBad = bad[randomIndex(rng, bad.size())];
    string luckyItem = items[randomIndex(rng, items.size())];
    string sign = signs[randomIndex(rng, signs.size())];

    typeText("====== 今日赛博算命报告 ======\n", 20);
    typeText("姓名：" + name + "\n", 25);
    typeText("生日：" + birthday + "\n", 25);
    typeText("今日运势：" + to_string(luck) + "/100\n", 25);
    typeText("抽签结果：" + sign + "\n", 25);
    typeText("命运批语：" + fortune + "\n", 30);
    typeText("今日宜：" + todayGood + "\n", 25);
    typeText("今日忌：" + todayBad + "\n", 25);
    typeText("幸运物：" + luckyItem + "\n", 25);

    if (luck >= 80) {
        typeText("隐藏签：大吉。今天写出的 bug 可能明天才会爆，先享受这份安静。\n", 30);
    } else if (luck >= 50) {
        typeText("隐藏签：中平。能跑就先别动，命运服务器建议你保持现状。\n", 30);
    } else {
        typeText("隐藏签：小凶。建议今天不要移动环境变量，也不要挑战未知配置。\n", 30);
    }

    typeText("==============================\n", 20);

    return 0;
}
