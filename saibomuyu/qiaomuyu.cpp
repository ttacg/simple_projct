#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <cmath>
#include <cstdlib>
#include <string>

int winW = 900;
int winH = 600;

HDC g_hdc = nullptr;
HGLRC g_glrc = nullptr;
HWND g_hwnd = nullptr;

GLuint frameTex[3] = {};
int currentFrame = 0;

int merit = 0;
bool hitting = false;
int animationTick = 0;
bool effectActive = false;
int effectTick = 0;
bool effectTriggered = false;
bool spaceDown = false;

const int animationFrames[] = { 0, 1, 2, 1, 0 };
const int animationFrameCount = sizeof(animationFrames) / sizeof(animationFrames[0]);
const int ticksPerFrame = 2;
const int flashDuration = 16;
const int floatingTextDuration = 42;

void useExeDirectory()
{
    wchar_t exePath[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);

    wchar_t* lastSlash = wcsrchr(exePath, L'\\');
    if (lastSlash)
    {
        *lastSlash = L'\0';
        SetCurrentDirectoryW(exePath);
    }
}

GLuint loadPNG(const char* path)
{
    int w = 0;
    int h = 0;
    int channels = 0;
    stbi_set_flip_vertically_on_load(true);
    std::string actualPath = path;
    unsigned char* data = stbi_load(actualPath.c_str(), &w, &h, &channels, 4);

    if (!data)
    {
        actualPath = std::string("../saibomuyu/") + path;
        data = stbi_load(actualPath.c_str(), &w, &h, &channels, 4);
    }

    if (!data)
    {
        std::wstring msg = L"PNG \u52a0\u8f7d\u5931\u8d25: ";
        int len = MultiByteToWideChar(CP_UTF8, 0, actualPath.c_str(), -1, nullptr, 0);
        if (len > 0)
        {
            std::wstring widePath(len, L'\0');
            MultiByteToWideChar(CP_UTF8, 0, actualPath.c_str(), -1, widePath.data(), len);
            msg += widePath.c_str();
        }
        else
        {
            msg += L"(\u672a\u77e5\u8def\u5f84)";
        }

        MessageBoxW(g_hwnd, msg.c_str(), L"\u8d44\u6e90\u9519\u8bef", MB_ICONWARNING);
        return 0;
    }

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        w,
        h,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    stbi_image_free(data);
    return tex;
}

void drawText(float x, float y, const wchar_t* text)
{
    HFONT font = CreateFontW(
        26, 0, 0, 0, FW_BOLD,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        L"\u5fae\u8f6f\u96c5\u9ed1"
    );

    HFONT oldFont = (HFONT)SelectObject(g_hdc, font);
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != L'\0'; i++)
    {
        GLuint list = glGenLists(1);
        wglUseFontBitmapsW(g_hdc, text[i], 1, list);
        glCallList(list);
        glDeleteLists(list, 1);
    }

    SelectObject(g_hdc, oldFont);
    DeleteObject(font);
}

void drawTexture(GLuint tex, float x, float y, float w, float h)
{
    if (!tex) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(x, y);
    glTexCoord2f(1, 0); glVertex2f(x + w, y);
    glTexCoord2f(1, 1); glVertex2f(x + w, y + h);
    glTexCoord2f(0, 1); glVertex2f(x, y + h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawFlash(float x, float y)
{
    if (!effectActive || effectTick >= flashDuration) return;

    float t = (float)effectTick / (float)flashDuration;
    float alpha = 1.0f - t;
    float innerRadius = 12.0f + t * 22.0f;
    float outerRadius = 32.0f + t * 55.0f;

    glDisable(GL_TEXTURE_2D);

    glColor4f(1.0f, 0.80f, 0.12f, 0.22f * alpha);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 40; i++)
    {
        float a = i * 2.0f * 3.1415926f / 40.0f;
        glVertex2f(x + cos(a) * outerRadius, y + sin(a) * outerRadius);
    }
    glEnd();

    glColor4f(1.0f, 0.92f, 0.25f, 0.85f * alpha);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 40; i++)
    {
        float a = i * 2.0f * 3.1415926f / 40.0f;
        glVertex2f(x + cos(a) * innerRadius, y + sin(a) * innerRadius);
    }
    glEnd();

    glColor4f(1.0f, 0.86f, 0.10f, 0.95f * alpha);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 10; i++)
    {
        float a = i * 2.0f * 3.1415926f / 10.0f;
        float r1 = 22.0f + t * 18.0f;
        float r2 = 55.0f + t * 55.0f;
        glVertex2f(x + cos(a) * r1, y + sin(a) * r1);
        glVertex2f(x + cos(a) * r2, y + sin(a) * r2);
    }
    glEnd();
}

void drawFloatingText(float x, float y)
{
    if (!effectActive || effectTick >= floatingTextDuration) return;

    float t = (float)effectTick / (float)floatingTextDuration;
    float alpha = 1.0f - t;
    float offsetY = t * 58.0f;

    glColor4f(1.0f, 0.72f, 0.08f, alpha);
    drawText(x, y + offsetY, L"\u529f\u5fb7 +1");
}

void playHitSound()
{
    const wchar_t* soundPath = L"assets\\muyu.wav";
    const wchar_t* fallbackPath = L"..\\saibomuyu\\assets\\muyu.wav";

    if (GetFileAttributesW(soundPath) != INVALID_FILE_ATTRIBUTES)
    {
        PlaySoundW(soundPath, nullptr, SND_FILENAME | SND_ASYNC);
    }
    else if (GetFileAttributesW(fallbackPath) != INVALID_FILE_ATTRIBUTES)
    {
        PlaySoundW(fallbackPath, nullptr, SND_FILENAME | SND_ASYNC);
    }
}

void triggerHitEffect()
{
    effectActive = true;
    effectTick = 0;
    effectTriggered = true;
    playHitSound();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.92f, 0.85f, 0.68f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f((float)winW, 0);
    glVertex2f((float)winW, (float)winH);
    glVertex2f(0, (float)winH);
    glEnd();

    glColor3f(0.25f, 0.12f, 0.05f);
    drawText(390, 525, L"\u7535\u5b50\u6728\u9c7c");

    std::wstring meritText = L"\u529f\u5fb7 + " + std::to_wstring(merit);
    drawText(390, 490, meritText.c_str());

    const float frameW = 226.0f;
    const float frameH = 320.0f;
    const float frameX = (winW - frameW) / 2.0f;
    const float frameY = 115.0f;
    drawTexture(frameTex[currentFrame], frameX, frameY, frameW, frameH);
    const float hitX = frameX + frameW * 0.74f;
    const float hitY = frameY + frameH * 0.36f;
    drawFlash(hitX, hitY);
    drawFloatingText(hitX - 20.0f, hitY + 28.0f);

    glColor3f(0.25f, 0.12f, 0.05f);
    drawText(290, 55, L"\u70b9\u51fb / \u7a7a\u683c: \u6572\u6728\u9c7c    ESC: \u9000\u51fa");

    SwapBuffers(g_hdc);
}

void triggerHit()
{
    if (hitting) return;

    merit++;
    hitting = true;
    animationTick = 0;
    currentFrame = animationFrames[0];
    effectTriggered = false;
    InvalidateRect(g_hwnd, nullptr, FALSE);
}

void update()
{
    if (hitting)
    {
        animationTick++;
        int sequenceIndex = animationTick / ticksPerFrame;

        if (sequenceIndex >= animationFrameCount)
        {
            hitting = false;
            animationTick = 0;
            currentFrame = 0;
        }
        else
        {
            currentFrame = animationFrames[sequenceIndex];
            if (currentFrame == 2 && !effectTriggered)
            {
                triggerHitEffect();
            }
        }
    }

    if (effectActive)
    {
        effectTick++;
        if (effectTick >= floatingTextDuration)
        {
            effectActive = false;
            effectTick = 0;
        }
    }

    InvalidateRect(g_hwnd, nullptr, FALSE);
}

void reshape(int w, int h)
{
    winW = w;
    winH = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);

    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    glClearColor(0.92f, 0.85f, 0.68f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    frameTex[0] = loadPNG("assets/1.png");
    frameTex[1] = loadPNG("assets/2.png");
    frameTex[2] = loadPNG("assets/3.png");
}

bool createOpenGLContext(HWND hwnd)
{
    g_hdc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ChoosePixelFormat(g_hdc, &pfd);
    if (pixelFormat == 0) return false;
    if (!SetPixelFormat(g_hdc, pixelFormat, &pfd)) return false;

    g_glrc = wglCreateContext(g_hdc);
    if (!g_glrc) return false;
    if (!wglMakeCurrent(g_hdc, g_glrc)) return false;

    init();
    return true;
}

void cleanupOpenGL()
{
    for (int i = 0; i < 3; i++)
    {
        if (frameTex[i]) glDeleteTextures(1, &frameTex[i]);
    }

    if (g_glrc)
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(g_glrc);
        g_glrc = nullptr;
    }

    if (g_hwnd && g_hdc)
    {
        ReleaseDC(g_hwnd, g_hdc);
        g_hdc = nullptr;
    }
}

LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        g_hwnd = hwnd;
        if (!createOpenGLContext(hwnd))
        {
            MessageBoxW(hwnd, L"OpenGL \u521d\u59cb\u5316\u5931\u8d25", L"\u9519\u8bef", MB_ICONERROR);
            return -1;
        }
        SetTimer(hwnd, 1, 16, nullptr);
        return 0;

    case WM_SIZE:
        reshape(LOWORD(lParam), HIWORD(lParam));
        return 0;

    case WM_TIMER:
        update();
        return 0;

    case WM_LBUTTONDOWN:
        triggerHit();
        return 0;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
        {
            DestroyWindow(hwnd);
        }
        else if (wParam == VK_SPACE && !spaceDown)
        {
            spaceDown = true;
            triggerHit();
        }
        return 0;

    case WM_KEYUP:
        if (wParam == VK_SPACE)
        {
            spaceDown = false;
        }
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        display();
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        KillTimer(hwnd, 1);
        cleanupOpenGL();
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int main()
{
    useExeDirectory();

    HINSTANCE instance = GetModuleHandleW(nullptr);

    WNDCLASSW wc = {};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = windowProc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = L"QiaoMuYuPngWindow";

    if (!RegisterClassW(&wc))
    {
        MessageBoxW(nullptr, L"\u7a97\u53e3\u7c7b\u6ce8\u518c\u5931\u8d25", L"\u9519\u8bef", MB_ICONERROR);
        return 1;
    }

    HWND hwnd = CreateWindowExW(
        0,
        wc.lpszClassName,
        L"\u7535\u5b50\u6728\u9c7c PNG\u7248",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        winW, winH,
        nullptr,
        nullptr,
        instance,
        nullptr
    );

    if (!hwnd)
    {
        MessageBoxW(nullptr, L"\u7a97\u53e3\u521b\u5efa\u5931\u8d25", L"\u9519\u8bef", MB_ICONERROR);
        return 1;
    }

    MSG msg = {};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}
