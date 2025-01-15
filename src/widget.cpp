#include <uva/widgets/widget.hpp>

#include <uva/xml.hpp>

uva::widgets::widget::widget(int x, int y, int w, int h, uva::widgets::widget_style style)
    : x(x), y(y), w(w), h(h), style(style)
{

}

void uva::widgets::widget::parse(uva::drawing::basic_renderer& renderer, uva::xml::schema& schema, uva::xml& xml) {
    style.background_color = schema.color_attribute(xml, "background-color");

    style.flex = atoi(xml.attribute("flex", "0").data());
    style.padding = atoi(xml.attribute("padding", "0").data());
    style.gap = atoi(xml.attribute("gap", "0").data());
    style.border_radius = atoi(xml.attribute("border-radius", "0").data());

    id = xml.attribute("id", "");
}

void uva::widgets::widget::render(uva::drawing::basic_renderer& drawing) {
    drawing.fill_rect({x, y, w, h}, style.background_color);
}