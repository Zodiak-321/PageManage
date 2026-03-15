#include "components.h"

/*================================================-BUTTON BEGIN-================================================*/

BUTTON_COMPONENT::BUTTON_COMPONENT(TFT_eSPI* tft, void* source, uint16_t x, uint16_t y, float size, uint16_t base_color, uint16_t press_color, uint16_t unPress_color, uint16_t back_color)
{
    _base_color = base_color;
    _press_color = press_color;
    _unPress_color = unPress_color;
    _back_color = back_color;

    _info.tft = tft;
    _info.source = source;
    _info.x = x;
    _info.y = y;
    _info.size = size;
}

void BUTTON_COMPONENT::show_static(void* context)
{
    uint16_t w = 10 * _info.size;
    uint16_t h = 10 * _info.size;
    uint16_t base_w = 20 * _info.size;
    uint16_t base_h = 10 * _info.size;

    uint16_t top_x = (base_w - w) / 2 + _info.x;
    uint16_t top_y = _info.y;
    uint16_t base_x = _info.x;
    uint16_t base_y = h + _info.y;

    _info.tft->fillRect(top_x, top_y, w, h, _unPress_color);
    _info.tft->fillRect(base_x, base_y, base_w, base_h, _base_color);
}

void BUTTON_COMPONENT::show_dynamic(void* context)
{
    uint16_t w = 10 * _info.size;
    uint16_t h = 10 * _info.size;
    uint16_t base_w = 20 * _info.size;

    uint16_t top_x = (base_w - w) / 2 + _info.x;
    uint16_t top_y = _info.y;

    bool* is_press = static_cast<bool*>(_info.source);

    if(*is_press == true)
    {
        _info.tft->fillRect(top_x, top_y, w, h / 2, _back_color);
        _info.tft->fillRect(top_x, top_y + h / 2, w, h / 2, _press_color);
    }
    else
        _info.tft->fillRect(top_x, top_y, w, h, _unPress_color);
}

/*=================================================-BUTTON END-=================================================*/

/*================================================-TRIGGER BEGIN-================================================*/

TRIGGER_COMPONENT::TRIGGER_COMPONENT(TFT_eSPI* tft, void* source, uint16_t x, uint16_t y, float size, uint16_t base_color, uint16_t press_color, uint16_t unPress_color)
{
    _base_color = base_color;
    _press_color = press_color;
    _unPress_color = unPress_color;

    _info.tft = tft;
    _info.source = source;
    _info.x = x;
    _info.y = y;
    _info.size = size;
}

void TRIGGER_COMPONENT::show_static(void* context)
{
    uint16_t w = 21 * _info.size;
    uint16_t h = 17 * _info.size;
    uint16_t base_w = 25 * _info.size;
    uint16_t base_h = 40 * _info.size;

    uint16_t top_x = (base_w - w) / 2 + _info.x;
    uint16_t top_y = base_h / 2 - h + _info.y;
    uint16_t but_y = top_y + h;
    uint16_t base_x = _info.x;
    uint16_t base_y = _info.y;

    _info.tft->fillRect(_info.x, _info.y, base_w, base_h, _base_color);
    _info.tft->fillRect(top_x, top_y, w, h, _press_color);
    _info.tft->fillRect(top_x, but_y, w, h, _unPress_color);
}

void TRIGGER_COMPONENT::show_dynamic(void* context)
{
    uint16_t w = 21 * _info.size;
    uint16_t h = 17 * _info.size;
    uint16_t base_w = 25 * _info.size;
    uint16_t base_h = 40 * _info.size;

    uint16_t top_x = (base_w - w) / 2 + _info.x;
    uint16_t top_y = base_h / 2 - h + _info.y;
    uint16_t but_y = top_y + h;

    bool* is_press = static_cast<bool*>(_info.source);

    if(*is_press == true)
    {
        _info.tft->fillRect(top_x, top_y, w, h, _press_color);
        _info.tft->fillRect(top_x, but_y, w, h, _unPress_color);
    }
    else
    {
        _info.tft->fillRect(top_x, top_y, w, h, _unPress_color);
        _info.tft->fillRect(top_x, but_y, w, h, _press_color);
    }
}

/*=================================================-TRIGGER END-=================================================*/

/*===============================================-JOYSTICK BEGIN-===============================================*/

JOYSTICK_COMPONENT::JOYSTICK_COMPONENT(TFT_eSPI* tft, void* source, uint16_t x, uint16_t y, float size, uint16_t base_color, uint16_t joystick_color)
{
    _base_color = base_color;
    _joystick_color = joystick_color;

    _info.tft = tft;
    _info.source = source;
    _info.x = x;
    _info.y = y;
    _info.size = size;
}

void JOYSTICK_COMPONENT::show_static(void* context)
{
    uint16_t r = 15 * _info.size;
    uint16_t base_r = 45 * _info.size;

    _info.tft->fillCircle(_info.x, _info.y, base_r, _base_color); 
    _info.tft->fillCircle(_info.x, _info.y, r, _joystick_color);
}

void JOYSTICK_COMPONENT::show_dynamic(void* context)
{
    uint32_t* joystick = static_cast<uint32_t*>(context);

    uint16_t joystick_v = (uint16_t)(((*joystick) & 0xFFFF0000) >> 16);
    uint16_t joystick_h = (uint16_t)((*joystick) | 0x0000FFFF);
}

/*================================================-JOYSTICK END-================================================*/

/*================================================-ENCODER BEGIN-================================================*/

ENCODER_COMPONENT::ENCODER_COMPONENT(TFT_eSPI* tft, void* source, uint16_t x, uint16_t y, float size, uint16_t base_color, uint16_t back_color, uint16_t encoder_color, uint16_t line_color, uint16_t point_color, uint16_t leftArrow_color, uint16_t rightArrow_color)
{
    _base_color = base_color;
    _back_color = back_color;
    _encoder_color = encoder_color;
    _line_color = line_color;
    _point_color = point_color;
    _leftArrow_color = leftArrow_color;
    _rightArrow_color = rightArrow_color;

    _info.tft = tft;
    _info.source = source;
    _info.x = x;
    _info.y = y;
    _info.size = size;
}

void ENCODER_COMPONENT::show_static(void* context)
{
    uint16_t r = 13 * _info.size;
    uint16_t base_r = 15 * _info.size;
    float line_len_half = (base_r - r) * 5 / 6;

    float line_start_y = _info.y - line_len_half;
    float line_end_y = _info.y + line_len_half;

    _info.tft->fillCircle(_info.x, _info.y, base_r, _base_color);
    _info.tft->fillCircle(_info.x, _info.y, r, _encoder_color);
    _info.tft->drawLine(_info.x, (uint16_t)line_start_y, _info.x, (uint16_t)line_end_y, _line_color);
    _info.tft->drawPixel(_info.x, (uint16_t)line_start_y, _point_color);
}

void ENCODER_COMPONENT::show_dynamic(void* context)
{
    uint16_t r = 13 * _info.size;
    uint16_t base_r = 15 * _info.size;
    float line_len_half = base_r - r * 5 / 6;
    float line_len = 2 * line_len_half - 2;

    uint16_t gap = 2 * _info.size;
    float t_w = 2 * r / 4;
    float t_h = t_w * 2 / 1.717f;
    float w = 2 * r - t_w;
    float h = t_h * 5 / 6.0f;
    
    uint16_t x = _info.x - r;
    float y = _info.y - gap - base_r - h;
    float t1_x = x + w;
    float t1_y = y - (t_h - h) / 2;
    float t2_x = t1_x;
    float t2_y = y + (t_h - h) / 2;
    float t3_x = x + w + t_w;
    float t3_y = y + h / 2;
    uint16_t base_x = x;
    float base_y = t1_y;
    float base_w = t3_x - x;
    float base_h = t_h;

    int16_t* encoder = static_cast<int16_t*>(_info.source);

    _info.tft->fillRect(base_x, base_y, base_w, base_h, _back_color);
    if(*encoder - _last_encoder < 0) {  _info.tft->fillRect(x, (uint16_t)y, (uint16_t)w, (uint16_t)h, _leftArrow_color); _info.tft->fillTriangle((uint16_t)t1_x, (uint16_t)t1_y, (uint16_t)t2_x, (uint16_t)t2_y, (uint16_t)t3_x, (uint16_t)t3_y, _leftArrow_color); }
    else if(*encoder - _last_encoder > 0) { _info.tft->fillRect(x + (uint16_t)t_w, (uint16_t)y, (uint16_t)w, (uint16_t)h, _rightArrow_color); _info.tft->fillTriangle(_info.x * 2 - (uint16_t)t1_x, (uint16_t)t1_y, _info.x * 2 - (uint16_t)t2_x, (uint16_t)t2_y, _info.x * 2 - (uint16_t)t3_x, (uint16_t)t3_y, _rightArrow_color); }
    _last_encoder = *encoder;

    uint16_t encoder_circle = 20;

    float theta = *encoder % encoder_circle * (360 / encoder_circle) * PI / 180.0f;
    _info.tft->fillCircle(_info.x, _info.y, r, TFT_WHITE);
    _info.tft->drawLine((uint16_t)(_info.x + line_len * sin(theta)), (uint16_t)(_info.y + line_len * cos(theta)), (uint16_t)(_info.x - line_len * sin(theta)), (uint16_t)(_info.y - line_len * cos(theta)), TFT_DARKCYAN);
    _info.tft->drawPixel((uint16_t)(_info.x + line_len * sin(theta)), (uint16_t)(_info.y + line_len * cos(theta)), TFT_RED);
}

/*=================================================-ENCODER END-=================================================*/
