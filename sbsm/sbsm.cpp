#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

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

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printLine(const string& text = "", int delay = 0) {
    cout << text << "\n";
    if (delay > 0) {
        sleepMs(delay);
    }
}

void loadingLine(const string& text, int dots = 6, int delay = 180) {
    cout << text;
    for (int i = 0; i < dots; i++) {
        cout << "." << flush;
        sleepMs(delay);
    }
    cout << " 完成\n";
}

void progressBar(const string& title, int width = 28) {
    cout << title << "\n[";
    for (int i = 0; i < width; i++) {
        cout << "=" << flush;
        sleepMs(45);
    }
    cout << "] 100%\n";
}

void printTitle() {
    printLine("+--------------------------------------+");
    printLine("|              日常小算命              |");
    printLine("|        今天也可以轻轻问一问          |");
    printLine("+--------------------------------------+");
    printLine();
}

void printSection(const string& title) {
    printLine();
    printLine("---------- " + title + " ----------");
}

string pick(mt19937& rng, const vector<string>& values) {
    uniform_int_distribution<int> dist(0, static_cast<int>(values.size()) - 1);
    return values[dist(rng)];
}

int randomInt(mt19937& rng, int minValue, int maxValue) {
    uniform_int_distribution<int> dist(minValue, maxValue);
    return dist(rng);
}

string emptyToDefault(const string& text, const string& defaultValue) {
    if (text.empty()) {
        return defaultValue;
    }
    return text;
}

string trimSpaces(const string& text) {
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

unsigned int makeSeed(const string& name, const string& birthday, const string& gender, const string& focus) {
    random_device rd;
    auto now = chrono::high_resolution_clock::now().time_since_epoch().count();

    unsigned int seed = rd();
    string all = name + birthday + gender + focus + to_string(now);
    for (unsigned char c : all) {
        seed = seed * 131u + c;
    }
    return seed;
}

string scoreLevel(int score) {
    if (score >= 90) {
        return "很旺";
    }
    if (score >= 75) {
        return "偏好";
    }
    if (score >= 60) {
        return "平稳";
    }
    if (score >= 45) {
        return "略低";
    }
    return "需要养养状态";
}

int main() {
    setupConsole();
    clearScreen();

    string name;
    string birthday;
    string gender;
    string focus;

    printTitle();
    cout << "请输入你的姓名：";
    getline(cin, name);

    cout << "请输入生日，例如 2005-08-16：";
    getline(cin, birthday);

    cout << "请输入性别或称呼（男/女/其他，可直接回车跳过）：";
    getline(cin, gender);

    cout << "你现在最关心什么？（学习/工作/感情/财运/健康/综合）：";
    getline(cin, focus);

    name = emptyToDefault(trimSpaces(name), "有缘人");
    birthday = emptyToDefault(trimSpaces(birthday), "未填写");
    gender = emptyToDefault(trimSpaces(gender), "未填写");
    focus = emptyToDefault(trimSpaces(focus), "综合");

    mt19937 rng(makeSeed(name, birthday, gender, focus));

    vector<string> keywords = {
        "慢慢来", "先稳住", "有转机", "贵人近", "适合整理", "少想多做",
        "心态放松", "先做小事", "别急着决定", "把话说清楚", "适合开始",
        "适合收尾", "注意休息", "顺其自然", "小心冲动"
    };

    vector<string> personality = {
        "你今天的状态比较敏感，容易注意到别人忽略的小细节。",
        "你今天适合把事情一件件理清楚，越急越容易乱。",
        "你今天的行动力还不错，只要开始做，就会比想象中顺。",
        "你今天容易被情绪影响判断，先缓一缓再做决定会更稳。",
        "你今天适合主动一点，很多事情不会自己变好，但你一动就有变化。",
        "你今天需要给自己一点空间，不必每件事都立刻给答案。"
    };

    vector<string> studyWork = {
        "学习或工作上适合先处理简单明确的任务，完成感会带动后面的效率。",
        "今天容易遇到临时变化，提前留一点余地会比较安心。",
        "适合复盘、整理资料、补漏洞，不一定要追求一下子突破。",
        "如果有沟通任务，建议把重点写下来，避免说着说着跑偏。",
        "今天适合推进已经开始的事，新开太多坑反而会分散精力。",
        "遇到难题时先换个角度，不要一直硬顶。"
    };

    vector<string> money = {
        "财运整体平稳，适合记账，不太适合冲动消费。",
        "今天可能有小额支出，买之前多想十分钟会省下一点钱。",
        "适合处理和钱有关的小事，比如预算、账单、退款、报销。",
        "偏财运普通，不建议靠运气做决定。",
        "容易被好看的东西吸引，付款前先问问自己是不是真的需要。",
        "今天适合守财，少一点冲动，多一点安全感。"
    };

    vector<string> relationship = {
        "感情和人际上，今天适合把话说清楚，别让对方猜太久。",
        "你今天容易多想，对方一个小动作不一定有特别含义。",
        "适合主动问候重要的人，简单一句话就能拉近距离。",
        "人际关系整体平和，但别为了照顾别人一直委屈自己。",
        "如果有误会，今天适合轻轻解释，不适合硬碰硬。",
        "桃花不一定明显，但温柔和耐心会给你加分。"
    };

    vector<string> health = {
        "身体状态提醒你别熬太晚，睡眠比硬撑更重要。",
        "今天适合多喝水、少久坐，给身体一点缓冲。",
        "情绪会影响体力，别把自己逼得太紧。",
        "注意肩颈、眼睛和胃口，别一直盯着屏幕。",
        "适合散步或做一点轻运动，不用追求强度。",
        "如果觉得累，就先休息，休息不是浪费时间。"
    };

    vector<string> directions = {
        "东方", "南方", "西方", "北方", "东南方", "西南方", "东北方", "西北方",
        "离你最近的窗边", "你常去但最近没去的地方"
    };

    vector<string> colors = {
        "米白色", "浅蓝色", "墨绿色", "暖黄色", "淡紫色", "灰蓝色",
        "奶茶色", "银灰色", "浅粉色", "深咖色"
    };

    vector<string> goodThings = {
        "整理房间", "早点出门", "主动沟通", "写计划", "复盘旧事",
        "喝温水", "做小决定", "完成一件拖了很久的小事",
        "给自己留十分钟安静时间", "把重要信息记下来"
    };

    vector<string> badThings = {
        "冲动消费", "熬夜硬撑", "情绪化回复消息", "一口气安排太多事",
        "临时改大计划", "和人较真到底", "空腹喝冰饮", "把小问题想得太严重",
        "没有确认就答应别人", "边焦虑边拖延"
    };

    vector<string> advice = {
        "今天不用一下子变得很厉害，能比昨天稳一点就已经很好。",
        "先把眼前的小事做好，运气往往藏在你开始行动之后。",
        "别急着证明自己，真正适合你的节奏会慢慢出现。",
        "如果心里乱，就先把事情写下来，写清楚之后就没那么吓人。",
        "今天的关键词是稳，不求惊喜，但求少一点内耗。",
        "对自己温柔一点，你不是没进步，只是还在路上。"
    };

    clearScreen();
    printTitle();
    loadingLine("正在摇签");
    loadingLine("正在排盘");
    loadingLine("正在解读今日气场");
    progressBar("正在整理你的日常运势");
    sleepMs(300);

    int totalScore = randomInt(rng, 35, 98);
    int luckyNumber = randomInt(rng, 1, 99);
    string keyword1 = pick(rng, keywords);
    string keyword2 = pick(rng, keywords);
    if (keyword2 == keyword1) {
        keyword2 = pick(rng, keywords);
    }

    clearScreen();
    printTitle();
    printLine("姓名：" + name);
    printLine("生日：" + birthday);
    printLine("称呼：" + gender);
    printLine("关注：" + focus);

    printSection("今日总览");
    printLine("总运势：" + to_string(totalScore) + "/100（" + scoreLevel(totalScore) + "）");
    printLine("今日关键词：" + keyword1 + " / " + keyword2);
    printLine("幸运数字：" + to_string(luckyNumber));
    printLine("幸运颜色：" + pick(rng, colors));
    printLine("贵人方向：" + pick(rng, directions));

    printSection("状态简析");
    printLine(pick(rng, personality));

    printSection("学业 / 事业");
    printLine(pick(rng, studyWork));

    printSection("财运");
    printLine(pick(rng, money));

    printSection("感情 / 人际");
    printLine(pick(rng, relationship));

    printSection("健康 / 状态");
    printLine(pick(rng, health));

    printSection("今日宜忌");
    printLine("宜：" + pick(rng, goodThings));
    printLine("忌：" + pick(rng, badThings));

    printSection("一句提醒");
    printLine(pick(rng, advice));

    printLine();
    printLine("+--------------------------------------+");
    printLine("|  结果仅供娱乐，真正的好运来自行动。  |");
    printLine("+--------------------------------------+");

    return 0;
}
