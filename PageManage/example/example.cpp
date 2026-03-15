#include "Page.h"          // 头文件引入
#include "components.h"  

bool button_source;
bool trigger_source;
uint16_t encoder_source;
uint32_t joystick_source;

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
PAGE_MANEGE page_manege;
COMPONENTS components;

void tft_init(void)
{
    tft.init();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 0, 240, 10, TFT_GREY);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Adding a background colour erases previous text automatically
}

void page_manege_init(void)
{
    components.create_component("button", BUTTON_COMPONENT(&tft, &button_source, 20, 90));
    BUTTON_COMPONENT* button = components.get_component<BUTTON_COMPONENT>("button");
    page_manege.create_page("button", [](void* ctx) { static_cast<BUTTON_COMPONENT*>(ctx)->show_static(ctx); }, button, [](void* ctx) { static_cast<BUTTON_COMPONENT*>(ctx)->show_dynamic(ctx); }, button);

    components.create_component("trigger", TRIGGER_COMPONENT(&tft, &trigger_source, 10, 120));
    TRIGGER_COMPONENT* trigger = components.get_component<TRIGGER_COMPONENT>("trigger");
    page_manege.create_page("trigger", [](void* ctx) { static_cast<TRIGGER_COMPONENT*>(ctx)->show_static(ctx); }, trigger, [](void* ctx) { static_cast<TRIGGER_COMPONENT*>(ctx)->show_dynamic(ctx); }, trigger);

    components.create_component("encoder", ENCODER_COMPONENT(&tft, &encoder_source, 98, 140));
    ENCODER_COMPONENT* encoder = components.get_component<ENCODER_COMPONENT>("encoder");
    page_manege.create_page("encoder", [](void* ctx) { static_cast<ENCODER_COMPONENT*>(ctx)->show_static(ctx); }, encoder, [](void* ctx) { static_cast<ENCODER_COMPONENT*>(ctx)->show_dynamic(ctx); }, encoder);

    components.create_component("joystick", JOYSTICK_COMPONENT(&tft, &joystick_source, 65, 215));
    JOYSTICK_COMPONENT* joystick = components.get_component<JOYSTICK_COMPONENT>("joystick");
    page_manege.create_page("joystick", [](void* ctx) { static_cast<JOYSTICK_COMPONENT*>(ctx)->show_static(ctx); }, joystick, [](void* ctx) { static_cast<JOYSTICK_COMPONENT*>(ctx)->show_dynamic(ctx); }, joystick);
}

void main(void)
{
    tft_init();
    page_manege_init();

    while(1)
    {
        page_manege.show_page("button");        // 使用string名称监听控制输出
        page_manege.show_page("trigger");
        page_manege.show_page("encoder");
        page_manege.show_page("joystick");
    }
}





