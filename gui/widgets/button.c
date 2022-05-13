#include <gui/widgets/button.h>

button_t *new_button(char *text)
{
    button_t *button = malloc(sizeof(struct Button));

    button->text = text;
    button->is_clicked = false;
    button->widget.bounds.w = strlen(text) * 8 + 4 * DEFAULT_PADDING;
    button->widget.bounds.h = 16 + 2 * DEFAULT_PADDING;
    button->widget.on_draw = (widget_draw_t) button_on_draw;
    button->widget.on_click = (widget_clicked_t) button_on_click;
    button->widget.on_mouse_release = (widget_mouse_released_t) button_on_release;

    return button;
}

void button_on_draw(button_t *button, fb_t fb)
{

}

void button_set_on_click(button_t *button, void (*callback)(button_t*))
{

}

void button_set_text(button_t *button, const char *text)
{

}
