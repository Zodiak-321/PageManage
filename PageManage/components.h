#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include <TFT_eSPI.h>

#include <map>
#include <variant>

#define COMPONENT_BLACK       0x0000      /*   0,   0,   0 */
#define COMPONENT_NAVY        0x000F      /*   0,   0, 128 */
#define COMPONENT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define COMPONENT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define COMPONENT_MAROON      0x7800      /* 128,   0,   0 */
#define COMPONENT_PURPLE      0x780F      /* 128,   0, 128 */
#define COMPONENT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define COMPONENT_LIGHTGREY   0xD69A      /* 211, 211, 211 */
#define COMPONENT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define COMPONENT_BLUE        0x001F      /*   0,   0, 255 */
#define COMPONENT_GREEN       0x07E0      /*   0, 255,   0 */
#define COMPONENT_CYAN        0x07FF      /*   0, 255, 255 */
#define COMPONENT_RED         0xF800      /* 255,   0,   0 */
#define COMPONENT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define COMPONENT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define COMPONENT_WHITE       0xFFFF      /* 255, 255, 255 */
#define COMPONENT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define COMPONENT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define COMPONENT_PINK        0xFE19      /* 255, 192, 203 */ //Lighter pink, was 0xFC9F
#define COMPONENT_BROWN       0x9A60      /* 150,  75,   0 */
#define COMPONENT_GOLD        0xFEA0      /* 255, 215,   0 */
#define COMPONENT_SILVER      0xC618      /* 192, 192, 192 */
#define COMPONENT_SKYBLUE     0x867D      /* 135, 206, 235 */
#define COMPONENT_VIOLET      0x915C      /* 180,  46, 226 */


typedef struct
{
    TFT_eSPI* tft;
    void* source;

    uint16_t x;
    uint16_t y;
    float size;
}Component_Base_Info;

class BUTTON_COMPONENT;
class TRIGGER_COMPONENT;
class JOYSTICK_COMPONENT;
class ENCODER_COMPONENT;

using ComponentVariant = std::variant<BUTTON_COMPONENT, TRIGGER_COMPONENT, JOYSTICK_COMPONENT, ENCODER_COMPONENT>;

class BUTTON_COMPONENT
{
    public:
        BUTTON_COMPONENT(TFT_eSPI* tft, void* source, uint16_t x, uint16_t y, float size = 1, uint16_t base_color = COMPONENT_DARKGREY, uint16_t press_color = COMPONENT_GREEN, uint16_t unPress_color = COMPONENT_RED, uint16_t back_color = COMPONENT_BLACK);

        void show_static(void* context);
        void show_dynamic(void* context);

    private:
        Component_Base_Info _info;

        uint16_t _base_color;
        uint16_t _press_color;
        uint16_t _unPress_color;
        uint16_t _back_color;
};

class TRIGGER_COMPONENT
{
    public:
        TRIGGER_COMPONENT(TFT_eSPI* tft, void* source, uint16_t x, uint16_t y, float size = 1, uint16_t base_color = COMPONENT_DARKGREY, uint16_t press_color = COMPONENT_WHITE, uint16_t unPress_color = COMPONENT_BLACK);

        void show_static(void* context);
        void show_dynamic(void* context);

    private:
        Component_Base_Info _info;

        uint16_t _base_color;
        uint16_t _press_color;
        uint16_t _unPress_color;
};

class JOYSTICK_COMPONENT
{
    public:
        JOYSTICK_COMPONENT(TFT_eSPI* tft, void* source, uint16_t x, uint16_t y, float size = 1, uint16_t base_color = COMPONENT_DARKGREY, uint16_t joystick_color = COMPONENT_WHITE);

        void show_static(void* context);
        void show_dynamic(void* context);

    private:
        Component_Base_Info _info;

        uint16_t _base_color;
        uint16_t _joystick_color;
};

class ENCODER_COMPONENT
{
    public:
        ENCODER_COMPONENT(TFT_eSPI* tft, void* source, uint16_t x, uint16_t y, float size = 1, uint16_t base_color = COMPONENT_DARKGREY, uint16_t back_color = COMPONENT_BLACK, uint16_t encoder_color = COMPONENT_WHITE, uint16_t line_color = COMPONENT_CYAN, uint16_t point_color = COMPONENT_RED, uint16_t leftArrow_color = COMPONENT_YELLOW, uint16_t rightArrow_color = COMPONENT_GREEN);

        void show_static(void* context);
        void show_dynamic(void* context);
        
    private:
        Component_Base_Info _info;

        int16_t _last_encoder;

        uint16_t _base_color;
        uint16_t _back_color;
        uint16_t _encoder_color;
        uint16_t _line_color;
        uint16_t _point_color;
        uint16_t _leftArrow_color;
        uint16_t _rightArrow_color;
};

class COMPONENTS
{
    public:

        COMPONENTS(void){}

        template<typename T>
        bool create_component(std::string name, T&& component)
        {
            return _components.try_emplace(name, std::forward<T>(component)).second;
        }

        template<typename T, typename... Args>
        bool create_component(std::string name, Args&&... args)
        {
            return _components.try_emplace(name, std::in_place_type<T>, std::forward<Args>(args)...).second;
        }

        bool delete_component(std::string name)
        {
            if(_components.find(name) == _components.end()) return false;
            _components.erase(name);
            return true;
        }

        template<typename T>
        T* get_component(std::string name)
        {
            auto it = _components.find(name);
            if (it == _components.end()) return nullptr;
            return std::get_if<T>(&it->second);
        }

    private:
        std::map<std::string , ComponentVariant>_components;
};


#endif

