#include <andy/widgets/widget.hpp>

#include <andy/xml.hpp>

andy::widgets::widget::widget(int x, int y, int w, int h, andy::widgets::widget_style style)
    : x(x), y(y), w(w), h(h), style(style)
{

}

void andy::widgets::widget::parse(void* target, andy::xml::schema& schema, andy::xml& xml) {
    style.background_color = schema.color_attribute(xml, "background-color");

    style.flex = atoi(xml.attribute("flex", "0").data());
    style.padding = atoi(xml.attribute("padding", "0").data());
    style.gap = atoi(xml.attribute("gap", "0").data());
    style.border_radius = atoi(xml.attribute("border-radius", "0").data());

    id = xml.attribute("id", "");
}

void andy::widgets::widget::render(void* target) {

}